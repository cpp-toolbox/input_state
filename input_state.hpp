#ifndef INPUT_STATE
#define INPUT_STATE

#include <string>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include "sbpt_generated_includes.hpp"

enum class KeyType {
    ALPHA,
    NUMERIC,
    MODIFIER,
    CONTROL,
    SYMBOL,
    MOUSE,
};

enum class EKey {
    a,
    b,
    c,
    d,
    e,
    f,
    g,
    h,
    i,
    j,
    k,
    l,
    m,
    n,
    o,
    p,
    q,
    r,
    s,
    t,
    u,
    v,
    w,
    x,
    y,
    z,

    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,

    SPACE,
    GRAVE_ACCENT,
    TILDE,

    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    ZERO,
    MINUS,
    EQUAL,

    EXCLAMATION_POINT,
    AT_SIGN,
    NUMBER_SIGN,
    DOLLAR_SIGN,
    PERCENT_SIGN,
    CARET,
    AMPERSAND,
    ASTERISK,
    LEFT_PARENTHESIS,
    RIGHT_PARENTHESIS,
    UNDERSCORE,
    PLUS,

    LEFT_SQUARE_BRACKET,
    RIGHT_SQUARE_BRACKET,

    LEFT_CURLY_BRACKET,
    RIGHT_CURLY_BRACKET,

    COMMA,
    PERIOD,
    LESS_THAN,
    GREATER_THAN,

    CAPS_LOCK,
    ESCAPE,
    ENTER,
    TAB,
    BACKSPACE,
    INSERT,

    // on windows DELETE is a macro in winnt.h so we must dodge this
    DELETE_,

    RIGHT,
    LEFT,
    UP,
    DOWN,

    SLASH,
    QUESTION_MARK,
    BACKSLASH,
    PIPE,
    COLON,
    SEMICOLON,
    SINGLE_QUOTE,
    DOUBLE_QUOTE,

    LEFT_SHIFT,
    RIGHT_SHIFT,
    LEFT_CONTROL,
    RIGHT_CONTROL,
    LEFT_ALT,
    RIGHT_ALT,
    LEFT_SUPER,
    RIGHT_SUPER,

    FUNCTION_KEY,
    MENU_KEY,

    LEFT_MOUSE_BUTTON,
    RIGHT_MOUSE_BUTTON,
    MIDDLE_MOUSE_BUTTON,
    SCROLL_UP,
    SCROLL_DOWN,

    // the dummy is used as the "biggest value" so that we can iterate through this.
    DUMMY
};

class Key {
  public:
    EKey key_enum;
    KeyType key_type;
    std::string string_repr;
    bool requires_modifer_to_be_typed;
    bool shiftable;
    EKey key_enum_of_shifted_version;
    // TODO: can we get rid of this?
    TemporalBinarySignal pressed_signal;

    Key(EKey e, KeyType t, std::string repr, bool requires_mod = true, bool shift = false, EKey shifted = EKey::DUMMY)
        : key_enum(e), key_type(t), string_repr(std::move(repr)), requires_modifer_to_be_typed(requires_mod),
          shiftable(shift), key_enum_of_shifted_version(shifted) {}

    Key() = default; // still allow default construction if needed
};
/**
 * @brief Represents the full state of keyboard and mouse input.
 *
 * This class provides a convenient way to query the entire keyboard and mouse state in a single location. It tracks
 * mouse position, mouse movement deltas, key presses, and key states.
 *
 * @note this class is agnostic of the input system you use
 *
 */
class InputState {
  public:
    InputState();
    ~InputState() = default;

    // NOTE: temporarily puttings these here for simplicity
    double mouse_position_x = 0, mouse_position_y = 0;
    double prev_mouse_position_x = 0, prev_mouse_position_y = 0;
    double mouse_delta_x = 0, mouse_delta_y = 0;

    std::tuple<double, double> get_mouse_delta() {
        std::tuple<double, double> tup = {mouse_delta_x, mouse_delta_y};
        // reset once read
        // TODO: a class with data that can only be used once or something.
        mouse_delta_x = 0;
        mouse_delta_y = 0;
        return tup;
    }

    bool is_just_pressed(EKey key_enum);
    bool is_pressed(EKey key_enum);

    std::vector<std::string> get_just_pressed_key_strings();

    std::string get_string_state();
    std::vector<std::string> get_keys_just_pressed_this_tick();

    // TODO: this shouldn't be a member function, it's a static function
    bool is_valid_key_string(const std::string &key_str) const;

    // TODO: same here.
    std::vector<Key> all_keys;
    std::set<int> glfw_keycodes;
    // pointers to the keys in all_keys
    // TODO: make this hold a reference wrapper instead of a raw pointer when we have time
    std::unordered_map<EKey, Key *> key_enum_to_object;
    std::unordered_map<std::string, EKey> key_str_to_key_enum;
};

#endif // INPUT_STATE
