/*
 *  KCemu -- the KC 85/3 and KC 85/4 Emulator
 *  Copyright (C) 1997-2001 Torsten Paul
 *
 *  $Id: ui_3.h,v 1.2 2002/10/31 01:02:43 torsten_paul Exp $
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

#ifndef __ui_generic_ui_3_h
#define __ui_generic_ui_3_h

#include "kc/system.h"

#include "ui/generic/scanline.h"

class UI_3
{
 protected:
  byte_t *_dirty;
  byte_t *_bitmap;
  byte_t *_pix_cache;
  byte_t *_col_cache;
  int     _dirty_size;

  int _bitswap1[256];
  int _bitswap2[256];
  int _bitswap3[256];

 protected:
  void generic_put_pixels(int x, int y, byte_t val, byte_t fg, byte_t bg);

 public:
  UI_3(void);
  virtual ~UI_3(void);

  virtual int get_real_width(void);
  virtual int get_real_height(void);

  virtual byte_t * get_dirty_buffer(void);
  virtual int get_dirty_buffer_size(void);

  virtual void generic_update(Scanline *scanline, bool clear_cache = false);
};

#endif /* __ui_generic_ui_3_h */