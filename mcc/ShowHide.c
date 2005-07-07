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

// ANSI
#include <string.h>

// Libraries
#include <libraries/mui.h>

// Protos
#include <clib/alib_protos.h>
#include <proto/graphics.h>
#include <proto/muimaster.h>
#include <proto/intuition.h>

// Toolbar inclusions
#include "Toolbar_mcc.h"
#include "Notify.h"
#include "InstanceData.h"
#include "Draw.h"

ULONG Toolbar_Show(struct IClass *cl, Object *obj, Msg msg)
{
  struct Toolbar_Data *data = (struct Toolbar_Data *)INST_DATA(cl, obj);
  WORD left, top;
  WORD leftover = 0;
  ULONG adjust = 0;
  WORD offset;
  struct MinNode *node;

  if (!(DoSuperMethodA(cl, obj, msg)))
    return(FALSE);

  data->Active = TRUE;

  memcpy(&data->RP, _rp(obj), sizeof(struct RastPort)); // To make MUIM_Draw faster the rastport is copied
  SetFont(&data->RP, data->ToolFont);
  left = _mleft(obj);
  top = _mtop(obj);  // Useful variables..

  // Initial offset calculations
// These calculations are not needed when the toolbar is totally fixed, but...
//  if(!data->FixSize || (data->FixSize && data->NeverShrink))
//  {
    if(data->GroupSpaces) // Are there any spaces at all?
    {
      WORD toolbar_size = data->ButtonSize*data->Buttons + data->ToolSpaces*data->ToolSpace;
      WORD area_size = data->Horizontal ? _mwidth(obj) : _mheight(obj);
      data->GroupSpace = (area_size - toolbar_size)/data->GroupSpaces;
      leftover = area_size - toolbar_size - data->GroupSpace*data->GroupSpaces;
    }
//  }

  offset = data->Horizontal ? left : top;

  // Calculating destination offsets...
  for(node = data->ToolList.mlh_Head; node->mln_Succ; node = *(struct MinNode **)node)
  {
    struct TB_Element *elem = (struct TB_Element *)node;
    WORD dst_offset;
    if(elem->Type == TDT_BUTTON)
    {
      dst_offset = offset + adjust*data->ToolSpace;
      offset += data->ButtonSize + adjust*data->ToolSpace;
      adjust = 1;
    }
    else // TDT_SPACE
    {
      UWORD size = data->GroupSpace + (leftover-- > 0 ? 1 : 0);
      dst_offset = offset;
      elem->Size = size;
      offset += size;
      adjust = 0;
    }

    if(data->Horizontal)
    {
      elem->DstX = elem->DstOffset = dst_offset;
      elem->DstY = top;
    }
    else
    {
      elem->DstX = left;
      elem->DstY = elem->DstOffset = dst_offset;
    }
  }

  // Update buttonpositions - Left/Right/Top/Bottom-Edge
  if(data->PositionNotify)
  {
    WORD width  = data->ButtonWidth-1;
    WORD height = data->ButtonHeight-1;
    struct MinNode *node;

    for(node = data->ToolList.mlh_Head; node->mln_Succ; node = *(struct MinNode **)node)
    {
      struct TB_Element *tool = (struct TB_Element *)node;
      if(tool->Type == TDT_BUTTON)
      {
        DoMethod(obj, MUIM_Toolbar_CheckNotify, tool->Number, MUIV_Toolbar_Notify_LeftEdge,   tool->DstX);
        DoMethod(obj, MUIM_Toolbar_CheckNotify, tool->Number, MUIV_Toolbar_Notify_RightEdge,   tool->DstX + width);
        DoMethod(obj, MUIM_Toolbar_CheckNotify, tool->Number, MUIV_Toolbar_Notify_TopEdge,   tool->DstY);
        DoMethod(obj, MUIM_Toolbar_CheckNotify, tool->Number, MUIV_Toolbar_Notify_BottomEdge,   tool->DstY + height);
      }
    }
  }

  return(TRUE);
}

ULONG Toolbar_Hide(struct IClass *cl,Object *obj, Msg msg)
{
  struct Toolbar_Data *data = (struct Toolbar_Data *)INST_DATA(cl, obj);

  data->Active = FALSE;

  return(DoSuperMethodA(cl, obj, msg));
}
