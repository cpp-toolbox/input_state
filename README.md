# input_state
SUBPROJECT

# why
when making games you need a good and robust way to query the current mouse and keyboard state, usually all this logic occurs inside of a key callback, something like this allows you instead query the keyboard state werever you have access to the `input_state` object allowing you to put the logic where you please instead of it all building up in the key callback.

Additionally you'll want to be able to know what key is pressed, and what the string is for a given key, when using a char callback the logic can become even more fragmented, thus this class also gives you tools to know what the string is for a key.

# operation 
In order to integrate this into your system first initialize one of these somewhere:
```cpp
InputState input_state;
```
Then use the callbacks provided:
```cpp
    std::function<void(int, int, int, int)> key_callback = [&](int key, int scancode, int action, int mods) {
        input_state.glfw_key_callback(key, scancode, action, mods);
    };
    std::function<void(double, double)> mouse_pos_callback = [&](double xpos, double ypos) {
        input_state.glfw_cursor_pos_callback(xpos, ypos);
    };
    std::function<void(int, int, int)> mouse_button_callback = [&](int button, int action, int mods) {
        input_state.glfw_mouse_button_callback(button, action, mods);
    };
```

note that since this system relies on `TemporalBinarySignal` you need to make this call once per tick
```cpp
TemporalBinarySignal::process_all();
```

then to check if a key has just been pressed we do: 
```cpp
input_state.is_just_pressed(EKey::J)
```
or to see if it's actively being pressed do: 
```cpp
input_state.is_pressed(EKey::J)
```
