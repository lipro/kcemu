/*
 *  KCemu -- the KC 85/3 and KC 85/4 Emulator
 *  Copyright (C) 1997-1998 Torsten Paul
 *
 *  $Id: ui_gtk3.h,v 1.8 2000/07/09 21:12:23 tp Exp $
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

#ifndef __ui_ui_gtk3_h
#define __ui_ui_gtk3_h

#include "ui/gtk/ui_gtk.h"

class UI_Gtk3 : public UI_Gtk
{
 private:
  bool       _auto_skip;
  int        _cur_auto_skip;
  int        _max_auto_skip;

 protected:
  static int _bitswap1[256];
  static int _bitswap2[256];
  static int _bitswap3[256];
  
 protected:
  virtual void allocate_colors(void);
  
 public:
  UI_Gtk3(void);
  virtual ~UI_Gtk3(void);
  virtual void update(bool force_update);
  virtual void memWrite(int addr, char val);
  virtual void callback(void *data);
  virtual void flash(bool enable);

  virtual const char * get_title(void);
  virtual int get_width(void) { return 320; }
  virtual int get_height(void) { return 256; }

  virtual void reset(bool power_on = false);
};

#endif /* __ui_ui_gtk3_h */
