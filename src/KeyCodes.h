#pragma once
/// <KNIGHT KEYCODES BUT THESE ARE BASED ON SDL KEYCODES ,THIS IS TAKEN FROM SDL3, SDL3 KEYCODES>///



#define KnightK_EXTENDED_MASK          (1u << 29)
#define KnightK_SCANCODE_MASK          (1u << 30)
#define Knight_SCANCODE_TO_KEYCODE(X)  (X | KnightK_SCANCODE_MASK)
#define KnightK_UNKNOWN                0x00000000u /**< 0 */
#define KnightK_RETURN                 0x0000000du /**< '\r' */
#define KnightK_ESCAPE                 0x0000001bu /**< '\x1B' */
#define KnightK_BACKSPACE              0x00000008u /**< '\b' */
#define KnightK_TAB                    0x00000009u /**< '\t' */
#define KnightK_SPACE                  0x00000020u /**< ' ' */
#define KnightK_EXCLAIM                0x00000021u /**< '!' */
#define KnightK_DBLAPOSTROPHE          0x00000022u /**< '"' */
#define KnightK_HASH                   0x00000023u /**< '#' */
#define KnightK_DOLLAR                 0x00000024u /**< '$' */
#define KnightK_PERCENT                0x00000025u /**< '%' */
#define KnightK_AMPERSAND              0x00000026u /**< '&' */
#define KnightK_APOSTROPHE             0x00000027u /**< '\'' */
#define KnightK_LEFTPAREN              0x00000028u /**< '(' */
#define KnightK_RIGHTPAREN             0x00000029u /**< ')' */
#define KnightK_ASTERISK               0x0000002au /**< '*' */
#define KnightK_PLUS                   0x0000002bu /**< '+' */
#define KnightK_COMMA                  0x0000002cu /**< ',' */
#define KnightK_MINUS                  0x0000002du /**< '-' */
#define KnightK_PERIOD                 0x0000002eu /**< '.' */
#define KnightK_SLASH                  0x0000002fu /**< '/' */
#define KnightK_0                      0x00000030u /**< '0' */
#define KnightK_1                      0x00000031u /**< '1' */
#define KnightK_2                      0x00000032u /**< '2' */
#define KnightK_3                      0x00000033u /**< '3' */
#define KnightK_4                      0x00000034u /**< '4' */
#define KnightK_5                      0x00000035u /**< '5' */
#define KnightK_6                      0x00000036u /**< '6' */
#define KnightK_7                      0x00000037u /**< '7' */
#define KnightK_8                      0x00000038u /**< '8' */
#define KnightK_9                      0x00000039u /**< '9' */
#define KnightK_COLON                  0x0000003au /**< ':' */
#define KnightK_SEMICOLON              0x0000003bu /**< ';' */
#define KnightK_LESS                   0x0000003cu /**< '<' */
#define KnightK_EQUALS                 0x0000003du /**< '=' */
#define KnightK_GREATER                0x0000003eu /**< '>' */
#define KnightK_QUESTION               0x0000003fu /**< '?' */
#define KnightK_AT                     0x00000040u /**< '@' */
#define KnightK_LEFTBRACKET            0x0000005bu /**< '[' */
#define KnightK_BACKSLASH              0x0000005cu /**< '\\' */
#define KnightK_RIGHTBRACKET           0x0000005du /**< ']' */
#define KnightK_CARET                  0x0000005eu /**< '^' */
#define KnightK_UNDERSCORE             0x0000005fu /**< '_' */
#define KnightK_GRAVE                  0x00000060u /**< '`' */
#define KnightK_A                      0x00000061u /**< 'a' */
#define KnightK_B                      0x00000062u /**< 'b' */
#define KnightK_C                      0x00000063u /**< 'c' */
#define KnightK_D                      0x00000064u /**< 'd' */
#define KnightK_E                      0x00000065u /**< 'e' */
#define KnightK_F                      0x00000066u /**< 'f' */
#define KnightK_G                      0x00000067u /**< 'g' */
#define KnightK_H                      0x00000068u /**< 'h' */
#define KnightK_I                      0x00000069u /**< 'i' */
#define KnightK_J                      0x0000006au /**< 'j' */
#define KnightK_K                      0x0000006bu /**< 'k' */
#define KnightK_L                      0x0000006cu /**< 'l' */
#define KnightK_M                      0x0000006du /**< 'm' */
#define KnightK_N                      0x0000006eu /**< 'n' */
#define KnightK_O                      0x0000006fu /**< 'o' */
#define KnightK_P                      0x00000070u /**< 'p' */
#define KnightK_Q                      0x00000071u /**< 'q' */
#define KnightK_R                      0x00000072u /**< 'r' */
#define KnightK_S                      0x00000073u /**< 's' */
#define KnightK_T                      0x00000074u /**< 't' */
#define KnightK_U                      0x00000075u /**< 'u' */
#define KnightK_V                      0x00000076u /**< 'v' */
#define KnightK_W                      0x00000077u /**< 'w' */
#define KnightK_X                      0x00000078u /**< 'x' */
#define KnightK_Y                      0x00000079u /**< 'y' */
#define KnightK_Z                      0x0000007au /**< 'z' */
#define KnightK_LEFTBRACE              0x0000007bu /**< '{' */
#define KnightK_PIPE                   0x0000007cu /**< '|' */
#define KnightK_RIGHTBRACE             0x0000007du /**< '}' */
#define KnightK_TILDE                  0x0000007eu /**< '~' */
#define KnightK_DELETE                 0x0000007fu /**< '\x7F' */
#define KnightK_PLUSMINUS              0x000000b1u /**< '\xB1' */
#define KnightK_CAPSLOCK               0x40000039u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_CAPSLOCK) */
#define KnightK_F1                     0x4000003au /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_F1) */
#define KnightK_F2                     0x4000003bu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_F2) */
#define KnightK_F3                     0x4000003cu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_F3) */
#define KnightK_F4                     0x4000003du /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_F4) */
#define KnightK_F5                     0x4000003eu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_F5) */
#define KnightK_F6                     0x4000003fu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_F6) */
#define KnightK_F7                     0x40000040u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_F7) */
#define KnightK_F8                     0x40000041u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_F8) */
#define KnightK_F9                     0x40000042u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_F9) */
#define KnightK_F10                    0x40000043u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_F10) */
#define KnightK_F11                    0x40000044u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_F11) */
#define KnightK_F12                    0x40000045u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_F12) */
#define KnightK_PRINTSCREEN            0x40000046u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_PRINTSCREEN) */
#define KnightK_SCROLLLOCK             0x40000047u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_SCROLLLOCK) */
#define KnightK_PAUSE                  0x40000048u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_PAUSE) */
#define KnightK_INSERT                 0x40000049u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_INSERT) */
#define KnightK_HOME                   0x4000004au /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_HOME) */
#define KnightK_PAGEUP                 0x4000004bu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_PAGEUP) */
#define KnightK_END                    0x4000004du /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_END) */
#define KnightK_PAGEDOWN               0x4000004eu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_PAGEDOWN) */
#define KnightK_RIGHT                  0x4000004fu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_RIGHT) */
#define KnightK_LEFT                   0x40000050u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_LEFT) */
#define KnightK_DOWN                   0x40000051u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_DOWN) */
#define KnightK_UP                     0x40000052u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_UP) */
#define KnightK_NUMLOCKCLEAR           0x40000053u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_NUMLOCKCLEAR) */
#define KnightK_KP_DIVIDE              0x40000054u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_DIVIDE) */
#define KnightK_KP_MULTIPLY            0x40000055u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_MULTIPLY) */
#define KnightK_KP_MINUS               0x40000056u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_MINUS) */
#define KnightK_KP_PLUS                0x40000057u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_PLUS) */
#define KnightK_KP_ENTER               0x40000058u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_ENTER) */
#define KnightK_KP_1                   0x40000059u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_1) */
#define KnightK_KP_2                   0x4000005au /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_2) */
#define KnightK_KP_3                   0x4000005bu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_3) */
#define KnightK_KP_4                   0x4000005cu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_4) */
#define KnightK_KP_5                   0x4000005du /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_5) */
#define KnightK_KP_6                   0x4000005eu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_6) */
#define KnightK_KP_7                   0x4000005fu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_7) */
#define KnightK_KP_8                   0x40000060u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_8) */
#define KnightK_KP_9                   0x40000061u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_9) */
#define KnightK_KP_0                   0x40000062u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_0) */
#define KnightK_KP_PERIOD              0x40000063u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_PERIOD) */
#define KnightK_APPLICATION            0x40000065u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_APPLICATION) */
#define KnightK_POWER                  0x40000066u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_POWER) */
#define KnightK_KP_EQUALS              0x40000067u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_EQUALS) */
#define KnightK_F13                    0x40000068u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_F13) */
#define KnightK_F14                    0x40000069u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_F14) */
#define KnightK_F15                    0x4000006au /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_F15) */
#define KnightK_F16                    0x4000006bu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_F16) */
#define KnightK_F17                    0x4000006cu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_F17) */
#define KnightK_F18                    0x4000006du /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_F18) */
#define KnightK_F19                    0x4000006eu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_F19) */
#define KnightK_F20                    0x4000006fu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_F20) */
#define KnightK_F21                    0x40000070u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_F21) */
#define KnightK_F22                    0x40000071u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_F22) */
#define KnightK_F23                    0x40000072u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_F23) */
#define KnightK_F24                    0x40000073u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_F24) */
#define KnightK_EXECUTE                0x40000074u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_EXECUTE) */
#define KnightK_HELP                   0x40000075u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_HELP) */
#define KnightK_MENU                   0x40000076u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_MENU) */
#define KnightK_SELECT                 0x40000077u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_SELECT) */
#define KnightK_STOP                   0x40000078u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_STOP) */
#define KnightK_AGAIN                  0x40000079u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_AGAIN) */
#define KnightK_UNDO                   0x4000007au /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_UNDO) */
#define KnightK_CUT                    0x4000007bu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_CUT) */
#define KnightK_COPY                   0x4000007cu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_COPY) */
#define KnightK_PASTE                  0x4000007du /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_PASTE) */
#define KnightK_FIND                   0x4000007eu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_FIND) */
#define KnightK_MUTE                   0x4000007fu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_MUTE) */
#define KnightK_VOLUMEUP               0x40000080u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_VOLUMEUP) */
#define KnightK_VOLUMEDOWN             0x40000081u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_VOLUMEDOWN) */
#define KnightK_KP_COMMA               0x40000085u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_COMMA) */
#define KnightK_KP_EQUALSAS400         0x40000086u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_EQUALSAS400) */
#define KnightK_ALTERASE               0x40000099u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_ALTERASE) */
#define KnightK_SYSREQ                 0x4000009au /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_SYSREQ) */
#define KnightK_CANCEL                 0x4000009bu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_CANCEL) */
#define KnightK_CLEAR                  0x4000009cu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_CLEAR) */
#define KnightK_PRIOR                  0x4000009du /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_PRIOR) */
#define KnightK_RETURN2                0x4000009eu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_RETURN2) */
#define KnightK_SEPARATOR              0x4000009fu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_SEPARATOR) */
#define KnightK_OUT                    0x400000a0u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_OUT) */
#define KnightK_OPER                   0x400000a1u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_OPER) */
#define KnightK_CLEARAGAIN             0x400000a2u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_CLEARAGAIN) */
#define KnightK_CRSEL                  0x400000a3u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_CRSEL) */
#define KnightK_EXSEL                  0x400000a4u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_EXSEL) */
#define KnightK_KP_00                  0x400000b0u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_00) */
#define KnightK_KP_000                 0x400000b1u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_000) */
#define KnightK_THOUSANDSSEPARATOR     0x400000b2u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_THOUSANDSSEPARATOR) */
#define KnightK_DECIMALSEPARATOR       0x400000b3u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_DECIMALSEPARATOR) */
#define KnightK_CURRENCYUNIT           0x400000b4u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_CURRENCYUNIT) */
#define KnightK_CURRENCYSUBUNIT        0x400000b5u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_CURRENCYSUBUNIT) */
#define KnightK_KP_LEFTPAREN           0x400000b6u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_LEFTPAREN) */
#define KnightK_KP_RIGHTPAREN          0x400000b7u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_RIGHTPAREN) */
#define KnightK_KP_LEFTBRACE           0x400000b8u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_LEFTBRACE) */
#define KnightK_KP_RIGHTBRACE          0x400000b9u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_RIGHTBRACE) */
#define KnightK_KP_TAB                 0x400000bau /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_TAB) */
#define KnightK_KP_BACKSPACE           0x400000bbu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_BACKSPACE) */
#define KnightK_KP_A                   0x400000bcu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_A) */
#define KnightK_KP_B                   0x400000bdu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_B) */
#define KnightK_KP_C                   0x400000beu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_C) */
#define KnightK_KP_D                   0x400000bfu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_D) */
#define KnightK_KP_E                   0x400000c0u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_E) */
#define KnightK_KP_F                   0x400000c1u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_F) */
#define KnightK_KP_XOR                 0x400000c2u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_XOR) */
#define KnightK_KP_POWER               0x400000c3u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_POWER) */
#define KnightK_KP_PERCENT             0x400000c4u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_PERCENT) */
#define KnightK_KP_LESS                0x400000c5u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_LESS) */
#define KnightK_KP_GREATER             0x400000c6u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_GREATER) */
#define KnightK_KP_AMPERSAND           0x400000c7u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_AMPERSAND) */
#define KnightK_KP_DBLAMPERSAND        0x400000c8u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_DBLAMPERSAND) */
#define KnightK_KP_VERTICALBAR         0x400000c9u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_VERTICALBAR) */
#define KnightK_KP_DBLVERTICALBAR      0x400000cau /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_DBLVERTICALBAR) */
#define KnightK_KP_COLON               0x400000cbu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_COLON) */
#define KnightK_KP_HASH                0x400000ccu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_HASH) */
#define KnightK_KP_SPACE               0x400000cdu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_SPACE) */
#define KnightK_KP_AT                  0x400000ceu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_AT) */
#define KnightK_KP_EXCLAM              0x400000cfu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_EXCLAM) */
#define KnightK_KP_MEMSTORE            0x400000d0u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_MEMSTORE) */
#define KnightK_KP_MEMRECALL           0x400000d1u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_MEMRECALL) */
#define KnightK_KP_MEMCLEAR            0x400000d2u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_MEMCLEAR) */
#define KnightK_KP_MEMADD              0x400000d3u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_MEMADD) */
#define KnightK_KP_MEMSUBTRACT         0x400000d4u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_MEMSUBTRACT) */
#define KnightK_KP_MEMMULTIPLY         0x400000d5u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_MEMMULTIPLY) */
#define KnightK_KP_MEMDIVIDE           0x400000d6u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_MEMDIVIDE) */
#define KnightK_KP_PLUSMINUS           0x400000d7u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_PLUSMINUS) */
#define KnightK_KP_CLEAR               0x400000d8u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_CLEAR) */
#define KnightK_KP_CLEARENTRY          0x400000d9u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_CLEARENTRY) */
#define KnightK_KP_BINARY              0x400000dau /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_BINARY) */
#define KnightK_KP_OCTAL               0x400000dbu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_OCTAL) */
#define KnightK_KP_DECIMAL             0x400000dcu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_DECIMAL) */
#define KnightK_KP_HEXADECIMAL         0x400000ddu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_KP_HEXADECIMAL) */
#define KnightK_LCTRL                  0x400000e0u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_LCTRL) */
#define KnightK_LSHIFT                 0x400000e1u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_LSHIFT) */
#define KnightK_LALT                   0x400000e2u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_LALT) */
#define KnightK_LGUI                   0x400000e3u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_LGUI) */
#define KnightK_RCTRL                  0x400000e4u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_RCTRL) */
#define KnightK_RSHIFT                 0x400000e5u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_RSHIFT) */
#define KnightK_RALT                   0x400000e6u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_RALT) */
#define KnightK_RGUI                   0x400000e7u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_RGUI) */
#define KnightK_MODE                   0x40000101u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_MODE) */
#define KnightK_SLEEP                  0x40000102u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_SLEEP) */
#define KnightK_WAKE                   0x40000103u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_WAKE) */
#define KnightK_CHANNEL_INCREMENT      0x40000104u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_CHANNEL_INCREMENT) */
#define KnightK_CHANNEL_DECREMENT      0x40000105u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_CHANNEL_DECREMENT) */
#define KnightK_MEDIA_PLAY             0x40000106u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_MEDIA_PLAY) */
#define KnightK_MEDIA_PAUSE            0x40000107u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_MEDIA_PAUSE) */
#define KnightK_MEDIA_RECORD           0x40000108u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_MEDIA_RECORD) */
#define KnightK_MEDIA_FAST_FORWARD     0x40000109u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_MEDIA_FAST_FORWARD) */
#define KnightK_MEDIA_REWIND           0x4000010au /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_MEDIA_REWIND) */
#define KnightK_MEDIA_NEXT_TRACK       0x4000010bu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_MEDIA_NEXT_TRACK) */
#define KnightK_MEDIA_PREVIOUS_TRACK   0x4000010cu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_MEDIA_PREVIOUS_TRACK) */
#define KnightK_MEDIA_STOP             0x4000010du /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_MEDIA_STOP) */
#define KnightK_MEDIA_EJECT            0x4000010eu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_MEDIA_EJECT) */
#define KnightK_MEDIA_PLAY_PAUSE       0x4000010fu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_MEDIA_PLAY_PAUSE) */
#define KnightK_MEDIA_SELECT           0x40000110u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_MEDIA_SELECT) */
#define KnightK_AC_NEW                 0x40000111u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_AC_NEW) */
#define KnightK_AC_OPEN                0x40000112u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_AC_OPEN) */
#define KnightK_AC_CLOSE               0x40000113u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_AC_CLOSE) */
#define KnightK_AC_EXIT                0x40000114u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_AC_EXIT) */
#define KnightK_AC_SAVE                0x40000115u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_AC_SAVE) */
#define KnightK_AC_PRINT               0x40000116u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_AC_PRINT) */
#define KnightK_AC_PROPERTIES          0x40000117u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_AC_PROPERTIES) */
#define KnightK_AC_SEARCH              0x40000118u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_AC_SEARCH) */
#define KnightK_AC_HOME                0x40000119u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_AC_HOME) */
#define KnightK_AC_BACK                0x4000011au /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_AC_BACK) */
#define KnightK_AC_FORWARD             0x4000011bu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_AC_FORWARD) */
#define KnightK_AC_STOP                0x4000011cu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_AC_STOP) */
#define KnightK_AC_REFRESH             0x4000011du /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_AC_REFRESH) */
#define KnightK_AC_BOOKMARKS           0x4000011eu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_AC_BOOKMARKS) */
#define KnightK_SOFTLEFT               0x4000011fu /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_SOFTLEFT) */
#define KnightK_SOFTRIGHT              0x40000120u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_SOFTRIGHT) */
#define KnightK_CALL                   0x40000121u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_CALL) */
#define KnightK_ENDCALL                0x40000122u /**< Knight_SCANCODE_TO_KEYCODE(Knight_SCANCODE_ENDCALL) */
#define KnightK_LEFT_TAB               0x20000001u /**< Extended key Left Tab */
#define KnightK_LEVEL5_SHIFT           0x20000002u /**< Extended key Level 5 Shift */
#define KnightK_MULTI_KEY_COMPOSE      0x20000003u /**< Extended key Multi-key Compose */
#define KnightK_LMETA                  0x20000004u /**< Extended key Left Meta */
#define KnightK_RMETA                  0x20000005u /**< Extended key Right Meta */
#define KnightK_LHYPER                 0x20000006u /**< Extended key Left Hyper */
#define KnightK_RHYPER                 0x20000007u /**< Extended key Right Hyper */

/**
 * Valid key modifiers (possibly OR'd together).
 *
 * \since This datatype is available since Knight 3.2.0.
 */


#define Knight_KMOD_NONE   0x0000u /**< no modifier is applicable. */
#define Knight_KMOD_LSHIFT 0x0001u /**< the left Shift key is down. */
#define Knight_KMOD_RSHIFT 0x0002u /**< the right Shift key is down. */
#define Knight_KMOD_LEVEL5 0x0004u /**< the Level 5 Shift key is down. */
#define Knight_KMOD_LCTRL  0x0040u /**< the left Ctrl (Control) key is down. */
#define Knight_KMOD_RCTRL  0x0080u /**< the right Ctrl (Control) key is down. */
#define Knight_KMOD_LALT   0x0100u /**< the left Alt key is down. */
#define Knight_KMOD_RALT   0x0200u /**< the right Alt key is down. */
#define Knight_KMOD_LGUI   0x0400u /**< the left GUI key (often the Windows key) is down. */
#define Knight_KMOD_RGUI   0x0800u /**< the right GUI key (often the Windows key) is down. */
#define Knight_KMOD_NUM    0x1000u /**< the Num Lock key (may be located on an extended keypad) is down. */
#define Knight_KMOD_CAPS   0x2000u /**< the Caps Lock key is down. */
#define Knight_KMOD_MODE   0x4000u /**< the !AltGr key is down. */
#define Knight_KMOD_SCROLL 0x8000u /**< the Scroll Lock key is down. */
#define Knight_KMOD_CTRL   (Knight_KMOD_LCTRL | Knight_KMOD_RCTRL)   /**< Any Ctrl key is down. */
#define Knight_KMOD_SHIFT  (Knight_KMOD_LSHIFT | Knight_KMOD_RSHIFT) /**< Any Shift key is down. */
#define Knight_KMOD_ALT    (Knight_KMOD_LALT | Knight_KMOD_RALT)     /**< Any Alt key is down. */
#define Knight_KMOD_GUI    (Knight_KMOD_LGUI | Knight_KMOD_RGUI)     /**< Any GUI key is down. */

