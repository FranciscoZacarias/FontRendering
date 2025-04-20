#ifndef FZ_WIN32_H
#define FZ_WIN32_H

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <userenv.h>

///////////////////////
//~ Win32
internal void application_stop();

///////////////////////
//~ Memory
internal void* memory_reserve(u64 size);
internal b32   memory_commit(void* memory, u64 size);
internal void  memory_decommit(void* memory, u64 size);
internal void  memory_release(void* memory, u64 size);
internal u64   memory_get_page_size();

///////////////////////
//~ Threading
typedef u64 thread_func(void* context); 

typedef struct Thread {
  u64 v[1];
} Thread;

internal Thread thread_create(thread_func* start, void* context);
internal void   thread_wait_for_join(Thread* other);
internal void   thread_wait_for_join_all(Thread** threads, u32 count);
internal void   thread_wait_for_join_any(Thread** threads, u32 count);

///////////////////////
//~ File handling

typedef enum {
  FileFlag_None       = 0,
  FileFlag_WhiteList  = 1 << 0,
  FileFlag_CFiles     = 1 << 2,
  FileFlag_HFiles     = 1 << 3,
  FileFlag_Dirs       = 1 << 4,
  FileFlag_DotFiles   = 1 << 5,
  FileFlag_DotDirs    = 1 << 6,
} FileFlags;

typedef struct File_Data {
  String8 path;
  String8 data;
} File_Data;

typedef struct File_Node {
  struct File_Node* next;
  File_Data value;
} File_Node;

typedef struct File_List {
  File_Node* first;
  File_Node* last;
  u64 node_count;
  u64 total_size;
} File_List;

internal void      file_list_push(Arena* arena, File_List* list, File_Data file);

internal b32       file_create(String8 file_path);
internal b32       file_exists(String8 file_path);
internal u32       file_write(String8 file_path, u8* data, u64 data_size);
internal u32       file_size(String8 file_path);
internal File_Data file_load(Arena* arena, String8 file_path);
internal b32       file_has_extension(String8 filename, String8 ext);
internal u64       file_get_last_modified_time(String8 file_path);
internal File_List file_get_all_files_in_path_recursively(Arena* arena, String8 path, u32 flags);

internal b32 path_is_directory(String8 path);

///////////////////////
//~ Logging 
internal void println_string(String8 string); // TODO(fz): This should be abstracted into a more generic win32_print that then String can use to implement it's own print_string

///////////////////////
//~ Error
// TODO(Fz): I'm not sure if I like this macro. Feels constrained and unecessary
#define ERROR_MESSAGE_AND_EXIT(fmt, ...) _error_message_and_exit(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
internal void _error_message_and_exit(const char8 *file, int line, const char8 *func, const char8 *fmt, ...);

#endif // FZ_WIN32_H