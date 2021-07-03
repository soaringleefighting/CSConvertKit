#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
yyyy yyyy
uv    uv
->
yyyy yyyy
uu
vv
*/
void yuv422sp_to_yuv422p(unsigned char* yuv422sp, unsigned char* yuv422p, int width, int height)
{
	int i, j;
	int y_size;
	int uv_size;
	unsigned char* p_y1;
	unsigned char* p_uv;

	unsigned char* p_y2;
	unsigned char* p_u;
	unsigned char* p_v;

	y_size = uv_size = width * height;

	p_y1 = yuv422sp;
	p_uv = yuv422sp + y_size;

	p_y2 = yuv422p;
	p_u  = yuv422p + y_size;
	p_v  = p_u + width * height / 2;

	memcpy(p_y2, p_y1, y_size);

	for (j = 0, i = 0; j < uv_size; j+=2, i++)
	{
		p_u[i] = p_uv[j];
		p_v[i] = p_uv[j+1];
	}
}

/**
yyyy yyyy
uu
vv
->
yyyy yyyy
uv    uv
*/
void yuv422p_to_yuv422sp(unsigned char* yuv422p, unsigned char* yuv422sp, int width, int height)
{
	int i, j;
	int y_size;
	int uv_size;
	unsigned char* p_y1;
	unsigned char* p_uv;

	unsigned char* p_y2;
	unsigned char* p_u;
	unsigned char* p_v;

	y_size = uv_size = width * height;

	p_y1 = yuv422p;

	p_y2 = yuv422sp;
	p_u  = p_y1 + y_size;
	p_v  = p_u + width * height / 2;

	p_uv = p_y2 + y_size;

	memcpy(p_y2, p_y1, y_size);

	for (j = 0, i = 0; j < uv_size; j+=2, i++)
	{
		// 此处可调整U、V的位置，变成NV16或NV61
#if 01
		p_uv[j] = p_u[i];
		p_uv[j+1] = p_v[i];
#else
		p_uv[j] = p_v[i];
		p_uv[j+1] = p_u[i];
#endif
	}
}




int main(int argc, char** argv)
{
	int width, height;
	int frame_size;
	FILE *fin, *fou;
	unsigned char *y, *nv16;
	int frame_num = 0;
	char outname[512]="out_NV16.yuv";

	if (argc != 4)
	{
		printf("\nUsage: YUV422PtoNV16.exe input.yuv width height\n\n");
#if WIN32
        system("pause");
#endif
        return -1;
	}
	fin = fopen(argv[1], "rb");
	if (fin == NULL)
	{
		printf("error:open %s fail\n", argv[1]);
		return -1;
	}

	width = atoi(argv[2]);
	height = atoi(argv[3]);
	frame_size = width * height * 2;//++YUV422P
	y = (unsigned char *)malloc(frame_size);
	if (y == NULL)
	{
		printf("malloc y fail\n");
		return -1;
	}

	nv16 = (unsigned char *)malloc(width*height*2);

	if (nv16 == NULL)
	{
		printf("malloc nv16 fail\n");
		return -1;
	}
	//memset(outname, 0, sizeof(outname));
	//sprintf_s(outname, "%s_NV16.yuv", argv[1]);
	fou = fopen(outname, "wb");
	if (fou == NULL)
	{
		printf("error: open %s fail\n", outname);
		return -1;
	}

	while (!feof(fin))
	{
		int n = 0;
		n = fread(y, 1, width*height*2, fin);

		yuv422p_to_yuv422sp(y, nv16, width, height);

		fwrite(nv16, 1, height*width*2, fou);

		printf("%dth frame ok!!\n", frame_num);

		frame_num++;
	} 
	printf("[CSConvertKit] YUV422P to NV16 successfully!!, total frames: %d\n", frame_num);

	free(y);
	y = NULL;
	free(nv16);
	nv16 = NULL;

	fclose(fin); 
	fclose(fou);

	return 0;
}
