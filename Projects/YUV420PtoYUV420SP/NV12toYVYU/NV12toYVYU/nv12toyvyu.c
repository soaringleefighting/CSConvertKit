#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
	int width, height, frame_size;
	FILE *fin, *fou;
	char *y, *uv, *y2, *temp_y, *temp_uv, *temp_y2;
	int i, j, frame_num = 0;

	if (argc != 5)
	{
		printf("\nUsage: NV12toYVYU.exe infile outfile width height\n\n");
#if WIN32
		system("pause");
#endif
        return -1;
	}
	fin = fopen(argv[1], "rb");
	if (fin == NULL)
	{
		printf("ERROR: open %s fail\n", argv[1]);
		return -1;
	}
	fou = fopen(argv[2], "wb");
	if (fou == NULL)
	{
		printf("RRROR: open %s fail\n", argv[2]);
		return -1;
	}

	width = atoi(argv[3]);
	height = atoi(argv[4]);
	frame_size = width * height;
	y = (char *)malloc(frame_size * 3 / 2);//++NV12
	if (y == NULL)
	{
		printf("ERROR: malloc y fail\n");
		return -1;
	}
	uv = y + width*height;

	y2 = (char *)malloc(frame_size * 2);//++YVYU
	if (y2 == NULL)
	{
		printf("ERROR: malloc y2 fail\n");
		return -1;
	}

	while (!feof(fin))
	{
		int n = 0;
		n = fread(y, 1, width*height, fin);
		n += fread(uv, 1, width*height >> 1, fin);
		if (n != frame_size *3/2)
		{
			break;
		}

		temp_y = y;
		temp_uv = uv;
		temp_y2 = y2;

		for (j = 0; j < height;j++)
		{
			for (i = 0; i < width / 2;i++)
			{
				temp_y2[0] = temp_y[2 * i];//y
				temp_y2[1] = temp_uv[2 * i + 1];//v
				temp_y2[2] = temp_y[2 * i + 1];//y
				temp_y2[3] = temp_uv[2 * i];//u
				temp_y2 += 4;
			}
			temp_y += width;
			if (j & 1)
			{
				temp_uv += width;
			}
		}
		fwrite(y2, 1, frame_size * 2, fou);
		printf("%dth frame ok!!\n", frame_num);
		frame_num++;
	}
	printf("[CSConvertKit] NV12 to YVYU successfully!!,total frames: %d\n", frame_num);

	free(y);
	y = NULL;
	free(y2);
	y2 = NULL;
	fclose(fin);
	fclose(fou);

	return 0;
}
