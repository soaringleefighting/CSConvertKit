#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
	int width, height;
	int frame_size;
	FILE *fin, *fou;
	char *y, *uv, *u, *v;
	int i, frame_num = 0;
	char outname[512] = { 0, };

	if (argc != 4)
	{
		printf("\nUsage: NV12toI420.exe input.yuv width height\n\n");
		system("pause");
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
	frame_size = width*height * 3 / 2;//++YUV420
	y = (char *)malloc(frame_size);
	if (y == NULL)
	{
		printf("malloc y fail\n");
		return -1;
	}
	u = y + width*height;
	v = u + width*height / 4;

	uv = (char *)malloc(width*height >> 1);
	if (uv == NULL)
	{
		printf("malloc uv fail\n");
		return -1;
	}
	memset(outname, 0, sizeof(outname));
	sprintf_s(outname, "%s_I420.yuv", argv[1]);
	fou = fopen(outname, "wb");
	if (fou == NULL)
	{
		printf("error: open %s fail\n", outname);
		return -1;
	}

	while (!feof(fin))
	{
		int n = 0;
		n = fread(y, 1, width*height, fin);
		n += fread(uv, 1, width*height >> 1, fin);
		if (n != frame_size)
		{
			break;
		}
		for (i = 0; i < height*width >> 2; i++)
		{
			u[i] = uv[2 * i + 0];
			v[i] = uv[2 * i + 1];
		}
		fwrite(y, 1, frame_size, fou);
		printf("%dth frame ok!!\n", frame_num);
		frame_num++;
	}
	printf("NV12 to I420 successfully!!,total frames: %d\n", frame_num);

	free(y);
	y = NULL;
	free(uv);
	uv = NULL;
	fclose(fin);
	fclose(fou);

	return 0;
}