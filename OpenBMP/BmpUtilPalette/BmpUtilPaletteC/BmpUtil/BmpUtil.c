

/*************  BmpUtil.cpp ******************/

/**********************************************
*
* author   sxylq
* date     2013-07-02
*
**********************************************/


/*************  BmpUtil.c ******************/

/**********************************************
*
* modify author   BozhongShao
* date     2014-02-20
*
**********************************************/

//History:
//2014/2/20  Bozhongshao second release
//update:  change the data struct ,save the palette in the whole process,
//then improve the performance when open and save gray bitmap picture



#include "BmpUtil.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define FILENAME_ERROR 1
#define BITMAPFILEHEADER_ERROR 2
#define BITMAPINFOHEADER_ERROR 3
#define RGBQUAD_ERROR 4;
#define FORMAT_ERROR 5;
#define MEMORYMALLOC_ERROR 6;


/**
**************************************************************************
*  Init bitmap file Data struct
*
* \param bmpData [IN][OUT] -bitmap file data struct
*
* \return  0  success , otherwise failed
*/


void initBmpData(BmpData *bmpData)//can add some init for bf and bi
{
    bmpData->data=NULL;
    bmpData->palette=NULL;
	bmpData->something=NULL;
}





/**
**************************************************************************
*  free the memery of  bitmap file Data struct
*
* \param bmpData [IN][OUT] -bitmap file data struct
*
* \return  0  success , otherwise failed
*/

int freeBmpData_Data(BmpData *bmpData)
{
	if (bmpData->data==NULL)
	{
		return 0;
	}
    int i;
    for(i=0; i<bmpData->bi._bm_image_height; i++){
		free(bmpData->data[i]);
	}
	free(bmpData->data);
	bmpData->data=NULL;

    return 0;
}

int freeBmpData_Palette(BmpData *bmpData)
{
    if (bmpData->palette!=NULL)
    {
    free(bmpData->palette);
    bmpData->palette=NULL;
    }
    return 0;
}

int freeBmpData_Something(BmpData *bmpData)
{
	if (bmpData->something!=NULL)
	{
		free(bmpData->something);
		bmpData->something=NULL;
	}
	return 0;
}

int freeBmpData(BmpData *bmpData)
{
	freeBmpData_Data(bmpData);
	freeBmpData_Palette(bmpData);
	freeBmpData_Something(bmpData);
	return 0;
}

/**
**************************************************************************
*  load bitmap file
*
* \param filename			[IN] - bitmap file name
*        bf                 [OUT] - bitmap file header
*        bi                 [OUT] - bitmap info header
*        data          [OUT] - bitmap data
*
* \return  0  success , otherwise failed
*/
int loadBitmap(char* filename,BmpData *bmpData){

	freeBmpData(bmpData);	//clear the container before load anther bitmap file

    int i;
    int j;
	FILE* fp = 0;
	int ret = 0;
	BITMAPFILEHEADER *bf;
	BITMAPINFOHEADER *bi;

	bf=&(bmpData->bf);
	bi=&(bmpData->bi);
	// open file
	fp = fopen(filename,"rb");
	if( fp == 0 ){
		return FILENAME_ERROR;
	}

	// read bitmap file header
	ret = fread( bf, sizeof(BITMAPFILEHEADER), 1, fp);
	if( ret !=1 ){
		return BITMAPFILEHEADER_ERROR;
	}

	// read bitmap info header
	ret = fread( bi, sizeof(BITMAPINFOHEADER) , 1, fp);
	if( ret !=1 ){
		return BITMAPINFOHEADER_ERROR;
	}

	// whether compressed
	if( bi->_bm_compressed != 0 ){
		return FORMAT_ERROR;
	}

	int bitcount = bi->_bm_color_depth;

	if( bitcount== 8 ){// gray bitmap

		RGBQUAD* palette = NULL;
		int size = sizeof(RGBQUAD)*256;

		palette = (RGBQUAD*)malloc(size);
		if( palette == 0 ){
			return MEMORYMALLOC_ERROR;
		}else{
			memset(palette,0,size);
		}


		// read palette
		ret = fread(palette, sizeof(RGBQUAD), 256, fp);
		if( ret !=256 ){
			return  RGBQUAD_ERROR;
		}

		bmpData->palette=palette;
		// read bitmap data
		int width = bi->_bm_image_width;
		int height = bi->_bm_image_height;
		int pad = ((width+3)/4)*4 - width;   // padding size per line

		byte** ppdata = 0;
		if( (ppdata = (byte**)malloc(height*sizeof(byte*))) == 0){
			return MEMORYMALLOC_ERROR;
		}

		for(i=0; i<height; i++){

			if( (ppdata[i] = (byte*)malloc(width*sizeof(byte))) != 0){
				memset(ppdata[i], 0, sizeof(byte)*width );
			}else{
				return MEMORYMALLOC_ERROR;
			}

		}

		byte index = 0;
//		byte gray = 0;

		// bottom->top and left->right
		for(i=height-1; i>=0; i-- ){
			for(j=0; j<width; j++ ){
				fread(&index, sizeof(byte), 1, fp );
				//gray = (byte)round_f(0.299*palette[index].rgbRed + 0.574*palette[index].rgbGreen + 0.114*palette[index].rgbBlue);
				ppdata[i][j] = index;
				//printf("%d ",ppdata[i][j]);
			}
			//printf("\n");
			fseek( fp, pad, SEEK_CUR );
		}

		bmpData->data = ppdata;



//		for(i=0; i<height; i++){
//			for(j=0; j<width ; j++){
//				printf("%d ",ppdata[i][j]);
//			}
//			printf("\n");
//		}

	}else if( bitcount == 24 ){ // color bitmap

		// read bitmap data
		int width = bi->_bm_image_width;
		int height = bi->_bm_image_height;
		int pad = ((width*3+3)/4)*4 - width*3;   // padding size per line

		byte** ppdata = 0;
		ppdata = (byte**)malloc(height*sizeof(byte*));
		for( i=0; i<height; i++){
			ppdata[i] = (byte*)malloc(3*width*sizeof(byte));
			memset(ppdata[i], 0, sizeof(byte)*width );
		}

		byte red=0, green=0, blue=0;
		int r = 0;
		int g = width;
		int b = width*2;

		// bottom->top and left->right
		for( i=height-1; i>=0; i-- ){
			for(j=0; j<width; j++ ){
				fread(&blue, sizeof(byte), 1, fp );
				fread(&green, sizeof(byte), 1, fp);
				fread(&red, sizeof(byte), 1, fp );
				ppdata[i][r+j] = red;
				ppdata[i][g+j] = green;
				ppdata[i][b+j] = blue;
			}
			fseek(fp, pad, SEEK_CUR);
		}
		bmpData->data = ppdata;

	}else if(bitcount==1){
		int padOfHeader;
		padOfHeader=(bf->_bf_bitmap_data+3)/4*4-54;//54 is the sum of bf and bi 's memory
		if (padOfHeader!=0)
		{
			bmpData->something=(byte*)malloc(padOfHeader*sizeof(byte));
			fread(bmpData->something, sizeof(byte), padOfHeader, fp );
		}

	    // read bitmap data
		int width = bi->_bm_image_width;
		int height = bi->_bm_image_height;
		//int pad = ((width*3+3)/4)*4 - width*3;   // padding size per line
		int byteWidth=(width+7)/8;//binary bitmap 's unit is bit
		int pad = ((byteWidth+3)/4)*4-byteWidth;   // padding size per line

		byte** ppdata = 0;
		ppdata = (byte**)malloc(height*sizeof(byte*));
		for( i=0; i<height; i++){
			ppdata[i] = (byte*)malloc(byteWidth*sizeof(byte));
			memset(ppdata[i], 0, sizeof(byte)*byteWidth );
		}

		// bottom->top and left->right
		for( i=height-1; i>=0; i-- ){
			for(j=0; j<byteWidth; j++ ){
				fread(&ppdata[i][j], sizeof(byte), 1, fp );
			}
			fseek(fp, pad, SEEK_CUR);
		}
		bmpData->data = ppdata;
	}else{
		return FORMAT_ERROR;
	}

	// close file
	if( fp ){
		fclose(fp);
		fp = 0;
	}

	return 0;
}

/**
**************************************************************************
*  save bitmap file
*
* \param filename			[IN] - bitmap file name
*        bf                 [IN] - bitmap file header
*        bi                 [IN] - bitmap info header
*        data          [IN] - bitmap data
*
* \return  0  success , otherwise failed
*/

int saveBitmap(char* filename,const BmpData bmpData){

    int i;
    int j;
	FILE* fp = 0;
	int ret = 0;


	const BITMAPFILEHEADER *bf;
	const BITMAPINFOHEADER *bi;

	byte **data;
	data=bmpData.data;

	bf=&(bmpData.bf);
	bi=&(bmpData.bi);
	// open file
	fp = fopen(filename, "wb");
	if( fp == 0 ){
		return FILENAME_ERROR;
	}

	// write bitmap file header
	ret = fwrite( bf, sizeof(BITMAPFILEHEADER), 1, fp );
	if( ret !=1 ){
		return BITMAPFILEHEADER_ERROR;
	}

	// write bitmap info header
	ret = fwrite( bi, sizeof(BITMAPINFOHEADER), 1, fp );
	if( ret !=1 ){
		return BITMAPINFOHEADER_ERROR;
	}

	int bicount = bi->_bm_color_depth;

	if( bicount==8 ){ // gray bitmap

		// write palette
		fwrite(bmpData.palette, sizeof(RGBQUAD), 256, fp );

		// write bitmap data
		int width = bi->_bm_image_width;
		int height = bi->_bm_image_height;
		int pad = ((width+3)/4)*4 - width;   // padding size per line
		byte* padding = 0;
		if( pad !=0 ){
			padding = (byte*)malloc(sizeof(byte)*pad);
			if( padding != 0 ){
				memset(padding, 0, sizeof(byte)*pad );
			}else{
				return MEMORYMALLOC_ERROR;
			}

		}

		// bottom->top and left->right
		for(i=height-1; i>=0; i-- ){
			fwrite(data[i], sizeof(byte), width, fp );
			if( pad !=0){
				fwrite(padding, sizeof(byte), pad, fp );
			}
		}

	}else if(bicount==24){ // color bitmap

		// write bitmap data
		int width = bi->_bm_image_width;
		int height = bi->_bm_image_height;

		int pad = ((width*3+3)/4)*4 - width*3;   // padding size per line
		byte* padding = 0;
		if( pad !=0 ){
			padding = (byte*)malloc(sizeof(byte)*pad);
			if( padding != 0){
				memset(padding, 0, sizeof(byte)*pad );
			}else{
				return MEMORYMALLOC_ERROR;
			}
		}

		int r = 0;
		int g = width;
		int b = width*2;

		// bottom->top and left->right
		for(i=height-1; i>=0; i-- ){
			for( j=0; j<width; j++ ){
				fwrite(&data[i][b+j], sizeof(byte), 1, fp );
				fwrite(&data[i][g+j], sizeof(byte), 1, fp );
				fwrite(&data[i][r+j], sizeof(byte), 1, fp );
			}
			if( pad !=0){
				fwrite(padding, sizeof(byte), pad, fp );
			}
		}
		// release
		if( padding ){
			free(padding);
			padding = 0;
		}

	}
	else if (bicount==1){//binary bitmap file

		//Write padOf bmp file header
		int padOfHeader;
		padOfHeader=(bf->_bf_bitmap_data+3)/4*4-54;//54 is the sum of bf and bi 's memory
		if (padOfHeader!=0)
		{
			fwrite(bmpData.something, sizeof(byte), padOfHeader, fp );
		}


		int width = bi->_bm_image_width;
		int height = bi->_bm_image_height;
        int byteWidth=(width+7)/8;
		int pad = ((byteWidth+3)/4)*4 - byteWidth;   // padding size per line
		byte* padding = 0;
		if( pad !=0 ){
			padding = (byte*)malloc(sizeof(byte)*pad);
			if( padding != 0){
				memset(padding, 0, sizeof(byte)*pad );
			}else{
				return MEMORYMALLOC_ERROR;
			}
		}
		// bottom->top and left->right
		for(i=height-1; i>=0; i-- ){
			for( j=0; j<byteWidth; j++ ){
				fwrite(&data[i][j], sizeof(byte), 1, fp );
			}
			if( pad !=0){
				fwrite(padding, sizeof(byte), pad, fp );
			}
		}
		// release
		if( padding ){
			free(padding);
			padding = 0;
		}

	}else{
		return FORMAT_ERROR;
	}

	// close file
	if( fp ){
		fclose(fp);
		fp = 0;
	}

	return 0;
}

/**
**************************************************************************
*  Float round to nearest value
*
* \param num			[IN] - Float value to round
*
* \return The closest to the input float integer value
*/

int round_f(float num)
{
	float value = fabs(num);
	int valueI = (int)(value + 0.5f);
	int sign = num > 0 ? 1.0 : -1.0;
	return sign * valueI;
}


