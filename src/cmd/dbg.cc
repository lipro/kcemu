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

#include "kc/kc.h"

#include "cmd/cmd.h"

#include "ui/status.h"

#include "libdbg/dbg.h"

class CMD_dbg : public CMD
{
public:
  
  CMD_dbg(void) : CMD("dbg")
    {
      register_cmd("reload-debug-config", 0);
    }

  void execute(CMD_Args *args, CMD_Context context)
    {
      Status::instance()->setMessage("*** RELOAD DEBUG CONFIG ***");
      DBG_load_config();
    }
};

__force_link(CMD_dbg);
