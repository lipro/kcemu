/*
 *  KCemu -- the KC 85/3 and KC 85/4 Emulator
 *  Copyright (C) 1997-1998 Torsten Paul
 *
 *  $Id: mod_list.h,v 1.4 2000/06/24 03:39:23 tp Exp $
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

#ifndef __kc_mod_list_h
#define __kc_mod_list_h

#include <list.h>
#include <string.h>

#include "kc/config.h"
#include "kc/system.h"

#include "kc/module.h"

class ModuleListEntry
{
private:
  char *_name;
  ModuleInterface *_mod;
  
public:
  ModuleListEntry(const char *name, ModuleInterface *mod)
    {
      _mod = mod;
      _name = strdup(name);
    }
  virtual ~ModuleListEntry(void)
    {
      free(_name);
    }
  virtual ModuleInterface * get_mod(void) { return _mod; }
  virtual const char * get_name(void) { return _name; }
};

class ModuleList
{
private:
  enum {
    MAX_BD = 4,
  };

  int _nr_of_bd;
  ModuleListEntry *_init_floppy_basis;
  const char *_init_mod[4 * MAX_BD + 2];

  typedef list<ModuleListEntry *> mod_list_t;

public:
  typedef mod_list_t::iterator iterator;
    
private:
  mod_list_t _mod_list;

public:
  ModuleList(void);
  virtual ~ModuleList(void);
  virtual void init(void);
  virtual int get_nr_of_busdrivers(void) { return _nr_of_bd; }
  
  virtual void insert(int slot, ModuleListEntry *entry);
  virtual iterator begin(void) { return _mod_list.begin(); }
  virtual iterator end(void) { return _mod_list.end(); }
};

#endif /* __kc_mod_list_h */
