#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
	int i, j, width, height, frame_size;
	FILE *fp_in, *fp_out;
	unsigned char *y1, *u1, *v1, *y2, *u2, *v2;
	int n = 0;


	printf("Input parameters: ");
	for (i = 0; i < argc;i++)
	{
		printf("%s  ", argv[i]);
	}
	if (argc < 5)
	{
		printf("\nUsage:YUV420toYUV444.exe inputfile outputfile width height\n\n");
		system("pause");
		return -1;
	}

	fp_in = fopen(argv[1], "rb");
	if (NULL == fp_in)
	{
		printf("ERROR: open %s fail\n", argv[1]);
		return -1;
	}
	fp_out = fopen(argv[2], "wb");
	if (NULL == fp_out)
	{
		printf("ERROR: open %s fail\n", argv[2]);
		return -1;
	}

	width = atoi(argv[3]);
	height = atoi(argv[4]);
	frame_size = width*height;

	y1 = (unsigned char *)malloc(frame_size*3/2);
	if ( NULL == y1 )
	{
		printf("malloc y1 fail\n");
		return -1;
	}
	u1 = y1 + width*height;
	v1 = u1 + width*height / 4;

	y2 = (char *)malloc(frame_size*3);
	if (NULL== y2 )
	{
		printf("malloc y2 fail\n");
		return -1;
	}
	u2 = y2 + width*height;
	v2 = u2 + width*height;

	while (fread(y1,1,frame_size*3/2,fp_in) == frame_size*3/2)
	{
		memcpy(y2, y1, frame_size);//Y

		for (j = 0; j < height; j++)//U,V
		{
			for (i = 0; i < width; i++)
			{
				u2[j*width + i] = u1[j / 2 * width / 2 + i / 2];
				v2[j*width + i] = v1[j / 2 * width / 2 + i / 2];
			}
		}

		fwrite(y2, 1, frame_size*3, fp_out);

		printf("%dth frame ok!!\n", n);
		n++;
	}

	printf("YUV420toYUV444 successfully!!,total frames: %d\n",n);

	free(y1);
	y1 = NULL;
	free(y2);
	y2 = NULL;
	fclose(fp_in);
	fclose(fp_out);

	return 0;
}