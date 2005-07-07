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

#ifndef INSTANCEDATA_H
#define INSTANCEDATA_H

#include <mcc_common.h>
#include <mcc_debug.h>

enum
{
  Look = 0,
  GroupSpace,
  ToolSpace,
  InnerSpace_Text,
  InnerSpace_NoText,
  UseImages,
  Precision,
  GhostEffect,
  ToolPen,
  ToolFont,
  BorderType,
  SelectionMode,
  AutoActive,
  NumberOfGadgets
};

struct Toolbar_DataP
{
  struct Catalog *catalog;
  Object *Gadgets[NumberOfGadgets];
  Object  *PrefsGroup;
  Object  *FontASL;
};

#define TB_OBSOLETE

#endif
