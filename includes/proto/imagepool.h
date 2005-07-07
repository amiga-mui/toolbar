#ifndef PROTO_IMAGEPOOL_H
#define PROTO_IMAGEPOOL_H

/*
**	$VER: ImagePool.h 0.8 (01.03.00)
**
**	(C) Copyright 1999-2k by Linus McCabe.
**	    All Rights Reserved
*/

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif

extern struct Library *ImagePoolBase;
#include <clib/ImagePool_protos.h>

#ifdef __STORM__
#include <pragma/ImagePool_lib.h>
#else
#include <pragmas/ImagePool_pragmas.h>
#endif

#include <libraries/ImagePool.h>

#endif
