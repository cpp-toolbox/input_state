#include "input_state.hpp"

#include <iostream>
#include <string>
#include <sstream>

/* https://toolbox.cuppajoeman.com/ascii_art/keyboard.html
 * ---------------------------------
 * |`|1|2|3|4|5|6|7|8|9|0|-|=|   bs|
 * |tb|q|w|e|r|t|y|u|i|o|p|[|]| \  |
 * |cps|a|s|d|f|g|h|j|k|l|;|'|  ent|
 * |shft|z|x|c|v|b|n|m|,|.|/|  shft|
 * |ct|sp|al|          |al|fn|mn|rc|
 * ---------------------------------
 */

std::vector<std::vector<std::string>> keyboard = {
    {"`", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "   bs"},
    {"tb", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "[", "]", " \\  "},
    {"cps", "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "'", "  ent"},
    {"shft", "z", "x", "c", "v", "b", "n", "m", ",", ".", "/", "  shft"},
    {"ct", "sp", "al", "          ", "al", "fn", "mn", "rc"}};

std::unordered_map<std::string, EKey> keyboard_key_str_to_key_enum = {{"`", EKey::GRAVE_ACCENT},
                                                                      {"1", EKey::ONE},
                                                                      {"2", EKey::TWO},
                                                                      {"3", EKey::THREE},
                                                                      {"4", EKey::FOUR},
                                                                      {"5", EKey::FIVE},
                                                                      {"6", EKey::SIX},
                                                                      {"7", EKey::SEVEN},
                                                                      {"8", EKey::EIGHT},
                                                                      {"9", EKey::NINE},
                                                                      {"0", EKey::ZERO},
                                                                      {"-", EKey::MINUS},
                                                                      {"=", EKey::EQUAL},
                                                                      {"   bs", EKey::BACKSPACE},

                                                                      {"tb", EKey::TAB},
                                                                      {"q", EKey::q},
                                                                      {"w", EKey::w},
                                                                      {"e", EKey::e},
                                                                      {"r", EKey::r},
                                                                      {"t", EKey::t},
                                                                      {"y", EKey::y},
                                                                      {"u", EKey::u},
                                                                      {"i", EKey::i},
                                                                      {"o", EKey::o},
                                                                      {"p", EKey::p},
                                                                      {"[", EKey::LEFT_SQUARE_BRACKET},
                                                                      {"]", EKey::RIGHT_SQUARE_BRACKET},
                                                                      {" \\  ", EKey::BACKSLASH},

                                                                      {"cps", EKey::CAPS_LOCK},
                                                                      {"a", EKey::a},
                                                                      {"s", EKey::s},
                                                                      {"d", EKey::d},
                                                                      {"f", EKey::f},
                                                                      {"g", EKey::g},
                                                                      {"h", EKey::h},
                                                                      {"j", EKey::j},
                                                                      {"k", EKey::k},
                                                                      {"l", EKey::l},
                                                                      {";", EKey::SEMICOLON},
                                                                      {"'", EKey::SINGLE_QUOTE},
                                                                      {"  ent", EKey::ENTER},
                                                                      {"shft", EKey::LEFT_SHIFT},
                                                                      {"z", EKey::z},
                                                                      {"x", EKey::x},
                                                                      {"c", EKey::c},
                                                                      {"v", EKey::v},
                                                                      {"b", EKey::b},
                                                                      {"n", EKey::n},
                                                                      {"m", EKey::m},
                                                                      {",", EKey::COMMA},
                                                                      {".", EKey::PERIOD},
                                                                      {"/", EKey::SLASH},
                                                                      {"  shft", EKey::RIGHT_SHIFT},
                                                                      {"ct", EKey::LEFT_CONTROL},
                                                                      {"sp", EKey::LEFT_SUPER},
                                                                      {"al", EKey::LEFT_ALT},
                                                                      {"          ", EKey::SPACE},
                                                                      {"al", EKey::RIGHT_ALT},
                                                                      {"fn", EKey::FUNCTION_KEY},
                                                                      {"mn", EKey::MENU_KEY},
                                                                      {"rc", EKey::RIGHT_CONTROL}};

std::string InputState::get_visual_keyboard_state() {
    std::stringstream state_stream;

    // Create a copy of the keyboard to modify without changing the original one
    auto modified_keyboard = keyboard;

    // Iterate over all keys in the keyboard
    for (auto &row : modified_keyboard) {
        for (auto &key : row) {
            // Check if the key has a corresponding enum value
            auto key_enum_iter = keyboard_key_str_to_key_enum.find(key);
            if (key_enum_iter != keyboard_key_str_to_key_enum.end()) {
                EKey key_enum = key_enum_iter->second;

                // If the key is just pressed, replace with the correct number of X's
                if (is_just_pressed(key_enum)) {
                    key = std::string(key.size(), '*'); // Replace with *'s of the same length
                }
                if (is_held(key_enum)) {
                    key = std::string(key.size(), 'X'); // Replace with X's of the same length
                }
            }
        }
    }

    // Construct the state string (instead of printing)
    state_stream << "---------------------------------" << std::endl;
    for (const auto &row : modified_keyboard) {
        for (const auto &key : row) {
            // Ensure alignment of output
            state_stream << "|" << key;
        }
        state_stream << "|" << std::endl;
    }
    state_stream << "---------------------------------" << std::endl;

    // Return the state string
    state_stream << "State updated." << std::endl;

    // Return the constructed state string
    return state_stream.str();
}

std::vector<EKey> InputState::get_just_pressed_keys() {
    std::vector<EKey> keys_just_pressed_this_tick;
    for (const auto &key : all_keys) {
        if (key.pressed_signal.just_switched_on()) {
            keys_just_pressed_this_tick.push_back(key.key_enum);
        }
    }
    return keys_just_pressed_this_tick;
}

std::vector<EKey> InputState::get_held_keys() {
    std::vector<EKey> keys_held_this_tick;
    for (const auto &key : all_keys) {
        if (key.pressed_signal.sustained_on()) {
            keys_held_this_tick.push_back(key.key_enum);
        }
    }
    return keys_held_this_tick;
}

std::vector<EKey> InputState::get_just_released_keys() {
    std::vector<EKey> keys_just_released_this_tick;
    for (const auto &key : all_keys) {
        if (key.pressed_signal.just_switched_off()) {
            keys_just_released_this_tick.push_back(key.key_enum);
        }
    }
    return keys_just_released_this_tick;
}

std::vector<std::string> InputState::get_just_pressed_key_strings() {
    std::vector<std::string> keys_just_pressed_this_tick;
    for (const auto &key : all_keys) {
        bool char_is_printable =
            key.key_type == KeyType::ALPHA or key.key_type == KeyType::SYMBOL or key.key_type == KeyType::NUMERIC;
        if (char_is_printable and key.pressed_signal.just_switched_on()) {
            std::string key_str = key.string_repr;
            if (key.shiftable and key_enum_to_object.at(EKey::LEFT_SHIFT)->pressed_signal.is_on()) {
                Key shifted_key = *key_enum_to_object.at(key.key_enum_of_shifted_version);
                key_str = shifted_key.string_repr;
            }
            keys_just_pressed_this_tick.push_back(key_str);
        }
    }
    return keys_just_pressed_this_tick;
}

bool InputState::is_just_pressed(EKey key_enum) {
    return key_enum_to_object.at(key_enum)->pressed_signal.just_switched_on();
}
bool InputState::is_pressed(EKey key_enum) { return key_enum_to_object.at(key_enum)->pressed_signal.is_on(); }
bool InputState::is_held(EKey key_enum) { return key_enum_to_object.at(key_enum)->pressed_signal.sustained_on(); }
bool InputState::is_just_released(EKey key_enum) {
    return key_enum_to_object.at(key_enum)->pressed_signal.just_switched_off();
}

const TemporalBinarySwitch::State &InputState::get_current_state(EKey key_enum) {
    return key_enum_to_object.at(key_enum)->pressed_signal.get_current_state();
}

std::vector<std::string> InputState::get_keys_just_pressed_this_tick() {
    std::vector<std::string> keys_just_pressed_this_tick;
    for (const auto &key : all_keys) {
        bool char_is_printable =
            key.key_type == KeyType::ALPHA or key.key_type == KeyType::SYMBOL or key.key_type == KeyType::NUMERIC;
        if (char_is_printable and key.pressed_signal.just_switched_on()) {
            std::string key_str = key.string_repr;
            bool shift_pressed = key_enum_to_object.at(EKey::LEFT_SHIFT)->pressed_signal.is_on() or
                                 key_enum_to_object.at(EKey::RIGHT_SHIFT)->pressed_signal.is_on();
            if (key.shiftable and shift_pressed) {
                Key shifted_key = *key_enum_to_object.at(key.key_enum_of_shifted_version);
                key_str = shifted_key.string_repr;
            } else {
            }
            keys_just_pressed_this_tick.push_back(key_str);
        }
    }
    return keys_just_pressed_this_tick;
}

InputState::InputState() {
    // OLD: this line looks trivial but is extremely important, if not the way temporary objects are copied
    // will make it so that the temporal binary states are destroyed making it so that they're not processed anymore
    // horrible bug, so keep this line, using 500 for overkill but I don't like counting.
    // NOTE: now i don't think i need to do tis because the rule of 5
    this->all_keys.reserve(500);
    all_keys.emplace_back(EKey::a, KeyType::ALPHA, "a", false, true, EKey::A);
    all_keys.emplace_back(EKey::b, KeyType::ALPHA, "b", false, true, EKey::B);
    all_keys.emplace_back(EKey::c, KeyType::ALPHA, "c", false, true, EKey::C);
    all_keys.emplace_back(EKey::d, KeyType::ALPHA, "d", false, true, EKey::D);
    all_keys.emplace_back(EKey::e, KeyType::ALPHA, "e", false, true, EKey::E);
    all_keys.emplace_back(EKey::f, KeyType::ALPHA, "f", false, true, EKey::F);
    all_keys.emplace_back(EKey::g, KeyType::ALPHA, "g", false, true, EKey::G);
    all_keys.emplace_back(EKey::h, KeyType::ALPHA, "h", false, true, EKey::H);
    all_keys.emplace_back(EKey::i, KeyType::ALPHA, "i", false, true, EKey::I);
    all_keys.emplace_back(EKey::j, KeyType::ALPHA, "j", false, true, EKey::J);
    all_keys.emplace_back(EKey::k, KeyType::ALPHA, "k", false, true, EKey::K);
    all_keys.emplace_back(EKey::l, KeyType::ALPHA, "l", false, true, EKey::L);
    all_keys.emplace_back(EKey::m, KeyType::ALPHA, "m", false, true, EKey::M);
    all_keys.emplace_back(EKey::n, KeyType::ALPHA, "n", false, true, EKey::N);
    all_keys.emplace_back(EKey::o, KeyType::ALPHA, "o", false, true, EKey::O);
    all_keys.emplace_back(EKey::p, KeyType::ALPHA, "p", false, true, EKey::P);
    all_keys.emplace_back(EKey::q, KeyType::ALPHA, "q", false, true, EKey::Q);
    all_keys.emplace_back(EKey::r, KeyType::ALPHA, "r", false, true, EKey::R);
    all_keys.emplace_back(EKey::s, KeyType::ALPHA, "s", false, true, EKey::S);
    all_keys.emplace_back(EKey::t, KeyType::ALPHA, "t", false, true, EKey::T);
    all_keys.emplace_back(EKey::u, KeyType::ALPHA, "u", false, true, EKey::U);
    all_keys.emplace_back(EKey::v, KeyType::ALPHA, "v", false, true, EKey::V);
    all_keys.emplace_back(EKey::w, KeyType::ALPHA, "w", false, true, EKey::W);
    all_keys.emplace_back(EKey::x, KeyType::ALPHA, "x", false, true, EKey::X);
    all_keys.emplace_back(EKey::y, KeyType::ALPHA, "y", false, true, EKey::Y);
    all_keys.emplace_back(EKey::z, KeyType::ALPHA, "z", false, true, EKey::Z);

    all_keys.emplace_back(EKey::A, KeyType::ALPHA, "A");
    all_keys.emplace_back(EKey::B, KeyType::ALPHA, "B");
    all_keys.emplace_back(EKey::C, KeyType::ALPHA, "C");
    all_keys.emplace_back(EKey::D, KeyType::ALPHA, "D");
    all_keys.emplace_back(EKey::E, KeyType::ALPHA, "E");
    all_keys.emplace_back(EKey::F, KeyType::ALPHA, "F");
    all_keys.emplace_back(EKey::G, KeyType::ALPHA, "G");
    all_keys.emplace_back(EKey::H, KeyType::ALPHA, "H");
    all_keys.emplace_back(EKey::I, KeyType::ALPHA, "I");
    all_keys.emplace_back(EKey::J, KeyType::ALPHA, "J");
    all_keys.emplace_back(EKey::K, KeyType::ALPHA, "K");
    all_keys.emplace_back(EKey::L, KeyType::ALPHA, "L");
    all_keys.emplace_back(EKey::M, KeyType::ALPHA, "M");
    all_keys.emplace_back(EKey::N, KeyType::ALPHA, "N");
    all_keys.emplace_back(EKey::O, KeyType::ALPHA, "O");
    all_keys.emplace_back(EKey::P, KeyType::ALPHA, "P");
    all_keys.emplace_back(EKey::Q, KeyType::ALPHA, "Q");
    all_keys.emplace_back(EKey::R, KeyType::ALPHA, "R");
    all_keys.emplace_back(EKey::S, KeyType::ALPHA, "S");
    all_keys.emplace_back(EKey::T, KeyType::ALPHA, "T");
    all_keys.emplace_back(EKey::U, KeyType::ALPHA, "U");
    all_keys.emplace_back(EKey::V, KeyType::ALPHA, "V");
    all_keys.emplace_back(EKey::W, KeyType::ALPHA, "W");
    all_keys.emplace_back(EKey::X, KeyType::ALPHA, "X");
    all_keys.emplace_back(EKey::Y, KeyType::ALPHA, "Y");
    all_keys.emplace_back(EKey::Z, KeyType::ALPHA, "Z");

    all_keys.emplace_back(EKey::SPACE, KeyType::SYMBOL, " ", false);
    all_keys.emplace_back(EKey::GRAVE_ACCENT, KeyType::SYMBOL, "`", false, true, EKey::TILDE);
    all_keys.emplace_back(EKey::TILDE, KeyType::SYMBOL, "`");

    all_keys.emplace_back(EKey::ONE, KeyType::NUMERIC, "1", false, true, EKey::EXCLAMATION_POINT);
    all_keys.emplace_back(EKey::TWO, KeyType::NUMERIC, "2", false, true, EKey::AT_SIGN);
    all_keys.emplace_back(EKey::THREE, KeyType::NUMERIC, "3", false, true, EKey::NUMBER_SIGN);
    all_keys.emplace_back(EKey::FOUR, KeyType::NUMERIC, "4", false, true, EKey::DOLLAR_SIGN);
    all_keys.emplace_back(EKey::FIVE, KeyType::NUMERIC, "5", false, true, EKey::PERCENT_SIGN);
    all_keys.emplace_back(EKey::SIX, KeyType::NUMERIC, "6", false, true, EKey::CARET);
    all_keys.emplace_back(EKey::SEVEN, KeyType::NUMERIC, "7", false, true, EKey::AMPERSAND);
    all_keys.emplace_back(EKey::EIGHT, KeyType::NUMERIC, "8", false, true, EKey::ASTERISK);
    all_keys.emplace_back(EKey::NINE, KeyType::NUMERIC, "9", false, true, EKey::LEFT_PARENTHESIS);
    all_keys.emplace_back(EKey::ZERO, KeyType::NUMERIC, "0", false, true, EKey::RIGHT_PARENTHESIS);
    all_keys.emplace_back(EKey::MINUS, KeyType::SYMBOL, "-", false, true, EKey::UNDERSCORE);
    all_keys.emplace_back(EKey::EQUAL, KeyType::SYMBOL, "=", false, true, EKey::PLUS);

    all_keys.emplace_back(EKey::EXCLAMATION_POINT, KeyType::SYMBOL, "!");
    all_keys.emplace_back(EKey::AT_SIGN, KeyType::SYMBOL, "@");
    all_keys.emplace_back(EKey::NUMBER_SIGN, KeyType::SYMBOL, "#");
    all_keys.emplace_back(EKey::DOLLAR_SIGN, KeyType::SYMBOL, "$");
    all_keys.emplace_back(EKey::PERCENT_SIGN, KeyType::SYMBOL, "%");
    all_keys.emplace_back(EKey::CARET, KeyType::SYMBOL, "^");
    all_keys.emplace_back(EKey::AMPERSAND, KeyType::SYMBOL, "&");
    all_keys.emplace_back(EKey::ASTERISK, KeyType::SYMBOL, "*");
    all_keys.emplace_back(EKey::LEFT_PARENTHESIS, KeyType::SYMBOL, "(");
    all_keys.emplace_back(EKey::RIGHT_PARENTHESIS, KeyType::SYMBOL, ")");
    all_keys.emplace_back(EKey::UNDERSCORE, KeyType::SYMBOL, "_");
    all_keys.emplace_back(EKey::PLUS, KeyType::SYMBOL, "+");

    all_keys.emplace_back(EKey::LEFT_SQUARE_BRACKET, KeyType::SYMBOL, "[", false, true, EKey::LEFT_CURLY_BRACKET);
    all_keys.emplace_back(EKey::RIGHT_SQUARE_BRACKET, KeyType::SYMBOL, "]", false, true, EKey::RIGHT_CURLY_BRACKET);

    all_keys.emplace_back(EKey::LEFT_CURLY_BRACKET, KeyType::SYMBOL, "{");
    all_keys.emplace_back(EKey::RIGHT_CURLY_BRACKET, KeyType::SYMBOL, "}");

    all_keys.emplace_back(EKey::COMMA, KeyType::SYMBOL, ",", false, true, EKey::LESS_THAN);
    all_keys.emplace_back(EKey::PERIOD, KeyType::SYMBOL, ".", false, true, EKey::GREATER_THAN);
    all_keys.emplace_back(EKey::LESS_THAN, KeyType::SYMBOL, "<");
    all_keys.emplace_back(EKey::GREATER_THAN, KeyType::SYMBOL, ">");

    all_keys.emplace_back(EKey::CAPS_LOCK, KeyType::CONTROL, "caps_lock", false);
    all_keys.emplace_back(EKey::ESCAPE, KeyType::CONTROL, "escape", false);
    all_keys.emplace_back(EKey::ENTER, KeyType::CONTROL, "enter", false);
    all_keys.emplace_back(EKey::TAB, KeyType::CONTROL, "tab", false);
    all_keys.emplace_back(EKey::BACKSPACE, KeyType::CONTROL, "backspace", false);
    all_keys.emplace_back(EKey::INSERT, KeyType::CONTROL, "insert", false);
    all_keys.emplace_back(EKey::DELETE_, KeyType::CONTROL, "delete", false);

    all_keys.emplace_back(EKey::RIGHT, KeyType::CONTROL, "right", false);
    all_keys.emplace_back(EKey::LEFT, KeyType::CONTROL, "left", false);
    all_keys.emplace_back(EKey::UP, KeyType::CONTROL, "up", false);
    all_keys.emplace_back(EKey::DOWN, KeyType::CONTROL, "down", false);

    all_keys.emplace_back(EKey::SLASH, KeyType::SYMBOL, "/", false, true, EKey::QUESTION_MARK);
    all_keys.emplace_back(EKey::QUESTION_MARK, KeyType::SYMBOL, "?");

    all_keys.emplace_back(EKey::BACKSLASH, KeyType::SYMBOL, "\\", false, true, EKey::PIPE);
    all_keys.emplace_back(EKey::PIPE, KeyType::SYMBOL, "|");

    all_keys.emplace_back(EKey::SEMICOLON, KeyType::SYMBOL, ";", false, true, EKey::COLON);
    all_keys.emplace_back(EKey::COLON, KeyType::SYMBOL, ":");

    all_keys.emplace_back(EKey::SINGLE_QUOTE, KeyType::SYMBOL, "'", false, true, EKey::DOUBLE_QUOTE);
    all_keys.emplace_back(EKey::DOUBLE_QUOTE, KeyType::SYMBOL, "\"");

    all_keys.emplace_back(EKey::FUNCTION_KEY, KeyType::CONTROL, "function_key", true);
    all_keys.emplace_back(EKey::MENU_KEY, KeyType::CONTROL, "menu_key", true);

    all_keys.emplace_back(EKey::LEFT_SHIFT, KeyType::MODIFIER, "left_shift", false);
    all_keys.emplace_back(EKey::RIGHT_SHIFT, KeyType::MODIFIER, "right_shift", false);
    all_keys.emplace_back(EKey::LEFT_CONTROL, KeyType::MODIFIER, "left_control", false);
    all_keys.emplace_back(EKey::RIGHT_CONTROL, KeyType::MODIFIER, "right_control", false);
    all_keys.emplace_back(EKey::LEFT_ALT, KeyType::MODIFIER, "left_alt", false);
    all_keys.emplace_back(EKey::RIGHT_ALT, KeyType::MODIFIER, "right_alt", false);
    all_keys.emplace_back(EKey::LEFT_SUPER, KeyType::MODIFIER, "left_super", false);
    all_keys.emplace_back(EKey::RIGHT_SUPER, KeyType::MODIFIER, "right_super", false);

    all_keys.emplace_back(EKey::LEFT_MOUSE_BUTTON, KeyType::MOUSE, "left_mouse_button", false);
    all_keys.emplace_back(EKey::RIGHT_MOUSE_BUTTON, KeyType::MOUSE, "right_mouse_button", false);
    all_keys.emplace_back(EKey::MIDDLE_MOUSE_BUTTON, KeyType::MOUSE, "middle_mouse_button", false);
    // not sure how to handle these yet.
    all_keys.emplace_back(EKey::SCROLL_UP, KeyType::MOUSE, "scroll_up", false);
    /*{EKey::SCROLL_DOWN, KeyType::SYMBOL, 999, "scroll_down"}*/

    for (auto &key : all_keys) {
        Key *key_ptr = &key;

        // Ensure no duplicate key_enum during construction
        // assert(this->key_enum_to_object.find(key.key_enum) == this->key_enum_to_object.end() &&
        //        "Duplicate key_enum detected during construction!");

        this->key_enum_to_object[key.key_enum] = key_ptr;
        this->key_str_to_key_enum[key.string_repr] = key.key_enum;
    }
}
