/***************************************************************
//������YUV420PtoRGB24.cpp
//���ܣ�
//1). ֧�ֽ���֡yuvת���ɵ���rgb24��ʽ��bmpͼ��
//2). ֧�ֽ���֡yuvת����rgb24��ʽ����Ƶ�ļ���
//ʱ�䣺2018.6.10
****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <windows.h>

int bmp24_write(unsigned char *image, int xsize, int ysize, FILE *pfile)
{
	BITMAPFILEHEADER bmpFileHeader; //++BMP�ļ�ͷ
	BITMAPINFOHEADER bmpInfoHeader; //++BMP��Ϣͷ
	bmpInfoHeader.biBitCount = 24; //++����λ��
	//����BMP�ļ�ͷ
	bmpFileHeader.bfType = 0x04D42;
	bmpFileHeader.bfSize = sizeof(bmpFileHeader)+sizeof(bmpInfoHeader)+bmpInfoHeader.biBitCount;
	bmpFileHeader.bfReserved1 = 0;
	bmpFileHeader.bfReserved2 = 0;
	bmpFileHeader.bfOffBits = 54;//λͼ����λ�õ���ʼ��ַ

	//����BMP��Ϣͷ
	bmpInfoHeader.biSize = 40;
	bmpInfoHeader.biWidth = xsize;
	bmpInfoHeader.biHeight = ysize;
	bmpInfoHeader.biPlanes = 1;

	bmpInfoHeader.biCompression = 0;//ѹ�����ͣ�0����ѹ��
	bmpInfoHeader.biSizeImage = 0;
	bmpInfoHeader.biXPelsPerMeter = 0;
	bmpInfoHeader.biYPelsPerMeter = 0;
	bmpInfoHeader.biClrUsed = 0;
	bmpInfoHeader.biClrImportant = 0;

	fwrite(&bmpFileHeader, 1, sizeof(bmpFileHeader), pfile);
	fwrite(&bmpInfoHeader, 1, sizeof(bmpInfoHeader), pfile);
	fwrite(image, 1, xsize*ysize * 3, pfile);

	return 0;
}

int rgb24_write(unsigned char *image, int xsize, int ysize, FILE *pfile)
{
	fwrite(image, 1, xsize*ysize * 3, pfile);
	return 0;
}
int yuv420toRGB24(unsigned char* yuv420, unsigned char*rgb24, int width, int height,int bmp_flag)
{
	//++�������
	if (NULL == yuv420 || NULL == rgb24 || width < 1 || height < 1)
	{
		printf("ERROR: input para error!!\n");
		return -1;
	}
	int Y, U, V, R, G, B;
	int i, j;
	int cwidth = width >> 1;

	for (i = 0; i < height; ++i)
	{
		for (j = 0; j < width; ++j)
		{
			Y = *(yuv420 + i * width + j);
			U = *(yuv420 + width * height + (i >> 1) * cwidth + (j >> 1));
			V = *(yuv420 + width * height * 5 / 4 + (i >> 1) * cwidth + (j >> 1));
			R = Y + 1.403 * (V - 128);
			G = Y - 0.344 * (U - 128) - 0.714 * (V - 128);
			B = Y + 1.772 * (U - 128);

			if (R <= 0 || R >= 255)
			{
				R = (R < 0) ? 0 : 255;
			}
			if (G <= 0 || G >= 255)
			{
				G = (G < 0) ? 0 : 255;
			}
			if (B <= 0 || B >= 255)
			{
				B = (B < 0) ? 0 : 255;
			}
			if (bmp_flag)
			{
				//BMPͼ��Ĵ���Ǵ����һ��(��������)��ʼ����B\G\R��˳����д�ŵ�
				*(rgb24 + ((height - i - 1)*width + j) * 3) = B;
				*(rgb24 + ((height - i - 1)*width + j) * 3 + 1) = G;
				*(rgb24 + ((height - i - 1)*width + j) * 3 + 2) = R;
			}
			else
			{
				*(rgb24 + (i * width + j) * 3) = B;
				*(rgb24 + (i * width + j) * 3 + 1) = G;
				*(rgb24 + (i* width + j) * 3 + 2) = R;
			}
		}
	}

	return 0;
}

int main(int argc, char** argv)
{
	int width, height, filelen, frameno, framenum, bmp_flag;
	FILE *yuv_file, *rgb_file;
	unsigned char *yuv420, *rgb24;
	char filename[50];

	if (argc < 5)
	{
		printf("Usage: yuv420ptoRGB24.exe yuv420_file rgb24_filename width height\n\n");
		system("pause");
		return -1;
	}

	yuv_file = fopen(argv[1], "rb");
	if (NULL == yuv_file)
	{
		printf("ERROR: open %s fail!\n", argv[1]);
		return -1;
	}

	width = atoi(argv[3]);
	height = atoi(argv[4]);

	yuv420 = (unsigned char *)malloc(width*height * 3 / 2);
	if (NULL == yuv420)
	{
		printf("ERROR: malloc yuv420 fail!\n");
		return -1;
	}
	rgb24 = (unsigned char *)malloc(width*height * 3);
	if (NULL == rgb24)
	{
		printf("ERROR: malloc rgb24 fail!\n");
		return -1;
	}

	fseek(yuv_file, 0, SEEK_END);
	filelen = ftell(yuv_file);
	frameno = filelen / (width*height * 3 / 2);
	fseek(yuv_file, 0, SEEK_SET); //++���ļ�ָ������ָ���ļ���ʼλ��

	if (frameno == 1)
	{
		sprintf(filename, "%s_rgb24.bmp", argv[2]);
	}
	else
	{
		sprintf(filename, "%s.rgb24", argv[2]);
	}
	rgb_file = fopen(filename, "wb");
	if (NULL == rgb_file)
	{
		printf("ERROR: open %s fail!\n", filename);
		return -1;
	}

	framenum = 0;
	bmp_flag = (frameno == 1) ? 1 : 0;
	while (fread(yuv420, sizeof(unsigned char), width*height * 3 / 2, yuv_file) == width*height * 3 / 2)
	{
		yuv420toRGB24(yuv420, rgb24, width, height, bmp_flag);
		printf("%dth frames ok!!!\n", framenum);
		framenum++;
		if (bmp_flag)//++��֡yuvת��bmpͼ��
		{
			bmp24_write(rgb24, width, height, rgb_file);
		}
		else//++��֡yuvת��rgb24��ʽ��Ƶ
		{
			rgb24_write(rgb24, width, height, rgb_file);
		}
	}

	printf("yuv420p to RGB24 succeessfully!!,total frames: %d\n", frameno);

	free(yuv420);
	yuv420 = NULL;
	free(rgb24);
	rgb24 = NULL;
	fclose(yuv_file);
	fclose(rgb_file);
	return 0;
}