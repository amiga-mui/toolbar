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

/******************************************************************************/
/*                                                                            */
/* includes                                                                   */
/*                                                                            */
/******************************************************************************/

#include <proto/exec.h>

/******************************************************************************/
/*                                                                            */
/* MCC/MCP name and version                                                   */
/*                                                                            */
/* ATTENTION:  The FIRST LETTER of NAME MUST be UPPERCASE                     */
/*                                                                            */
/******************************************************************************/

#include "InstanceData.h"
#include "rev.h"
#include "Debug.h"

#define VERSION       LIB_VERSION
#define REVISION      LIB_REVISION

#define CLASS         "Toolbar.mcp"
#define SUPERCLASSP   MUIC_Mccprefs

#define INSTDATAP     Toolbar_DataP

#define UserLibID     "$VER: Toolbar.mcp " LIB_REV_STRING CPU " (" LIB_DATE ") " LIB_COPYRIGHT
#define MASTERVERSION 15

#define PreClassInit
#define PostClassExit

#define USE_UTILITYBASE

struct Library *LocaleBase = NULL;
#if defined(__amigaos4__)
struct LocaleIFace *ILocale = NULL;
#endif

BOOL PreClassInitFunc(void)
{
  if((LocaleBase = OpenLibrary("locale.library", 37L)) &&
     GETINTERFACE(ILocale, LocaleBase))
  {
    return TRUE;
  }

  return FALSE;
}

VOID PostClassExitFunc(void)
{
  if(LocaleBase)
  {
    DROPINTERFACE(ILocale);
    CloseLibrary(LocaleBase);
    LocaleBase = NULL;
  }
}

/******************************************************************************/
/*                                                                            */
/* include the lib startup code for the mcc/mcp  (and muimaster inlines)      */
/*                                                                            */
/******************************************************************************/

#define USE_PREFSIMAGE_COLORS
#define USE_PREFSIMAGE_BODY
#include "PrefsImage.h"

#define PREFSIMAGEOBJECT \
  BodychunkObject,\
    MUIA_FixWidth,              PREFSIMAGE_WIDTH,\
    MUIA_FixHeight,             PREFSIMAGE_HEIGHT,\
    MUIA_Bitmap_Width,          PREFSIMAGE_WIDTH ,\
    MUIA_Bitmap_Height,         PREFSIMAGE_HEIGHT,\
    MUIA_Bodychunk_Depth,       PREFSIMAGE_DEPTH,\
    MUIA_Bodychunk_Body,        (UBYTE *)PrefsImage_body,\
    MUIA_Bodychunk_Compression, PREFSIMAGE_COMPRESSION,\
    MUIA_Bodychunk_Masking,     PREFSIMAGE_MASKING,\
    MUIA_Bitmap_SourceColors,   (ULONG *)PrefsImage_colors,\
    MUIA_Bitmap_Transparent,    0,\
  End

#include "mccheader.c"
