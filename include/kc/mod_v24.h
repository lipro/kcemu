/*
 *  KCemu -- the KC 85/3 and KC 85/4 Emulator
 *  Copyright (C) 1997-1998 Torsten Paul
 *
 *  $Id: mod_v24.h,v 1.6 2001/01/05 18:38:40 tp Exp $
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

#ifndef __kc_mod_v24_h
#define __kc_mod_v24_h

#include <string.h>
#include <termios.h>

#include "kc/ic.h"
#include "kc/ports.h"
#include "kc/module.h"

class ModuleV24 : public ModuleInterface,
		  public PortInterface,
		  public InterfaceCircuit
{
private:
  typedef enum { IO_NONE, IO_FILE, IO_SOCKET, IO_FIFO } io_type_t;
  
  enum {
    A         = 0,
    B         = 1,
    CHANNELS  = 2,
    WR_REGS   = 7,
    RD_REGS   = 3,
    INBUF_LEN = 1024,
  };

  byte_t _in_buf[INBUF_LEN], *_in_buf_ptr;
  int _reg[CHANNELS];
  byte_t _reg_wr[CHANNELS][WR_REGS];
  byte_t _reg_rd[CHANNELS][RD_REGS];
  byte_t _data_in[CHANNELS];
  int    _irq_pending[CHANNELS];
  int    _irq_active[CHANNELS];
  int _fd_in[CHANNELS];
  int _fd_out[CHANNELS];
  struct termios _tio_old[CHANNELS];
  struct termios _tio_new[CHANNELS];
  bool _ok;
  byte_t _id;
  byte_t _val;
  const char *_name;
  char *_socket_name;
  int _pid;
  PortGroup *_portg;
  io_type_t _io_type;
  
protected:
  void open_device(void);
  void close_device(void);
  bool open_device_serial(int dev, const char *dev_name);
  bool open_device_socket_or_fifo(io_type_t io_type);
  void set_signal_handler(int fd, void (*sig_func)(int));
  static void signal_handler_IO_read(int status);
  static void signal_handler_IO_recv(int status);
  void push_data(char *buf, int len);
  void socket_server(int fd);
  void fifo_server(int fd);
  
public:
  ModuleV24(ModuleV24 &tmpl);
  ModuleV24(const char *name, byte_t id);
  virtual ~ModuleV24(void);

  virtual byte_t in(word_t addr);
  virtual void out(word_t addr, byte_t val);
  virtual byte_t in_reg(int channel);
  virtual void out_reg(int channel, byte_t val);
  virtual ModuleInterface * clone(void);

  void iei(byte_t val);
  virtual void reset(bool power_on = false);
  virtual void reti(void);
};

#endif /* __kc_mod_v24_h */
