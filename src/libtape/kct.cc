/*
 *  KCemu -- the KC 85/3 and KC 85/4 Emulator
 *  Copyright (C) 1997-1998 Torsten Paul
 *
 *  $Id: kct.cc,v 1.9 2000/07/15 13:24:40 tp Exp $
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

#include <string.h>
#include <strstream.h>

#include <zlib.h>

#include "libtape/kct.h"

#include "libdbg/dbg.h"

#define CHECK_HEAD(buffer, byte)           \
        (((buffer)[0] & 0xff) == (byte) && \
         ((buffer)[1] & 0xff) == (byte) && \
         ((buffer)[2] & 0xff) == (byte))

const unsigned short KCTFile::KCT_VERSION          = __KCT_VERSION__;
const unsigned long  KCTFile::BLOCK_SIZE           = 256;
const unsigned long  KCTFile::HEADER_OFFSET        = 0;
const unsigned long  KCTFile::BAM_OFFSET           = 256;
const unsigned long  KCTFile::DIR_BLOCKS           = KCT_DIR_BLOCKS;
const unsigned long  KCTFile::DIR_BLOCK1_OFFSET    = 512;
const unsigned long  KCTFile::DIRBLOCK_OFFSET_MASK = 0xffffff00;
const unsigned long  KCTFile::DIRBLOCK_INDEX_MASK  = 0x000000ff;
const unsigned long  KCTFile::DIRBLOCK_MAGIC       = 0x6564434b;

KCTDir::KCTDir(void)
{
}

KCTDir::~KCTDir(void)
{
}
  
void
KCTDir::clear(void)
{
  erase(begin(), end());
}

void
KCTDir::add(kct_dirent_t *dirent)
{
  insert(end(), dirent);
}

KCTFile::KCTFile(void)
{  
  /* cerr << "KCTFile::KCTFile()" << endl; */
}

KCTFile::~KCTFile(void)
{
  _f.close();
  /* cerr << "KCTFile::~KCTFile()" << endl; */
}

const char *
KCTFile::type_name(kct_file_type_t type)
{
  switch (type)
    {
    case KCT_TYPE_COM:    return "COM";
    case KCT_TYPE_BAS:    return "BASIC";
    case KCT_TYPE_MINTEX: return "MINTEX";
    case KCT_TYPE_BAS_P:  return "BASIC*";
    }
  return "???";
}

/*
 *  HEADER functions
 */
bool
KCTFile::header_read(kct_header_t &header, unsigned long offset)
{
  /* cerr.form("KCTFile::header_read():  %08lx\n", offset); */
  
  _f.seekp(offset);
  if (!_f)
    {
      cerr << "KCTFile::header_read(): seek error" << endl;
      return false;
    }
  _f.read(&header, sizeof(kct_header_t));
  if (!_f)
    {
      cerr << "KCTFile::header_read(): read error" << endl;
      return false;
    }
  if (strcmp("KCemu tape file\032", header.id) != 0) return false;

  if (header.version != KCT_VERSION)
    {
      cerr.form("Warning: tape version mismatch!\n");
      cerr.form("         expected v%d.%d and got v%d.%d\n",
                KCT_VERSION_MAJOR(KCT_VERSION),
                KCT_VERSION_MINOR(KCT_VERSION),
                KCT_VERSION_MAJOR(header.version),
                KCT_VERSION_MINOR(header.version));
    }

  return true;
}
void
KCTFile::header_write(kct_header_t &header, unsigned long offset)
{
  /* cerr.form("KCTFile::header_write():   %08lx\n", offset); */
  
  _f.seekp(offset);
  if (!_f)
    {
      cerr << "KCTFile::header_write(): seek error" << endl;
      exit(1);
    }
  _f.write(&header, sizeof(kct_header_t));
  if (!_f)
    {
      cerr << "KCTFile::header_write(): write error" << endl;
      exit(1);
    }  
}

/*
 *  BAM functions
 */
void
KCTFile::bam_clear(kct_bam_t &bam)
{
  memset(bam, 0, sizeof(kct_bam_t));
}

bool
KCTFile::bam_block_available(kct_bam_t &bam, long block)
{
  long a = block / 8;
  long b = block % 8;

  if (bam[a] & (128 >> b)) return false;
  return true;
}

void
KCTFile::bam_block_free(kct_bam_t &bam, long block)
{
  long a = block / 8;
  long b = block % 8;

  bam[a] &= ~(128 >> b);
}

void
KCTFile::bam_block_allocate(kct_bam_t &bam, long block)
{
  long a = block / 8;
  long b = block % 8;

  bam[a] |= (128 >> b);
}

unsigned long
KCTFile::bam_block_find_free(kct_bam_t &bam)
{
  unsigned int a;
  
  for (a = 0;a < 8 * sizeof(kct_bam_t);a++)
    {
      if (bam_block_available(bam, a))
        {
          bam_block_allocate(bam, a);
          return a * 256;
        }
    }

  return 0;
}

void
KCTFile::bam_read(kct_bam_t &bam, unsigned long offset)
{
  /* cerr.form("KCTFile::bam_read():  %08lx\n", offset); */
  
  _f.seekp(offset);
  if (!_f)
    {
      cerr << "KCTFile::bam_read(): seek error" << endl;
      exit(1);
    }
  _f.read(bam, sizeof(kct_bam_t));
  if (!_f)
    {
      cerr << "KCTFile::bam_read(): read error" << endl;
      exit(1);
    }
}
void
KCTFile::bam_write(kct_bam_t &bam, unsigned long offset)
{
  /* cerr.form("KCTFile::bam_write():      %08lx\n", offset); */
  
  _f.seekp(offset);
  if (!_f)
    {
      cerr << "KCTFile::bam_write(): seek error" << endl;
      exit(1);
    }
  _f.write(bam, sizeof(kct_bam_t));
  if (!_f)
    {
      cerr << "KCTFile::bam_write(): write error" << endl;
      exit(1);
    }  
}

/*
 *  DIRENT functions
 */
kct_error_t
KCTFile::dirblock_clear(kct_dirblock_t &dirblock)
{
  memset(dirblock, 0, sizeof(kct_dirblock_t));
  dirblock[0].magic = DIRBLOCK_MAGIC;
  dirblock[1].magic = DIRBLOCK_MAGIC;
  dirblock[2].magic = DIRBLOCK_MAGIC;
  dirblock[3].magic = DIRBLOCK_MAGIC;
  return KCT_OK;
}

kct_error_t
KCTFile::dirblock_read(kct_dirblock_t &dirblock, unsigned long offset)
{
  unsigned long o = offset & DIRBLOCK_OFFSET_MASK;
  /* cerr.form("KCTFile::dirblock_read():  %08lx [%08lx]\n", o, offset); */
  
  _f.seekp(o);
  if (!_f)
    {
      cerr << "KCTFile::dirblock_read(): seek error" << endl;
      return KCT_ERROR_IO;
    }
  _f.read(dirblock, sizeof(kct_dirblock_t));
  if (!_f)
    {
      cerr << "KCTFile::dirblock_read(): read error" << endl;
      return KCT_ERROR_IO;
    }
  if ((dirblock[0].magic != DIRBLOCK_MAGIC) ||
      (dirblock[1].magic != DIRBLOCK_MAGIC) ||
      (dirblock[2].magic != DIRBLOCK_MAGIC) ||
      (dirblock[3].magic != DIRBLOCK_MAGIC))
    {
      cerr << "KCTFile::dirblock_read(): wrong magic" << endl;
      return KCT_ERROR_IO;
    }
  return KCT_OK;
}

kct_error_t
KCTFile::dirblock_write(kct_dirblock_t &dirblock, unsigned long offset)
{
  unsigned long o = offset & DIRBLOCK_OFFSET_MASK;
  /* cerr.form("KCTFile::dirblock_write(): %08lx [%08lx]\n", o, offset); */
  
  _f.seekp(o);
  if (!_f)
    {
      cerr << "KCTFile::dirblock_write(): seek error" << endl;
      return KCT_ERROR_IO;
    }
  _f.write(dirblock, sizeof(kct_dirblock_t));
  if (!_f)
    {
      cerr << "KCTFile::dirblock_write(): write error" << endl;
      return KCT_ERROR_IO;
    }
  return KCT_OK;
}

kct_error_t
KCTFile::dirent_allocate(const char        *filename,
			 unsigned short     load,
			 unsigned short     start,
                         unsigned long      len,
                         unsigned long      clen,
                         unsigned long      crc,
                         unsigned long     *offset,
			 kct_file_type_t    type,
                         kct_machine_type_t machine)
{
  int idx, ent;
  unsigned int a;
  unsigned long o;
  unsigned long pos;
  kct_error_t ret;

  /* cerr.form("KCTFile::dirent_allocate(): offset == %08x\n", *offset); */
  
  idx = -1;
  for (a = 0;a < DIR_BLOCKS;a++)
    {
      if ((_header.offset[a] & 0x0f) != 0x0f)
        {
          idx = a;
          break;
        }
    }

  if (idx == -1)
    return KCT_ERROR_NOMEM;

  o = _header.offset[idx];

  if (o == 0)
    {
      ret = dirblock_clear(_dirblock);
      if (ret != KCT_OK)
        return ret;
      /* cerr.form("KCTFile::dirent_allocate(): o == 0\n"); */
      _f.seekp(0, ios::end);
      pos = _f.tellp();
      /* cerr.form("KCTFile::dirent_allocate(): pos = %08x\n", pos); */
      if ((pos % 256) != 0)
        {
          cerr << "warning: format error" << endl;
        }
      pos = (pos + 255) & DIRBLOCK_OFFSET_MASK;
      /* cerr.form("KCTFile::dirent_allocate(): pos = %08x\n", pos); */
      ent = 0;
      o = *offset;
      *offset = bam_block_find_free(_bam);
      if (*offset == 0)
        return KCT_ERROR_NOMEM;
      /* cerr.form("KCTFile::dirent_allocate():   o = %08x\n", o); */
      _header.offset[idx] = o | 1;
      bam_write(_bam, BAM_OFFSET);
    }
  else
    {
      if ((o & 1) == 0) ent = 0;
      else if ((o & 2) == 0) ent = 1;
      else if ((o & 4) == 0) ent = 2;
      else if ((o & 8) == 0) ent = 3;
      //o &= DIRBLOCK_OFFSET_MASK;
      _header.offset[idx] |= (1 << ent);
      ret = dirblock_read(_dirblock, o);
      if (ret != KCT_OK)
        return ret;
    }
    
  header_write(_header, HEADER_OFFSET);

  _dirblock[ent].magic             = DIRBLOCK_MAGIC;
  _dirblock[ent].file_crc          = crc;
  _dirblock[ent].compressed_size   = clen;
  _dirblock[ent].uncompressed_size = len;
  _dirblock[ent].offset            = *offset;
  _dirblock[ent].load_addr         = load;
  _dirblock[ent].start_addr        = start;
  _dirblock[ent].type              = type;
  _dirblock[ent].machine           = machine;
  strncpy(_dirblock[ent].name, filename, KCT_NAME_LENGTH);
  _dirblock[ent].name[KCT_NAME_LENGTH] = '\0';

  /* cerr.form("KCTFile::dirent_allocate(): offset == %08x\n", *offset); */

  return dirblock_write(_dirblock, o);
}

kct_error_t
KCTFile::create(const char *filename)
{
  /* cerr << "KCTFile::create(): " << filename << endl; */

  _f.open(filename, ios::in | ios::out | ios::noreplace | ios::bin);
  if (!_f)
    {
      /* cerr << "open error" << endl; */
      return KCT_ERROR_EXIST;
    }

  memset(&_header, 0, sizeof(kct_header_t));
  strcpy(_header.id, "KCemu tape file\032");
  _header.version = KCT_VERSION;
  
  _f.write(&_header, sizeof(_header));
  if (!_f)
    {
      /* cerr << "write error (header)" << endl; */
      return KCT_ERROR_IO;
    }

  bam_clear(_bam);
  bam_block_allocate(_bam, 0); /* header */
  bam_block_allocate(_bam, 1); /* the bam itself */
  _f.write(&_bam, sizeof(kct_bam_t));
  if (!_f)
    {
      /* cerr << "write error (bam)" << endl; */
      return KCT_ERROR_IO;
    }

  return KCT_OK;
}

/*
 *  return values: KCT_ERROR_NOENT
 *                 KCT_ERROR_IO
 *                 KCT_OK
 */
kct_error_t
KCTFile::open(const char *filename)
{
  /* cerr << "KCTFile::open(): " << filename << endl; */

#ifdef LINUX
  _f.open(filename, ios::in | ios::out | ios::nocreate | ios::bin);
#endif
#ifdef MSDOS
  _f.open(filename, ios::in | ios::bin);
#endif
  if (!_f)
    {
      /* cerr << "open error" << endl; */
      return KCT_ERROR_NOENT;
    }

  if (header_read(_header, HEADER_OFFSET) == 0)
    return KCT_ERROR_IO;
  
  bam_read(_bam, BAM_OFFSET);

  return KCT_OK;
}

kct_error_t
KCTFile::close(void)
{
  /* cerr << "KCTFile::close():" << endl; */

  _f.close();
  return KCT_OK;
}

void
KCTFile::list(void)
{
  int com;
  char *type;
  unsigned long count, c_total, u_total;

  count = 0;
  c_total = 0;
  u_total = 0;
  
  cout << "--------------------------------------------------------------------------"
       << endl
       << "Filename                         type  load   start  compr.     uncompr."
       << endl
       << "                                       addr   addr   size       size"
       << endl
       << "--------------------------------------------------------------------------"
       << endl;
  
  for (KCTDir::iterator it = _dir.begin();it != _dir.end();it++)
    {
      com = 0;
      switch ((*it)->type)
	{
	case KCT_TYPE_COM:    type = "COM"; com = 1; break;
	case KCT_TYPE_MINTEX: type = "MTEX"; break;
	case KCT_TYPE_BAS:    type = "BAS";  break;
	case KCT_TYPE_BAS_P:  type = "PBAS"; break;
	default:              type = "???";  break;
	}
      if (com && ((*it)->start_addr == 0xffff))
	cout.form("%-32s %-5s 0x%04x -      0x%08x 0x%08x\n",
		  (*it)->name,
		  type,
		  (*it)->load_addr,
		  (*it)->compressed_size,
		  (*it)->uncompressed_size);
      else if (com)
	cout.form("%-32s %-5s 0x%04x 0x%04x 0x%08x 0x%08x\n",
		  (*it)->name,
		  type,
		  (*it)->load_addr,
		  (*it)->start_addr,
		  (*it)->compressed_size,
		  (*it)->uncompressed_size);
      else
	cout.form("%-32s %-5s -      -      0x%08x 0x%08x\n",
		  (*it)->name,
		  type,
		  (*it)->compressed_size,
		  (*it)->uncompressed_size);
      count++;
      c_total += (*it)->compressed_size;
      u_total += (*it)->uncompressed_size;
    }
  cout << "--------------------------------------------------------------------------"
       << endl;
  cout.form("files: %ld, compressed size: %ld, uncompressed size: %ld, ratio: %4.2f\n",
            count, c_total, u_total, (100.0 * c_total) / u_total);
  cout << "--------------------------------------------------------------------------"
       << endl;
}

KCTDir *
KCTFile::readdir(void)
{
  unsigned int a, b;
  kct_dirent_t *dirent;

  _dir.clear();

  for (a = 0;a < DIR_BLOCKS;a++)
    {
      if (_header.offset[a] == 0) continue;
      dirblock_read(_dirblock, _header.offset[a]);
      for (b = 0;b < 4;b++)
        {
          if (_header.offset[a] & (1 << b))
            {
              dirent = new kct_dirent_t();
              memcpy(dirent, &_dirblock[b], sizeof(kct_dirent_t));
              _dir.add(dirent);
            }
        }
    }

  return &_dir;
}

int
KCTFile::translate_index(int idx)
{
  int _idx;
  int a, b;

  _idx = 0;
  for (a = 0;a < DIR_BLOCKS;a++)
    {
      for (b = 0;b < 4;b++)
        {
          if (_header.offset[a] & (1 << b)) idx--;
          if (idx < 0) return _idx;
	  _idx++;
        }
    }
}

istream *
KCTFile::read(int idx, kct_file_props_t *props)
{
  int ret;
  unsigned long csize, usize;
  unsigned long offset;
  kct_data_t data;
  unsigned char *cbuf, *ubuf, *ptr;
  istrstream *is;
  
  //cerr << "KCTFile::read(): idx = " << idx << endl;
  idx = translate_index(idx);
  //cerr << "KCTFile::read(): idx = " << idx << endl;

  offset = _header.offset[idx / 4];

  dirblock_read(_dirblock, offset);

  idx %= 4;
  /* cerr << "KCTFile::read(): name = " << _dirblock[idx].name << endl; */

  csize = _dirblock[idx].compressed_size;
  cbuf = new unsigned char[csize + 256];
  ptr = cbuf;
  
  offset = _dirblock[idx].offset;
  while (offset != 0)
    {
      // cerr.form("KCTFile::read(): offset = %08x\n", offset);
      _f.seekp(offset);
      _f.read(&data, BLOCK_SIZE);
      memcpy(ptr, &data.data, 252);
      ptr += 252;
      offset = data.link;
    }

  usize = _dirblock[idx].uncompressed_size;
  ubuf = new unsigned char[usize];
  ret = uncompress(ubuf, &usize, cbuf, csize);
  delete cbuf;

  if (ret != Z_OK)
    {
      cerr.form("error in uncompress: %d\n", ret);
      return NULL;
    }

  if (props)
    {
      if (ubuf[16] < 3)
        props->auto_start = false;
      else
        props->auto_start = true;
      props->load_addr = _dirblock[idx].load_addr;
      props->start_addr = _dirblock[idx].start_addr;
      props->size = usize;
      props->type = (kct_file_type_t)_dirblock[idx].type;
      props->machine = (kct_machine_type_t)_dirblock[idx].machine;
      //cerr.form("kct_props: auto_start: %d\n", props->auto_start);
      //cerr.form("kct_props: load_addr:  %04x\n", props->load_addr);
      //cerr.form("kct_props: start_addr: %04x\n", props->start_addr);
      //cerr.form("kct_props: size:       %08x\n", props->size);
    }
  else
    cerr.form("kct_props: NULL!\n");

  is = new istrstream((const char *)ubuf, usize);
  return is;
}

istream *
KCTFile::read(const char *name, kct_file_props_t *props)
{
  int a;

  a = 0;
  for (KCTDir::iterator it = _dir.begin();it != _dir.end();it++)
    {
      if (strcmp((*it)->name, name) == 0)
        return read(a, props);
      a++;
    }
  cerr.form("KCTFile::read(): file not found!\n");
  return NULL;
}

kct_error_t
KCTFile::write(const char *filename,
               const unsigned char *buf,
               unsigned long len,
               unsigned short load_addr,
               unsigned short start_addr,
               kct_file_type_t type,
               kct_machine_type_t machine = KCT_MACHINE_ALL)
{
  int ret;
  unsigned int a;
  unsigned long clen;
  unsigned char *cbuf;
  unsigned long crc;
  unsigned long offset;
  kct_error_t err;

  DBG(1, form("KCemu/KCT/write",
              "KCTFile::write(): name = '%s'\n"
              "KCTFile::write(): type = %s (%02x)\n"
              "KCTFile::write(): addr = %04x/%04x\n",
              filename, type_name(type), type,
              load_addr, start_addr));

  clen = len + (len / 1000 + 1) + 12;
  cbuf = new unsigned char [clen];
  if (cbuf == NULL)
    return KCT_ERROR_NOMEM;

  ret = compress(cbuf, &clen, buf, len);

  DBG(1, form("KCemu/KCT/write",
              "KCTFile::write(): compress returned %d\n" 
              "KCTFile::write():  len = %d\n"
              "KCTFile::write(): clen = %d\n",
              ret, len, clen));

  if (ret != Z_OK)
    {
      cerr << "error in compress" << endl;
      return KCT_ERROR_IO;
    }

  crc = crc32(0L, Z_NULL, 0);
  crc = crc32(crc, buf, len);

  offset = bam_block_find_free(_bam);
  if (offset == 0)
    return KCT_ERROR_IO;

  err = dirent_allocate(filename, load_addr, start_addr,
                        len, clen, crc, &offset,
                        type, machine);
  if (err != KCT_OK)
    return err;

  for (;;)
    {
      _f.seekp(offset);
      if (clen < 252)
        {
          offset = 0;
          _f.write(&offset, 4);
          _f.write(cbuf, clen);
          /* pad to 256 byte */
          for (a = 0;a < 252 - clen;a++) _f.put(0);
          break;
        }
      else
        {
          offset = bam_block_find_free(_bam);
          if (offset == 0)
            return KCT_ERROR_IO;
          _f.write(&offset, 4);
          _f.write(cbuf, 252);
        }
      cbuf += 252;
      clen -= 252;
    }

  bam_write(_bam, BAM_OFFSET);

  return KCT_OK;
}
              
kct_error_t
KCTFile::write(const char *filename,
               const unsigned char *buf,
               unsigned long len,
               kct_machine_type_t machine)
{
  cerr.form("*** obsolate function called ***\n");
  return KCT_ERROR_IO;
}

kct_error_t
KCTFile::remove(int idx)
{
  int entry;
  kct_data_t data;
  unsigned long offset;

  /* cerr << "KCTFile::remove(): idx = " << idx << endl; */
  idx = translate_index(idx);
  /* cerr << "KCTFile::remove(): idx = " << idx << endl; */

  entry = idx % 4;
  idx /= 4;
  offset = _header.offset[idx];
  _header.offset[idx] &= ~(1 << entry);
  /* cerr.form("_header.offset[%02x] = %08x\n", idx, _header.offset[idx]); */

  dirblock_read(_dirblock, offset);
  if ((_header.offset[idx] & DIRBLOCK_INDEX_MASK) == 0)
    {
      /* cerr << "*** free dirblock ***" << endl; */
      _header.offset[idx] = 0;
      bam_block_free(_bam, offset / BLOCK_SIZE);
    }
  header_write(_header, HEADER_OFFSET);

  /* cerr << "KCTFile::remove(): name = " << _dirblock[entry].name << endl; */

  offset = _dirblock[entry].offset;
  while (offset != 0)
    {
      /* cerr.form("KCTFile::remove(): offset = %08x\n", offset); */
      bam_block_free(_bam, offset / BLOCK_SIZE);
      _f.seekp(offset);
      _f.read(&data, BLOCK_SIZE);
      offset = data.link;
    }
  bam_write(_bam, BAM_OFFSET);

  readdir(); /* reload internal directory list (_dir) */

  return KCT_OK;
}

kct_error_t
KCTFile::remove(const char *name)
{
  int a;

  a = 0;
  for (KCTDir::iterator it = _dir.begin();it != _dir.end();it++)
    {
      if (strcmp((*it)->name, name) == 0)
        return remove(a);
      a++;
    }
  return KCT_ERROR_NOENT;
}

#ifdef DEBUG
void
KCTFile::test(void)
{
  int a;
  bool ok;
  kct_bam_t bam;

  /*
    cerr << "***" << endl
    << "*** KCTFile::test()" << endl
    << "***" << endl;
  */

  ok = true;

  if (sizeof(kct_header_t) != 256)
    {
      ok = false;
      cerr.form("*** sizeof kct_header_t != 256 (%d)\n", sizeof(kct_header_t));
    }
  
  if (sizeof(kct_bam_t) != 256)
    {
      ok = false;
      cerr.form("*** sizeof kct_bam_t != 256 (%d)\n", sizeof(kct_bam_t));
    }

  if (sizeof(kct_data_t) != 256)
    {
      ok = false;
      cerr.form("*** sizeof kct_data_t != 256 (%d)\n", sizeof(kct_data_t));
    }

  if (sizeof(kct_dirblock_t) != 256)
    {
      ok = false;
      cerr.form("*** sizeof kct_dirblock_t != 256 (%d)\n",
                sizeof(kct_dirblock_t));
    }

  bam_clear(bam);
  for (a = 0;a < 256;a++)
    {
      if (bam[a] != 0)
        {
          ok = false;
          cerr << "*** clearing BAM failed" << endl;
          break;
        }
    }

  for (a = 0;a < 2048;a++)
    {
      if (!bam_block_available(bam, a))
        {
          ok = false;
          cerr << "*** bam_block_available error (1)" << endl;
          break;
        }
      bam_block_allocate(bam, a);
      if (bam_block_available(bam, a))
        {
          ok = false;
          cerr << "*** bam_block_available error (2)" << endl;
          break;
        }
      bam_block_free(bam, a);
      if (!bam_block_available(bam, a))
        {
          ok = false;
          cerr << "*** bam_block_available error (3)" << endl;
          break;
        }
      bam_block_allocate(bam, a);
    }

  if (!ok) cerr << "*** check failed!" << endl;
}

void
KCTFile::print_bam(void)
{
  int a, b, c;

  for (a = 0;a < 16;a++)
    {
      for (b = 0;b < 16;b++)
        {
          for (c = 0;c < 8;c += 2)
            {
	      switch (((_bam[16 * a + b]) & (0xc0 >> c)) >> (6 - c))
                {
                case 0: cout << '-'; break;
                case 1: cout << ']'; break;
                case 2: cout << '['; break;
                case 3: cout << '#'; break;
		}
	    }
	}
      cout << endl;
    }
}

void
KCTFile::print_block_list(void)
{
  int a, b, c;

  for (a = 0;a < 16;a++)
    {
      for (b = 0;b < 16;b++)
        {
          for (c = 0;c < 8;c++)
            {
	      if ((_bam[16 * a + b]) & (0x80 >> c))
                cout.form("%08x\n", 32768 * a + 2048 * b + 256 * c);
	    }
	}
    }
}
#endif /* DEBUG */
