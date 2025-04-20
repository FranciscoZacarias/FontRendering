void _input_init() {
  AssertNoReentry();
  MemoryZeroStruct(&_InputState);

  // TODO(fz): Change macros with the state of the app.
  _InputState.mouse_current.screen_space_x = FZ_WINDOW_WIDTH/2;
  _InputState.mouse_current.screen_space_y = FZ_WINDOW_HEIGHT/2;
  
  _InputState.mouse_previous.screen_space_x = FZ_WINDOW_WIDTH/2;
  _InputState.mouse_previous.screen_space_y = FZ_WINDOW_HEIGHT/2;
}

void _input_update() {
  MemoryCopy(&_InputState.keyboard_previous, &_InputState.keyboard_current, sizeof(Keyboard_State));
  MemoryCopy(&_InputState.mouse_previous,    &_InputState.mouse_current,    sizeof(Mouse_State));
}

//~ Keyboard functions
internal b32 input_is_key_up(Keyboard_Key key) {
  b32 result = _InputState.keyboard_current.keys[key] == false;
  return result;
}

internal b32 input_is_key_down(Keyboard_Key key) {
  b32 result = _InputState.keyboard_current.keys[key] == true;
  return result;
}

internal b32 input_was_key_up(Keyboard_Key key) {
  b32 result = _InputState.keyboard_previous.keys[key] == false;
  return result;
}

internal b32 input_was_key_down(Keyboard_Key key) {
  b32 result = _InputState.keyboard_previous.keys[key] == true;
  return result;
}

internal b32 input_is_key_pressed(Keyboard_Key key) {
  return input_is_key_down(key) && input_was_key_up(key);
}

internal void _input_process_keyboard_key(Keyboard_Key key, b8 is_pressed) {
  if (_InputState.keyboard_current.keys[key] != is_pressed) {
    _InputState.keyboard_current.keys[key] = is_pressed;
  }
}

//~ Mouse functions
internal b32 input_is_button_up(Mouse_Button button) {
  b32 result = _InputState.mouse_current.buttons[button] == false;
  return result;
}

internal b32 input_is_button_down(Mouse_Button button) {
  b32 result = _InputState.mouse_current.buttons[button] == true;
  return result;
}

internal b32 input_was_button_up(Mouse_Button button) {
  b32 result = _InputState.mouse_previous.buttons[button] == false;
  return result;
}

internal b32 input_was_button_down(Mouse_Button button) {
  b32 result = _InputState.mouse_previous.buttons[button] == true;
  return result;
}

internal b32 input_is_button_pressed(Mouse_Button button) {
  b32 result = input_is_button_down(button) && input_was_button_up(button);
  return result;
}

internal void _input_process_mouse_button(Mouse_Button button, b32 is_pressed) {
  if (_InputState.mouse_current.buttons[button] != (b8)is_pressed) {
    _InputState.mouse_current.buttons[button] = (b8)is_pressed;
  }
}

internal void _input_process_mouse_cursor(s32 x, s32 y) {
  // Copy current state to previous
  MemoryCopyStruct(&(_InputState.mouse_previous), &(_InputState.mouse_current));

  // Compute new deltas
  _InputState.mouse_current.delta_x = x - _InputState.mouse_previous.screen_space_x;
  _InputState.mouse_current.delta_y = y - _InputState.mouse_previous.screen_space_y;

  // Update current position
  _InputState.mouse_current.screen_space_x = x;
  _InputState.mouse_current.screen_space_y = y;
}