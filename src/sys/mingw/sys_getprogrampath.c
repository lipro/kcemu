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

#include <windows.h>

#include "kc/config.h"
#include "sys/sysdep.h"

char *
sys_getprogrampath(void)
{
  int len;
  TCHAR cmd[MAX_PATH];

  int ret = GetModuleFileName(NULL, cmd, MAX_PATH);
  if ((ret == 0) || (ret == MAX_PATH))
    return NULL;

  // safeguard against path without drive letter
  if ((cmd[1] != ':') || (cmd[2] != '\\'))
    return NULL;

  // remove filename, loop end checked above
  len = strlen(cmd);
  while (cmd[len - 1] != '\\') len--;
  
  cmd[len] = '\0';

  return strdup(cmd);
}
