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

#ifndef DRAW_H
#define DRAW_H

#define UPDATE_UP   1
#define UPDATE_DOWN 2

ULONG Toolbar_Draw(struct IClass *cl, Object *obj, struct MUIP_Draw *msg);

struct TB_Element
{
  struct MinNode MNode;
  ULONG Type;
  WORD DstX, DstY;
  WORD DstOffset;
  BOOL Redraw;

  // the following three if for a TB_Tool
  WORD SrcOffset;
  UBYTE Number; // Placement in toolbar-structure (backwards compatibility).
  BOOL ParseUnderscore;

  // the Size is just used if it is a TB_Space element
  WORD Size;
};

#endif
