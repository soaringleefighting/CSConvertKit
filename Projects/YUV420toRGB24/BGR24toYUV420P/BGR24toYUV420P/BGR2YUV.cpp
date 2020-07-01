#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USE_OPENCV  (0)

#if USE_OPENCV
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
#endif

#define CLIP_COLOR(x) ((unsigned char)((x<0)?0:((x>255)?255:x)))

/*********************************************************************
/* Function: YUV420pToBGR24
/* Usage: colorspace convertation from YUV420P(I420) to BGR24
/* Parameters:
/* 	pYUV   [In]		- source YUV data
/*	pBGR24 [Out]	- output RGB data
/*  width  [In]		- image width
/*	height [In]		- image height
/*
/* Modified: 2019.7.13
/*********************************************************************/
int YUV420pToBGR24(unsigned char *pYUV, unsigned char *pBGR24, int width, int height)
{
	int bgr[3];
	int i,j,k;
	int yIdx, uIdx, vIdx, idx;
	int len = width * height;

	if(!pYUV || !pBGR24 || width < 1 || height < 1)
		return -1;

	unsigned char* yData = pYUV;
	unsigned char* uData = &yData[len];
	unsigned char* vData = &uData[len>>2];

	for(i = 0; i < height; i++)
	{
		for(j = 0; j < width; j++)
		{
			yIdx = i*width+j;
			vIdx = (i/2)*(width/2)+(j/2);
			uIdx = vIdx;

			// BT. 601
			bgr[0] = (298*(yData[yIdx] - 16) + 517 * (uData[uIdx] - 128) + (1<<7)) >> 8; // b分量值
			bgr[1] = (298*(yData[yIdx] - 16) - 208 * (vData[vIdx] - 128) - 100 * (uData[uIdx] - 128) + (1<<7))>>8;// g分量值
			bgr[2] = (298*(yData[yIdx] - 16) + 409 * (vData[vIdx] - 128) + (1<<7))>>8; // r分量值

			for(k=0; k<3; k++)
			{
				idx = (i*width+j)*3+k;
				pBGR24[idx] = CLIP_COLOR(bgr[k]);	
			}
		}
	}
	return 0;
}


/*********************************************************************
/* Function: BGR24toYUV420P
/* Usage: colorspace convertation from BGR24 to YUV420P(I420)
/* Parameters:
/* 	pBGR24  [In]		- source RGB data
/*	pYUV    [Out]		- output YUV data
/*  width   [In]		- image width
/*	height  [In]		- image height
/*
/* Modified: 2019.7.13
/*********************************************************************/
int BGR24toYUV420P(unsigned char *pBGR24, unsigned char *pYUV, int width, int height)
{
	int i,j,index;
	unsigned char *bufY, *bufU, *bufV, *bufRGB;
	unsigned char y, u, v, r, g, b;

	if(!pYUV || !pBGR24 || width < 1 || height < 1)

		return -1;

	memset(pYUV, 0 ,width*height*3/2*sizeof(unsigned char));

	bufY = pYUV;
	bufU = bufY + width*height;
	bufV = bufU + (width*height*1/4);

	for(j=0; j < height; j++)
	{
		bufRGB = pBGR24 + width*j*3;
		for(i=0; i < width; i++)
		{
			index = j*width+i;
			b = *(bufRGB++);
			g = *(bufRGB++);
			r = *(bufRGB++);

			y = (unsigned char)((66  * r + 129 * g + 25  * b + 128) >> 8) + 16;
			u = (unsigned char)((-38 * r - 74  * g + 112 * b + 128) >> 8) + 128;
			v = (unsigned char)((112 * r - 94  * g - 18  * b + 128) >> 8) + 128;

			*(bufY++) = CLIP_COLOR(y);
			if(j%2==0 && index%2==0)
			{
				*(bufU++) = CLIP_COLOR(u);
				*(bufV++) = CLIP_COLOR(v);	
			}
		}
	}
	return 0;
}


//Demo: This demo used to test YUV2BGR and BGR2YUV
int main(int argc, char *argv[])
{
	FILE *fin, *fou;
	unsigned char *pInYUVBuf, *pYBuf, *pUBuf, *pVBuf;
	unsigned char *pBGRBuf;

	int index, framesize;

	if (argc < 4)
	{
		printf("Usage: ./BGR24toYUV420P.exe inputYUV outputYUV width height\n");
		system("pause");
		return -1;
	}

	char* input = argv[1];
	char* output = argv[2];

	int width = atoi(argv[3]);
	int height = atoi(argv[4]);

#if USE_OPENCV
	Mat mBGR_to_show = Mat(height, width, CV_8UC3);
#endif

	fin = fopen(input, "rb");
	if(NULL == fin)
	{
		printf("[demo] error: open fin failed!!!\n");
		return -1;
	}

	fou = fopen(output, "wb");
	if(NULL == fou)
	{
		printf("[demo] error: open fou failed!!!\n");
		return -1;
	}

	pInYUVBuf = (unsigned char*) malloc(width*height*3/2); // YUV buffer
	if(NULL == pInYUVBuf)
	{
		printf("[demo] error: open pInYUVBuffer failed!!!\n");
		return -1;
	}
	pYBuf = pInYUVBuf;
	pUBuf = pYBuf + width*height;
	pVBuf = pUBuf + width*height/4;

	framesize = width*height*3/2;

	pBGRBuf = (unsigned char*) malloc(width*height*3); // BGR buffer
	if(NULL == pBGRBuf)
	{
		printf("[demo] error: open pBGRBuf failed!!!\n");
		return -1;
	}

	index = 0;
	while(framesize == fread(pInYUVBuf,1,width*height*3/2,fin))
	{
		YUV420pToBGR24(pInYUVBuf, pBGRBuf, width, height);
#if USE_OPENCV
		memcpy(mBGR_to_show.data, pBGRBuf, sizeof(unsigned char)*width*height*3);

		namedWindow("RGB", CV_WINDOW_NORMAL);
		imshow("RGB", mBGR_to_show);
		waitKey(2);
#endif

		BGR24toYUV420P(pBGRBuf, pInYUVBuf, width, height);
		fwrite(pInYUVBuf, 1, width*height*3/2, fou);

		index++;
		printf("[demo] info: %d frame process ok!!!\n", index);

	}

	return 0;   
}



