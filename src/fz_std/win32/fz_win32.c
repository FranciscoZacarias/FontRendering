internal void application_stop() {
  IsApplicationRunning = false;
  PostQuitMessage(0);
}

internal void* memory_reserve(u64 size) {
  void* result = VirtualAlloc(0, size, MEM_RESERVE, PAGE_NOACCESS);
  return result;
}

internal b32 memory_commit(void* memory, u64 size) {
  b32 result = (VirtualAlloc(memory, size, MEM_COMMIT, PAGE_READWRITE) != 0);
  return result;
}

internal void  memory_decommit(void* memory, u64 size) {
  VirtualFree(memory, size, MEM_DECOMMIT);
}

internal void  memory_release(void* memory, u64 size) {
  VirtualFree(memory, size, MEM_RELEASE);
}

internal u64 memory_get_page_size() {
  SYSTEM_INFO sysinfo = {0};
  GetSystemInfo(&sysinfo);
  return(sysinfo.dwPageSize);
}

//~ File handling
internal HANDLE _win32_get_file_handle_read(String8 file_path) {
  HANDLE file_handle = CreateFileA(file_path.str, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  if (file_handle == INVALID_HANDLE_VALUE) {
    DWORD error = GetLastError();
    printf("Error: Failed to open file %s. Error: %lu\n", file_path.str, error);
    return NULL;
  }
  return file_handle;
}

internal HANDLE _win32_get_file_handle_write(String8 file_path) {
  HANDLE file_handle = CreateFileA(file_path.str, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  if (file_handle == INVALID_HANDLE_VALUE) {
    DWORD error = GetLastError();
    printf("Error: Failed to open file %s. Error: %lu\n", file_path.str, error);
    return NULL;
  }
  return file_handle;
}

internal b32 file_create(String8 file_path) {
  b32 result  = 0;
  HANDLE file = CreateFileA(file_path.str, GENERIC_READ, 0, 0, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0);
  DWORD error = GetLastError();  
  if (error == ERROR_SUCCESS || error == ERROR_FILE_EXISTS) {
    result = 1;
  } else {
    // TODO(fz): We should send this error to user space
    printf("Error creating file %s with error: %lu\n", file_path.str, error);
  }
  CloseHandle(file);
  return result;
}

internal u64 file_get_last_modified_time(String8 file_path) {
  u32 result = 0;
  WIN32_FILE_ATTRIBUTE_DATA file_attribute_data;
  if (GetFileAttributesExA(file_path.str, GetFileExInfoStandard, &file_attribute_data)) {
    FILETIME last_write_time = file_attribute_data.ftLastWriteTime;
    result = (((u64)last_write_time.dwHighDateTime << 32) | ((u64)last_write_time.dwLowDateTime));
  }
  return result;
}

internal b32 file_has_extension(String8 filename, String8 ext) {
  if (filename.size < ext.size + 1)  return false;
  if (filename.str[filename.size - ext.size - 1] != '.')  return false;
  for (u64 i = 0; i < ext.size; i++) {
    if (tolower(filename.str[filename.size - ext.size + i]) != tolower(ext.str[i])) {
      return false;
    }
  }
  return true;
}

internal File_List file_get_all_files_in_path_recursively(Arena* arena, String8 path, u32 flags) {
  File_List result = {0};
  Arena_Temp scratch = scratch_begin(0, 0);

  if (!path_is_directory(path)) {
    arena_temp_end(&scratch);
    printf("Path '%s' is not a directory.\n", path.str);
    return result;
  }

  String_List dir_queue = {0};
  string8_list_push(scratch.arena, &dir_queue, path);

  while (dir_queue.node_count > 0) {
    String8 current_dir    = string8_list_pop(&dir_queue);
    String16 current_dir16 = string16_from_string8(scratch.arena, current_dir);
    if (current_dir16.size == 0) continue;

    String16 search_path = {current_dir16.size + 2, ArenaPushNoZero(scratch.arena, wchar_t, current_dir16.size + 3)};
    memcpy(search_path.str, current_dir16.str, current_dir16.size * sizeof(wchar_t));
    search_path.str[current_dir16.size] = L'\\';
    search_path.str[current_dir16.size + 1] = L'*';
    search_path.str[current_dir16.size + 2] = L'\0';

    WIN32_FIND_DATAW find_data;
    HANDLE find_handle = FindFirstFileW(search_path.str, &find_data);
    if (find_handle == INVALID_HANDLE_VALUE) continue;

    do {
      if (wcscmp(find_data.cFileName, L".") == 0 || wcscmp(find_data.cFileName, L"..") == 0) {
        continue;
      }

      String16 filename16 = {0, find_data.cFileName};
      while (filename16.str[filename16.size] != L'\0') filename16.size++;

      String8 filename8 = string8_from_string16(scratch.arena, filename16);
      if (filename8.size == 0) continue;

      u64 full_path_size = current_dir.size + 1 + filename8.size;
      char8* full_path_str = ArenaPushNoZero(arena, char8, full_path_size + 1);
      String8 full_path = {full_path_size, full_path_str};

      memcpy(full_path_str, current_dir.str, current_dir.size);
      full_path_str[current_dir.size] = '\\';
      memcpy(full_path_str + current_dir.size + 1, filename8.str, filename8.size);
      full_path_str[full_path_size] = '\0';

      b32 is_directory = HasFlags(find_data.dwFileAttributes, FILE_ATTRIBUTE_DIRECTORY);
      b32 is_c_file    = !is_directory && file_has_extension(filename8, Str8("c"));
      b32 is_h_file    = !is_directory && file_has_extension(filename8, Str8("h"));
      b32 is_dot_file  = !is_directory && filename8.size > 0 && (filename8.str[0] == '.');
      b32 is_dot_dir   =  is_directory && filename8.size > 0 && (filename8.str[0] == '.');

      b32 add_path = true;
      if (HasFlags(flags, FileFlag_WhiteList)) {
        add_path = (is_c_file    && HasFlags(flags, FileFlag_CFiles))   ||
                   (is_h_file    && HasFlags(flags, FileFlag_HFiles))   ||
                   (is_directory && HasFlags(flags, FileFlag_Dirs))     ||
                   (is_dot_file  && HasFlags(flags, FileFlag_DotFiles)) ||
                   (is_dot_dir   && HasFlags(flags, FileFlag_DotDirs)); 
      } else {
        add_path = !((is_c_file   && HasFlags(flags, FileFlag_CFiles))   ||
                    (is_h_file    && HasFlags(flags, FileFlag_HFiles))   ||
                    (is_directory && HasFlags(flags, FileFlag_Dirs))     ||
                    (is_dot_file  && HasFlags(flags, FileFlag_DotFiles)) ||
                    (is_dot_dir   && HasFlags(flags, FileFlag_DotDirs)));
      }

      if (add_path) {
        String8 path = string8_new(full_path_size, full_path_str);
        if (is_directory) {
          string8_list_push(scratch.arena, &dir_queue, path);
        } else {
          File_Data file = file_load(arena, path);
          file_list_push(arena, &result, file);
        }
      }

    } while (FindNextFileW(find_handle, &find_data));

    FindClose(find_handle);
  }

  scratch_end(&scratch);
  return result;
}

internal b32 path_is_directory(String8 path) {
  b32 result = false;

  if (path.size == 0 || path.str == NULL) {
    return result;
  }
  
  Arena_Temp scratch = scratch_begin(0, 0);
  String16 path16 = string16_from_string8(scratch.arena, path);
  if (path16.size == 0) {
    scratch_end(&scratch);
    return result;
  }
  
  wchar_t *wcstr   = wcstr_from_string16(scratch.arena, path16);
  DWORD attributes = GetFileAttributesW(wcstr);
  scratch_end(&scratch);

  if (attributes == INVALID_FILE_ATTRIBUTES) {
    return result;
  }

  result = (b32)(attributes & FILE_ATTRIBUTE_DIRECTORY);
  return result;;
}

internal b32 file_exists(String8 file_path) {
  b32 result = 0;
  DWORD file_attributes = GetFileAttributesA(file_path.str);
  if (file_attributes == INVALID_FILE_ATTRIBUTES) {
    printf("File %s attributes are invalid.\n", file_path.str);
  } else if (file_attributes & FILE_ATTRIBUTE_DIRECTORY) {
    printf("Path %s is a directory.\n", file_path.str);
  } else {
    result = true;
  }
  return result;
}

internal u32 file_write(String8 file_path, u8* data, u64 data_size) {
  s32 bytes_written = 0;
  HANDLE file_handle = _win32_get_file_handle_write(file_path);

  if (!WriteFile(file_handle, data, data_size, &bytes_written, NULL)) {
    printf("WriteFile failed (error %d)\n", GetLastError());
  }

  return bytes_written;
}

internal u32 file_size(String8 file_path) {
  u32 result = 0;
  if (!file_exists(file_path)) {
    printf("Error: file_exists failed because file %s doesn't exist\n", file_path.str);
    return result;
  }
  WIN32_FILE_ATTRIBUTE_DATA file_attribute_data;
  if (GetFileAttributesExA(file_path.str, GetFileExInfoStandard, &file_attribute_data)) {
    result = ((u64)file_attribute_data.nFileSizeHigh << 32) | ((u64)file_attribute_data.nFileSizeLow);
  }
  return result;
}

internal File_Data file_load(Arena* arena, String8 file_path) {
  File_Data result = { 0 };
  if (!file_exists(file_path)) {
    printf("Error: file_load failed because file %s doesn't exist\n", file_path.str);
    return result;
  }

  HANDLE file_handle = _win32_get_file_handle_read(file_path);
  if (file_handle == NULL) {
    return result;
  }
  
  u32 size    = file_size(file_path);
  char8* data = ArenaPush(arena, char8, size);
  MemoryZero(data, size);

  if (!ReadFile(file_handle, data, size, NULL, NULL)) {
    DWORD error = GetLastError();  
    printf("Error: %lu in file_load.\n", error);
    return result;
  }
  result.path = file_path;
  result.data.str = data;
  result.data.size = size;
  
  CloseHandle(file_handle);
  return result;
}

internal void file_list_push(Arena* arena, File_List* list, File_Data file) {
  File_Node* node = ArenaPush(arena, File_Node, sizeof(File_Node));
  
  node->value = file;
  if (!list->first && !list->last) {
    list->first = node;
    list->last  = node;
  } else {
    list->last->next = node;
    list->last       = node;
  }
  list->node_count += 1;
  list->total_size += node->value.data.size;
}

internal void println_string(String8 string) {
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  WriteFile(handle, string.str, string.size, NULL, NULL);
  char8 newline = '\n';
  WriteFile(handle, &newline, 1, NULL, NULL);
}

internal void _error_message_and_exit(const char8 *file, int line, const char8 *func, const char8 *fmt, ...) {
  char8 buffer[1024];
  va_list args;

  va_start(args, fmt);
  vsnprintf(buffer, sizeof(buffer), fmt, args);
  va_end(args);

  char8 detailed_buffer[2048];
  snprintf(detailed_buffer, sizeof(detailed_buffer), "Error at %s:%d in %s\n%s", file, line, func, buffer);

  MessageBoxA(0, detailed_buffer, "ahah idiot", MB_OK);
  ExitProcess(1);
}