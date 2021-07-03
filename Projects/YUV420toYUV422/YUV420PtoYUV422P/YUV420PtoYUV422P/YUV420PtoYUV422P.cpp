#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
	int i, j, width, height, frame_size;
	FILE *fp_in, *fp_out;
	unsigned char *y1, *u1, *v1, *y2, *u2, *v2;
	int n = 0;

	for (i = 0; i < argc;i++)
	{
		printf("Input parameters: %s \n", argv[i]);
	}
	if (argc < 5)
	{
		printf("\nUsage:YUV420PtoYUV422.exe inputfile outputfile width height\n\n");
#if WIN32
		system("pause");
#endif
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

	y2 = (unsigned char *)malloc(frame_size*2);
	if (NULL== y2 )
	{
		printf("malloc y2 fail\n");
		return -1;
	}
	u2 = y2 + width*height;
	v2 = u2 + width*height/2;

	while (fread(y1, 1, frame_size*3/2, fp_in) == frame_size*3/2)
	{
		// Y
		memcpy(y2, y1, frame_size);

		// U
		for (i = 0; i < height/2; i++) 
		{         
			memcpy(u2 + i*width,           u1 + i*width/2, width/2);
			memcpy(u2 + i*width + width/2, u1 + i*width/2, width/2);
		}

		// V
		for (j = 0; j < height/2; j++) 
		{  
			memcpy(v2 + j*width,           v1 + j*width/2, width/2);
			memcpy(v2 + j*width + width/2, v1 + j*width/2, width/2);
		} 

		fwrite(y2, 1, frame_size*2, fp_out);

		n++;

		printf("%dth frame process ok!!!\n", n);
	}

	printf("[CSConverKit] YUV420toYUV422 successfully!!, total frames: %d\n",n);

	free(y1);
	y1 = NULL;
	free(y2);
	y2 = NULL;
	fclose(fp_in);
	fclose(fp_out);

	return 0;
}
