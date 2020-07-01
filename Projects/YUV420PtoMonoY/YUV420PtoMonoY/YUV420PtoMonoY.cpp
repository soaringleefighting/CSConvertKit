#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
	int width, height;
	int frame_size, frame_size_y;
	FILE *fin, *fou;
	char *y, *u, *v,*u1,*v1;
	int i, frame_num = 0;
	char outname[512] = { 0, };
	
	if (argc != 5)
	{
		printf("\nUsage:YUV420PtoMonoY.exe input.yuv output.yuv width height\n\n");
		system("pause");
		return -1;
	}
	fin = fopen(argv[1], "rb");
	if (fin == NULL)
	{
		printf("error:open %s fail\n", argv[1]);
		return -1;
	}

	sprintf_s(outname,"%s", argv[2]);

	width = atoi(argv[3]);
	height = atoi(argv[4]);

	frame_size = width*height * 3 / 2;
	frame_size_y = width * height;

	y = (char *)malloc(frame_size_y);
	if (y == NULL)
	{
		printf("malloc y fail\n");
		return -1;
	}

	fou = fopen(outname, "wb");
	if (fou == NULL)
	{
		printf("error: open %s fail\n", outname);
		return -1;
	}

	while (width*height == fread(y, 1, width*height, fin))
	{
		fwrite(y, 1, frame_size_y, fou);
		fseek(fin, frame_size_y/2, SEEK_CUR);

		printf("%dth frame ok!!\n", frame_num);
		frame_num++;
	}
	printf("YUV420P to MonoY successfully!!, total frames: %d\n",frame_num);
	
	free(y);
	y = NULL;

	fclose(fin);
	fclose(fou);

	return 0;
}