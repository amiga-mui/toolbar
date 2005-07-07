/***************************************************************************

 Toolbar MCC - MUI Custom Class for Toolbar handling
 Copyright (C) 1997-2000 Benny Kj�r Nielsen <floyd@amiga.dk>
 Copyright (C) 2004-2005 by Toolbar.mcc Open Source Team

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 Toolbar class Support Site:  http://www.sf.net/projects/toolbar-mcc

 $Id$

***************************************************************************/

#ifdef USE_PREFSIMAGE_COLORS
static const ULONG PrefsImage_colors[24] =
{
  0x95959595,0x95959595,0x95959595,
  0x00000000,0x00000000,0x00000000,
  0xffffffff,0xffffffff,0xffffffff,
  0x3b3b3b3b,0x67676767,0xa2a2a2a2,
  0x7b7b7b7b,0x7b7b7b7b,0x7b7b7b7b,
  0xafafafaf,0xafafafaf,0xafafafaf,
  0xaaaaaaaa,0x90909090,0x7c7c7c7c,
  0xffffffff,0xa9a9a9a9,0x97979797,
};
#endif

#define PREFSIMAGE_WIDTH        24
#define PREFSIMAGE_HEIGHT       14
#define PREFSIMAGE_DEPTH         3
#define PREFSIMAGE_COMPRESSION   1
#define PREFSIMAGE_MASKING       2

#ifdef USE_PREFSIMAGE_HEADER
static const struct BitMapHeader PrefsImage_header =
{ 24,14,203,160,3,2,1,0,0,22,22,656,495 };
#endif

#ifdef USE_PREFSIMAGE_BODY
static const UBYTE PrefsImage_body[171] =
{
  0xfd,0x00,0xfd,0x00,0xfd,0x00,0xff,0xff,0x01,0xfe,0x00,0xfd,0x00,0xfd,0x00,
  0x03,0x80,0x30,0x06,0x00,0x03,0x7f,0xcf,0xf8,0x00,0x03,0x00,0x20,0x04,0x00,
  0x03,0xbf,0xf7,0xfe,0x00,0x03,0x40,0x08,0x40,0x00,0x03,0x3f,0xe7,0xfc,0x00,
  0x03,0xb0,0xb7,0xbe,0x00,0x03,0x4f,0x89,0xf0,0x00,0x03,0x30,0x27,0xbc,0x00,
  0x03,0xa6,0xd2,0x4a,0x00,0x03,0x49,0x8b,0xf8,0x00,0x03,0x26,0x42,0x08,0x00,
  0x03,0x97,0xb5,0x56,0x00,0x03,0x4f,0x8f,0xfc,0x00,0x03,0x17,0x24,0x04,0x00,
  0x03,0x86,0x96,0xae,0x00,0x03,0x49,0x8f,0xfc,0x00,0x03,0x06,0x04,0x04,0x00,
  0x03,0x80,0xd3,0x5a,0x00,0x03,0x4f,0x8b,0xf8,0x00,0x03,0x10,0x67,0x5c,0x00,
  0x03,0x87,0x90,0xa2,0x00,0x03,0x40,0x08,0xa0,0x00,0x03,0x20,0x02,0xa8,0x00,
  0x03,0xc0,0x18,0x02,0x00,0xfd,0x00,0x03,0x7f,0xef,0xfc,0x00,0xff,0xff,0x01,
  0xfe,0x00,0xfd,0x00,0xfd,0x00,0xfd,0x00,0xfd,0x00,0xfd,0x00,0xfd,0x00,0xfd,
  0x00,0xfd,0x00
};
#endif