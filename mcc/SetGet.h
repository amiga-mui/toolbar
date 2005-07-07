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

#ifndef SETGET_H
#define SETGET_H

struct TB_Element *FindTool(struct Toolbar_Data *data, ULONG number);

UWORD Toolbar_Edge(struct IClass *cl, Object *obj, struct MUIP_Toolbar_Edge *msg);
ULONG Toolbar_GetAttrib(struct IClass *cl, Object *obj, struct opGet *msg);
ULONG Toolbar_SetAttrib(struct IClass *cl, Object *obj, struct opSet *msg);
ULONG Toolbar_MultiSet(struct IClass *cl, Object *obj, struct MUIP_Toolbar_MultiSet *msg);
ULONG Toolbar_Set(struct IClass *cl, Object *obj, struct MUIP_Toolbar_Set *msg);


#endif
