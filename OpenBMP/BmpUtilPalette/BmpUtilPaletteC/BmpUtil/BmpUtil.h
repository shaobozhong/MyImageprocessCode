
/*************  BmpUtil.h *******************/

/**********************************************
*
* author   sxylq
* date     2013-07-02
*
**********************************************/

/*************  BmpUtil.h ******************/

/**********************************************
*
* modify author   BozhongShao
* date     2014-03-02
*
**********************************************/

//History:
//2014/2/20  Bozhongshao second release
//update:  change the data struct ,save the palette in the whole process,
//then improve the performance when open and save gray bitmap picture
//2014/2/26  add the feature to load and save binary image
//2014/2/27  repair the feature load and save binary image not successful
//2014/2/28  BozhongShao third release
//update :add the feature loading binaray image
//2014/3/2  BozhongShao fourth release
//update :modify the memory alloct and free function.

#pragma once

//#ifdef _WIN32
//#pragma pack(push)
//#endif

#pragma pack(push,1)

typedef char                       int8;
typedef short                      int16;
typedef int                        int32;
typedef unsigned char              uint8;
typedef unsigned short             uint16;
typedef unsigned int               uint32;

/**
*  One-byte unsigned integer type
*/
typedef unsigned char byte;

/**
* \brief Bitmap file header structure
*
*  Bitmap file header structure
*/
typedef struct
{
	uint16 _bf_signature;				//!< bfType, File signature, must be "BM"
	uint32 _bf_file_size;				//!< bfSize, File size
	uint32 _bf_reserved;				//!< Reserved, must be zero
	uint32 _bf_bitmap_data;				//!< bfOffBits, position of Bitmap data
} BITMAPFILEHEADER;


/**
* \brief Bitmap info header structure
*
*  Bitmap info header structure
*/
typedef struct
{
	uint32 _bm_info_header_size;			// biSize, Info header size, must be 40
	uint32 _bm_image_width;					// biWidth, Image width
	uint32 _bm_image_height;				// biHeight, Image height
	uint16 _bm_num_of_planes;				// biPlanes, Amount of image planes, must be 1
	uint16 _bm_color_depth;					// biBitCount, number of bytes per piexel  1, 2, 4, 8 or 24
	uint32 _bm_compressed;					// biCompression, Image compression, must be 0 no compression, 1 BI_RLE8, 2 BI_RLE4
	uint32 _bm_bitmap_size;					// biSizeImage, Size of bitmap data
	uint32 _bm_hor_resolution;				// biXPelsPerMeter, Horizontal resolution, assumed to be 0
	uint32 _bm_ver_resolution;				// biYPelsPerMeter, Vertical resolution, assumed to be 0
	uint32 _bm_num_colors_used;				// biClrUsed, Number of colors used, assumed to be 0
	uint32 _bm_num_important_colors;	    // biClrImportant, Number of important colors, assumed to be 0
} BITMAPINFOHEADER;




typedef struct tagRGBQUAD {
	uint8    rgbBlue;
	uint8    rgbGreen;
	uint8    rgbRed;
	uint8    rgbReserved;
} RGBQUAD;

typedef struct BmpData
{
    BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;
    byte** data;
    RGBQUAD* palette;
	byte *something;//if a file 's fileheader and bit header and other thing rather than pixel data  need to read and save then use this field
}BmpData;

//#ifdef _WIN32
//#pragma pack(pop)
//#else
#pragma pack(pop)
//#endif


    void initBmpData(BmpData *bmpData);//init BmpData struct
    int freeBmpData(BmpData *bmpData);//free the memmery of BmpData struct
	int freeBmpData_Data(BmpData *bmpData);//free the pixel data
    int freeBmpData_Palette(BmpData *bmpData);//free the Palette
	int freeBmpData_Something(BmpData *bmpData);//free  memory of BmpData struct;s Something field
	int loadBitmap( char* filename,BmpData *bmpData);
	int saveBitmap( char* filename,const BmpData bmpData);
	int round_f( float num );


