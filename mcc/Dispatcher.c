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

// Protos
#include <clib/alib_protos.h>
#ifndef __MORPHOS__
#include <clib/debug_protos.h>
#endif
#include <proto/muimaster.h>
#include <proto/intuition.h>

// Other
#include <libraries/mui.h>
#include "Toolbar_mcc.h"

#include "SDI_compiler.h"

#include "InstanceData.h"
#include "Draw.h"
#include "HandleEvent.h"
#include "NewDispose.h"
#include "Notify.h"
#include "SetGet.h"
#include "SetupCleanup.h"
#include "ShowHide.h"

#include "Dispatcher.h"

// Not defined in mui.h
#ifndef MUIM_CheckShortHelp
#define MUIM_CheckShortHelp 0x80423c79 /* V20 */
#include "amiga-align.h"
struct  MUIP_CheckShortHelp { ULONG MethodID; STRPTR help; LONG mx; LONG my; };
#include "default-align.h"
#endif

DISPATCHERPROTO(_Dispatcher)
{
  ULONG result = 0;
  struct Toolbar_Data *data = (struct Toolbar_Data *)INST_DATA(cl, obj);

  switch (msg->MethodID)
  {
    case OM_NEW:      result = Toolbar_New(cl, obj, (struct opSet *)msg); break;
    case OM_DISPOSE:  result = Toolbar_Dispose(cl, obj, msg); break;

    case MUIM_Setup:  result = Toolbar_Setup(cl, obj, msg); break;
    case MUIM_Cleanup:result = Toolbar_Cleanup(cl, obj, msg); break;

    case MUIM_AskMinMax:
    {
      struct MUIP_AskMinMax *amsg;
      struct MUI_MinMax *mi;
      LONG group_space, tool_space, buttons_size, fixed_size;

      // Ask parent to get border size etc.
      DoSuperMethodA(cl, obj, msg);

      amsg = (struct MUIP_AskMinMax *)msg;
      mi = amsg->MinMaxInfo;
      group_space = data->GroupSpaces * data->GroupSpace;
      tool_space  = data->ToolSpaces * data->ToolSpace;
      buttons_size = data->Buttons * data->ButtonSize;
      fixed_size = group_space + tool_space + buttons_size;

      if(data->Horizontal)
      {
        mi->DefWidth  += fixed_size;
        mi->MinWidth  += tool_space + data->GroupSpaces*data->ToolSpace + buttons_size;
        if(data->FixSize)
        {
          mi->MaxWidth  += fixed_size;
          if(data->NeverShrink)
            mi->MinWidth = mi->MaxWidth;
        }
        else
          mi->MaxWidth  += MUI_MAXMAX;

        mi->DefHeight += data->ButtonHeight;
        mi->MinHeight  += data->ButtonHeight;
        mi->MaxHeight  += data->ButtonHeight;
      }
      else
      {
        mi->DefWidth  += data->ButtonWidth;
        mi->MinWidth  += data->ButtonWidth;
        mi->MaxWidth  += data->ButtonWidth;

        mi->DefHeight += fixed_size;
        mi->MinHeight += tool_space + data->GroupSpaces*data->ToolSpace + buttons_size;
        if(data->FixSize)
        {
          mi->MaxHeight += fixed_size;
          if(data->NeverShrink)
            mi->MinHeight = mi->MaxHeight;
        }
        else
          mi->MaxHeight += MUI_MAXMAX;
      }

      //  result = 0; // Not neccesary
    }
    break;

    case MUIM_Show: result = Toolbar_Show(cl, obj, msg); break;
    case MUIM_Hide: result = Toolbar_Hide(cl, obj, msg); break;

    case MUIM_Draw: result = Toolbar_Draw(cl, obj, (struct MUIP_Draw *)msg); break;

//    case MUIM_Toolbar_DrawButton:
      // Draw button at the specified coordinates....
      // Evt. også DrawSpace...hmmmm
      // Hvad med kanterne...
//    break;

    case MUIM_HandleEvent: result = Toolbar_HandleEvent(cl,obj,(struct MUIP_HandleEvent *)msg); break;

    // SetGet
    case OM_GET: result = Toolbar_GetAttrib(cl, obj, (struct opGet *)msg); break;
    case OM_SET: result = Toolbar_SetAttrib(cl, obj, (struct opSet *)msg); break;
    case MUIM_Toolbar_MultiSet: result = Toolbar_MultiSet(cl, obj, (struct MUIP_Toolbar_MultiSet *)msg); break;
    case MUIM_Toolbar_Set: result = Toolbar_Set(cl, obj, (struct MUIP_Toolbar_Set *)msg); break;

    // Notify
    case MUIM_Toolbar_KillNotify: result = Toolbar_KillNotify(cl, obj, (struct MUIP_Toolbar_KillNotify *)msg); break;
    case MUIM_Toolbar_KillNotifyObj:  result = Toolbar_KillNotifyObj(cl, obj, (struct MUIP_Toolbar_KillNotifyObj *)msg); break;
    case MUIM_Toolbar_Notify: result = Toolbar_Notify(cl, obj, (struct MUIP_Toolbar_Notify *)msg); break;
    case MUIM_Toolbar_CheckNotify: Toolbar_CheckNotify(cl, obj, (struct MUIP_Toolbar_CheckNotify *)msg); break;

    case MUIM_Toolbar_Redraw:
    {
      if(data->Active)
      {
        struct MUIP_Toolbar_Redraw *rmsg = (struct MUIP_Toolbar_Redraw *)msg;
        ULONG redraw = rmsg->Changes;
        struct MinNode *node;

        for(node = data->ToolList.mlh_Head; node->mln_Succ; node = *(struct MinNode **)node)
        {
          struct TB_Element *elem = (struct TB_Element *)node;
          if(elem->Type == TDT_BUTTON)
          {
            if(redraw & (1L<<elem->Number))
            {
              elem->Redraw = TRUE;
            }
          }
        }

        data->RedrawFlag = TRUE;
        MUI_Redraw(obj, MADF_DRAWUPDATE);
      }

      result = TRUE;
    }
    break;

    case MUIM_Toolbar_ReloadImages:
    {
      struct MUIP_Toolbar_ReloadImages *rmsg = (struct MUIP_Toolbar_ReloadImages *)msg;

      data->NormalData = rmsg->Normal;
      data->SelectData = rmsg->Select;
      data->GhostData = rmsg->Ghost;

      if(data->Setup)
      {
        Object *parent = (Object *)xget(obj,MUIA_Parent);
        if (parent && DoMethod(parent, MUIM_Group_InitChange))
        {
          DoMethod(obj, MUIM_Cleanup);
          DoMethod(obj, MUIM_Setup);

          DoMethod(parent, MUIM_Group_ExitChange);
          result = TRUE;
        }
      }
    }
    break;

    case MUIM_Toolbar_LeftEdge:
    case MUIM_Toolbar_RightEdge:
    case MUIM_Toolbar_TopEdge:
    case MUIM_Toolbar_BottomEdge:
      result = Toolbar_Edge(cl, obj, (struct MUIP_Toolbar_Edge *)msg);
    break;

    case MUIM_CreateShortHelp:
    {
      result = xget(obj, MUIA_Toolbar_HelpString);
    }
    break;

    // Undocumented MUI-feature???
    case MUIM_CheckShortHelp:
    {
      struct MUIP_CheckShortHelp *cmsg = (struct MUIP_CheckShortHelp *)msg;

      if(cmsg->help == (STRPTR)xget(obj, MUIA_Toolbar_HelpString))
        result = DoSuperMethodA(cl,obj,msg);
    }
    break;

    default:
      result = DoSuperMethodA(cl,obj,msg);
    break;
  }

  return(result);
}
