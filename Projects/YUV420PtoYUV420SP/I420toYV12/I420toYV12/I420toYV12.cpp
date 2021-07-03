#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
	int width, height;
	int frame_size;
	FILE *fin, *fou;
	char *y, *u, *v,*u1,*v1;
	int i, frame_num = 0;
	char outname[512] = { 0, };

	if (argc != 4)
	{
		printf("\nUsage:I420toYV12.exe input.yuv width height\n\n");
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
	frame_size = width*height * 3 / 2;
	y = (char *)malloc(frame_size);
	if (y == NULL)
	{
		printf("malloc y fail\n");
		return -1;
	}
	v = y + width*height;
	u = v + width*height/4;

	u1 = (char *)malloc(width*height >> 2);
	v1 = (char *)malloc(width*height >> 2);

	if (u1 == NULL || v1== NULL)
	{
		printf("malloc u1 or v1 fail\n");
		return -1;
	}
	memset(outname, 0, sizeof(outname));
#if WIN32
	sprintf_s(outname, "%s_YV12.yuv", argv[1]);
#else
	sprintf(outname, "%s_YV12.yuv", argv[1]);
#endif

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
		n += fread(u1, 1, width*height >> 2, fin);
		n += fread(v1, 1, width*height >> 2, fin);

		if (n != frame_size)
		{
			break;
		}
		for (i = 0; i < height*width >> 2; i++)
		{
			v[i] = v1[i];
			u[i] = u1[i];
		}
		fwrite(y, 1, frame_size, fou);

		printf("%dth frame ok!!\n", frame_num);
		frame_num++;
	}
	printf("[CSConverKit] I420 to YV12 successfully!!,total frames: %d\n", frame_num);
	
	free(y);
	y = NULL;
	free(u1);
	u1 = NULL;
	free(v1);
	v1 = NULL;
	fclose(fin);
	fclose(fou);

	return 0;
}