/*
 *  KCemu -- the KC 85/3 and KC 85/4 Emulator
 *  Copyright (C) 1997-2001 Torsten Paul
 *
 *  $Id$
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

#include "kc/system.h"

#include "kc/kc.h"
#include "kc/ports6.h"

#include "ui/generic/ui_6.h"

UI_6::UI_6(void) : UI_LED(560, 112, 32, 64, 1, 2, 4, 128, 16, 8)
{
}

UI_6::~UI_6(void)
{
}

void
UI_6::generic_update(bool clear_cache)
{
  byte_t led_value;

  for (int a = 0;a < 8;a++)
    {
      led_value = ((Ports6 *)porti)->get_led_value(a);
      generic_draw_digit(65 * a + 32, 12, a, led_value, clear_cache);
    }
}

int
UI_6::generic_get_mode(void)
{
  return 0;
}

void
UI_6::generic_set_mode(int mode)
{
}