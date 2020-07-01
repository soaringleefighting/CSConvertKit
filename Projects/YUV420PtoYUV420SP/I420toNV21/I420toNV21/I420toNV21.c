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
		printf("\nUsage:I420toNV21.exe input.yuv width height\n\n");
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
	uv = y + width*height;

	u = (char *)malloc(width*height >> 2);
	v = (char *)malloc(width*height >> 2);

	if (u == NULL || v == NULL)
	{
		printf("malloc u or v fail\n");
		return -1;
	}
	memset(outname, 0, sizeof(outname));
	sprintf(outname, "%s_NV21.yuv", argv[1]);
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
		n += fread(u, 1, width*height >> 2, fin);
		n += fread(v, 1, width*height >> 2, fin);

		if (n != frame_size)
		{
			break;
		}
		for (i = 0; i < height*width >> 2; i++)
		{
			uv[2 * i + 0] = v[i]; // v
			uv[2 * i + 1] = u[i]; // u
		}
		fwrite(y, 1, height*width, fou);
		fwrite(uv, 1, height*width >> 1, fou);

		printf("%dth frame ok!!\n", frame_num);

		frame_num++;
	}
	printf("I420 to NV21 successfully!!, total frames: %d\n", frame_num);

	free(y);
	y = NULL;
	free(u);
	u = NULL;
	free(v);
	v = NULL;
	fclose(fin);
	fclose(fou);

	return 0;
}