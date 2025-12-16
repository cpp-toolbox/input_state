#include "input_state.hpp"

#include <iostream>
#include <string>
#include <sstream>

/* https://toolbox.cuppajoeman.com/ascii_art/keyboard.html
 * -------------------------------------------------------------
 * |esc|   |f1 |f2 |f3 |f4 | |f5 |f6 |f7 |f8 | |f9 |f10|f11|f12|
 * | ` | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = |backspa|
 * |tab | q | w | e | r | t | y | u | i | o | p | [ | ] |  \   |
 * |caps | a | s | d | f | g | h | j | k | l | ; | ' |    enter|
 * |lshift | z | x | c | v | b | n | m | , | . | / |     rshift|
 * |lctr|spec|lalt|                       |ralt| fn |menu|rctr |
 * -------------------------------------------------------------
 */

// used in function row
const std::string three_space = "   ";
const std::string one_space = " ";

// Top row
const std::string key_esc = "esc";
const std::string key_f1 = "f1 ";
const std::string key_f2 = "f2 ";
const std::string key_f3 = "f3 ";
const std::string key_f4 = "f4 ";
const std::string key_f5 = "f5 ";
const std::string key_f6 = "f6 ";
const std::string key_f7 = "f7 ";
const std::string key_f8 = "f8 ";
const std::string key_f9 = "f9 ";
const std::string key_f10 = "f10";
const std::string key_f11 = "f11";
const std::string key_f12 = "f12";

// Number row
const std::string key_grave = " ` ";
const std::string key_1 = " 1 ";
const std::string key_2 = " 2 ";
const std::string key_3 = " 3 ";
const std::string key_4 = " 4 ";
const std::string key_5 = " 5 ";
const std::string key_6 = " 6 ";
const std::string key_7 = " 7 ";
const std::string key_8 = " 8 ";
const std::string key_9 = " 9 ";
const std::string key_0 = " 0 ";
const std::string key_minus = " - ";
const std::string key_equal = " = ";
const std::string key_backspace = "backspa";

// QWERTY row
const std::string key_tab = "tab ";
const std::string key_q = " q ";
const std::string key_w = " w ";
const std::string key_e = " e ";
const std::string key_r = " r ";
const std::string key_t_ = " t "; // for some reason key_t was already defined somewhere
const std::string key_y = " y ";
const std::string key_u = " u ";
const std::string key_i = " i ";
const std::string key_o = " o ";
const std::string key_p = " p ";
const std::string key_left_bracket = " [ ";
const std::string key_right_bracket = " ] ";
const std::string key_backslash = "  \\   ";

// Home row
const std::string key_caps = "caps ";
const std::string key_a = " a ";
const std::string key_s = " s ";
const std::string key_d = " d ";
const std::string key_f = " f ";
const std::string key_g = " g ";
const std::string key_h = " h ";
const std::string key_j = " j ";
const std::string key_k = " k ";
const std::string key_l = " l ";
const std::string key_semicolon = " ; ";
const std::string key_apostrophe = " ' ";
const std::string key_enter = "    enter";

// Bottom row
const std::string key_lshift = "lshift ";
const std::string key_z = " z ";
const std::string key_x = " x ";
const std::string key_c = " c ";
const std::string key_v = " v ";
const std::string key_b = " b ";
const std::string key_n = " n ";
const std::string key_m = " m ";
const std::string key_comma = " , ";
const std::string key_period = " . ";
const std::string key_slash = " / ";
const std::string key_rshift = "     rshift";

// Modifier keys
const std::string key_lctrl = "lctr";
const std::string key_special = "spec"; // maybe Windows key or Command
const std::string key_lalt = "lalt";
const std::string key_space = "                       "; // center space bar
const std::string key_ralt = "ralt";
const std::string key_fn = " fn ";
const std::string key_menu = "menu";
const std::string key_rctrl = "rctr ";

std::vector<std::vector<std::string>> keyboard = {
    // Function row
    {key_esc, three_space, key_f1, key_f2, key_f3, key_f4, one_space, key_f5, key_f6, key_f7, key_f8, one_space, key_f9,
     key_f10, key_f11, key_f12},

    // Number row
    {key_grave, key_1, key_2, key_3, key_4, key_5, key_6, key_7, key_8, key_9, key_0, key_minus, key_equal,
     key_backspace},

    // QWERTY row
    {key_tab, key_q, key_w, key_e, key_r, key_t_, key_y, key_u, key_i, key_o, key_p, key_left_bracket,
     key_right_bracket, key_backslash},

    // Home row
    {key_caps, key_a, key_s, key_d, key_f, key_g, key_h, key_j, key_k, key_l, key_semicolon, key_apostrophe, key_enter},

    // Bottom row
    {key_lshift, key_z, key_x, key_c, key_v, key_b, key_n, key_m, key_comma, key_period, key_slash, key_rshift},

    // Modifier / space row
    {key_lctrl, key_special, key_lalt, key_space, key_ralt, key_fn, key_menu, key_rctrl}};

std::unordered_map<std::string, EKey> keyboard_key_str_to_key_enum = {

    {key_esc, EKey::ESCAPE},
    {key_f1, EKey::F1},
    {key_f2, EKey::F2},
    {key_f3, EKey::F3},
    {key_f4, EKey::F4},
    {key_f5, EKey::F5},
    {key_f6, EKey::F6},
    {key_f7, EKey::F7},
    {key_f8, EKey::F8},
    {key_f9, EKey::F9},
    {key_f10, EKey::F10},
    {key_f11, EKey::F11},
    {key_f12, EKey::F12},

    {key_grave, EKey::GRAVE_ACCENT},
    {key_1, EKey::ONE},
    {key_2, EKey::TWO},
    {key_3, EKey::THREE},
    {key_4, EKey::FOUR},
    {key_5, EKey::FIVE},
    {key_6, EKey::SIX},
    {key_7, EKey::SEVEN},
    {key_8, EKey::EIGHT},
    {key_9, EKey::NINE},
    {key_0, EKey::ZERO},
    {key_minus, EKey::MINUS},
    {key_equal, EKey::EQUAL},
    {key_backspace, EKey::BACKSPACE},

    {key_tab, EKey::TAB},
    {key_q, EKey::q},
    {key_w, EKey::w},
    {key_e, EKey::e},
    {key_r, EKey::r},
    {key_t_, EKey::t},
    {key_y, EKey::y},
    {key_u, EKey::u},
    {key_i, EKey::i},
    {key_o, EKey::o},
    {key_p, EKey::p},
    {key_left_bracket, EKey::LEFT_SQUARE_BRACKET},
    {key_right_bracket, EKey::RIGHT_SQUARE_BRACKET},
    {key_backslash, EKey::BACKSLASH},

    {key_caps, EKey::CAPS_LOCK},
    {key_a, EKey::a},
    {key_s, EKey::s},
    {key_d, EKey::d},
    {key_f, EKey::f},
    {key_g, EKey::g},
    {key_h, EKey::h},
    {key_j, EKey::j},
    {key_k, EKey::k},
    {key_l, EKey::l},
    {key_semicolon, EKey::SEMICOLON},
    {key_apostrophe, EKey::SINGLE_QUOTE},
    {key_enter, EKey::ENTER},

    {key_lshift, EKey::LEFT_SHIFT},
    {key_z, EKey::z},
    {key_x, EKey::x},
    {key_c, EKey::c},
    {key_v, EKey::v},
    {key_b, EKey::b},
    {key_n, EKey::n},
    {key_m, EKey::m},
    {key_comma, EKey::COMMA},
    {key_period, EKey::PERIOD},
    {key_slash, EKey::SLASH},
    {key_rshift, EKey::RIGHT_SHIFT},

    {key_lctrl, EKey::LEFT_CONTROL},
    {key_special, EKey::LEFT_SUPER},
    {key_lalt, EKey::LEFT_ALT},
    {key_space, EKey::SPACE},
    {key_ralt, EKey::RIGHT_ALT},
    {key_fn, EKey::FUNCTION_KEY},
    {key_menu, EKey::MENU_KEY},
    {key_rctrl, EKey::RIGHT_CONTROL}};

std::string InputState::get_visual_keyboard_state() {
    std::stringstream state_stream;

    // create a copy of the keyboard to modify without changing the original one
    auto modified_keyboard = keyboard;

    for (auto &row : modified_keyboard) {
        for (auto &key : row) {
            // check if the key has a corresponding enum value
            auto key_enum_iter = keyboard_key_str_to_key_enum.find(key);
            if (key_enum_iter != keyboard_key_str_to_key_enum.end()) {
                EKey key_enum = key_enum_iter->second;

                // if the key is just pressed, replace with the correct number of x's
                if (is_just_pressed(key_enum)) {
                    key = std::string(key.size(), '*'); // replace with *'s of the same length
                }
                if (is_held(key_enum)) {
                    key = std::string(key.size(), 'X'); // replace with X's of the same length
                }
            }
        }
    }

    state_stream << "-------------------------------------------------------------" << std::endl;
    for (const auto &row : modified_keyboard) {
        for (const auto &key : row) {
            // Ensure alignment of output
            state_stream << "|" << key;
        }
        state_stream << "|" << std::endl;
    }
    state_stream << "-------------------------------------------------------------" << std::endl;

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
    all_keys.emplace_back(EKey::F1, KeyType::CONTROL, "f1", true);
    all_keys.emplace_back(EKey::F2, KeyType::CONTROL, "f2", true);
    all_keys.emplace_back(EKey::F3, KeyType::CONTROL, "f3", true);
    all_keys.emplace_back(EKey::F4, KeyType::CONTROL, "f4", true);
    all_keys.emplace_back(EKey::F5, KeyType::CONTROL, "f5", true);
    all_keys.emplace_back(EKey::F6, KeyType::CONTROL, "f6", true);
    all_keys.emplace_back(EKey::F7, KeyType::CONTROL, "f7", true);
    all_keys.emplace_back(EKey::F8, KeyType::CONTROL, "f8", true);
    all_keys.emplace_back(EKey::F9, KeyType::CONTROL, "f9", true);
    all_keys.emplace_back(EKey::F10, KeyType::CONTROL, "f10", true);
    all_keys.emplace_back(EKey::F11, KeyType::CONTROL, "f11", true);
    all_keys.emplace_back(EKey::F12, KeyType::CONTROL, "f12", true);
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
