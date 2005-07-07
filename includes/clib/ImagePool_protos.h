#ifndef  CLIB_IMAGEPOOL_PROTOS_H
#define  CLIB_IMAGEPOOL_PROTOS_H

/*
**	$VER: ImagePool_protos.h 0.8 (01.03.00)
**
**	(C) Copyright 1999-2k by Linus McCabe.
**	    All Rights Reserved
*/

#ifndef  EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef	GRAPHICS_GFX_H
#include <graphics/gfx.h>
#endif

/* Public entries */

#ifdef __cplusplus
extern "C" {
#endif

struct IP_Image	*IP_RequestImageTags (STRPTR, Tag tag1Type, ...);
void 					IP_FreeImage (struct IP_Image *);
void 					IP_DebugInfo (BPTR filehandle);

#ifdef __cplusplus
};
#endif

#endif	 /* CLIB_IMAGEPOOL_PROTOS_H */
