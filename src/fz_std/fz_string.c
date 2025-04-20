internal String8 string8_new(u64 size, char8* str) {
  String8 result = { size, str };
  return result;
}

internal String8 string8_format(String8 fmt, ...) {
  // TODO(fz): Implement
  return fmt;
}

internal String8 string8_range(char8* first, char8* range) {
  String8 result = (String8){(u64)(range - first), first};
  return result;
}

internal b32 string8_equal(String8 a, String8 b) {
  if (a.size != b.size) {
    return 0;
  }
  for(u32 i = 0; i < a.size; i++) {
    if (a.str[i] != b.str[i]) {
      return 0;
    }
  }
  return 1;
}

internal String_List string8_split(Arena* arena, String8 str, String8 split_character) {
  String_List result = { 0 };
  
  if (split_character.size != 1) {
    ERROR_MESSAGE_AND_EXIT("string8_split expects only one char8acter in split_character. It got %s of size %llu\n", split_character.str, split_character.size);
  }
  
  char8* cursor = str.str;
  char8* end    = str.str + str.size;
  for(; cursor < end; cursor++) {
    char8 byte  = *cursor;
    if (byte == split_character.str[0]) {
      string8_list_push(arena, &result, string8_range(str.str, cursor));
      string8_list_push(arena, &result, string8_range(cursor, end));
      break;
    }
  }
  
  return result;
}

internal String8 string8_list_pop(String_List* list) {
  String8 result = {0};
  if (list->node_count < 1)  return result;
  
  String_Node* last_node = list->last;
  result            = last_node->value;
  list->total_size -= last_node->value.size;

  if (list->node_count == 1) {
    list->first = 0;
    list->last = 0;
    list->node_count = 0;
  } else {
    String_Node* current = list->first;
    while (current->next != last_node) {
      current = current->next;
    }
    current->next = 0;
    list->last = current;
    list->node_count -= 1;
  }

return result;
}

internal void string8_list_push(Arena* arena, String_List* list, String8 str) {
  String_Node* node = ArenaPush(arena, String_Node, sizeof(String_Node));
  
  node->value = str;
  if (!list->first && !list->last) {
    list->first = node;
    list->last  = node;
  } else {
    list->last->next = node;
    list->last       = node;
  }
  list->node_count += 1;
  list->total_size += node->value.size;
}

internal b32 b32_from_string8(String8 str, b32* value) {
  b32 result = 1;
  if (string8_equal(str, Str8("false"))) {
    *value = 0;
  } else if (string8_equal(str, Str8("true"))) {
    *value = 1;
  } else {
    result = 0;
  }
  return result;
}

internal b32 f32_from_string8(String8 str, f32* value) {
  *value = 0.0f;
  s32 decimal_position = -1;
  
  for (u64 i = 0; i < str.size; i++) {
    if (str.str[i] >= '0'  && str.str[i] <= '9') {
      *value = *value * 10.0f + (str.str[i] - '0');
      if (decimal_position != -1) {
        decimal_position += 1;
      }
    } else if (str.str[i] == '.') {
      decimal_position = 0;
    } else {
      return 0;
    }
  }
  
  if (decimal_position != -1) {
    *value = *value / (f32)pow(10, decimal_position);
  }
  
  return 1;
}

internal b32 s32_from_string8(String8 str, s32* value) {
  *value = 0.0f;
  for (u64 i = 0; i < str.size; i++) {
    if (str.str[i] >= '0'  && str.str[i] <= '9') {
      *value = *value * 10.0f + (str.str[i] - '0');
    } else {
      return 0;
    }
  }
  return 1;
}

internal String16 string16_from_string8(Arena *arena, String8 str8) {
  String16 result = {0};
  s32 str16_length = MultiByteToWideChar(CP_UTF8, 0, str8.str, (s32)str8.size, NULL, 0);
  if (str16_length > 0) {
    result.size = str16_length;
    result.str  = ArenaPushNoZero(arena, char16, str16_length);
    MultiByteToWideChar(CP_UTF8, 0, str8.str, (s32)str8.size, (wchar_t*)result.str, str16_length);
  }
  return result;
}

internal String8 string8_from_string16(Arena* arena, String16 str16) {
  String8 result = {0};
  s32 len = WideCharToMultiByte(CP_UTF8, 0, (wchar_t*)str16.str, (s32)str16.size, NULL, 0, NULL, NULL);
  if (len > 0) {
    result.size = len;
    result.str = ArenaPushNoZero(arena, char, len);
    WideCharToMultiByte(CP_UTF8, 0, (wchar_t*)str16.str, (s32)str16.size, result.str, len, NULL, NULL);
  }
  return result;
}

internal wchar_t* wcstr_from_string16(Arena *arena, String16 str16) {
  wchar_t *wcstr = ArenaPushNoZero(arena, wchar_t, str16.size + 1);
  memcpy(wcstr, str16.str, str16.size * sizeof(char16));
  wcstr[str16.size] = L'\0';
  return wcstr;
}

//~ Char Functions
internal b32 char8_is_alpha(char8 c) {
  return char8_is_alpha_upper(c) || char8_is_alpha_lower(c);
}

internal b32 char8_is_alpha_upper(char8 c) {
  return c >= 'A' && c <= 'Z';
}

internal b32 char8_is_alpha_lower(char8 c) {
  return c >= 'a' && c <= 'z';
}

internal b32 char8_is_digit(char8 c) {
  return c >= '1' && c <= '9';
}

internal b32 char8_is_symbol(char8 c) {
  return (c == '~' || c == '!'  || c == '$' || c == '%' || c == '^' ||
          c == '&' || c == '*'  || c == '-' || c == '=' || c == '+' ||
          c == '<' || c == '.'  || c == '>' || c == '/' || c == '?' ||
          c == '|' || c == '\\' || c == '{' || c == '}' || c == '(' ||
          c == ')' || c == '\\' || c == '[' || c == ']' || c == '#' ||
          c == ',' || c == ';'  || c == ':' || c == '@');
}

internal b32 char8_is_space(char8 c) {
  return c == ' ' || c == '\r' || c == '\t' || c == '\f' || c == '\v' || c == '\n';
}

internal char8 char8_to_upper(char8 c) {
  return (c >= 'a' && c <= 'z') ? ('A' + (c - 'a')) : c;
}

internal char8 char8_to_lower(char8 c) {
  return (c >= 'A' && c <= 'Z') ? ('a' + (c - 'A')) : c;
}