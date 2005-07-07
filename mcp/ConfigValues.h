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

#ifndef CONFIGVALUES_H
#define CONFIGVALUES_H

#ifndef BKN_SERIAL
#define BKN_SERIAL 0xfcf70000
#endif

enum { LOOK_IMAGE_TEXT=0, LOOK_IMAGE, LOOK_TEXT };
enum { GHOST_DIMMED=0, GHOST_LIGHT, GHOST_HEAVY, GHOST_SUPERLIGHT, GHOST_BITMAP };
enum { BORDERTYPE_OLD=0, BORDERTYPE_OFF, BORDERTYPE_NEW };
enum { SELECTIONMODE_OLD=0, SELECTIONMODE_OFF, SELECTIONMODE_NEW };

/* General */
#define DEFAULT_TOOLBARLOOK   LOOK_IMAGE_TEXT

#define DEFAULT_SEPARATOR       FALSE
//#define DEFAULT_FRAMESPEC       "202211" // MUI default
#define DEFAULT_FRAMESPEC       "602222" // Xen with prober border...

#define DEFAULT_GROUPSPACE_MAX    20L
#define DEFAULT_GROUPSPACE_MIN    20L
#define DEFAULT_TOOLSPACE         -1L
#define DEFAULT_IMAGETEXTSPACE      2

#ifdef TB_OBSOLETE
#define DEFAULT_GROUPSPACE 20L
#define DEFAULT_INNERSPACE_TEXT   1
#define DEFAULT_INNERSPACE_NOTEXT 2
#endif

/* Graphics */
#define DEFAULT_USEIMAGES    TRUE
#define DEFAULT_PRECISION    0 // Exact
#define DEFAULT_GHOSTEFFECT  GHOST_LIGHT

/* Text */
#define DEFAULT_PLACEMENT 0
#define DEFAULT_TEXTPEN   "m5" // MPEN_TEXT
#define DEFAULT_TEXTFONT  NULL
#define DEFAULT_BACKGROUND_NORMAL   "2:m1"
#define DEFAULT_BACKGROUND_SELECTED "2:m1"
#define DEFAULT_BACKGROUND_GHOSTED  "2:m2"


/* BorderType */
#define DEFAULT_BORDERTYPE BORDERTYPE_OLD

/* SelectionMode */
#define DEFAULT_SELECTIONMODE SELECTIONMODE_OLD

/*** Configs ***/

/* General */
#define MUICFG_Toolbar_ToolbarLook        (BKN_SERIAL | 0x0030)
#define MUICFG_Toolbar_Separator          (BKN_SERIAL | 0x003d)
#define MUICFG_Toolbar_FrameSpec          (BKN_SERIAL | 0x003b)

#define MUICFG_Toolbar_GroupSpace         (BKN_SERIAL | 0x0031)
#define MUICFG_Toolbar_GroupSpace_Max     (BKN_SERIAL | 0x0031)
#define MUICFG_Toolbar_GroupSpace_Min     (BKN_SERIAL | 0x003c)
#define MUICFG_Toolbar_ToolSpace          (BKN_SERIAL | 0x0032)
#define MUICFG_Toolbar_ImageTextSpace     (BKN_SERIAL | 0x003f)

#define MUICFG_Toolbar_InnerSpace_Text    (BKN_SERIAL | 0x0033)
#define MUICFG_Toolbar_InnerSpace_NoText  (BKN_SERIAL | 0x0034)

/* Graphics */
#define MUICFG_Toolbar_Precision          (BKN_SERIAL | 0x0035)
#define MUICFG_Toolbar_GhostEffect        (BKN_SERIAL | 0x0036)
#define MUICFG_Toolbar_UseImages          (BKN_SERIAL | 0x003a)

/* Text */
#define MUICFG_Toolbar_Placement          (BKN_SERIAL | 0x0037)
#define MUICFG_Toolbar_ToolFont           (BKN_SERIAL | 0x0038)
#define MUICFG_Toolbar_ToolPen            (BKN_SERIAL | 0x0039)

#define MUICFG_Toolbar_Background_Normal   (BKN_SERIAL | 0x0040)
#define MUICFG_Toolbar_Background_Selected (BKN_SERIAL | 0x0041)
#define MUICFG_Toolbar_Background_Ghosted  (BKN_SERIAL | 0x0042)

/* Border Type*/
#define MUICFG_Toolbar_BorderType (BKN_SERIAL | 0x0043)

/* Selection Mode */
#define MUICFG_Toolbar_SelectionMode (BKN_SERIAL | 0x0044)

/* AutoActive */
#define MUICFG_Toolbar_AutoActive (BKN_SERIAL | 0x0045)
#endif
