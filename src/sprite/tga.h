	// TGA Loader - 16/11/04 Codehead

	// Modified	  - 14/02/09 Craig Sturdy
#pragma once

#include <stdio.h>
#include <string.h>
 
#define IMG_OK              0x1
#define IMG_ERR_NO_FILE     0x2
#define IMG_ERR_MEM_FAIL    0x4
#define IMG_ERR_BAD_FORMAT  0x8
#define IMG_ERR_UNSUPPORTED 0x40
 
class TGAImg
 {
  public:
						TGAImg();
						TGAImg( short int, short int, short int );
					   ~TGAImg();
   int					Load( char *, int );
   int					GetBPP();
   int					GetWidth();
   int					GetHeight();
   int					GetFrameCount();
   unsigned char*		GetFrame( int );// Return a pointer to frame in image data (craig sturdy)
   unsigned char*		GetImg();       // Return a pointer to image data
   unsigned char*		GetPalette();   // Return a pointer to VGA palette
   void					SetImg( unsigned char * );
 
  private:
   short int			iFrmCnt;
   short int			iWidth, iHeight, iBPP;
   unsigned long		lImageSize, ByteCount;
   char					bEnc;
   unsigned char	   *pImage, *pPalette, *pData, *pTemp;
 
   // Internal workers
   int					ReadHeader();
   int					LoadRawData();
   int					LoadTgaRLEData();
   int					LoadTgaPalette();
   void					BGRtoRGB();
   void					FlipImg();
 };
