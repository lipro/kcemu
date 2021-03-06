/*
 *  KCemu -- The emulator for the KC85 homecomputer series and much more.
 *  Copyright (C) 1997-2010 Torsten Paul
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef __kc_kramermc_keydef_h
#define __kc_kramermc_keydef_h

/*
 *  01 (1)   02 (2)   04 (3)   08 (4)   10 (5)   20 (6)   40 (7)   80 (8) (low nibble)
 *  |        |        |        |        |        |        |        |
 *  *-[^ ]-* *-[*b]-* *-[;+]-* *-[<,]-+ *-[*f]-* *-[*h]-* *-[*i]-* *-[:*]-*
 *  |      | |      | |      | |      | |      | |      | |      | |      |
 *  �      *-+------*-+------*-+------*-+------*-+------*-+------*-+------*--01 (1)
 *  |        |        |        |        |        |        |        |
 *  *-[P ]-* *-[O ]-* *-[*d]-* *-[K ]-+ *-[*g]-* *-[L ]-* *-[0 ]-* *-[9)]-*
 *  |      | |      | |      | |      | |      | |      | |      | |      |
 *  �      *-+------*-+------*-+------*-+------*-+------*-+------*-+------*--02 (2)
 *  |        |        |        |        |        |        |        |
 *  *-[I ]-* *-[U ]-* *-[N ]-* *-[H ]-+ *-[M ]-* *-[J ]-* *-[8(]-* *-[7']-*
 *  |      | |      | |      | |      | |      | |      | |      | |      |
 *  �      *-+------*-+------*-+------*-+------*-+------*-+------*-+------*--04 (3)
 *  |        |        |        |        |        |        |        |
 *  *-[Z ]-* *-[T ]-* *-[V ]-* *-[F ]-+ *-[B ]-* *-[G ]-* *-[6 ]-* *-[5 ]-*
 *  |      | |      | |      | |      | |      | |      | |      | |      |
 *  �      *-+------*-+------*-+------*-+------*-+------*-+------*-+------*--08 (4)
 *  |        |        |        |        |        |        |        |
 *  *-[R ]-* *-[E ]-* *-[X ]-* *-[S ]-+ *-[C ]-* *-[D ]-* *-[4 ]-* *-[3 ]-*
 *  |      | |      | |      | |      | |      | |      | |      | |      |
 *  �      *-+------*-+------*-+------*-+------*-+------*-+------*-+------*--10 (5)
 *  |        |        |        |        |        |        |        |
 *  *-[W ]-* *-[Q ]-* *-[  ]-* *-[  ]-+ *-[Y ]-* *-[A ]-* *-[2 ]-* *-[1 ]-*
 *  |      | |      | |      | |      | |      | |      | |      | |      |
 *  �      *-+------*-+------*-+------*-+------*-+------*-+------*-+------*--20 (6)
 *  |        |        |        |        |        |        |        |
 *  *-[*a]-* *-[*c]-* *-[  ]-* *-[*e]-+ *-[  ]-* *-[>.]-* *-[?/]-* *-[=-]-*
 *  |      | |      | |      | |      | |      | |      | |      | |      |
 *  �      *-+------*-+------*-+------*-+------*-+------*-+------*-+------*--40 (7)
 *  |        |        |        |        |        |        |        |
 *  *-[  ]-* *-[  ]-* *-[  ]-* *-[  ]-+ *-[  ]-* *-[  ]-* *-[  ]-* *-[  ]-*
 *         |        |        |        |        |        |        |        |
 *         *--------*--------*--------*--------*--------*--------*--------*--80 (8)
 *
 *           *a = ->           *d = DEL          *g = CR	  
 *           *b = <-           *e = CTRL         *h = SHIFT
 *           *c = SPACE        *f = ETX          *i = DOWN 
 *
 */

static unsigned int __keys[] = {
  /* 0x00 [.] */ 0x00,
  /* 0x01 [.] */ 0x00,
  /* 0x02 [.] */ 0x00,
  /* 0x03 [.] */ 0x00,
  /* 0x04 [.] */ 0x00,
  /* 0x05 [.] */ 0x00,
  /* 0x06 [.] */ 0x00,
  /* 0x07 [.] */ 0x00,
  /* 0x08 [.] */ 0x00,
  /* 0x09 [.] */ 0x00,
  /* 0x0a [.] */ 0x00,
  /* 0x0b [.] */ 0x00,
  /* 0x0c [.] */ 0x00,
  /* 0x0d [.] */ 0x52, /* ENTER */
  /* 0x0e [.] */ 0x00,
  /* 0x0f [.] */ 0x00,
  /* 0x10 [.] */ 0x00,
  /* 0x11 [.] */ 0x00,
  /* 0x12 [.] */ 0x00,
  /* 0x13 [.] */ 0x00,
  /* 0x14 [.] */ 0x00,
  /* 0x15 [.] */ 0x00,
  /* 0x16 [.] */ 0x00,
  /* 0x17 [.] */ 0x00,
  /* 0x18 [.] */ 0x00,
  /* 0x19 [.] */ 0x00,
  /* 0x1a [.] */ 0x00,
  /* 0x1b [.] */ 0x51, /* ESC | CL LN */
  /* 0x1c [.] */ 0x00,
  /* 0x1d [.] */ 0x00,
  /* 0x1e [.] */ 0x00,
  /* 0x1f [.] */ 0x00,
  /* 0x20 [ ] */ 0x27, /* SPACE */
  /* 0x21 [!] */ 0x00,
  /* 0x22 ["] */ 0x00,
  /* 0x23 [#] */ 0x00,
  /* 0x24 [$] */ 0x00,
  /* 0x25 [%] */ 0x00,
  /* 0x26 [&] */ 0x00,
  /* 0x27 ['] */ 0x6183,
  /* 0x28 [(] */ 0x6173,
  /* 0x29 [)] */ 0x6182,
  /* 0x2a [*] */ 0x6181,
  /* 0x2b [+] */ 0x6131,
  /* 0x2c [,] */ 0x6141,
  /* 0x2d [-] */ 0x6187,
  /* 0x2e [.] */ 0x6167,
  /* 0x2f [/] */ 0x6177,
  /* 0x30 [0] */ 0x72,
  /* 0x31 [1] */ 0x86,
  /* 0x32 [2] */ 0x76,
  /* 0x33 [3] */ 0x85,
  /* 0x34 [4] */ 0x75,
  /* 0x35 [5] */ 0x84,
  /* 0x36 [6] */ 0x74,
  /* 0x37 [7] */ 0x83,
  /* 0x38 [8] */ 0x73,
  /* 0x39 [9] */ 0x82,
  /* 0x3a [:] */ 0x81,
  /* 0x3b [;] */ 0x31,
  /* 0x3c [<] */ 0x41,
  /* 0x3d [=] */ 0x87,
  /* 0x3e [>] */ 0x67,
  /* 0x3f [?] */ 0x77,
  /* 0x40 [@] */ 0x00,
  /* 0x41 [A] */ 0x6166,
  /* 0x42 [B] */ 0x6154,
  /* 0x43 [C] */ 0x6155,
  /* 0x44 [D] */ 0x6165,
  /* 0x45 [E] */ 0x6125,
  /* 0x46 [F] */ 0x6144,
  /* 0x47 [G] */ 0x6164,
  /* 0x48 [H] */ 0x6143,
  /* 0x49 [I] */ 0x6113,
  /* 0x4a [J] */ 0x6163,
  /* 0x4b [K] */ 0x6142,
  /* 0x4c [L] */ 0x6162,
  /* 0x4d [M] */ 0x6153,
  /* 0x4e [N] */ 0x6133,
  /* 0x4f [O] */ 0x6122,
  /* 0x50 [P] */ 0x6112,
  /* 0x51 [Q] */ 0x6126,
  /* 0x52 [R] */ 0x6115,
  /* 0x53 [S] */ 0x6145,
  /* 0x54 [T] */ 0x6124,
  /* 0x55 [U] */ 0x6123,
  /* 0x56 [V] */ 0x6134,
  /* 0x57 [W] */ 0x6116,
  /* 0x58 [X] */ 0x6135,
  /* 0x59 [Y] */ 0x6156,
  /* 0x5a [Z] */ 0x6114,
  /* 0x5b [[] */ 0x00,
  /* 0x5c [\] */ 0x00,
  /* 0x5d []] */ 0x00,
  /* 0x5e [^] */ 0x00,
  /* 0x5f [_] */ 0x00,
  /* 0x60 [`] */ 0x00,
  /* 0x61 [a] */ 0x66,
  /* 0x62 [b] */ 0x54,
  /* 0x63 [c] */ 0x55,
  /* 0x64 [d] */ 0x65,
  /* 0x65 [e] */ 0x25,
  /* 0x66 [f] */ 0x44,
  /* 0x67 [g] */ 0x64,
  /* 0x68 [h] */ 0x43,
  /* 0x69 [i] */ 0x13,
  /* 0x6a [j] */ 0x63,
  /* 0x6b [k] */ 0x42,
  /* 0x6c [l] */ 0x62,
  /* 0x6d [m] */ 0x53,
  /* 0x6e [n] */ 0x33,
  /* 0x6f [o] */ 0x22,
  /* 0x70 [p] */ 0x12,
  /* 0x71 [q] */ 0x26,
  /* 0x72 [r] */ 0x15,
  /* 0x73 [s] */ 0x45,
  /* 0x74 [t] */ 0x24,
  /* 0x75 [u] */ 0x23,
  /* 0x76 [v] */ 0x34,
  /* 0x77 [w] */ 0x16,
  /* 0x78 [x] */ 0x35,
  /* 0x79 [y] */ 0x56,
  /* 0x7a [z] */ 0x14,
  /* 0x7b [{] */ 0x00,
  /* 0x7c [|] */ 0x00,
  /* 0x7d [}] */ 0x00,
  /* 0x7e [~] */ 0x00,
  /* 0x7f [.] */ 0x00,
  /* 0x80 [.] */ 0x00,
  /* 0x81 [.] */ 0x00,
  /* 0x82 [.] */ 0x00,
  /* 0x83 [.] */ 0x00,
  /* 0x84 [.] */ 0x00,
  /* 0x85 [.] */ 0x00,
  /* 0x86 [.] */ 0x00,
  /* 0x87 [.] */ 0x00,
  /* 0x88 [.] */ 0x00,
  /* 0x89 [.] */ 0x00,
  /* 0x8a [.] */ 0x00,
  /* 0x8b [.] */ 0x00,
  /* 0x8c [.] */ 0x00,
  /* 0x8d [.] */ 0x00,
  /* 0x8e [.] */ 0x00,
  /* 0x8f [.] */ 0x00,
  /* 0x90 [.] */ 0x00,
  /* 0x91 [.] */ 0x00,
  /* 0x92 [.] */ 0x00,
  /* 0x93 [.] */ 0x00,
  /* 0x94 [.] */ 0x00,
  /* 0x95 [.] */ 0x00,
  /* 0x96 [.] */ 0x00,
  /* 0x97 [.] */ 0x00,
  /* 0x98 [.] */ 0x00,
  /* 0x99 [.] */ 0x00,
  /* 0x9a [.] */ 0x00,
  /* 0x9b [.] */ 0x00,
  /* 0x9c [.] */ 0x00,
  /* 0x9d [.] */ 0x00,
  /* 0x9e [.] */ 0x00,
  /* 0x9f [.] */ 0x00,
  /* 0xa0 [.] */ 0x00,
  /* 0xa1 [.] */ 0x00,
  /* 0xa2 [.] */ 0x00,
  /* 0xa3 [.] */ 0x00,
  /* 0xa4 [.] */ 0x00,
  /* 0xa5 [.] */ 0x00,
  /* 0xa6 [.] */ 0x00,
  /* 0xa7 [.] */ 0x00,
  /* 0xa8 [.] */ 0x00,
  /* 0xa9 [.] */ 0x00,
  /* 0xaa [.] */ 0x00,
  /* 0xab [.] */ 0x00,
  /* 0xac [.] */ 0x00,
  /* 0xad [.] */ 0x00,
  /* 0xae [.] */ 0x00,
  /* 0xaf [.] */ 0x00,
  /* 0xb0 [.] */ 0x00,
  /* 0xb1 [.] */ 0x00,
  /* 0xb2 [.] */ 0x00,
  /* 0xb3 [.] */ 0x00,
  /* 0xb4 [.] */ 0x00,
  /* 0xb5 [.] */ 0x00,
  /* 0xb6 [.] */ 0x00,
  /* 0xb7 [.] */ 0x00,
  /* 0xb8 [.] */ 0x00,
  /* 0xb9 [.] */ 0x00,
  /* 0xba [.] */ 0x00,
  /* 0xbb [.] */ 0x00,
  /* 0xbc [.] */ 0x00,
  /* 0xbd [.] */ 0x00,
  /* 0xbe [.] */ 0x00,
  /* 0xbf [.] */ 0x00,
  /* 0xc0 [.] */ 0x00,
  /* 0xc1 [.] */ 0x00,
  /* 0xc2 [.] */ 0x00,
  /* 0xc3 [.] */ 0x00,
  /* 0xc4 [.] */ 0x00,
  /* 0xc5 [.] */ 0x00,
  /* 0xc6 [.] */ 0x00,
  /* 0xc7 [.] */ 0x00,
  /* 0xc8 [.] */ 0x00,
  /* 0xc9 [.] */ 0x00,
  /* 0xca [.] */ 0x00,
  /* 0xcb [.] */ 0x00,
  /* 0xcc [.] */ 0x00,
  /* 0xcd [.] */ 0x00,
  /* 0xce [.] */ 0x00,
  /* 0xcf [.] */ 0x00,
  /* 0xd0 [.] */ 0x00,
  /* 0xd1 [.] */ 0x00,
  /* 0xd2 [.] */ 0x00,
  /* 0xd3 [.] */ 0x00,
  /* 0xd4 [.] */ 0x00,
  /* 0xd5 [.] */ 0x00,
  /* 0xd6 [.] */ 0x00,
  /* 0xd7 [.] */ 0x00,
  /* 0xd8 [.] */ 0x00,
  /* 0xd9 [.] */ 0x00,
  /* 0xda [.] */ 0x00,
  /* 0xdb [.] */ 0x00,
  /* 0xdc [.] */ 0x00,
  /* 0xdd [.] */ 0x00,
  /* 0xde [.] */ 0x00,
  /* 0xdf [.] */ 0x00,
  /* 0xe0 [.] */ 0x00,
  /* 0xe1 [.] */ 0x00,
  /* 0xe2 [.] */ 0x00,
  /* 0xe3 [.] */ 0x00,
  /* 0xe4 [.] */ 0x00,
  /* 0xe5 [.] */ 0x00,
  /* 0xe6 [.] */ 0x00,
  /* 0xe7 [.] */ 0x00,
  /* 0xe8 [.] */ 0x00,
  /* 0xe9 [.] */ 0x00,
  /* 0xea [.] */ 0x00,
  /* 0xeb [.] */ 0x00,
  /* 0xec [.] */ 0x00,
  /* 0xed [.] */ 0x00,
  /* 0xee [.] */ 0x00,
  /* 0xef [.] */ 0x00,
  /* 0xf0 [.] */ 0x00,
  /* 0xf1 [.] */ 0x00,
  /* 0xf2 [.] */ 0x00,
  /* 0xf3 [.] */ 0x00,
  /* 0xf4 [.] */ 0x00,
  /* 0xf5 [.] */ 0x00,
  /* 0xf6 [.] */ 0x00,
  /* 0xf7 [.] */ 0x00,
  /* 0xf8 [.] */ 0x00,
  /* 0xf9 [.] */ 0x00,
  /* 0xfa [.] */ 0x00,
  /* 0xfb [.] */ 0x00,
  /* 0xfc [.] */ 0x00,
  /* 0xfd [.] */ 0x00,
  /* 0xfe [.] */ 0x00,
  /* 0xff [.] */ 0x00,

  /* 0x100 */ 0x00,
  /* 0x101 */ 0x00,
  /* 0x102 */ 0x00,
  /* 0x103 */ 0x00,
  /* 0x104 */ 0x00,
  /* 0x105 */ 0x00,
  /* 0x106 */ 0x00,
  /* 0x107 */ 0x00,
  /* 0x108 */ 0x00,
  /* 0x109 */ 0x00,
  /* 0x10a */ 0x00,
  /* 0x10b */ 0x00,
  /* 0x10c */ 0x00,
  /* 0x10d */ 0x00,
  /* 0x10e */ 0x00,
  /* 0x10f */ 0x00,
  /* 0x110 */ 0x61,   /* SHIFT */
  /* 0x111 */ 0x47,   /* CONTROL */
  /* 0x112 */ 0x00,   /* ALT */
  /* 0x113 */ 0x00,   /* ALT_GR */
  /* 0x114 */ 0x21,   /* LEFT */
  /* 0x115 */ 0x17,   /* RIGHT */
  /* 0x116 */ 0x71,   /* DOWN */
  /* 0x117 */ 0x6171, /* UP */
  /* 0x118 */ 0x00,   /* HOME */
  /* 0x119 */ 0x00,   /* END */
  /* 0x11a */ 0x32,   /* DEL */
  /* 0x11b */ 0x00,   /* INSERT */
  /* 0x11c */ 0x00,
  /* 0x11d */ 0x00,
  /* 0x11e */ 0x00,   /* PAUSE */
  /* 0x11f */ 0x00,
  /* 0x120 */ 0x00,   /* COLOR */
  /* 0x121 */ 0x00,   /* GRAPHIC */
  /* 0x122 */ 0x00,   /* LIST */
  /* 0x123 */ 0x00,   /* RUN */
  /* 0x124 */ 0x00,   /* STOP */
  /* 0x125 */ 0x00,   /* SHIFT LOCK */

  /* 0x126 */ 0x00,
  /* 0x127 */ 0x00,
  /* 0x128 */ 0x00,
  /* 0x129 */ 0x00,
  /* 0x12a */ 0x00,
  /* 0x12b */ 0x00,
  /* 0x12c */ 0x00,
  /* 0x12d */ 0x00,
  /* 0x12e */ 0x00,
  /* 0x12f */ 0x00,
};

#endif /* __kc_kramermc_keydef_h */
