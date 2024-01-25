/*******************************************************************************
 * Size: 20 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#include "../include/font.h"

#ifndef HIGHWAY_GOTHIC
#define HIGHWAY_GOTHIC 1
#endif

#if HIGHWAY_GOTHIC

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
const uint8_t font[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xff, 0xf3, 0xc0,

    /* U+0022 "\"" */
    0xcf, 0x3c, 0xf3, 0xcc,

    /* U+0023 "#" */
    0x18, 0x83, 0x30, 0x66, 0x3f, 0xff, 0xfe, 0x63,
    0xc, 0x47, 0xfe, 0xff, 0xc6, 0x60, 0xcc, 0x11,
    0x86, 0x30,

    /* U+0024 "$" */
    0x18, 0xc, 0xf, 0xf, 0xee, 0x76, 0x3, 0x80,
    0xfc, 0x1f, 0x1, 0xc0, 0x68, 0x3e, 0x3b, 0xf8,
    0xf8, 0x30, 0x18, 0x0,

    /* U+0025 "%" */
    0x61, 0x92, 0x92, 0x64, 0x4, 0x8, 0x8, 0x10,
    0x20, 0x26, 0x49, 0x49, 0x86,

    /* U+0026 "&" */
    0x3c, 0x1f, 0x86, 0x61, 0x80, 0x70, 0xc, 0x7,
    0x83, 0xf6, 0xcf, 0x31, 0xcc, 0x71, 0xfe, 0x39,
    0xc0,

    /* U+0027 "'" */
    0xff, 0xc0,

    /* U+0028 "(" */
    0x32, 0x66, 0xcc, 0xcc, 0xcc, 0xc6, 0x62, 0x30,

    /* U+0029 ")" */
    0xc4, 0x66, 0x33, 0x33, 0x33, 0x36, 0x64, 0xc0,

    /* U+002A "*" */
    0x18, 0x18, 0x7e, 0x7e, 0x3c, 0x66, 0x24,

    /* U+002B "+" */
    0x18, 0xc, 0x6, 0x3, 0xf, 0xff, 0xfc, 0x60,
    0x30, 0x18, 0x0,

    /* U+002C "," */
    0xf6,

    /* U+002D "-" */
    0xff,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0x1, 0x80, 0x60, 0x30, 0xc, 0x6, 0x3, 0x0,
    0xc0, 0x60, 0x18, 0xc, 0x6, 0x1, 0x80, 0xc0,
    0x0,

    /* U+0030 "0" */
    0x1e, 0x1f, 0xe6, 0x1b, 0x87, 0xc0, 0xf0, 0x3c,
    0xf, 0x3, 0xc0, 0xf8, 0x76, 0x19, 0xfe, 0x1e,
    0x0,

    /* U+0031 "1" */
    0xfd, 0xb6, 0xdb, 0x6d, 0xb6,

    /* U+0032 "2" */
    0x3e, 0x3f, 0xb8, 0xe8, 0x30, 0x18, 0x3c, 0x3c,
    0x78, 0x78, 0x38, 0x38, 0x1f, 0xff, 0xf8,

    /* U+0033 "3" */
    0x1e, 0x1f, 0xc6, 0x18, 0x6, 0x7, 0x81, 0xe0,
    0x1c, 0x3, 0x0, 0xd8, 0x37, 0x19, 0xfe, 0x1e,
    0x0,

    /* U+0034 "4" */
    0x3, 0x1, 0xc0, 0xf0, 0x7c, 0x1b, 0xc, 0xc7,
    0x33, 0x8c, 0xff, 0xff, 0xf0, 0x30, 0xc, 0x3,
    0x0,

    /* U+0035 "5" */
    0x7f, 0x3f, 0x98, 0xf, 0xc7, 0xf3, 0x1c, 0x6,
    0x3, 0x1, 0x81, 0xc1, 0xcf, 0xc7, 0xc0,

    /* U+0036 "6" */
    0x0, 0x6, 0x7, 0x7, 0x7, 0x3, 0x3, 0xf9,
    0xfe, 0xe3, 0xe0, 0xf0, 0x7c, 0x77, 0xf1, 0xf0,

    /* U+0037 "7" */
    0xff, 0xff, 0xc0, 0xe0, 0x60, 0x60, 0x30, 0x38,
    0x18, 0xc, 0xe, 0x6, 0x3, 0x1, 0x80,

    /* U+0038 "8" */
    0x1c, 0x3f, 0x98, 0xcc, 0x67, 0xf3, 0xfb, 0x8f,
    0x83, 0xc1, 0xe0, 0xd8, 0xcf, 0xe3, 0xe0,

    /* U+0039 "9" */
    0x3e, 0x3f, 0xb8, 0xf8, 0x3c, 0x1f, 0x1d, 0xfe,
    0x7e, 0x3, 0x3, 0x83, 0x83, 0x81, 0x80, 0x0,

    /* U+003A ":" */
    0xf0, 0x0, 0xf0,

    /* U+003B ";" */
    0xf0, 0x0, 0xf6,

    /* U+003C "<" */
    0x0, 0x40, 0xf0, 0xf1, 0xf0, 0xe0, 0x38, 0x3,
    0xc0, 0x3c, 0x3, 0xc0, 0x10,

    /* U+003D "=" */
    0xff, 0xff, 0xc0, 0x0, 0xf, 0xff, 0xfc,

    /* U+003E ">" */
    0x80, 0x38, 0x3, 0xc0, 0x3c, 0x3, 0xc0, 0xf0,
    0xf1, 0xe0, 0xe0, 0x20, 0x0,

    /* U+003F "?" */
    0x3c, 0x7e, 0xe7, 0x43, 0x3, 0x6, 0xc, 0xc,
    0x18, 0x18, 0x0, 0x18, 0x18,

    /* U+0040 "@" */
    0xf, 0xc0, 0x7f, 0xc3, 0x83, 0x9b, 0xe7, 0xef,
    0xcf, 0x7f, 0x3d, 0x8c, 0xf6, 0x37, 0xdf, 0xf9,
    0xbd, 0xc7, 0x80, 0xf, 0xf8, 0xf, 0xc0,

    /* U+0041 "A" */
    0x6, 0x0, 0xf0, 0xf, 0x0, 0xf0, 0x1f, 0x81,
    0x98, 0x19, 0x83, 0xfc, 0x3f, 0xc3, 0xc, 0x60,
    0x66, 0x6, 0x60, 0x70,

    /* U+0042 "B" */
    0xfe, 0x7f, 0xb0, 0x78, 0x3c, 0x1f, 0xfb, 0xfd,
    0x87, 0xc1, 0xe0, 0xf0, 0xff, 0xef, 0xe0,

    /* U+0043 "C" */
    0x1e, 0x3f, 0x98, 0xfc, 0xc, 0x6, 0x3, 0x1,
    0x80, 0xc0, 0x70, 0x18, 0xef, 0xe1, 0xe0,

    /* U+0044 "D" */
    0xfc, 0x7f, 0xb0, 0xd8, 0x7c, 0x1e, 0xf, 0x7,
    0x83, 0xc1, 0xe1, 0xf0, 0xdf, 0xef, 0xc0,

    /* U+0045 "E" */
    0xff, 0x7f, 0xb0, 0x18, 0xc, 0x7, 0xe3, 0xf1,
    0x80, 0xc0, 0x60, 0x30, 0x1f, 0xff, 0xf8,

    /* U+0046 "F" */
    0xff, 0xff, 0xf0, 0x18, 0xc, 0x7, 0xe3, 0xf1,
    0x80, 0xc0, 0x60, 0x30, 0x18, 0xc, 0x0,

    /* U+0047 "G" */
    0x1e, 0x3f, 0x98, 0xdc, 0xc, 0x6, 0x3, 0x1f,
    0x8f, 0xc1, 0xf1, 0xd8, 0xcf, 0xe1, 0xe0,

    /* U+0048 "H" */
    0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1f, 0xff, 0xff,
    0x83, 0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x18,

    /* U+0049 "I" */
    0xff, 0xff, 0xff, 0xc0,

    /* U+004A "J" */
    0x1, 0x80, 0xc0, 0x60, 0x30, 0x18, 0xc, 0x6,
    0x3, 0x1, 0xb0, 0xd8, 0xef, 0xe3, 0xe0,

    /* U+004B "K" */
    0xc3, 0xe3, 0xb3, 0x9b, 0x8d, 0x87, 0xc3, 0xf1,
    0xd8, 0xce, 0x63, 0x31, 0xd8, 0x6c, 0x38,

    /* U+004C "L" */
    0xc0, 0x60, 0x30, 0x18, 0xc, 0x6, 0x3, 0x1,
    0x80, 0xc0, 0x60, 0x30, 0x1f, 0xff, 0xf8,

    /* U+004D "M" */
    0xc0, 0xf8, 0x7e, 0x1f, 0x87, 0xf3, 0xfc, 0xff,
    0xff, 0x7b, 0xde, 0xf3, 0x3c, 0xcf, 0x33, 0xc0,
    0xc0,

    /* U+004E "N" */
    0xc1, 0xf0, 0xfc, 0x7e, 0x3f, 0x9e, 0xcf, 0x77,
    0x9f, 0xc7, 0xe3, 0xf0, 0xf8, 0x7c, 0x18,

    /* U+004F "O" */
    0x1e, 0x1f, 0xe6, 0x1b, 0x87, 0xc0, 0xf0, 0x3c,
    0xf, 0x3, 0xc0, 0xf8, 0x76, 0x19, 0xfe, 0x1e,
    0x0,

    /* U+0050 "P" */
    0xfe, 0x7f, 0xb0, 0x78, 0x3c, 0x1f, 0xfb, 0xf9,
    0x80, 0xc0, 0x60, 0x30, 0x18, 0xc, 0x0,

    /* U+0051 "Q" */
    0x1e, 0x1f, 0xe6, 0x1b, 0x87, 0xc0, 0xf0, 0x3c,
    0xf, 0x3, 0xc6, 0xf9, 0xf6, 0x39, 0xfe, 0x1f,
    0x80, 0x20,

    /* U+0052 "R" */
    0xfe, 0x7f, 0xb0, 0x78, 0x3c, 0x1f, 0xfb, 0xf9,
    0x8c, 0xc7, 0x61, 0xb0, 0xd8, 0x3c, 0x18,

    /* U+0053 "S" */
    0x3c, 0x3f, 0xb9, 0xd8, 0xe, 0x3, 0xf0, 0x7c,
    0x7, 0x1, 0xa0, 0xf8, 0xef, 0xe3, 0xe0,

    /* U+0054 "T" */
    0xff, 0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    0x18, 0x18, 0x18, 0x18, 0x18,

    /* U+0055 "U" */
    0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xc1, 0xe0, 0xf8, 0xef, 0xe3, 0xe0,

    /* U+0056 "V" */
    0x60, 0xcc, 0x19, 0xc3, 0x18, 0xe3, 0x18, 0x73,
    0xe, 0xe0, 0xd8, 0x1b, 0x3, 0xe0, 0x38, 0x7,
    0x0, 0xe0,

    /* U+0057 "W" */
    0xe6, 0x36, 0x73, 0x67, 0x36, 0xf3, 0x6f, 0xf6,
    0xde, 0x7d, 0xe3, 0xde, 0x39, 0xe3, 0x8e, 0x38,
    0xe3, 0x8e, 0x30, 0xc0,

    /* U+0058 "X" */
    0xc3, 0x33, 0x99, 0x87, 0xc3, 0xc0, 0xe0, 0x60,
    0x78, 0x3c, 0x3b, 0x19, 0x9c, 0x6c, 0x30,

    /* U+0059 "Y" */
    0x60, 0x67, 0xe, 0x30, 0xc1, 0x98, 0x1f, 0x80,
    0xf0, 0xf, 0x0, 0x60, 0x6, 0x0, 0x60, 0x6,
    0x0, 0x60, 0x6, 0x0,

    /* U+005A "Z" */
    0xff, 0xff, 0xc0, 0xe0, 0xe0, 0xe0, 0x60, 0x70,
    0x70, 0x30, 0x30, 0x38, 0x1f, 0xff, 0xf8,

    /* U+005B "[" */
    0xff, 0xf1, 0x8c, 0x63, 0x18, 0xc6, 0x31, 0x8c,
    0x63, 0x18, 0xff, 0xc0,

    /* U+005C "\\" */
    0xc0, 0x18, 0x6, 0x0, 0xc0, 0x18, 0x6, 0x0,
    0xc0, 0x30, 0x6, 0x0, 0xc0, 0x30, 0x6, 0x1,
    0x80,

    /* U+005D "]" */
    0xff, 0xc6, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x31,
    0x8c, 0x63, 0xff, 0xc0,

    /* U+005E "^" */
    0x18, 0x38, 0x3c, 0x2c, 0x64, 0x46, 0xc2, 0xc3,

    /* U+005F "_" */
    0xff, 0xff, 0xff,

    /* U+0060 "`" */
    0xcc,

    /* U+0061 "a" */
    0x78, 0xfc, 0x19, 0xf7, 0xf8, 0xf1, 0xe3, 0xfe,
    0xfc,

    /* U+0062 "b" */
    0x0, 0xc0, 0xc0, 0xc0, 0xfc, 0xfe, 0xc7, 0xc3,
    0xc3, 0xc3, 0xc3, 0xc7, 0xfe, 0xfc,

    /* U+0063 "c" */
    0x3c, 0x7e, 0xe7, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7,
    0x7e, 0x3c,

    /* U+0064 "d" */
    0x0, 0x3, 0x3, 0x3, 0x3f, 0x7f, 0xe3, 0xc3,
    0xc3, 0xc3, 0xc3, 0xe3, 0x7f, 0x3f,

    /* U+0065 "e" */
    0x3c, 0x7e, 0xe6, 0xc3, 0xff, 0xff, 0xc0, 0xe2,
    0x7e, 0x3c,

    /* U+0066 "f" */
    0x3b, 0xd9, 0xff, 0xb1, 0x8c, 0x63, 0x18, 0xc6,
    0x0,

    /* U+0067 "g" */
    0x3f, 0x7f, 0xe3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe3,
    0x7f, 0x3f, 0x3, 0x7, 0xe, 0xc, 0x8,

    /* U+0068 "h" */
    0x0, 0xc0, 0xc0, 0xc0, 0xfc, 0xfe, 0xc7, 0xc3,
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,

    /* U+0069 "i" */
    0xf3, 0xff, 0xff, 0xc0,

    /* U+006A "j" */
    0x6c, 0x36, 0xdb, 0x6d, 0xb6, 0xde, 0xd0,

    /* U+006B "k" */
    0x40, 0xc0, 0xc0, 0xc0, 0xce, 0xdc, 0xf8, 0xf8,
    0xfc, 0xcc, 0xce, 0xc6, 0xc7, 0xc3,

    /* U+006C "l" */
    0x3f, 0xff, 0xff, 0xf0,

    /* U+006D "m" */
    0xfc, 0xf3, 0xff, 0xee, 0x79, 0xf0, 0xc3, 0xc3,
    0xf, 0xc, 0x3c, 0x30, 0xf0, 0xc3, 0xc3, 0xf,
    0xc, 0x30,

    /* U+006E "n" */
    0xfc, 0xfe, 0xc7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3,

    /* U+006F "o" */
    0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7,
    0x7e, 0x3c,

    /* U+0070 "p" */
    0xfc, 0xfe, 0xc7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7,
    0xfe, 0xfc, 0xc0, 0xc0, 0xc0, 0xc0, 0x0,

    /* U+0071 "q" */
    0x3f, 0x7f, 0xe3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe3,
    0x7f, 0x3f, 0x3, 0x3, 0x3, 0x3, 0x0,

    /* U+0072 "r" */
    0xff, 0xf1, 0x8c, 0x63, 0x18, 0xc6, 0x0,

    /* U+0073 "s" */
    0x79, 0xff, 0x17, 0x7, 0x83, 0x81, 0xe3, 0xfe,
    0xf8,

    /* U+0074 "t" */
    0x23, 0x18, 0xcf, 0xfd, 0x8c, 0x63, 0x18, 0xc7,
    0x18,

    /* U+0075 "u" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe3,
    0x7f, 0x3f,

    /* U+0076 "v" */
    0x61, 0xd8, 0x66, 0x38, 0xcc, 0x33, 0xf, 0xc1,
    0xe0, 0x78, 0xe, 0x3, 0x0,

    /* U+0077 "w" */
    0xc7, 0x3b, 0x39, 0x9b, 0xcc, 0xdf, 0x66, 0xdf,
    0x3e, 0xf0, 0xe7, 0x87, 0x1c, 0x38, 0xe1, 0xc7,
    0x0,

    /* U+0078 "x" */
    0x71, 0x8c, 0xc1, 0xf0, 0x78, 0xe, 0x7, 0x81,
    0xf0, 0xce, 0x71, 0x98, 0x70,

    /* U+0079 "y" */
    0xe0, 0xd8, 0x77, 0x18, 0xc6, 0x33, 0x8e, 0xc1,
    0xf0, 0x78, 0x1e, 0x3, 0x80, 0xc0, 0x70, 0x18,
    0x6, 0x3, 0x80,

    /* U+007A "z" */
    0xff, 0xfc, 0x38, 0xe1, 0x86, 0x18, 0x30, 0xff,
    0xfc,

    /* U+007B "{" */
    0x1c, 0xf3, 0xc, 0x30, 0xc3, 0xc, 0x63, 0x8e,
    0x1c, 0x30, 0xc3, 0xc, 0x30, 0xf1, 0xc0,

    /* U+007C "|" */
    0xff, 0xff, 0xc0,

    /* U+007D "}" */
    0xe3, 0xc3, 0xc, 0x30, 0xc3, 0xc, 0x30, 0x71,
    0xce, 0x30, 0xc3, 0xc, 0x33, 0xce, 0x0,

    /* U+007E "~" */
    0x78, 0x7f, 0xf8, 0x78
};


#endif /*#if HIGHWAY_GOTHIC*/
