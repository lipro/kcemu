/*
 *  KCemu -- the KC 85/3 and KC 85/4 Emulator
 *  Copyright (C) 1997-2001 Torsten Paul
 *
 *  $Id: keyb8.cc,v 1.3 2002/10/31 01:46:35 torsten_paul Exp $
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
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <iostream>
#include <iomanip>

#include "kc/system.h"

#include "kc/keys.h"
#include "kc/keyb8.h"
#include "kc/keyb8k.h"

#include "cmd/cmd.h"

Keyboard8::Keyboard8(void)
{
  init();
}

Keyboard8::~Keyboard8(void)
{
}

void
Keyboard8::init(void)
{
}

void
Keyboard8::keyPressed(int keysym, int keycode)
{
  _key = __keys[keysym];
}

void
Keyboard8::keyReleased(int keysym, int keycode)
{
  _key = 0;

  if (keysym == 0x1b)
    CMD_EXEC("emu-reset");
  if (keysym == 0x10a)
    CMD_EXEC("lc80-key-f10");
  if (keysym == 0x10b)
    CMD_EXEC("lc80-key-f11");
  if (keysym == 0x10c)
    CMD_EXEC("lc80-key-f12");
}

void
Keyboard8::replayString(const char *text)
{
}

void
Keyboard8::callback(void *data)
{
}

int
Keyboard8::callback_A_in(void)
{
  return -1;
}

int
Keyboard8::callback_B_in(void)
{
  byte_t b;
  unsigned int c;

  b = ~pio->in_B_DATA();
  b >>= 2;

  c = 0xf0;
  if (_key & b)
    c = (~(_key & 0xf00) >> 4);

  pio2->set_B_EXT(0xf0, c);
  return c;
}

void
Keyboard8::reset(bool power_on)
{
  init();
}

void
Keyboard8::reti(void)
{
}
