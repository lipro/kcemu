/*
 *  KCemu -- the KC 85/3 and KC 85/4 Emulator
 *  Copyright (C) 1997-2004 Torsten Paul
 *
 *  $Id: mod_list.cc,v 1.16 2002/10/31 01:46:35 torsten_paul Exp $
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

/*
 *  Quelle: http://www.kc85emu.de/scans/fa0192/Bild5.jpg
 *  Original: Zeitschrift Funkamateur
 * 
 *  ---: D001 Grundger�t KC85/2
 *  ---: D001 Grundger�t KC85/3
 *  ---: D001 Grundger�t KC85/4
 *  ---: D002 Busdriver
 *  ---: D004 Floppy Disk Drive
 *  a7h: D004 Floppy Disk Basis (ROM) -- always at slot fch!
 *  efh: M001 Digital IN/OUT
 *  eeh: M003 V24 (2 Kan�le)
 *  ---: M005 User (Leermodul)
 *  ---: M006 BASIC (f�r KC 85/2)
 *  ---: M007 Adapter (Herausf�hrung der Anschl�sse an die Frontseite)
 *  ---: M008 Joystick
 *  e7h: M010 ADU1
 *  f6h: M011 64 KByte RAM
 *  fbh: M012 Software: Texor
 *  ---: M021 Joy + Centronics
 *  f4h: M022 Expander RAM (16 KByte)
 *  f7h: M025 User PROM (8 KByte)
 *  fbh: M026 Software: Forth
 *  fbh: M027 Software: Development
 *  e3h: M029 DAU1
 *  ---: M030 EPROMmer
 *  79h: M032 256 KByte RAM
 *  ---: M033 Software: TYPESTAR
 *  7bh: M035 1 MByte RAM
 *  7bh: M035 4 MByte RAM (intern 4 x 1MByte)
 *  ---: M036 128 KByte RAM
 *  ---: M040 USER PROM ? KByte
 *  ---: M053 RS 232
 *  ---: M125 USER ROM ? KByte
 */

/*
 *  Modul�bersicht f�r KC85
 *  
 *  von Mario Leubner
 *  
 *  (KC-News 2/95 - http://www.iee.et.tu-dresden.de/~kc-club/)
 *  
 *  Modul  Kenn.  Steuerb.  Bezeichnung
 *  
 *  D001     -       -      Grundger�t KC85/2 (PIO 88-8B, CTC 8C-8F)
 *  D001     -       -      Grundger�t KC85/3 (PIO 88-8B, CTC 8C-8F)
 *  D001     -       -      Grundger�t KC85/4 (OUT 84-87, PIO 88-8B, CTC 8C-8F)
 *  D002     -       -      Busdriver f�r 4 Module (OUT 80 zur Modulsteuerung)
 *  D003*    -       -      Programmer (�hnl. D002, ROM-Module brennen?)
 *  D004    A7    xxAxxKxM  Floppy Disk Basis (Koppel-RAM F0-F3, OUT F4-F7)
 *  D004     -       -      Floppy Disk Drive (Laufwerk K5601, 5 1/4")
 *  D005                    Komfort-Tastatur f�r KC85/4 (mit EMR UB8830)
 *  
 *  M000*   01              Spezial f. KC85/3: autom. Start in Schacht 8 ab 4000H
 *  M001    EF    xxxxxxxM  Digital IN/OUT (CTC 00-03, PIO 04-07)
 *  M002*   DA    xxxxxxxM  PIO 3 (PIO 10-13, PIO 14-17)
 *  M003    EE    xxxxxxxM  V.24 (2 Kan�le, SIO 08-0B, CTC 0C-0F)
 *  M005     -       -      USER-Leermodul (freie Ports: C0-CF, Kennbytes C0-D7)
 *  M006    FC    AAxxxxxM  BASIC und CAOS 3.1 f�r KC85/2 (1 Block zu 16K ROM)
 *  M007     -       -      Adapter (Busverl�ngerung f�r Modulschacht)
 *  M008     -       -      Joystick (PIO 90-93)
 *  M009*   ED    xxxxxxxM  TLCM (Spracheingabe- und Datenkompressionsmodul)
 *  M010    E7    xxxxxxxM  ADU1: 4 Analogeing�nge mit Multiplexer (PIO 40-43)
 *  M011    F6    AAxxxxWM  64K RAM (1 Block zu 64K, rotierbar)
 *  M012    FB    AAAxxxxM  Software: TEXOR + V.24-Treiber (1 Block ROM 8K)
 *  M021*    -       -      Joystick + Centronics (PIO 90-93)
 *  M022    F4    AAxxxxWM  Expander-RAM 16K (1 Block zu 16K)
 *  M024*   F5    AAxxxxWM  32K RAM (1 Block zu 32K)
 *  M025    F7    AAAxxxxM  USER PROM 8K (1 Block zu 8K, 4 Sockel f�r 2716)
 *  M026    FB    AAAxxxxM  Software: FORTH (1 Block ROM 8K)
 *  M027    FB    AAAxxxxM  Software: DEVELOPMENT+V.24-Treiber (1 Block ROM 8K)
 *  M029    E3    xxxxxxxM  DAU1: 2 Analogausg�nge + 1 Relais (OUT 44..47)
 *  M030    D9              EPROMER ?
 *  M030    DB    AAAxxxxM  EPROMER f�r 2-64K (8K EPROM, PIO D0-D3, PIO D4-D7)
 *  M032    79    AxSSSSWM  256K segmented RAM (16 Bl�cke je 16K, 4000 od. 8000)
 *  M033    01    AA0SxxxM  Software: TYPESTAR+RAMDOS (2 Bl�cke ROM zu je 8K)
 *  M034    7A    ASSSSSWM  512K segmented RAM (32 Bl�cke je 16K, 4000 od. 8000)
 *  M035    7B    SSSSSSWM  1M segmented RAM (64 Bl�cke je 16K, Adr. 8000)
 *  M036    78    AxxSSSWM  128K segmented RAM (8 Bl�cke je 16K, 4000 od. 8000)
 *  M040    F8    AAxxxxxM  USER PROM 16K (1 Block zu 16KByte)
 *  M045    70    AASSxxxM  32K segmented ROM (4 Bl�cke je 8K)
 *  M046    71    AASSxSxM  64K segmented ROM (8 Bl�cke je 8K)
 *  M047    72    AASSSSxM  128K segmented ROM (16 Bl�cke je 8K)
 *  M048*   73    AASSSSxM  256K segmented ROM (16 Bl�cke je 16K)
 *  M053    EE    xxxxxxxM  RS232: wie M003, jedoch 2. Kanal mit TTL-Pegel
 *  M120*   F0    AAAxxxWM  8K CMOS-RAM (1 Block zu 8K)
 *  M122*   F1    AAxxxxWM  16K CMOS-RAM (1 Block zu 16K)
 *  M124*   F2    AAxxxxWM  32K CMOS-RAM (1 Block zu 32K)
 *  
 *  Im Steuerbyte bedeuten:
 *  
 *      A (Basis-)Adresse
 *      K Kopplung ein/aus
 *      S Segmentnummer
 *      W Schreibfreigabe
 *      M Modulschaltzustand
 *      x nicht benutzt
 *  
 *  Verwendete Kennbytes
 *  
 *      01 Autostart-ROM
 *      7x segmented Memory
 *      Dx..Ex I/O-Module
 *      Fx Memory
 *  
 *  Mit '*' gekennzeichnete Module kamen offenbar nicht in den Handel! 
 */

#include <string.h>

#include "kc/system.h"

#include "kc/kc.h"
#include "kc/rc.h"
#include "kc/mod_dio.h"
#include "kc/mod_ram.h"
#include "kc/mod_ram1.h"
#include "kc/mod_r64.h"
#include "kc/mod_cpm.h"
#include "kc/mod_ram8.h"
#include "kc/mod_64k.h"
#include "kc/mod_128k.h"
#include "kc/mod_256k.h"
#include "kc/mod_512k.h"
#include "kc/mod_1m.h"
#include "kc/mod_4m.h"
#include "kc/mod_rom.h"
#include "kc/mod_rom1.h"
#include "kc/mod_romb.h"
#include "kc/mod_boot.h"
#include "kc/mod_192k.h"
#include "kc/mod_320k.h"
#include "kc/mod_fdc.h"
#include "kc/mod_gdc.h"
#include "kc/mod_rtc.h"
#include "kc/mod_ramf.h"
#include "kc/mod_disk.h"
#include "kc/mod_list.h"
#include "kc/mod_4131.h"

#ifdef HOST_OS_LINUX
#include "kc/mod_v24.h"
#include "kc/mod_js.h"
#endif /* HOST_OS_LINUX */

#include "ui/ui.h"
#include "ui/error.h"

#include "libdbg/dbg.h"

ModuleList::ModuleList(void)
{
  int cnt;
  char *ptr;
  ModuleInterface *m;
  ModuleListEntry *entry;
  
  /*
   *  placeholder for a not present module ;-)
   */
  m = 0;
  _mod_list.push_back(new ModuleListEntry(_("<no module>"), m, KC_TYPE_ALL));

  /*
   *  RAM modules 1k at 2400h-27ffh,
   *                    2800h-2fffh,
   *                    3000h-3fffh,
   *                    4000h-7fffh,
   *                    8000h-ffffh
   *  (lc80)
   */
  m = new ModuleRAM8("RAM2400", 0x2400, 0x0400);
  _mod_list.push_back(new ModuleListEntry(_("RAM Module (1k/2400h)"), m, KC_TYPE_LC80));
  m = new ModuleRAM8("RAM2800", 0x2800, 0x0800);
  _mod_list.push_back(new ModuleListEntry(_("RAM Module (2k/2800h)"), m, KC_TYPE_LC80));
  m = new ModuleRAM8("RAM3000", 0x3000, 0x1000);
  _mod_list.push_back(new ModuleListEntry(_("RAM Module (4k/3000h)"), m, KC_TYPE_LC80));
  m = new ModuleRAM8("RAM4000", 0x4000, 0x4000);
  _mod_list.push_back(new ModuleListEntry(_("RAM Module (16k/4000h)"), m, KC_TYPE_LC80));
  m = new ModuleRAM8("RAM8000", 0x8000, 0x8000);
  _mod_list.push_back(new ModuleListEntry(_("RAM Module (32k/8000h)"), m, KC_TYPE_LC80));

  /*
   *  256k RAM floppy (Z1013)
   */
  m = new ModuleRAMFloppy("RAMFLOPPY");
  _mod_list.push_back(new ModuleListEntry(_("256k RAM Floppy"), m, KC_TYPE_Z1013));

  /*
   *  FDC (schneider) (Z1013)
   */
  m = new ModuleFDC("FDC_SCHNEIDER", ModuleFDC::FDC_INTERFACE_SCHNEIDER);
  _mod_list.push_back(new ModuleListEntry(_("FDC (Schneider)"), m, KC_TYPE_Z1013));

  /*
   *  FDC (kramer) (Z1013)
   */
  m = new ModuleFDC("FDC_KRAMER", ModuleFDC::FDC_INTERFACE_KRAMER);
  _mod_list.push_back(new ModuleListEntry(_("FDC (Kramer)"), m, KC_TYPE_Z1013));

  /*
   *  GDC (Z1013)
   */
  m = new ModuleGDC("GDC");
  _mod_list.push_back(new ModuleListEntry(_("GDC 82720"), m, KC_TYPE_Z1013));

  /*
   *  RTC (port 20h-2fh) (Z1013)
   */
  m = new ModuleRTC("RTC20", 0x20);
  _mod_list.push_back(new ModuleListEntry(_("RTC (port 20h-2fh)"), m, KC_TYPE_Z1013));

  /*
   *  RTC (port 70h-7fh) (Z1013)
   */
  m = new ModuleRTC("RTC70", 0x70);
  _mod_list.push_back(new ModuleListEntry(_("RTC (port 70h-7fh)"), m, KC_TYPE_Z1013));

  /*
   *  basic (kc85/1)
   */
  ptr = new char[strlen(kcemu_datadir) + 14];
  strcpy(ptr, kcemu_datadir);
  strcat(ptr, "/basic_c0.851");
  m = new ModuleROM1(ptr, "BASIC", 0xc000, 0x2800);
  _mod_list.push_back(new ModuleListEntry(_("Basic Module (c000h-e7ffh)"), m, KC_TYPE_85_1));
  delete[] ptr;

  /*
   *  plotter module (kc85/1, kc87.10, kc87.11)
   *
   *  The ROM of this module is identical with the internal ROM BASIC of the KC87.21
   *  that already includes the extensions to interface to an external plotter unit
   *  like the XY4131. To actually use the plotter an additional driver is needed
   *  though.
   */
  ptr = new char[strlen(kcemu_datadir) + 14];
  strcpy(ptr, kcemu_datadir);
  strcat(ptr, "/basic_c0.87b");
  m = new ModuleROM1(ptr, "PLOTTER", 0xc000, 0x2800);
  _mod_list.push_back(new ModuleListEntry(_("Plotter Module (c000h-e7ffh)"), m, KC_TYPE_85_1));
  delete[] ptr;

  /*
   *  RAM modules 16k at 4000h and 8000h (kc85/1)
   */
  m = new ModuleRAM1("RAM4", 0x4000, 0x4000);
  _mod_list.push_back(new ModuleListEntry(_("RAM Module (16k/4000h)"), m, KC_TYPE_85_1_CLASS));
  m = new ModuleRAM1("RAM8", 0x8000, 0x4000);
  _mod_list.push_back(new ModuleListEntry(_("RAM Module (16k/8000h)"), m, KC_TYPE_85_1_CLASS));

  /*
   *  ZM30 (kc85/1)
   */
  ptr = new char[strlen(kcemu_datadir) + 14];
  strcpy(ptr, kcemu_datadir);
  strcat(ptr, "/zm30__c0.851");
  m = new ModuleROM1(ptr, "ZM30", 0xc000, 0x0d00, true);
  _mod_list.push_back(new ModuleListEntry(_("ZM30 (c000h-ccffh)"), m, KC_TYPE_85_1_CLASS));
  delete[] ptr;

  /*
   *  edas (kc85/1)
   */
  ptr = new char[strlen(kcemu_datadir) + 14];
  strcpy(ptr, kcemu_datadir);
  strcat(ptr, "/edas__c0.851");
  m = new ModuleROM1(ptr, "EDAS", 0xc000, 0x2800, true);
  _mod_list.push_back(new ModuleListEntry(_("EDAS (c000h-e7ffh)"), m, KC_TYPE_85_1_CLASS));
  delete[] ptr;

  /*
   *  idas (kc85/1)
   */
  ptr = new char[strlen(kcemu_datadir) + 14];
  strcpy(ptr, kcemu_datadir);
  strcat(ptr, "/idas__c0.851");
  m = new ModuleROM1(ptr, "IDAS", 0xc000, 0x2800, true);
  _mod_list.push_back(new ModuleListEntry(_("IDAS / ZM (c000h-e7ffh)"), m, KC_TYPE_85_1_CLASS));
  delete[] ptr;

  /*
   *  bitex (kc85/1)
   */
  ptr = new char[strlen(kcemu_datadir) + 14];
  strcpy(ptr, kcemu_datadir);
  strcat(ptr, "/bitex_c0.851");
  m = new ModuleROM1(ptr, "BITEX", 0xc000, 0x1800, true);
  _mod_list.push_back(new ModuleListEntry(_("BITEX (c000h-d7ffh)"), m, KC_TYPE_85_1_CLASS));
  delete[] ptr;

  /*
   *  zsid (kc85/1)
   */
  /*
  ptr = new char[strlen(kcemu_datadir) + 14];
  strcpy(ptr, kcemu_datadir);
  strcat(ptr, "/zsid__c0.851");
  m = new ModuleROM1(ptr, "ZSID", 0xc000, 0x2800, true);
  _mod_list.push_back(new ModuleListEntry(_("ZSID (c000h-e7ffh)"), m, KC_TYPE_85_1_CLASS));
  delete[] ptr;
  */

  /*
   *  r80 (kc85/1)
   */
  /*
  ptr = new char[strlen(kcemu_datadir) + 14];
  strcpy(ptr, kcemu_datadir);
  strcat(ptr, "/r80___c0.851");
  m = new ModuleROM1(ptr, "R80", 0xc000, 0x1c00, true);
  _mod_list.push_back(new ModuleListEntry(_("R80 (c000h-dbffh)"), m, KC_TYPE_85_1_CLASS));
  delete[] ptr;
  */

  /*
   *  192 KByte RAM/EPROM module (kc85/1)
   */
  ptr = new char[strlen(kcemu_datadir) + 14];
  strcpy(ptr, kcemu_datadir);
  char * ptr_d2 = strcat(ptr, "/192k__d2.851");
  ptr = new char[strlen(kcemu_datadir) + 14];
  strcpy(ptr, kcemu_datadir);
  char * ptr_d3 = strcat(ptr, "/192k__d3.851");
  ptr = new char[strlen(kcemu_datadir) + 14];
  strcpy(ptr, kcemu_datadir);
  char * ptr_d5 = strcat(ptr, "/192k__d5.851");
  m = new Module192k(ptr_d2, ptr_d3, ptr_d5, "192k");
  _mod_list.push_back(new ModuleListEntry(_("192 KByte RAM/EPROM"), m, KC_TYPE_85_1_CLASS));
  delete[] ptr_d2;
  delete[] ptr_d3;
  delete[] ptr_d5;

  /*
   *  320k ROM Modul (kc85/1)
   */
  ptr = new char[strlen(kcemu_datadir) + 11];
  strcpy(ptr, kcemu_datadir);
  strcat(ptr, "/super.rom");
  m = new Module320k(ptr, "Super");
  _mod_list.push_back(new ModuleListEntry(_("320k ROM Module"), m, KC_TYPE_85_1_CLASS));
  delete [] ptr;

  /*
   *  128 KByte ROM bank module (kc85/1)
   */
  ptr = new char[strlen(kcemu_datadir) + 14];
  strcpy(ptr, kcemu_datadir);
  strcat(ptr, "/rom_bank.851");
  m = new ModuleROMBank(ptr, "ROMBANK");
  _mod_list.push_back(new ModuleListEntry(_("128k ROM Bank"), m, KC_TYPE_85_1_CLASS));
  delete[] ptr;

  /*
   *  IRM Expansion for color display (kc85/1)
   *
   *  FIXME: check whether to enable the color expansion by default shouldn't
   *  FIXME: go here!
   */
  m = new ModuleRAM1("IRMX", 0xe800, 0x0800);
  _color_expansion = new ModuleListEntry(_("IRM Color Expansion"), m, KC_TYPE_NONE);
  _mod_list.push_back(_color_expansion);
  _init_color_expansion = 0;
  if (get_kc_type() == KC_TYPE_85_1)
    if (get_kc_variant() == KC_VARIANT_85_1_11)
      _init_color_expansion = _color_expansion;
  if (get_kc_type() == KC_TYPE_87)
    if ((get_kc_variant() != KC_VARIANT_87_10) && (get_kc_variant() != KC_VARIANT_87_20))
      _init_color_expansion = _color_expansion;

  /*
   *  Plotter-Anschlu�
   */
#ifdef HOST_OS_LINUX
  m = new ModuleXY4131("XY4131");
  _mod_list.push_back(new ModuleListEntry(_("Plotter XY4131"), m, KC_TYPE_85_1_CLASS));
#endif /* HOST_OS_LINUX */

  /*
   *  CPM-Z9 boot rom module (kc85/1)
   */
  ptr = new char[strlen(kcemu_datadir) + 14];
  strcpy(ptr, kcemu_datadir);
  strcat(ptr, "/cpmz9_c0.851");
  m = new ModuleBOOT(ptr, "CPM-Z9-BOOT", 0xc000, 0x0800, true);
  _mod_list.push_back(new ModuleListEntry(_("CPM-Z9 BOOT (c000h-c7ffh)"), m, KC_TYPE_85_1_CLASS));
  delete[] ptr;

  /*
   *  CPM-Z9 floppy module (kc85/1)
   */
  m = new ModuleCPMZ9("CPM-Z9-FLOPPY");
  _mod_list.push_back(new ModuleListEntry(_("CPM-Z9 Floppy"), m, KC_TYPE_85_1_CLASS));

  /*
   *  CPM-Z9 64k ram module
   */
  m = new ModuleRAM64("CPM-Z9-RAM64");
  _mod_list.push_back(new ModuleListEntry(_("CPM-Z9 64k RAM"), m, KC_TYPE_85_1_CLASS));

  /*
   *  Digital I/O (kc85/2-4)
   */
  m = new ModuleDIO("M001", 0xef);
  _mod_list.push_back(new ModuleListEntry(_("M001: Digital In / Out"), m, KC_TYPE_85_2_CLASS));

  /*
   *  V24 module
   */
#ifdef HOST_OS_LINUX
  if (RC::instance()->get_int("Enable V24-Module"))
    {
      m = new ModuleV24("M003", 0xee);
      entry = new ModuleListEntry(_("M003: V24"), m, KC_TYPE_85_2_CLASS);
      _mod_list.push_back(entry);
    }

  /*
   *  basic (kc85/2) (this is actually 16k and includes a new system rom!)
   */
  ptr = new char[strlen(kcemu_datadir) + 10];
  strcpy(ptr, kcemu_datadir);
  strcat(ptr, "/m006.rom");
  m = new ModuleROM(ptr, "M006", 0x4000, 0xfb);
  _mod_list.push_back(new ModuleListEntry(_("M006: Basic"), m, KC_TYPE_85_2_CLASS));
  delete[] ptr;

  /*
   *  Joystick module (kc85/2-4)
   */
  m = new ModuleJoystick("M008", 0xff);
  _mod_list.push_back(new ModuleListEntry(_("M008: Joystick"), m, KC_TYPE_85_2_CLASS));
#endif /* HOST_OS_LINUX */

  /*
   *  RAM module 64k (kc85/2-4)
   */
  m = new Module64k("M011", 0xf6);
  _mod_list.push_back(new ModuleListEntry(_("M011: 64k RAM"), m, KC_TYPE_85_2_CLASS));
  
  /*
   *  texor
   */
  ptr = new char[strlen(kcemu_datadir) + 10];
  strcpy(ptr, kcemu_datadir);
  strcat(ptr, "/m012.rom");
  m = new ModuleROM(ptr, "M012", 0x2000, 0xfb);
  _mod_list.push_back(new ModuleListEntry(_("M012: Texor"), m, KC_TYPE_85_2_CLASS));
  delete[] ptr;

  /*
   *  RAM module 16k (kc85/2-4)
   */
  m = new ModuleRAM("M022", 0xf4);
  _mod_list.push_back(new ModuleListEntry(_("M022: Expander RAM (16k)"), m, KC_TYPE_85_2_CLASS));

  /*
   *  forth
   */
  ptr = new char[strlen(kcemu_datadir) + 10];
  strcpy(ptr, kcemu_datadir);
  strcat(ptr, "/m026.rom");
  m = new ModuleROM(ptr, "M026", 0x2000, 0xfb);
  _mod_list.push_back(new ModuleListEntry(_("M026: Forth"), m, KC_TYPE_85_2_CLASS));
  delete[] ptr;

  /*
   *  development
   */
  ptr = new char[strlen(kcemu_datadir) + 10];
  strcpy(ptr, kcemu_datadir);
  strcat(ptr, "/m027.rom");
  m = new ModuleROM(ptr, "M027", 0x2000, 0xfb);
  entry = new ModuleListEntry(_("M027: Development"), m, KC_TYPE_85_2_CLASS);
  _mod_list.push_back(entry);
  delete[] ptr;

  /*
   *  RAM module 256k (kc85/2-4)
   */
  m = new Module256k("M032", 0x79);
  _mod_list.push_back(new ModuleListEntry(_("M032: 256k Segmented RAM"), m, KC_TYPE_85_2_CLASS));

  /*
   *  RAM module 512k (kc85/2-4)
   */
  m = new Module512k("M034", 0x7a);
  _mod_list.push_back(new ModuleListEntry(_("M034: 512k Segmented RAM"), m, KC_TYPE_85_2_CLASS));

  /*
   *  RAM module 1M (kc85/2-4)
   */
  m = new Module1M("M035", 0x7b);
  _mod_list.push_back(new ModuleListEntry(_("M035: 1M Segmented RAM"), m, KC_TYPE_85_2_CLASS));

  /*
   *  RAM module 4M (kc85/2-4)
   */
  m = new Module4M("M035x4", 0x7b);
  _mod_list.push_back(new ModuleListEntry(_("M035x4: 4M RAM"), m, KC_TYPE_85_2_CLASS));

  /*
   *  RAM module 128k (kc85/2-4)
   */
  m = new Module128k("M036", 0x78);
  _mod_list.push_back(new ModuleListEntry(_("M036: 128k Segmented RAM"), m, KC_TYPE_85_2_CLASS));

  /*
   *  wordpro ROM version for kc85/3
   */
  ptr = new char[strlen(kcemu_datadir) + 10];
  strcpy(ptr, kcemu_datadir);
  strcat(ptr, "/m900.rom");
  m = new ModuleROM(ptr, "M900", 0x2000, 0xfb);
  entry = new ModuleListEntry(_("M900: WordPro '86 (KC85/3)"), m, KC_TYPE_85_3);
  _mod_list.push_back(entry);
  delete[] ptr;

  /*
   *  wordpro ROM version for kc85/4
   */
  ptr = new char[strlen(kcemu_datadir) + 10];
  strcpy(ptr, kcemu_datadir);
  strcat(ptr, "/m901.rom");
  m = new ModuleROM(ptr, "M901", 0x2000, 0xfb);
  entry = new ModuleListEntry(_("M901: WordPro '86 (KC85/4)"), m, KC_TYPE_85_4);
  _mod_list.push_back(entry);
  delete[] ptr;

  /*
   *  Floppy Disk Basis Extension ROM (F8)
   */
  ptr = new char[strlen(kcemu_datadir) + 14];
  strcpy(ptr, kcemu_datadir);
  strcat(ptr, "/floppyf8.rom");
  m = new ModuleDisk(ptr, "Floppy Disk Basis F8", 0x2000, 0xa7);
  entry = new ModuleListEntry(_("Floppy Disk Basis F8"), m, KC_TYPE_NONE);
  _mod_list.push_back(entry);
  delete[] ptr;

  _init_floppy_basis_f8 = 0;
  if (get_kc_type() & KC_TYPE_85_2_CLASS)
    if (RC::instance()->get_int("Floppy Disk Basis", 0))
      _init_floppy_basis_f8 = entry;

  /*
   *  Floppy Disk Basis ROM (FC)
   */
  ptr = new char[strlen(kcemu_datadir) + 12];
  strcpy(ptr, kcemu_datadir);
  strcat(ptr, "/floppy.rom");
  m = new ModuleDisk(ptr, "Floppy Disk Basis FC", 0x2000, 0xa7);
  entry = new ModuleListEntry(_("Floppy Disk Basis FC"), m, KC_TYPE_NONE);
  _mod_list.push_back(entry);
  delete[] ptr;

  _init_floppy_basis_fc = 0;
  if (get_kc_type() & KC_TYPE_85_2_CLASS)
    if (RC::instance()->get_int("Floppy Disk Basis", 0))
      _init_floppy_basis_fc = entry;
  
  bool swap_floppy_roms = (get_kc_type() == KC_TYPE_85_5) ? true : false;
  if (RC::instance()->get_int("Swap Floppy ROMs", 0))
    swap_floppy_roms = !swap_floppy_roms;

  if (get_kc_type() & KC_TYPE_85_2_CLASS)
    if (RC::instance()->get_int("Floppy Disk Basis", 0))
      if (swap_floppy_roms)
	{
	  // entry is still set to the FC module...
	  _init_floppy_basis_fc = _init_floppy_basis_f8;
	  _init_floppy_basis_f8 = entry;
	}
    
  if (get_kc_type() & KC_TYPE_85_2_CLASS)
    if (!RC::instance()->get_int("Enable Second Floppy ROM", 0))
      _init_floppy_basis_f8 = 0;

  _nr_of_bd = RC::instance()->get_int("Busdrivers");
  if (_nr_of_bd < 0)
    _nr_of_bd = 0;
  if (_nr_of_bd > MAX_BD)
    _nr_of_bd = MAX_BD;
  if (get_kc_type() & KC_TYPE_85_1_CLASS)
    _nr_of_bd = 0;
  if (get_kc_type() & KC_TYPE_LC80)
    _nr_of_bd = 1;

  switch (get_kc_type())
    {
    case KC_TYPE_85_1:
    case KC_TYPE_87:
      cnt = 4;
      break;
    case KC_TYPE_Z1013:
      cnt = 8;
      break;
    case KC_TYPE_85_2:
    case KC_TYPE_85_3:
    case KC_TYPE_85_4:
      cnt = 4 * _nr_of_bd + 2;
      break;
    default:
      cnt = 0;
      break;
    }

  add_custom_modules();

  init_modules(cnt);
}

void
ModuleList::add_custom_modules(void)
{
  for (int a = 0;a < 10;a++)
    {
      const char *name = RC::instance()->get_string_i(a, "Custom ROM Module");
      const char *text = RC::instance()->get_string_i(a, "Custom ROM Module (Name)");
      int id = RC::instance()->get_int_i(a, "Custom ROM Module (Id)");
      const char *file = RC::instance()->get_string_i(a, "Custom ROM Module (File)");
      int size = RC::instance()->get_int_i(a, "Custom ROM Module (Size)");

      if ((name == NULL) || (file == NULL))
	continue;

      if (id == 0)
	id = 0xfb;

      size &= 0xfc00;

      if (size == 0)
	size = 0x2000;

      if (size > 0x4000)
	size = 0x4000;

      if (text == NULL)
	text = name;

      ModuleInterface *m = new ModuleROM(file, name, size, id);
      ModuleListEntry *entry = new ModuleListEntry(text, m, KC_TYPE_85_2_CLASS);
      _mod_list.push_back(entry);
    }
}

void
ModuleList::init_modules(int max_modules)
{
  int idx, mode;
  const char *mod;
  char *ptr, *buffer;

  for (int a = 0;a < 4 * MAX_BD + 2;a++)
    _init_mod[a] = NULL;

  mode = 1;
  ptr = kcemu_modules;
  if (ptr)
    {
      if (*ptr == '+')
        ptr++;
      else
	mode = 0;
    }

  idx = 0;
  if (mode == 1)
    for (int a = 0;a < max_modules;a++)
      {
	mod = RC::instance()->get_string_i(a, "Module");
	if (mod)
	  _init_mod[idx++] = strdup(mod);
      }

  if (kcemu_modules == NULL)
    return;
  
  buffer = new char[strlen(ptr) + 1];
  strcpy(buffer, ptr);

  ptr = strtok(buffer, ",");
  while (ptr != 0)
    {
      _init_mod[idx++] = strdup(ptr);
      ptr = strtok(0, ",");
    }

  delete[] buffer;
}

ModuleList::~ModuleList(void)
{
  ModuleList::iterator it;

  for (it = module_list->begin();it != module_list->end();it++)
    {
      ModuleListEntry *entry = *it;
      delete entry->get_mod();
      delete entry;
    }

  for (int a = 0;a < 4 * MAX_BD + 2;a++)
    if (_init_mod[a])
      free(_init_mod[a]);

  /* inserted clones of modules are freed in module.cc */
}

void
ModuleList::init(void)
{
  int a;
  ModuleInterface *m;
  ModuleList::iterator it;

  for (a = 0;a < 4 * MAX_BD + 2;a++)
    {
      if (!_init_mod[a])
	continue;

      for (it = module_list->begin();it != module_list->end();it++)
        {
          m = (*it)->get_mod();
          if (!m)
	    continue;
          if (strcmp(m->get_name(), _init_mod[a]) == 0)
            insert(a, *it);
        }
    }
  if (_init_floppy_basis_f8)
    {
      /*
       *  floppy disk basis extension ROM is always in slot f8h!
       */
      insert(60, _init_floppy_basis_f8);
    }

  if (_init_floppy_basis_fc)
    {
      /*
       *  floppy disk basis ROM is always in slot fch!
       */
      insert(61, _init_floppy_basis_fc);
    }

  if (_init_color_expansion)
    {
      /*
       *  this is set if the emulator runs in KC 87 mode which means
       *  the color expansion is always present
       *  the KC 87 doesn't support the module slot notation like
       *  the KC 85/2 class we just insert it at slot fch like
       *  the floppy disk interface for KC 85/2 which is never available
       *  in KC 87 mode.
       */
      insert(61, _init_color_expansion);
    }
}

void
ModuleList::insert(int slot, ModuleListEntry *entry)
{
  ModuleInterface *m = NULL;
  
  /*
   *  the module object is deleted in module->insert()
   *  or module->remove()!
   */
  if (entry != NULL)
    m = entry->get_mod();

  if (m)
    {
      ModuleInterface *mod = m->clone();
      if (!mod)
	return;

      if (mod->is_valid())
	{
	  module->insert(slot, mod);
	}
      else
	{
	  const char *error_text = mod->get_error_text();
	  if (error_text != NULL)
	    Error::instance()->info(error_text);
	  m = NULL;
	  delete mod;
	}
    }
  else
    {
      module->remove(slot);
    }

  ui->getModuleInterface()->insert(slot, m);
  ui->getModuleInterface()->activate(slot, 0);
}

ModuleListEntry *
ModuleList::get_color_expansion()
{
  return _color_expansion;
}
