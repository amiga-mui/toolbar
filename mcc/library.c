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

#include "Toolbar_mcc.h"

#include "InstanceData.h"
#include "rev.h"

#define VERSION       LIB_VERSION
#define REVISION      LIB_REVISION

#define CLASS         MUIC_Toolbar
#define SUPERCLASS    MUIC_Area

#define INSTDATA      Toolbar_Data

#define UserLibID     "$VER: Toolbar.mcc " LIB_REV_STRING CPU " (" LIB_DATE ") " LIB_COPYRIGHT
#define MASTERVERSION 15

#define USEDCLASSESP  used_classesP
static const STRPTR used_classesP[] = { "Toolbar.mcp", NULL };

#define USE_UTILITYBASE

#define PreClassInit
#define PostClassExit

struct Library *DataTypesBase = NULL;
struct Library *KeymapBase    = NULL;
struct Library *DiskfontBase  = NULL;
struct Library *LayersBase    = NULL;
#if defined(__amigaos4__)
struct DataTypesIFace *IDataTypes = NULL;
struct KeymapIFace *IKeymap       = NULL;
struct DiskfontIFace *IDiskfont   = NULL;
struct LayersIFace *ILayers       = NULL;
#endif

#ifdef USE_IMAGEPOOL
struct Library *ImagePoolBase = NULL;
#if defined(__amigaos4__)
struct ImagePoolIFace *IImagePool = NULL;
#endif
#endif

BOOL PreClassInitFunc(void)
{
  if((DataTypesBase = OpenLibrary("datatypes.library", 37L)) &&
     GETINTERFACE(IDataTypes, DataTypesBase))
  {
    if((KeymapBase = OpenLibrary("keymap.library", 37L)) &&
       GETINTERFACE(IKeymap, KeymapBase))
    {
      if((DiskfontBase = OpenLibrary("diskfont.library", 37L)) &&
         GETINTERFACE(IDiskfont, DiskfontBase))
      {
        if((LayersBase = OpenLibrary("layers.library", 39L)) &&
           GETINTERFACE(ILayers, LayersBase))
        {
          #ifdef USE_IMAGEPOOL
          // ImagePool is no MUST
          if((ImagePoolBase = OpenLibrary("imagepool.library", 37L)) &&
             GETINTERFACE(IImagePool, ImagePoolBase)) { }
          #endif

          return TRUE;
        }

        DROPINTERFACE(IDiskfont);
        CloseLibrary(DiskfontBase);
        DiskfontBase = NULL;
      }

      DROPINTERFACE(IKeymap);
      CloseLibrary(KeymapBase);
      KeymapBase = NULL;
    }

    DROPINTERFACE(IDataTypes);
    CloseLibrary(DataTypesBase);
    DataTypesBase = NULL;
  }

  return FALSE;
}

VOID PostClassExitFunc(void)
{
  #ifdef USE_IMAGEPOOL
  if(ImagePoolBase) { DROPINTERFACE(IImagePool); CloseLibrary(ImagePoolBase); ImagePoolBase = NULL; }
  #endif

  if(LayersBase)    { DROPINTERFACE(ILayers);    CloseLibrary(LayersBase);    LayersBase    = NULL; }
  if(DiskfontBase)  { DROPINTERFACE(IDiskfont);  CloseLibrary(DiskfontBase);  DiskfontBase  = NULL; }
  if(KeymapBase)    { DROPINTERFACE(IKeymap);    CloseLibrary(KeymapBase);    KeymapBase    = NULL; }
  if(DataTypesBase) { DROPINTERFACE(IDataTypes); CloseLibrary(DataTypesBase); DataTypesBase = NULL; }
}

/******************************************************************************/
/*                                                                            */
/* include the lib startup code for the mcc/mcp  (and muimaster inlines)      */
/*                                                                            */
/******************************************************************************/

#include "Debug.h"
#include "mccheader.c"
