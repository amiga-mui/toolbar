/***************************************************************************

 Toolbar MCC - MUI Custom Class for Toolbar handling
 Copyright (C) 1997-2000 Benny Kjær Nielsen <floyd@amiga.dk>
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

#define LIB_VERSION    15
#define LIB_REVISION   12

#define LIB_REV_STRING "15.12"
#define LIB_DATE       "01.08.2005"

#if defined(__PPC__)
  #if defined(__MORPHOS__)
    #define CPU " [MOS/PPC]"
  #else
    #define CPU " [OS4/PPC]"
  #endif
#elif defined(_M68060) || defined(__M68060) || defined(__mc68060)
  #define CPU " [060]"
#elif defined(_M68040) || defined(__M68040) || defined(__mc68040)
  #define CPU " [040]"
#elif defined(_M68030) || defined(__M68030) || defined(__mc68030)
  #define CPU " [030]"
#elif defined(_M68020) || defined(__M68020) || defined(__mc68020)
  #define CPU " [020]"
#else
  #define CPU ""
#endif

#define LIB_COPYRIGHT  "Copyright (c) 2004-2005 Toolbar.mcc Open Source Team"
