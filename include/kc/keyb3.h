/*
 *  KCemu -- the KC 85/3 and KC 85/4 Emulator
 *  Copyright (C) 1997-1998 Torsten Paul
 *
 *  $Id: keyb3.h,v 1.4 2001/01/06 15:11:37 tp Exp $
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

#ifndef __kc_keyb3_h
#define __kc_keyb3_h

#include <glib.h>

#include "kc/kc.h"
#include "kc/cb.h"
#include "kc/keyboard.h"

/*
 *  serial keyboard protocol (U807/ SAB 3011)
 *
 *  bit 0 = 5.120 ms = 5 * 64 * 16�s
 *  bit 1 = 7.168 ms = 7 * 64 * 16�s
 *
 *  Tw  = 14.336 ms = 14 * 64 * 16�s (time between repeated words)
 *  Tdw = 19.456 ms = 19 * 64 * 16�s (time between double words)
 *
 *  Every keypress is encoded by sending a double word (2 x 7 bits)
 *  with a delay (Tw) between both words.
 *  If the key remains pressed the the double word is repeated
 *  immedately after the first double word (delay = Tdw)
 *
 *  The delay before the user visible key repeat is done by the
 *  KC ROM-software!
 *
 *  Key release is determined by CTC interrupt. The timer is
 *  loaded with a value of 143 (and clock divider = 256) which
 *  gives a timeout (Tto) of about 21 ms.
 *
 *  KC85/4 runs with 1.75 MHz which gives the following cycle
 *  counts for the delays above:
 *
 *  1 cycle is 1/1750000 seconds = 0.0005714 ms = 0.5714 �s
 *
 *  bit 0 =  5.120 ms  =>  8960 cycles
 *  bit 1 =  7.168 ms  => 12544 cycles
 *  Tw    = 14.336 ms  => 25088 cycles
 *  Tdw   = 19.456 ms  => 34048 cycles
 *  Tto   = 20.918 ms  => 36608 cycles
 */
class Keyboard3 : public Keyboard
{
  private:
    int _lock;
    int _key;
    int _keysym;
    int _release;
    bool _shift;
    bool _control;
    int _replay_idx;
    int _replay_offset;
    GString *_replay_text;

    enum {
      KEY_CYCLES_BIT_0 =  8960,
      KEY_CYCLES_BIT_1 = 12544,
      KEY_CYCLES_T_W   = 25088,
      KEY_CYCLES_T_DW  = 34048,
      KEY_CYCLES_T_TO  = 36608,
    };

  protected:
    void sendKey(void);
    int checkReplay(void);

  public:
    Keyboard3(void);
    virtual ~Keyboard3(void) {}
    
    virtual void keyPressed(int keysym, int keycode);
    virtual void keyReleased(int keysym, int keycode);
    virtual void replayString(const char *text);

    virtual void callback(void *data);
};

#endif /* __kc_keyb3_h */
