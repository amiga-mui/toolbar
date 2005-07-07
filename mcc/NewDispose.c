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

#include <stdlib.h>
#include <stdarg.h>

// Protos
#include <clib/alib_protos.h>
#include <proto/exec.h> // CopyMem
#include <proto/muimaster.h>
#include <proto/utility.h>
#include <proto/intuition.h>

// Other
#include <libraries/mui.h>

#include "Toolbar_mcc.h"
#include "NewDispose.h"
#include "Notify.h"
#include "InstanceData.h"

#if !defined(__MORPHOS__) // MorphOS has its DoSuperNew in libamiga.a
Object * STDARGS VARARGS68K DoSuperNew(struct IClass *cl, Object *obj, ...)
{
  Object *rc;
  VA_LIST args;

  VA_START(args, obj);
  rc = (Object *)DoSuperMethod(cl, obj, OM_NEW, VA_ARG(args, ULONG), NULL);
  VA_END(args);

  return rc;
}
#endif

ULONG Toolbar_New(struct IClass *cl, Object *obj, struct opSet *msg)
{
  struct Toolbar_Data *data;

  if (!(obj = (Object *)DoSuperNew(cl, obj, MUIA_FillArea, FALSE,
                              TAG_MORE, msg->ops_AttrList)))
  {
    CoerceMethod(cl, obj, OM_DISPOSE);
    return(0);
  }

  data = (struct Toolbar_Data *)INST_DATA(cl, obj);

  // Initialization of all the nice variables.
  data->Dragable = GetTagData(MUIA_Draggable, FALSE, msg->ops_AttrList);

  data->ImageType = GetTagData(MUIA_Toolbar_ImageType, 0, msg->ops_AttrList);
  data->Path = (STRPTR)GetTagData(MUIA_Toolbar_Path, 0, msg->ops_AttrList);

  data->NormalData = (APTR)GetTagData(MUIA_Toolbar_ImageNormal, 0, msg->ops_AttrList);
  data->SelectData = (APTR)GetTagData(MUIA_Toolbar_ImageSelect, 0, msg->ops_AttrList);
  data->GhostData  = (APTR)GetTagData(MUIA_Toolbar_ImageGhost,  0, msg->ops_AttrList);

  data->Horizontal = (BOOL)GetTagData(MUIA_Toolbar_Horizontal,  TRUE, msg->ops_AttrList);

  data->Desc = (struct MUIP_Toolbar_Description *)GetTagData(MUIA_Toolbar_Description, 0, msg->ops_AttrList);

  data->Permutation = (BYTE *)GetTagData(MUIA_Toolbar_Permutation, 0, msg->ops_AttrList);
  data->ParseUnderscore = (BOOL)GetTagData(MUIA_Toolbar_ParseUnderscore, FALSE, msg->ops_AttrList);

//      data->debug_perm  = (GetVar("toolbar_debug_permutation", &buffer, 1, NULL)!=-1);

  NewList((struct List *)&data->NotifyList);

  // Copy the structure (not the strings) if MUIA_Toolbar_Reusable is set...
  data->Reusable = (BOOL)GetTagData(MUIA_Toolbar_Reusable,  FALSE, msg->ops_AttrList);

  if(data->Reusable)
  {
    struct MUIP_Toolbar_Description *src_desc = data->Desc;
    if(src_desc)
    {
      struct MUIP_Toolbar_Description *desc = data->Desc;
      ULONG size = 0;
      do  size++;
      while((desc++)->Type != TDT_END);

      if(!(data->Desc = AllocVec(size*sizeof(struct MUIP_Toolbar_Description), MEMF_CLEAR)))
      {
        CoerceMethod(cl, obj, OM_DISPOSE);
        return(0);
      }

      CopyMem(src_desc, data->Desc, size*sizeof(struct MUIP_Toolbar_Description));
    }
  }

  return((ULONG)obj);
}

ULONG Toolbar_Dispose(struct IClass *cl, Object *obj, Msg msg)
{
  struct Toolbar_Data *data = (struct Toolbar_Data *)INST_DATA(cl, obj);

  DoMethod(obj, MUIM_Toolbar_KillNotifyObj);

  if(data->PermutationCreated) FreeVec(data->Permutation);
  if(data->Reusable)           FreeVec(data->Desc);

  return(DoSuperMethodA(cl, obj, msg));
}
