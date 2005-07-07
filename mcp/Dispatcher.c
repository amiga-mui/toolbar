/***************************************************************************

 Toolbar MCC - MUI Custom Class for Toolbar handling
 Copyright (C) 1997-2000 Benny Kj�r Nielsen <floyd@amiga.dk>
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

//look for //fix to restore default handling (darius)
// ANSI
#include <string.h>

// Protos
#include <clib/alib_protos.h>
#include <proto/intuition.h>
#include <proto/locale.h>
#include <proto/muimaster.h>

// Libraries
#include <libraries/mui.h>

#include "SDI_compiler.h"

#include "InstanceData.h"
#include "ConfigValues.h"
#include "MyLocale.h"
#include "CreatePrefs.h"
#include "rev.h"

// some undocumented MUI methods
#define MUIM_Mccprefs_RegisterGadget  0x80424828 /* V20 */

struct PrefsExchangeData { ULONG ObjIndex, Tag, CfgItem, Length; APTR DefValue; };

static struct PrefsExchangeData PrefsInfo[] =
{
  { Look,         MUIA_Radio_Active,    MUICFG_Toolbar_ToolbarLook,   4,  (APTR)DEFAULT_TOOLBARLOOK },
  { GroupSpace,     MUIA_Slider_Level,    MUICFG_Toolbar_GroupSpace,      4,  (APTR)DEFAULT_GROUPSPACE },
  { ToolSpace,      MUIA_Slider_Level,    MUICFG_Toolbar_ToolSpace,     4,  (APTR)DEFAULT_TOOLSPACE },
  { InnerSpace_Text,  MUIA_Slider_Level,    MUICFG_Toolbar_InnerSpace_Text, 4,  (APTR)DEFAULT_INNERSPACE_TEXT },
  { InnerSpace_NoText,  MUIA_Slider_Level,    MUICFG_Toolbar_InnerSpace_NoText,4, (APTR)DEFAULT_INNERSPACE_NOTEXT },
  { UseImages,      MUIA_Selected,        MUICFG_Toolbar_UseImages,     4,  (APTR)DEFAULT_USEIMAGES },
  { Precision,      MUIA_Cycle_Active,    MUICFG_Toolbar_Precision,     4,  (APTR)DEFAULT_PRECISION },
  { GhostEffect,      MUIA_Cycle_Active,    MUICFG_Toolbar_GhostEffect,   4,  (APTR)DEFAULT_GHOSTEFFECT },
  { ToolPen,        MUIA_Pendisplay_Spec, MUICFG_Toolbar_ToolPen,       32,(APTR)DEFAULT_TEXTPEN },
  { ToolFont,       MUIA_String_Contents, MUICFG_Toolbar_ToolFont,      0,  (APTR)DEFAULT_TEXTFONT },
  { BorderType,     MUIA_Cycle_Active,   MUICFG_Toolbar_BorderType,     4,  (APTR)DEFAULT_BORDERTYPE },
  { SelectionMode,  MUIA_Cycle_Active,   MUICFG_Toolbar_SelectionMode,  4,  (APTR)DEFAULT_SELECTIONMODE },
  { AutoActive,     MUIA_Selected,       MUICFG_Toolbar_AutoActive,     4,  (APTR) FALSE}
};

DISPATCHERPROTO(_DispatcherP)
{
  struct Toolbar_DataP *data = (struct Toolbar_DataP *)INST_DATA(cl, obj);
  ULONG result = 0;

  switch(msg->MethodID)
  {
    case OM_NEW:
    {
      if((obj = (Object *)DoSuperMethodA(cl, obj, msg)) != NULL)
      {
        static const struct TagItem tags[] =
        {
          { OC_BuiltInLanguage, (ULONG)"english" },
          { OC_Version,         0                },
          { TAG_DONE,           0                }
        };

        data = (struct Toolbar_DataP *)INST_DATA(cl, obj);

        data->catalog = OpenCatalogA(NULL,
                                     "Toolbar_mcp.catalog",
                                     (struct TagItem *)&tags[0]);

        if((data->PrefsGroup = CreatePrefs(data)) != NULL)
        {
          ULONG i;

          DoMethod(obj, OM_ADDMEMBER, data->PrefsGroup);

          /* This is MUI 3.9 stuff: Each registered object will get a context-menu, like normal pref-items */
          for(i=0; i < NumberOfGadgets; i++)
            DoMethod(obj, MUIM_Mccprefs_RegisterGadget, data->Gadgets[PrefsInfo[i].ObjIndex], PrefsInfo[i].CfgItem, 0L, NULL);

          result = (ULONG)obj;
        }
        else
          CoerceMethod(cl, obj, OM_DISPOSE);
      }
    }
    break;

    case OM_DISPOSE:
    {
      DoMethod(obj, OM_REMMEMBER, data->PrefsGroup);
      CloseCatalog(data->catalog);

      result = DoSuperMethodA(cl, obj, msg);
    }
    break;

    case OM_GET:
    {
      ULONG *store = ((struct opGet *)msg)->opg_Storage;

      switch(((struct opGet *)msg)->opg_AttrID)
      {
        case MUIA_Version:
        {
          *store = LIB_VERSION;
          return(TRUE);
        }
        break;

        case MUIA_Revision:
        {
          *store = LIB_REVISION;
          return(TRUE);
        }
        break;
      }

      return (DoSuperMethodA(cl, obj, msg));
    }
    break;

/*    case MUIM_Setup:
      result = DoSuperMethodA(cl,obj,msg);
    break;*/

    case MUIM_Cleanup:
    {
      LONG active;
      while(get(data->FontASL, MUIA_Popasl_Active, &active), active)
      {
        char *tmp = LOCALE(MSG_ASL_ERROR, "Cannot leave now, still\nan asl popup opened.\nPlease close it now.");

        MUI_Request(_app(obj), _win(obj), 0, NULL, LOCALE(MSG_OK, "OK"), tmp);
      }

      result = DoSuperMethodA(cl,obj,msg);
    }
    break;

    case MUIM_Settingsgroup_GadgetsToConfig:
    {
      Object *configdata = ((struct MUIP_Settingsgroup_ConfigToGadgets *)msg)->configdata;
      ULONG i;

      for(i=0; i<NumberOfGadgets; i++)
      {
        APTR cfg_val;
        ULONG len;
        get(data->Gadgets[PrefsInfo[i].ObjIndex], PrefsInfo[i].Tag, &cfg_val);

        // Temp. hack..
        if(PrefsInfo[i].ObjIndex == GhostEffect)
          cfg_val = (APTR)((LONG)cfg_val + 1);

        len = PrefsInfo[i].Length;
        DoMethod(configdata, MUIM_Dataspace_Add, len==4 ? &cfg_val : cfg_val, len ? len : strlen((STRPTR)cfg_val)+1, PrefsInfo[i].CfgItem);
      }
    }
    break;
    case MUIM_Settingsgroup_ConfigToGadgets:
    {
      Object *configdata = ((struct MUIP_Settingsgroup_ConfigToGadgets *)msg)->configdata;
      ULONG i;

      for(i=0; i<NumberOfGadgets; i++)
      {
        APTR cfg_val = (APTR)DoMethod(configdata, MUIM_Dataspace_Find, PrefsInfo[i].CfgItem);
        cfg_val = cfg_val ? (PrefsInfo[i].Length == 4 ? *((APTR *)cfg_val) : cfg_val) : PrefsInfo[i].DefValue;

        // Temp. hack
        if(PrefsInfo[i].ObjIndex == GhostEffect)
          cfg_val = (APTR)((LONG)cfg_val - 1);

        set(data->Gadgets[PrefsInfo[i].ObjIndex], PrefsInfo[i].Tag, cfg_val);
      }
    }
    break;
    default:
      result = DoSuperMethodA(cl,obj,msg);
  }

  return result;
}
