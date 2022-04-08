#include "KeyCode.h"

#define NO_CHARACTER '\0'

KeyCode::KeyCode(unsigned int index, unsigned char ascii, const char* name, unsigned int keycodeType) : _index(index), _ascii(ascii), _name(name), _keycodeType(keycodeType)
{

}

unsigned int KeyCode::getIndex() const
{
	return this->_index;
}

unsigned char KeyCode::asASCII() const
{
	if(!this->isASCII())
	{
		return '?';
	}
	return this->_ascii;
}

bool KeyCode::isASCII() const
{
	return this->_ascii != NO_CHARACTER;
}

const char* KeyCode::getName() const
{
	return this->_name;
}

bool KeyCode::isKeyCodeType(KeyCodeType type) const
{
	return (this->_keycodeType & static_cast<unsigned char>(type)) != 0;
}

bool KeyCode::operator==(const KeyCode& rhs) const
{
	return _index == rhs._index;
}

bool KeyCode::operator!=(const KeyCode& rhs) const
{
	return !(rhs == *this);
}

#define ASSIGN_KEYCODE(staticName, index, ascii, name, keycodeType) const KeyCode KeyCode::staticName(index, ascii, name, keycodeType);

ASSIGN_KEYCODE(ESCAPE, 0, NO_CHARACTER, "Escape", KeyCodeType::NO_TYPE)
ASSIGN_KEYCODE(ONE, 1, '1', "One", KeyCodeType::DIGIT)
ASSIGN_KEYCODE(EXCLAMATION_MARK, 2, '!', "Exclamation Mark", KeyCodeType::SYMBOL)
ASSIGN_KEYCODE(TWO, 3, '2', "Two", KeyCodeType::DIGIT)
ASSIGN_KEYCODE(AT, 4, '@', "At", KeyCodeType::SYMBOL)
ASSIGN_KEYCODE(THREE, 5, '3', "Three", KeyCodeType::DIGIT)
ASSIGN_KEYCODE(HASHTAG, 6, '#', "Hashtag", KeyCodeType::SYMBOL)
ASSIGN_KEYCODE(FOUR, 7, '4', "Four", KeyCodeType::DIGIT)
ASSIGN_KEYCODE(DOLLAR_SIGN, 8, '$', "Dollar Sign", KeyCodeType::SYMBOL)
ASSIGN_KEYCODE(FIVE, 9, '5', "Five", KeyCodeType::DIGIT)
ASSIGN_KEYCODE(PERCENT_SIGN, 10, '%', "Percent Sign", KeyCodeType::SYMBOL)
ASSIGN_KEYCODE(SIX, 11, '6', "Six", KeyCodeType::DIGIT)
ASSIGN_KEYCODE(CARET, 12, '^', "Caret", KeyCodeType::SYMBOL)
ASSIGN_KEYCODE(SEVEN, 13, '7', "Seven", KeyCodeType::DIGIT)
ASSIGN_KEYCODE(AMPERSAND, 14, '&', "Ampersand", KeyCodeType::SYMBOL)
ASSIGN_KEYCODE(EIGHT, 15, '8', "Eight", KeyCodeType::DIGIT)
ASSIGN_KEYCODE(ASTERISK, 16, '*', "Asterisk", KeyCodeType::SYMBOL)
ASSIGN_KEYCODE(NINE, 17, '9', "Nine", KeyCodeType::DIGIT)
ASSIGN_KEYCODE(OPEN_BRACKET, 18, '(', "Open Bracket", KeyCodeType::SYMBOL)
ASSIGN_KEYCODE(ZERO, 19, '0', "Zero", KeyCodeType::DIGIT)
ASSIGN_KEYCODE(CLOSE_BRACKET, 20, ')', "Close Bracket", KeyCodeType::SYMBOL)
ASSIGN_KEYCODE(MINUS, 21, '-', "Minus", KeyCodeType::SYMBOL)
ASSIGN_KEYCODE(UNDERSCORE, 22, '_', "Underscore", KeyCodeType::SYMBOL)
ASSIGN_KEYCODE(EQUAL_SIGN, 23, '=', "Equal Sign", KeyCodeType::SYMBOL)
ASSIGN_KEYCODE(PLUS, 24, '+', "Plus", KeyCodeType::SYMBOL)
ASSIGN_KEYCODE(BACKSPACE, 25, NO_CHARACTER, "Backspace", KeyCodeType::NO_TYPE)
ASSIGN_KEYCODE(TAB, 26, '\t', "Tab", KeyCodeType::WHITESPACE)

#define ASSIGN_LETTER(lowercase, uppercase, index) ASSIGN_KEYCODE(uppercase, index, #uppercase[0], #uppercase, KeyCodeType::LETTER) ASSIGN_KEYCODE(lowercase, (index) + 1, #lowercase[0], #lowercase, KeyCodeType::LETTER)

ASSIGN_LETTER(Q, q, 27)
ASSIGN_LETTER(W, w, 29)
ASSIGN_LETTER(E, e, 31)
ASSIGN_LETTER(R, r, 33)
ASSIGN_LETTER(T, t, 35)
ASSIGN_LETTER(Y, y, 37)
ASSIGN_LETTER(U, u, 39)
ASSIGN_LETTER(I, i, 41)
ASSIGN_LETTER(O, o, 43)
ASSIGN_LETTER(P, p, 45)
ASSIGN_KEYCODE(OPEN_SQUARE_BRACKET, 46, '[', "Open Square Bracket", KeyCodeType::SYMBOL)
ASSIGN_KEYCODE(OPEN_CURLEY_BRACKET, 47, '{', "Open Curley Bracket", KeyCodeType::SYMBOL)
ASSIGN_KEYCODE(CLOSE_SQUARE_BRACKET, 48, ']', "Close Square Bracket", KeyCodeType::SYMBOL)
ASSIGN_KEYCODE(CLOSE_CURLEY_BRACKET, 49, '}', "Close Curley Bracket", KeyCodeType::SYMBOL)
ASSIGN_KEYCODE(ENTER, 50, '\n', "Enter", KeyCodeType::WHITESPACE)
ASSIGN_KEYCODE(LEFT_CONTROL, 51, NO_CHARACTER, "Left Control", KeyCodeType::MODIFIER)
ASSIGN_LETTER(A, a, 52)
ASSIGN_LETTER(S, s, 54)
ASSIGN_LETTER(D, d, 56)
ASSIGN_LETTER(F, f, 58)
ASSIGN_LETTER(G, g, 60)
ASSIGN_LETTER(H, h, 62)
ASSIGN_LETTER(J, j, 64)
ASSIGN_LETTER(K, k, 66)
ASSIGN_LETTER(L, l, 68)
ASSIGN_KEYCODE(SEMICOLON, 69, ';', "Semicolon", KeyCodeType::SYMBOL)
ASSIGN_KEYCODE(COLON, 70, ':', "Colon", KeyCodeType::SYMBOL)
ASSIGN_KEYCODE(QUOTE, 71, '\'', "Quote", KeyCodeType::SYMBOL)
ASSIGN_KEYCODE(QUOTATION_MARKS, 72, '"', "Quotation Marks", KeyCodeType::SYMBOL)
ASSIGN_KEYCODE(GRAVE_ACCENT, 73, '`', "Grave Accent", KeyCodeType::SYMBOL)
ASSIGN_KEYCODE(TILDE, 74, '~', "Tilde", KeyCodeType::SYMBOL)
ASSIGN_KEYCODE(LEFT_SHIFT, 75, NO_CHARACTER, "Left Shift", KeyCodeType::MODIFIER)
ASSIGN_KEYCODE(BACKSLASH, 76, '\\', "Back Slash", KeyCodeType::SYMBOL)
ASSIGN_KEYCODE(VERTICAL_BAR, 77, '|', "Vertical Bar", KeyCodeType::SYMBOL)
ASSIGN_LETTER(Z, z, 78)
ASSIGN_LETTER(X, x, 80)
ASSIGN_LETTER(C, c, 82)
ASSIGN_LETTER(V, v, 84)
ASSIGN_LETTER(B, b, 86)
ASSIGN_LETTER(N, n, 88)
ASSIGN_LETTER(M, m, 90)
ASSIGN_KEYCODE(COMMA, 91, ',', "Comma", KeyCodeType::SYMBOL)
ASSIGN_KEYCODE(LESS_THAN, 92, '<', "Less Than", KeyCodeType::SYMBOL)
ASSIGN_KEYCODE(DOT, 93, '.', "Dot", KeyCodeType::SYMBOL)
ASSIGN_KEYCODE(GREATER_THAN, 94, '>', "Greater Than", KeyCodeType::SYMBOL)
ASSIGN_KEYCODE(SLASH, 95, '/', "Slash", KeyCodeType::SYMBOL)
ASSIGN_KEYCODE(RIGHT_SHIFT, 96, NO_CHARACTER, "Right Shift", KeyCodeType::NO_TYPE)
ASSIGN_KEYCODE(QUESTION_MARK, 97, '?', "Question Mark", KeyCodeType::SYMBOL)
ASSIGN_KEYCODE(KEYPAD, 98, NO_CHARACTER, "Keypad", KeyCodeType::KEYPAD)
ASSIGN_KEYCODE(PRINT_SCREEN, 99, NO_CHARACTER, "Print Screen", KeyCodeType::NO_TYPE)
ASSIGN_KEYCODE(LEFT_ALT, 100, NO_CHARACTER, "Left Alt", KeyCodeType::SYMBOL)
ASSIGN_KEYCODE(SPACE_BAR, 101, ' ', "Space Bar", KeyCodeType::WHITESPACE)
ASSIGN_KEYCODE(CAPS_LOCK, 102, NO_CHARACTER, "Caps Lock", KeyCodeType::NO_TYPE)

#define ASSIGN_FUNCTION(key, index) ASSIGN_KEYCODE(key, index, NO_CHARACTER, #key, KeyCodeType::FUNCTION)

ASSIGN_FUNCTION(F1, 103)
ASSIGN_FUNCTION(F2, 104)
ASSIGN_FUNCTION(F3, 105)
ASSIGN_FUNCTION(F4, 106)
ASSIGN_FUNCTION(F5, 107)
ASSIGN_FUNCTION(F6, 108)
ASSIGN_FUNCTION(F7, 109)
ASSIGN_FUNCTION(F8, 110)
ASSIGN_FUNCTION(F9, 111)
ASSIGN_FUNCTION(F10, 112)

ASSIGN_KEYCODE(NUM_LOCK, 113, NO_CHARACTER, "Num Lock", KeyCodeType::NO_TYPE)
ASSIGN_KEYCODE(SCROLL_LOCK, 114, NO_CHARACTER, "Scroll Lock", KeyCodeType::NO_TYPE)
ASSIGN_KEYCODE(KEYPAD_7, 115, '7', "Keypad 7", KeyCodeType::KEYPAD | KeyCodeType::DIGIT)
ASSIGN_KEYCODE(HOME, 116, NO_CHARACTER, "Home", KeyCodeType::NAVIGATION)
ASSIGN_KEYCODE(KEYPAD_8, 117, '8', "Keypad 8", KeyCodeType::KEYPAD | KeyCodeType::DIGIT)
ASSIGN_KEYCODE(UP, 118, NO_CHARACTER, "Up", KeyCodeType::NAVIGATION | KeyCodeType::ARROW)
ASSIGN_KEYCODE(KEYPAD_9, 119, '9', "Keypad 9", KeyCodeType::KEYPAD | KeyCodeType::DIGIT)
ASSIGN_KEYCODE(PAGE_UP, 120, NO_CHARACTER, "Page Up", KeyCodeType::NAVIGATION)
ASSIGN_KEYCODE(KEYPAD_MINUS, 121, '-', "Keypad Minus", KeyCodeType::KEYPAD | KeyCodeType::SYMBOL)
ASSIGN_KEYCODE(KEYPAD_4, 122, '4', "Keypad 4", KeyCodeType::KEYPAD | KeyCodeType::DIGIT)
ASSIGN_KEYCODE(LEFT, 123, NO_CHARACTER, "Left", KeyCodeType::NAVIGATION | KeyCodeType::ARROW)
ASSIGN_KEYCODE(KEYPAD_5, 124, '5', "Keypad 5", KeyCodeType::KEYPAD | KeyCodeType::DIGIT)
ASSIGN_KEYCODE(KEYPAD_6, 125, '6', "Keypad 6", KeyCodeType::KEYPAD | KeyCodeType::DIGIT)
ASSIGN_KEYCODE(RIGHT, 126, NO_CHARACTER, "Right", KeyCodeType::NAVIGATION | KeyCodeType::ARROW)
ASSIGN_KEYCODE(KEYPAD_PLUS, 127, '+', "Keypad Plus", KeyCodeType::KEYPAD | KeyCodeType::SYMBOL)
ASSIGN_KEYCODE(KEYPAD_1, 128, '1', "Keypad 1", KeyCodeType::KEYPAD | KeyCodeType::DIGIT)
ASSIGN_KEYCODE(END, 129, NO_CHARACTER, "End", KeyCodeType::NAVIGATION)
ASSIGN_KEYCODE(KEYPAD_2, 130, '2', "Keypad 2", KeyCodeType::KEYPAD | KeyCodeType::DIGIT)
ASSIGN_KEYCODE(DOWN, 131, NO_CHARACTER, "Down", KeyCodeType::NAVIGATION | KeyCodeType::ARROW)
ASSIGN_KEYCODE(KEYPAD_3, 132, '3', "Keypad 3", KeyCodeType::KEYPAD | KeyCodeType::DIGIT)
ASSIGN_KEYCODE(PAGE_DOWN, 133, NO_CHARACTER, "Page Down", KeyCodeType::NAVIGATION)
ASSIGN_KEYCODE(KEYPAD_0, 134, '0', "Keypad 0", KeyCodeType::KEYPAD | KeyCodeType::DIGIT)
ASSIGN_KEYCODE(INSERT, 135, NO_CHARACTER, "Insert", KeyCodeType::NO_TYPE)
ASSIGN_KEYCODE(DEL, 136, NO_CHARACTER, "Delete", KeyCodeType::NO_TYPE)

ASSIGN_KEYCODE(NO_KEY, 999, NO_CHARACTER, "No Keycode specified", KeyCodeType::NO_TYPE)