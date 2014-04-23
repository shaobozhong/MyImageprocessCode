
#include<stdio.h>
#include "BmpUtil.h"
#include <stdlib.h>

int main(){

	char filename[] = "C:\\lena\\4.bmp";
	char savename[] = "C:\\lena\\4_save.bmp";

	printf("%s\n",filename);
	printf("%s\n",savename);

	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;
	byte** data = 0;

	int ret = 0;

	ret = loadBitmap(filename, &bf, &bi, &data);
	if( ret != 0 ){
		printf("load bitmap failed! error:%d\n", ret );
		return -1;
	}else{
		printf("load bitmap success!\n" );
	}
/*
	int width = bi._bm_image_width;
	int height = bi._bm_image_height;
	for(int i=0; i<height; i++){
		for( int j=0; j<width ; j++){
			printf("%d ",data[i][j]);
		}
		printf("\n");
	}
*/
	ret = saveBitmap(savename, &bf, &bi, data );
	if( ret != 0 ){
		printf("save bitmap failed! error:%d\n", ret );
		return -1;
	}else{
		printf("save bitmap success!\n" );
	}


	int height = bi._bm_image_height;
	for(int i=0; i<height; i++){
		free(data[i]);
	}
	free(data);
	data = 0;

	return 0;
}