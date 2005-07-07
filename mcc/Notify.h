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

#ifndef NOTIFY_H
#define NOTIFY_H

ULONG Toolbar_KillNotify(struct IClass *cl,Object *obj,struct MUIP_Toolbar_KillNotify *msg);
ULONG Toolbar_KillNotifyObj(struct IClass *cl,Object *obj,struct MUIP_Toolbar_KillNotifyObj *msg);
ULONG Toolbar_Notify(struct IClass *cl,Object *obj,struct MUIP_Toolbar_Notify *msg);
VOID Toolbar_CheckNotify(struct IClass *cl,Object *obj,struct MUIP_Toolbar_CheckNotify *msg);

struct ToolbarNotify
{
  struct  MinNode TNNode; // MUST be the first variable!!!!
  UBYTE   Type;
  UBYTE   TrigButton;
  UBYTE   TrigAttribute;
  ULONG   TrigValue;

  Object  *DestObject;
  ULONG   Number_Of_Args;
  Msg     DestMessage; // Msg is defined in intuition/classusr.h
  Msg     DestMessageCopy;
};

#endif
