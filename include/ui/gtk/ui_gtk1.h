/*
 *  KCemu -- the KC 85/3 and KC 85/4 Emulator
 *  Copyright (C) 1997-1998 Torsten Paul
 *
 *  $Id: ui_gtk1.h,v 1.3 2000/05/21 17:38:47 tp Exp $
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

#ifndef __ui_ui_gtk1_h
#define __ui_ui_gtk1_h

#include "ui/gtk/ui_gtk.h"

class UI_Gtk1 : public UI_Gtk
{
 private:
  byte_t     _changed[24];
  byte_t     _dirty_val[960];
  byte_t     _dirty_col[960];
  bool       _auto_skip;
  int        _cur_auto_skip;
  int        _max_auto_skip;

 protected:
  virtual void allocate_colors(void);

 public:
  UI_Gtk1(void);
  virtual ~UI_Gtk1(void);
  virtual void update(bool force_update);
  virtual void memWrite(int addr, char val);
  virtual void callback(void *data);
  virtual void flash(bool enable);
  
  virtual const char * get_title(void);
  virtual int get_width(void) { return 320; }
  virtual int get_height(void) { return 192; }

  virtual void reset(bool power_on = false);
};

#endif /* __ui_ui_gtk1_h */
