/*
 * xkeysym.c: mapping from X keysyms to Unicode values
 *
 * The basic idea of this is shamelessly cribbed from xterm. The
 * actual character data is generated from Markus Kuhn's proposed
 * redraft of the X11 keysym mapping table, using the following
 * piece of Perl/sh code:

wget -q -O - http://www.cl.cam.ac.uk/~mgk25/ucs/X11.keysyms | \
perl -ne '/^(\d+)\s+(\d+)\s+[\d\/]+\s+U\+([\dA-Fa-f]+)/ and' \
      -e '  do { $a{$1 * 256+ $2} = hex $3; };' \
      -e 'END { foreach $i (sort {$a <=> $b} keys %a) {' \
      -e '  printf "    {0x%x, 0x%x},\n", $i, $a{$i} } }' \
      -e 'BEGIN { $a{0x13a4} = 0x20ac }'

 * (The BEGIN clause inserts a mapping for the Euro sign which for
 * some reason isn't in the list but xterm supports. *shrug*.)
 */

#include "misc.h"

struct keysym {
    /*
     * Currently nothing in here is above 0xFFFF, so I'll use
     * `unsigned short' to save space.
     */
    unsigned short keysym;
    unsigned short unicode;
};

static struct keysym keysyms[] = {
    {0x20, 0x20},
    {0x21, 0x21},
    {0x22, 0x22},
    {0x23, 0x23},
    {0x24, 0x24},
    {0x25, 0x25},
    {0x26, 0x26},
    {0x27, 0x27},
    {0x28, 0x28},
    {0x29, 0x29},
    {0x2a, 0x2a},
    {0x2b, 0x2b},
    {0x2c, 0x2c},
    {0x2d, 0x2d},
    {0x2e, 0x2e},
    {0x2f, 0x2f},
    {0x30, 0x30},
    {0x31, 0x31},
    {0x32, 0x32},
    {0x33, 0x33},
    {0x34, 0x34},
    {0x35, 0x35},
    {0x36, 0x36},
    {0x37, 0x37},
    {0x38, 0x38},
    {0x39, 0x39},
    {0x3a, 0x3a},
    {0x3b, 0x3b},
    {0x3c, 0x3c},
    {0x3d, 0x3d},
    {0x3e, 0x3e},
    {0x3f, 0x3f},
    {0x40, 0x40},
    {0x41, 0x41},
    {0x42, 0x42},
    {0x43, 0x43},
    {0x44, 0x44},
    {0x45, 0x45},
    {0x46, 0x46},
    {0x47, 0x47},
    {0x48, 0x48},
    {0x49, 0x49},
    {0x4a, 0x4a},
    {0x4b, 0x4b},
    {0x4c, 0x4c},
    {0x4d, 0x4d},
    {0x4e, 0x4e},
    {0x4f, 0x4f},
    {0x50, 0x50},
    {0x51, 0x51},
    {0x52, 0x52},
    {0x53, 0x53},
    {0x54, 0x54},
    {0x55, 0x55},
    {0x56, 0x56},
    {0x57, 0x57},
    {0x58, 0x58},
    {0x59, 0x59},
    {0x5a, 0x5a},
    {0x5b, 0x5b},
    {0x5c, 0x5c},
    {0x5d, 0x5d},
    {0x5e, 0x5e},
    {0x5f, 0x5f},
    {0x60, 0x60},
    {0x61, 0x61},
    {0x62, 0x62},
    {0x63, 0x63},
    {0x64, 0x64},
    {0x65, 0x65},
    {0x66, 0x66},
    {0x67, 0x67},
    {0x68, 0x68},
    {0x69, 0x69},
    {0x6a, 0x6a},
    {0x6b, 0x6b},
    {0x6c, 0x6c},
    {0x6d, 0x6d},
    {0x6e, 0x6e},
    {0x6f, 0x6f},
    {0x70, 0x70},
    {0x71, 0x71},
    {0x72, 0x72},
    {0x73, 0x73},
    {0x74, 0x74},
    {0x75, 0x75},
    {0x76, 0x76},
    {0x77, 0x77},
    {0x78, 0x78},
    {0x79, 0x79},
    {0x7a, 0x7a},
    {0x7b, 0x7b},
    {0x7c, 0x7c},
    {0x7d, 0x7d},
    {0x7e, 0x7e},
    {0xa0, 0xa0},
    {0xa1, 0xa1},
    {0xa2, 0xa2},
    {0xa3, 0xa3},
    {0xa4, 0xa4},
    {0xa5, 0xa5},
    {0xa6, 0xa6},
    {0xa7, 0xa7},
    {0xa8, 0xa8},
    {0xa9, 0xa9},
    {0xaa, 0xaa},
    {0xab, 0xab},
    {0xac, 0xac},
    {0xad, 0xad},
    {0xae, 0xae},
    {0xaf, 0xaf},
    {0xb0, 0xb0},
    {0xb1, 0xb1},
    {0xb2, 0xb2},
    {0xb3, 0xb3},
    {0xb4, 0xb4},
    {0xb5, 0xb5},
    {0xb6, 0xb6},
    {0xb7, 0xb7},
    {0xb8, 0xb8},
    {0xb9, 0xb9},
    {0xba, 0xba},
    {0xbb, 0xbb},
    {0xbc, 0xbc},
    {0xbd, 0xbd},
    {0xbe, 0xbe},
    {0xbf, 0xbf},
    {0xc0, 0xc0},
    {0xc1, 0xc1},
    {0xc2, 0xc2},
    {0xc3, 0xc3},
    {0xc4, 0xc4},
    {0xc5, 0xc5},
    {0xc6, 0xc6},
    {0xc7, 0xc7},
    {0xc8, 0xc8},
    {0xc9, 0xc9},
    {0xca, 0xca},
    {0xcb, 0xcb},
    {0xcc, 0xcc},
    {0xcd, 0xcd},
    {0xce, 0xce},
    {0xcf, 0xcf},
    {0xd0, 0xd0},
    {0xd1, 0xd1},
    {0xd2, 0xd2},
    {0xd3, 0xd3},
    {0xd4, 0xd4},
    {0xd5, 0xd5},
    {0xd6, 0xd6},
    {0xd7, 0xd7},
    {0xd8, 0xd8},
    {0xd9, 0xd9},
    {0xda, 0xda},
    {0xdb, 0xdb},
    {0xdc, 0xdc},
    {0xdd, 0xdd},
    {0xde, 0xde},
    {0xdf, 0xdf},
    {0xe0, 0xe0},
    {0xe1, 0xe1},
    {0xe2, 0xe2},
    {0xe3, 0xe3},
    {0xe4, 0xe4},
    {0xe5, 0xe5},
    {0xe6, 0xe6},
    {0xe7, 0xe7},
    {0xe8, 0xe8},
    {0xe9, 0xe9},
    {0xea, 0xea},
    {0xeb, 0xeb},
    {0xec, 0xec},
    {0xed, 0xed},
    {0xee, 0xee},
    {0xef, 0xef},
    {0xf0, 0xf0},
    {0xf1, 0xf1},
    {0xf2, 0xf2},
    {0xf3, 0xf3},
    {0xf4, 0xf4},
    {0xf5, 0xf5},
    {0xf6, 0xf6},
    {0xf7, 0xf7},
    {0xf8, 0xf8},
    {0xf9, 0xf9},
    {0xfa, 0xfa},
    {0xfb, 0xfb},
    {0xfc, 0xfc},
    {0xfd, 0xfd},
    {0xfe, 0xfe},
    {0xff, 0xff},
    {0x1a1, 0x104},
    {0x1a2, 0x2d8},
    {0x1a3, 0x141},
    {0x1a5, 0x13d},
    {0x1a6, 0x15a},
    {0x1a9, 0x160},
    {0x1aa, 0x15e},
    {0x1ab, 0x164},
    {0x1ac, 0x179},
    {0x1ae, 0x17d},
    {0x1af, 0x17b},
    {0x1b1, 0x105},
    {0x1b2, 0x2db},
    {0x1b3, 0x142},
    {0x1b5, 0x13e},
    {0x1b6, 0x15b},
    {0x1b7, 0x2c7},
    {0x1b9, 0x161},
    {0x1ba, 0x15f},
    {0x1bb, 0x165},
    {0x1bc, 0x17a},
    {0x1bd, 0x2dd},
    {0x1be, 0x17e},
    {0x1bf, 0x17c},
    {0x1c0, 0x154},
    {0x1c3, 0x102},
    {0x1c5, 0x139},
    {0x1c6, 0x106},
    {0x1c8, 0x10c},
    {0x1ca, 0x118},
    {0x1cc, 0x11a},
    {0x1cf, 0x10e},
    {0x1d0, 0x110},
    {0x1d1, 0x143},
    {0x1d2, 0x147},
    {0x1d5, 0x150},
    {0x1d8, 0x158},
    {0x1d9, 0x16e},
    {0x1db, 0x170},
    {0x1de, 0x162},
    {0x1e0, 0x155},
    {0x1e3, 0x103},
    {0x1e5, 0x13a},
    {0x1e6, 0x107},
    {0x1e8, 0x10d},
    {0x1ea, 0x119},
    {0x1ec, 0x11b},
    {0x1ef, 0x10f},
    {0x1f0, 0x111},
    {0x1f1, 0x144},
    {0x1f2, 0x148},
    {0x1f5, 0x151},
    {0x1f8, 0x159},
    {0x1f9, 0x16f},
    {0x1fb, 0x171},
    {0x1fe, 0x163},
    {0x1ff, 0x2d9},
    {0x2a1, 0x126},
    {0x2a6, 0x124},
    {0x2a9, 0x130},
    {0x2ab, 0x11e},
    {0x2ac, 0x134},
    {0x2b1, 0x127},
    {0x2b6, 0x125},
    {0x2b9, 0x131},
    {0x2bb, 0x11f},
    {0x2bc, 0x135},
    {0x2c5, 0x10a},
    {0x2c6, 0x108},
    {0x2d5, 0x120},
    {0x2d8, 0x11c},
    {0x2dd, 0x16c},
    {0x2de, 0x15c},
    {0x2e5, 0x10b},
    {0x2e6, 0x109},
    {0x2f5, 0x121},
    {0x2f8, 0x11d},
    {0x2fd, 0x16d},
    {0x2fe, 0x15d},
    {0x3a2, 0x138},
    {0x3a3, 0x156},
    {0x3a5, 0x128},
    {0x3a6, 0x13b},
    {0x3aa, 0x112},
    {0x3ab, 0x122},
    {0x3ac, 0x166},
    {0x3b3, 0x157},
    {0x3b5, 0x129},
    {0x3b6, 0x13c},
    {0x3ba, 0x113},
    {0x3bb, 0x123},
    {0x3bc, 0x167},
    {0x3bd, 0x14a},
    {0x3bf, 0x14b},
    {0x3c0, 0x100},
    {0x3c7, 0x12e},
    {0x3cc, 0x116},
    {0x3cf, 0x12a},
    {0x3d1, 0x145},
    {0x3d2, 0x14c},
    {0x3d3, 0x136},
    {0x3d9, 0x172},
    {0x3dd, 0x168},
    {0x3de, 0x16a},
    {0x3e0, 0x101},
    {0x3e7, 0x12f},
    {0x3ec, 0x117},
    {0x3ef, 0x12b},
    {0x3f1, 0x146},
    {0x3f2, 0x14d},
    {0x3f3, 0x137},
    {0x3f9, 0x173},
    {0x3fd, 0x169},
    {0x3fe, 0x16b},
    {0x47e, 0x203e},
    {0x4a1, 0x3002},
    {0x4a2, 0x300c},
    {0x4a3, 0x300d},
    {0x4a4, 0x3001},
    {0x4a5, 0x30fb},
    {0x4a6, 0x30f2},
    {0x4a7, 0x30a1},
    {0x4a8, 0x30a3},
    {0x4a9, 0x30a5},
    {0x4aa, 0x30a7},
    {0x4ab, 0x30a9},
    {0x4ac, 0x30e3},
    {0x4ad, 0x30e5},
    {0x4ae, 0x30e7},
    {0x4af, 0x30c3},
    {0x4b0, 0x30fc},
    {0x4b1, 0x30a2},
    {0x4b2, 0x30a4},
    {0x4b3, 0x30a6},
    {0x4b4, 0x30a8},
    {0x4b5, 0x30aa},
    {0x4b6, 0x30ab},
    {0x4b7, 0x30ad},
    {0x4b8, 0x30af},
    {0x4b9, 0x30b1},
    {0x4ba, 0x30b3},
    {0x4bb, 0x30b5},
    {0x4bc, 0x30b7},
    {0x4bd, 0x30b9},
    {0x4be, 0x30bb},
    {0x4bf, 0x30bd},
    {0x4c0, 0x30bf},
    {0x4c1, 0x30c1},
    {0x4c2, 0x30c4},
    {0x4c3, 0x30c6},
    {0x4c4, 0x30c8},
    {0x4c5, 0x30ca},
    {0x4c6, 0x30cb},
    {0x4c7, 0x30cc},
    {0x4c8, 0x30cd},
    {0x4c9, 0x30ce},
    {0x4ca, 0x30cf},
    {0x4cb, 0x30d2},
    {0x4cc, 0x30d5},
    {0x4cd, 0x30d8},
    {0x4ce, 0x30db},
    {0x4cf, 0x30de},
    {0x4d0, 0x30df},
    {0x4d1, 0x30e0},
    {0x4d2, 0x30e1},
    {0x4d3, 0x30e2},
    {0x4d4, 0x30e4},
    {0x4d5, 0x30e6},
    {0x4d6, 0x30e8},
    {0x4d7, 0x30e9},
    {0x4d8, 0x30ea},
    {0x4d9, 0x30eb},
    {0x4da, 0x30ec},
    {0x4db, 0x30ed},
    {0x4dc, 0x30ef},
    {0x4dd, 0x30f3},
    {0x4de, 0x309b},
    {0x4df, 0x309c},
    {0x5ac, 0x60c},
    {0x5bb, 0x61b},
    {0x5bf, 0x61f},
    {0x5c1, 0x621},
    {0x5c2, 0x622},
    {0x5c3, 0x623},
    {0x5c4, 0x624},
    {0x5c5, 0x625},
    {0x5c6, 0x626},
    {0x5c7, 0x627},
    {0x5c8, 0x628},
    {0x5c9, 0x629},
    {0x5ca, 0x62a},
    {0x5cb, 0x62b},
    {0x5cc, 0x62c},
    {0x5cd, 0x62d},
    {0x5ce, 0x62e},
    {0x5cf, 0x62f},
    {0x5d0, 0x630},
    {0x5d1, 0x631},
    {0x5d2, 0x632},
    {0x5d3, 0x633},
    {0x5d4, 0x634},
    {0x5d5, 0x635},
    {0x5d6, 0x636},
    {0x5d7, 0x637},
    {0x5d8, 0x638},
    {0x5d9, 0x639},
    {0x5da, 0x63a},
    {0x5e0, 0x640},
    {0x5e1, 0x641},
    {0x5e2, 0x642},
    {0x5e3, 0x643},
    {0x5e4, 0x644},
    {0x5e5, 0x645},
    {0x5e6, 0x646},
    {0x5e7, 0x647},
    {0x5e8, 0x648},
    {0x5e9, 0x649},
    {0x5ea, 0x64a},
    {0x5eb, 0x64b},
    {0x5ec, 0x64c},
    {0x5ed, 0x64d},
    {0x5ee, 0x64e},
    {0x5ef, 0x64f},
    {0x5f0, 0x650},
    {0x5f1, 0x651},
    {0x5f2, 0x652},
    {0x6a1, 0x452},
    {0x6a2, 0x453},
    {0x6a3, 0x451},
    {0x6a4, 0x454},
    {0x6a5, 0x455},
    {0x6a6, 0x456},
    {0x6a7, 0x457},
    {0x6a8, 0x458},
    {0x6a9, 0x459},
    {0x6aa, 0x45a},
    {0x6ab, 0x45b},
    {0x6ac, 0x45c},
    {0x6ae, 0x45e},
    {0x6af, 0x45f},
    {0x6b0, 0x2116},
    {0x6b1, 0x402},
    {0x6b2, 0x403},
    {0x6b3, 0x401},
    {0x6b4, 0x404},
    {0x6b5, 0x405},
    {0x6b6, 0x406},
    {0x6b7, 0x407},
    {0x6b8, 0x408},
    {0x6b9, 0x409},
    {0x6ba, 0x40a},
    {0x6bb, 0x40b},
    {0x6bc, 0x40c},
    {0x6be, 0x40e},
    {0x6bf, 0x40f},
    {0x6c0, 0x44e},
    {0x6c1, 0x430},
    {0x6c2, 0x431},
    {0x6c3, 0x446},
    {0x6c4, 0x434},
    {0x6c5, 0x435},
    {0x6c6, 0x444},
    {0x6c7, 0x433},
    {0x6c8, 0x445},
    {0x6c9, 0x438},
    {0x6ca, 0x439},
    {0x6cb, 0x43a},
    {0x6cc, 0x43b},
    {0x6cd, 0x43c},
    {0x6ce, 0x43d},
    {0x6cf, 0x43e},
    {0x6d0, 0x43f},
    {0x6d1, 0x44f},
    {0x6d2, 0x440},
    {0x6d3, 0x441},
    {0x6d4, 0x442},
    {0x6d5, 0x443},
    {0x6d6, 0x436},
    {0x6d7, 0x432},
    {0x6d8, 0x44c},
    {0x6d9, 0x44b},
    {0x6da, 0x437},
    {0x6db, 0x448},
    {0x6dc, 0x44d},
    {0x6dd, 0x449},
    {0x6de, 0x447},
    {0x6df, 0x44a},
    {0x6e0, 0x42e},
    {0x6e1, 0x410},
    {0x6e2, 0x411},
    {0x6e3, 0x426},
    {0x6e4, 0x414},
    {0x6e5, 0x415},
    {0x6e6, 0x424},
    {0x6e7, 0x413},
    {0x6e8, 0x425},
    {0x6e9, 0x418},
    {0x6ea, 0x419},
    {0x6eb, 0x41a},
    {0x6ec, 0x41b},
    {0x6ed, 0x41c},
    {0x6ee, 0x41d},
    {0x6ef, 0x41e},
    {0x6f0, 0x41f},
    {0x6f1, 0x42f},
    {0x6f2, 0x420},
    {0x6f3, 0x421},
    {0x6f4, 0x422},
    {0x6f5, 0x423},
    {0x6f6, 0x416},
    {0x6f7, 0x412},
    {0x6f8, 0x42c},
    {0x6f9, 0x42b},
    {0x6fa, 0x417},
    {0x6fb, 0x428},
    {0x6fc, 0x42d},
    {0x6fd, 0x429},
    {0x6fe, 0x427},
    {0x6ff, 0x42a},
    {0x7a1, 0x386},
    {0x7a2, 0x388},
    {0x7a3, 0x389},
    {0x7a4, 0x38a},
    {0x7a5, 0x3aa},
    {0x7a7, 0x38c},
    {0x7a8, 0x38e},
    {0x7a9, 0x3ab},
    {0x7ab, 0x38f},
    {0x7ae, 0x385},
    {0x7af, 0x2015},
    {0x7b1, 0x3ac},
    {0x7b2, 0x3ad},
    {0x7b3, 0x3ae},
    {0x7b4, 0x3af},
    {0x7b5, 0x3ca},
    {0x7b6, 0x390},
    {0x7b7, 0x3cc},
    {0x7b8, 0x3cd},
    {0x7b9, 0x3cb},
    {0x7ba, 0x3b0},
    {0x7bb, 0x3ce},
    {0x7c1, 0x391},
    {0x7c2, 0x392},
    {0x7c3, 0x393},
    {0x7c4, 0x394},
    {0x7c5, 0x395},
    {0x7c6, 0x396},
    {0x7c7, 0x397},
    {0x7c8, 0x398},
    {0x7c9, 0x399},
    {0x7ca, 0x39a},
    {0x7cb, 0x39b},
    {0x7cc, 0x39c},
    {0x7cd, 0x39d},
    {0x7ce, 0x39e},
    {0x7cf, 0x39f},
    {0x7d0, 0x3a0},
    {0x7d1, 0x3a1},
    {0x7d2, 0x3a3},
    {0x7d4, 0x3a4},
    {0x7d5, 0x3a5},
    {0x7d6, 0x3a6},
    {0x7d7, 0x3a7},
    {0x7d8, 0x3a8},
    {0x7d9, 0x3a9},
    {0x7e1, 0x3b1},
    {0x7e2, 0x3b2},
    {0x7e3, 0x3b3},
    {0x7e4, 0x3b4},
    {0x7e5, 0x3b5},
    {0x7e6, 0x3b6},
    {0x7e7, 0x3b7},
    {0x7e8, 0x3b8},
    {0x7e9, 0x3b9},
    {0x7ea, 0x3ba},
    {0x7eb, 0x3bb},
    {0x7ec, 0x3bc},
    {0x7ed, 0x3bd},
    {0x7ee, 0x3be},
    {0x7ef, 0x3bf},
    {0x7f0, 0x3c0},
    {0x7f1, 0x3c1},
    {0x7f2, 0x3c3},
    {0x7f3, 0x3c2},
    {0x7f4, 0x3c4},
    {0x7f5, 0x3c5},
    {0x7f6, 0x3c6},
    {0x7f7, 0x3c7},
    {0x7f8, 0x3c8},
    {0x7f9, 0x3c9},
    {0x8a1, 0x23b7},
    {0x8a2, 0x250c},
    {0x8a3, 0x2500},
    {0x8a4, 0x2320},
    {0x8a5, 0x2321},
    {0x8a6, 0x2502},
    {0x8a7, 0x23a1},
    {0x8a8, 0x23a3},
    {0x8a9, 0x23a4},
    {0x8aa, 0x23a6},
    {0x8ab, 0x239b},
    {0x8ac, 0x239d},
    {0x8ad, 0x239e},
    {0x8ae, 0x23a0},
    {0x8af, 0x23a8},
    {0x8b0, 0x23ac},
    {0x8bc, 0x2264},
    {0x8bd, 0x2260},
    {0x8be, 0x2265},
    {0x8bf, 0x222b},
    {0x8c0, 0x2234},
    {0x8c1, 0x221d},
    {0x8c2, 0x221e},
    {0x8c5, 0x2207},
    {0x8c8, 0x223c},
    {0x8c9, 0x2243},
    {0x8cd, 0x21d4},
    {0x8ce, 0x21d2},
    {0x8cf, 0x2261},
    {0x8d6, 0x221a},
    {0x8da, 0x2282},
    {0x8db, 0x2283},
    {0x8dc, 0x2229},
    {0x8dd, 0x222a},
    {0x8de, 0x2227},
    {0x8df, 0x2228},
    {0x8ef, 0x2202},
    {0x8f6, 0x192},
    {0x8fb, 0x2190},
    {0x8fc, 0x2191},
    {0x8fd, 0x2192},
    {0x8fe, 0x2193},
    {0x9e0, 0x25c6},
    {0x9e1, 0x2592},
    {0x9e2, 0x2409},
    {0x9e3, 0x240c},
    {0x9e4, 0x240d},
    {0x9e5, 0x240a},
    {0x9e8, 0x2424},
    {0x9e9, 0x240b},
    {0x9ea, 0x2518},
    {0x9eb, 0x2510},
    {0x9ec, 0x250c},
    {0x9ed, 0x2514},
    {0x9ee, 0x253c},
    {0x9ef, 0x23ba},
    {0x9f0, 0x23bb},
    {0x9f1, 0x2500},
    {0x9f2, 0x23bc},
    {0x9f3, 0x23bd},
    {0x9f4, 0x251c},
    {0x9f5, 0x2524},
    {0x9f6, 0x2534},
    {0x9f7, 0x252c},
    {0x9f8, 0x2502},
    {0xaa1, 0x2003},
    {0xaa2, 0x2002},
    {0xaa3, 0x2004},
    {0xaa4, 0x2005},
    {0xaa5, 0x2007},
    {0xaa6, 0x2008},
    {0xaa7, 0x2009},
    {0xaa8, 0x200a},
    {0xaa9, 0x2014},
    {0xaaa, 0x2013},
    {0xaae, 0x2026},
    {0xaaf, 0x2025},
    {0xab0, 0x2153},
    {0xab1, 0x2154},
    {0xab2, 0x2155},
    {0xab3, 0x2156},
    {0xab4, 0x2157},
    {0xab5, 0x2158},
    {0xab6, 0x2159},
    {0xab7, 0x215a},
    {0xab8, 0x2105},
    {0xabb, 0x2012},
    {0xabc, 0x2329},
    {0xabe, 0x232a},
    {0xac3, 0x215b},
    {0xac4, 0x215c},
    {0xac5, 0x215d},
    {0xac6, 0x215e},
    {0xac9, 0x2122},
    {0xaca, 0x2613},
    {0xacc, 0x25c1},
    {0xacd, 0x25b7},
    {0xace, 0x25cb},
    {0xacf, 0x25af},
    {0xad0, 0x2018},
    {0xad1, 0x2019},
    {0xad2, 0x201c},
    {0xad3, 0x201d},
    {0xad4, 0x211e},
    {0xad6, 0x2032},
    {0xad7, 0x2033},
    {0xad9, 0x271d},
    {0xadb, 0x25ac},
    {0xadc, 0x25c0},
    {0xadd, 0x25b6},
    {0xade, 0x25cf},
    {0xadf, 0x25ae},
    {0xae0, 0x25e6},
    {0xae1, 0x25ab},
    {0xae2, 0x25ad},
    {0xae3, 0x25b3},
    {0xae4, 0x25bd},
    {0xae5, 0x2606},
    {0xae6, 0x2022},
    {0xae7, 0x25aa},
    {0xae8, 0x25b2},
    {0xae9, 0x25bc},
    {0xaea, 0x261c},
    {0xaeb, 0x261e},
    {0xaec, 0x2663},
    {0xaed, 0x2666},
    {0xaee, 0x2665},
    {0xaf0, 0x2720},
    {0xaf1, 0x2020},
    {0xaf2, 0x2021},
    {0xaf3, 0x2713},
    {0xaf4, 0x2717},
    {0xaf5, 0x266f},
    {0xaf6, 0x266d},
    {0xaf7, 0x2642},
    {0xaf8, 0x2640},
    {0xaf9, 0x260e},
    {0xafa, 0x2315},
    {0xafb, 0x2117},
    {0xafc, 0x2038},
    {0xafd, 0x201a},
    {0xafe, 0x201e},
    {0xba3, 0x3c},
    {0xba6, 0x3e},
    {0xba8, 0x2228},
    {0xba9, 0x2227},
    {0xbc0, 0xaf},
    {0xbc2, 0x22a5},
    {0xbc3, 0x2229},
    {0xbc4, 0x230a},
    {0xbc6, 0x5f},
    {0xbca, 0x2218},
    {0xbcc, 0x2395},
    {0xbce, 0x22a4},
    {0xbcf, 0x25cb},
    {0xbd3, 0x2308},
    {0xbd6, 0x222a},
    {0xbd8, 0x2283},
    {0xbda, 0x2282},
    {0xbdc, 0x22a2},
    {0xbfc, 0x22a3},
    {0xcdf, 0x2017},
    {0xce0, 0x5d0},
    {0xce1, 0x5d1},
    {0xce2, 0x5d2},
    {0xce3, 0x5d3},
    {0xce4, 0x5d4},
    {0xce5, 0x5d5},
    {0xce6, 0x5d6},
    {0xce7, 0x5d7},
    {0xce8, 0x5d8},
    {0xce9, 0x5d9},
    {0xcea, 0x5da},
    {0xceb, 0x5db},
    {0xcec, 0x5dc},
    {0xced, 0x5dd},
    {0xcee, 0x5de},
    {0xcef, 0x5df},
    {0xcf0, 0x5e0},
    {0xcf1, 0x5e1},
    {0xcf2, 0x5e2},
    {0xcf3, 0x5e3},
    {0xcf4, 0x5e4},
    {0xcf5, 0x5e5},
    {0xcf6, 0x5e6},
    {0xcf7, 0x5e7},
    {0xcf8, 0x5e8},
    {0xcf9, 0x5e9},
    {0xcfa, 0x5ea},
    {0xda1, 0xe01},
    {0xda2, 0xe02},
    {0xda3, 0xe03},
    {0xda4, 0xe04},
    {0xda5, 0xe05},
    {0xda6, 0xe06},
    {0xda7, 0xe07},
    {0xda8, 0xe08},
    {0xda9, 0xe09},
    {0xdaa, 0xe0a},
    {0xdab, 0xe0b},
    {0xdac, 0xe0c},
    {0xdad, 0xe0d},
    {0xdae, 0xe0e},
    {0xdaf, 0xe0f},
    {0xdb0, 0xe10},
    {0xdb1, 0xe11},
    {0xdb2, 0xe12},
    {0xdb3, 0xe13},
    {0xdb4, 0xe14},
    {0xdb5, 0xe15},
    {0xdb6, 0xe16},
    {0xdb7, 0xe17},
    {0xdb8, 0xe18},
    {0xdb9, 0xe19},
    {0xdba, 0xe1a},
    {0xdbb, 0xe1b},
    {0xdbc, 0xe1c},
    {0xdbd, 0xe1d},
    {0xdbe, 0xe1e},
    {0xdbf, 0xe1f},
    {0xdc0, 0xe20},
    {0xdc1, 0xe21},
    {0xdc2, 0xe22},
    {0xdc3, 0xe23},
    {0xdc4, 0xe24},
    {0xdc5, 0xe25},
    {0xdc6, 0xe26},
    {0xdc7, 0xe27},
    {0xdc8, 0xe28},
    {0xdc9, 0xe29},
    {0xdca, 0xe2a},
    {0xdcb, 0xe2b},
    {0xdcc, 0xe2c},
    {0xdcd, 0xe2d},
    {0xdce, 0xe2e},
    {0xdcf, 0xe2f},
    {0xdd0, 0xe30},
    {0xdd1, 0xe31},
    {0xdd2, 0xe32},
    {0xdd3, 0xe33},
    {0xdd4, 0xe34},
    {0xdd5, 0xe35},
    {0xdd6, 0xe36},
    {0xdd7, 0xe37},
    {0xdd8, 0xe38},
    {0xdd9, 0xe39},
    {0xdda, 0xe3a},
    {0xddf, 0xe3f},
    {0xde0, 0xe40},
    {0xde1, 0xe41},
    {0xde2, 0xe42},
    {0xde3, 0xe43},
    {0xde4, 0xe44},
    {0xde5, 0xe45},
    {0xde6, 0xe46},
    {0xde7, 0xe47},
    {0xde8, 0xe48},
    {0xde9, 0xe49},
    {0xdea, 0xe4a},
    {0xdeb, 0xe4b},
    {0xdec, 0xe4c},
    {0xded, 0xe4d},
    {0xdf0, 0xe50},
    {0xdf1, 0xe51},
    {0xdf2, 0xe52},
    {0xdf3, 0xe53},
    {0xdf4, 0xe54},
    {0xdf5, 0xe55},
    {0xdf6, 0xe56},
    {0xdf7, 0xe57},
    {0xdf8, 0xe58},
    {0xdf9, 0xe59},
    {0xea1, 0x3131},
    {0xea2, 0x3132},
    {0xea3, 0x3133},
    {0xea4, 0x3134},
    {0xea5, 0x3135},
    {0xea6, 0x3136},
    {0xea7, 0x3137},
    {0xea8, 0x3138},
    {0xea9, 0x3139},
    {0xeaa, 0x313a},
    {0xeab, 0x313b},
    {0xeac, 0x313c},
    {0xead, 0x313d},
    {0xeae, 0x313e},
    {0xeaf, 0x313f},
    {0xeb0, 0x3140},
    {0xeb1, 0x3141},
    {0xeb2, 0x3142},
    {0xeb3, 0x3143},
    {0xeb4, 0x3144},
    {0xeb5, 0x3145},
    {0xeb6, 0x3146},
    {0xeb7, 0x3147},
    {0xeb8, 0x3148},
    {0xeb9, 0x3149},
    {0xeba, 0x314a},
    {0xebb, 0x314b},
    {0xebc, 0x314c},
    {0xebd, 0x314d},
    {0xebe, 0x314e},
    {0xebf, 0x314f},
    {0xec0, 0x3150},
    {0xec1, 0x3151},
    {0xec2, 0x3152},
    {0xec3, 0x3153},
    {0xec4, 0x3154},
    {0xec5, 0x3155},
    {0xec6, 0x3156},
    {0xec7, 0x3157},
    {0xec8, 0x3158},
    {0xec9, 0x3159},
    {0xeca, 0x315a},
    {0xecb, 0x315b},
    {0xecc, 0x315c},
    {0xecd, 0x315d},
    {0xece, 0x315e},
    {0xecf, 0x315f},
    {0xed0, 0x3160},
    {0xed1, 0x3161},
    {0xed2, 0x3162},
    {0xed3, 0x3163},
    {0xed4, 0x11a8},
    {0xed5, 0x11a9},
    {0xed6, 0x11aa},
    {0xed7, 0x11ab},
    {0xed8, 0x11ac},
    {0xed9, 0x11ad},
    {0xeda, 0x11ae},
    {0xedb, 0x11af},
    {0xedc, 0x11b0},
    {0xedd, 0x11b1},
    {0xede, 0x11b2},
    {0xedf, 0x11b3},
    {0xee0, 0x11b4},
    {0xee1, 0x11b5},
    {0xee2, 0x11b6},
    {0xee3, 0x11b7},
    {0xee4, 0x11b8},
    {0xee5, 0x11b9},
    {0xee6, 0x11ba},
    {0xee7, 0x11bb},
    {0xee8, 0x11bc},
    {0xee9, 0x11bd},
    {0xeea, 0x11be},
    {0xeeb, 0x11bf},
    {0xeec, 0x11c0},
    {0xeed, 0x11c1},
    {0xeee, 0x11c2},
    {0xeef, 0x316d},
    {0xef0, 0x3171},
    {0xef1, 0x3178},
    {0xef2, 0x317f},
    {0xef3, 0x3181},
    {0xef4, 0x3184},
    {0xef5, 0x3186},
    {0xef6, 0x318d},
    {0xef7, 0x318e},
    {0xef8, 0x11eb},
    {0xef9, 0x11f0},
    {0xefa, 0x11f9},
    {0xeff, 0x20a9},
    {0x13a4, 0x20ac},
    {0x13bc, 0x152},
    {0x13bd, 0x153},
    {0x13be, 0x178},
    {0x20a0, 0x20a0},
    {0x20a1, 0x20a1},
    {0x20a2, 0x20a2},
    {0x20a3, 0x20a3},
    {0x20a4, 0x20a4},
    {0x20a5, 0x20a5},
    {0x20a6, 0x20a6},
    {0x20a7, 0x20a7},
    {0x20a8, 0x20a8},
    {0x20aa, 0x20aa},
    {0x20ab, 0x20ab},
    {0x20ac, 0x20ac},
};

int keysym_to_unicode(int keysym)
{
    int i, j, k;

    i = -1;
    j = lenof(keysyms);

    while (j - i >= 2) {
        k = (j + i) / 2;
        if (keysyms[k].keysym == keysym)
            return keysyms[k].unicode;
        else if (keysyms[k].keysym < keysym)
            i = k;
        else
            j = k;
    }
    return -1;
}
