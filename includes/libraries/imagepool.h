/*
**      $VER: ImagePool.h 0.8 (01.03.00)
**
**      (C) Copyright 1999-2k by Linus McCabe.
**      All Rights Reserved.
*/

#ifndef IMAGEPOOL_IMAGEPOOL_H
#define IMAGEPOOL_IMAGEPOOL_H

#ifndef EXEC_SEMAPHORES_H
#include <exec/semaphores.h>
#endif

#ifndef INTUITION_CLASSUSR_H
#include <intuition/classusr.h>
#endif

#define ImagePool_Screen		(TAG_USER|0x06660001)
#define ImagePool_Precision	(TAG_USER|0x06660002)

//next 3

struct IP_Image 
{
	struct BitMap				*BMP;							/* The Image's BitMap 			*/
	ULONG							Width,						/* Original width, 				*/
									Height,						/*   height,					 	*/
									Depth;						/*   and depth of the image 	*/
	STRPTR						Name;							/* Full filename of the image */
	struct SignalSemaphore	Semaphore;					/* Semaphore for the Image 	*/

	struct IP_Image			*PrevImage, *NextImage;	/* Previous and next image 	*/
	Object 						*DataTypeObj;				/* The Image's datatypeobj, this may be NULL! */
	struct Screen				*Screen;						/* What screen the Image is remapped for */
	ULONG							OpenCount;					/* Number of users 				*/
	LONG							Memory;						/* Estimated amount of mem used by this img*/
	APTR							MaskPlane;					/* Transparency mask for this image */
	LONG							TransparentColor;			/* Transparent colour for this image */
	ULONG							Flags;						/* Defined below */
};

/* IP_Image Flags */

#define IPF_ValidMaskPlane					1				/* The IP_Image.MaskPlane pointer is valid */
#define IPF_ValidTransparentColor		2				/* The IP_Image.TransparenColor is valid */


#endif /* IMAGEPOOL_IMAGEPOOL_H */
