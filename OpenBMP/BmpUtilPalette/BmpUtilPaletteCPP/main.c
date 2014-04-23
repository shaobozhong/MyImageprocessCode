#include<stdio.h>
#include<BmpUtil.h>


int main()
{
    char filename[] = "E:\\����\\�о���ѧϰ\\ͼ����ؿ���\\����\\����10ʵ��֣���hadamard�任\\ʵ����\\watermark\\lena64.bmp";
	printf("%s\n",filename);

	BmpData bmpData;
	initBmpData(&bmpData);
	int ret = 0;

	ret = loadBitmap(filename, &bmpData);
	printf("%d\n",bmpData.bi._bm_compressed);
	printf("%d\n",bmpData.bi._bm_color_depth);
	if( ret != 0 ){
		printf("load bitmap failed! error:%d\n", ret );
		return -1;
	}else{
		printf("load bitmap success!\n" );
	}
    ret=saveBitmap("E:\\����\\�о���ѧϰ\\ͼ����ؿ���\\����\\����10ʵ��֣���hadamard�任\\ʵ����\\watermark\\lena64OKOKOK.bmp",bmpData);
    if( ret != 0 ){
		printf("save bitmap failed! error:%d\n", ret );
		return -1;
	}else{
		printf("save bitmap success!\n" );
	}


    freeBmpData(&bmpData);

    return 0;
}
