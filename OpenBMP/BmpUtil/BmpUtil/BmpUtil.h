
/*************  BmpUtil.h *******************/

/**********************************************
*  
* author   sxylq
* date     2013-07-02
*
**********************************************/


#pragma once

#ifdef _WIN32
#pragma pack(push)
#endif

#pragma pack(1)

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

#ifdef _WIN32
#pragma pack(pop)
#else
#pragma pack()
#endif


extern "C" 
{
	int loadBitmap( char* filename, BITMAPFILEHEADER* bf, BITMAPINFOHEADER* bi, byte*** data );
	int saveBitmap( char* filename, BITMAPFILEHEADER* bf, BITMAPINFOHEADER* bi, byte** data );

	float round_f( float num );

}
