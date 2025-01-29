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
then inside of your key callback function (in this case glfw) you need to run this code:
```cpp
// these events happen once when the key is pressed down, aka its non-repeating; a one time event
if (action == GLFW_PRESS || action == GLFW_RELEASE) {
    Key &active_key = *input_state.glfw_code_to_key.at(key);
    bool is_pressed = (action == GLFW_PRESS);
    active_key.pressed_signal.set_signal(is_pressed);
    ...
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

If you want to get all keys that were just pressed this tick you can do this:
```cpp
std::vector<std::string> keys_just_pressed_this_tick;
for (const auto &key : input_state.all_keys) {
    bool char_is_printable =
        key.key_type == KeyType::ALPHA or key.key_type == KeyType::SYMBOL or key.key_type == KeyType::NUMERIC;
    if (char_is_printable and key.pressed_signal.is_just_on()) {
        std::string key_str = key.string_repr;
        if (key.shiftable and input_state.key_enum_to_object.at(EKey::LEFT_SHIFT)->pressed_signal.is_on()) {
            Key shifted_key = *input_state.key_enum_to_object.at(key.key_enum_of_shifted_version);
            key_str = shifted_key.string_repr;
        }
        keys_just_pressed_this_tick.push_back(key_str);
    }
}
```
