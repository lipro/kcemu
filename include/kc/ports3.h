/*
 *  KCemu -- the KC 85/3 and KC 85/4 Emulator
 *  Copyright (C) 1997-1998 Torsten Paul
 *
 *  $Id: ports3.h,v 1.4 2000/06/24 03:39:30 tp Exp $
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

#ifndef __kc_ports3_h
#define __kc_ports3_h

#include "kc/ports.h"

class Ports3 : public PortInterface
{
public:
  enum {
    NR_PORTS = 256,
  };

protected:
  byte_t inout[Ports::NR_PORTS];

protected:
  virtual void change_0x84(byte_t changed, byte_t val);
  virtual void change_0x86(byte_t changed, byte_t val);
  // virtual void change_0x88(byte_t changed, byte_t val);

public:
  Ports3(void);
  virtual ~Ports3(void);
  virtual byte_t in(word_t addr);
  virtual void out(word_t addr, byte_t val);
};

#endif /* __kc_ports3_h */
