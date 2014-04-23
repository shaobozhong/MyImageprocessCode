#include<stdio.h>
#include<BmpUtil.h>


int main()
{
    char filename[] = "E:\\快盘\\研究生学习\\图像相关科研\\任务\\任务10实现郑培嘉hadamard变换\\实验结果\\watermark\\lena64.bmp";
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
    ret=saveBitmap("E:\\快盘\\研究生学习\\图像相关科研\\任务\\任务10实现郑培嘉hadamard变换\\实验结果\\watermark\\lena64OKOKOK.bmp",bmpData);
    if( ret != 0 ){
		printf("save bitmap failed! error:%d\n", ret );
		return -1;
	}else{
		printf("save bitmap success!\n" );
	}


    freeBmpData(&bmpData);

    return 0;
}
