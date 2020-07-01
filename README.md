# CSConvertKit

CSConvertKit is a series of projects for Converting YUV colorspace, such as YUV420P(I420,YV12),YUV420SP(NV21,NV12), NV16, RGB24, BGR24,
YUV422P, YUV444 and so on.


## 1���ο�

��Codecsϵ�С���ɫ�ռ�ת��CSConvertϵ�л���: https://blog.csdn.net/SoaringLee_fighting/article/details/95213543

## 2��֧�ֹ���

˵������ǰ֧������6������ɫ�ռ�ת�����ܡ�

### 2.1��YUV420��YUV400�໥ת��

���ܣ� ʵ��YUV420Pת�������ȷ���Y��

Usage:YUV420PtoMonoY.exe input.yuv output.yuv width height

### 2.2��YUV420P��YUV420SP�໥ת��

(1) I420toNV12

Usage:I420toNV12.exe input.yuv width height

(2) I420toNV21

Usage:I420toNV21.exe input.yuv width height

(3) I420toYV12

Usage:I420toYV12.exe input.yuv width height

(4) NV12toI420

Usage: NV12toI420.exe input.yuv width height

(5) NV12toYV12

Usage:NV12toYV12.exe input.yuv width height

(6) NV12toYVYU

Usage: NV12toYVYU.exe infile outfile width height

(7) NV21toYV12

Usage: NV21toYV12.exe input.yuv width height

### 2.3��YUV420��RGB24�໥ת��

(1) yuv420ptoRGB24

Usage: yuv420ptoRGB24.exe yuv420_file rgb24_filename width height

(2) NV21toBGR24

Usage: NV21toBGR24.exe inputYUV outputYUV width height framenum

(3) BGR24toYUV420P

Usage: ./BGR24toYUV420P.exe inputYUV outputYUV width height

### 2.4��YUV420��YUV422�໥ת��

(1) YUV420PtoYUV422

Usage:YUV420PtoYUV422.exe inputfile outputfile width height

### 2.5��YUV420��YUV444�໥ת��

(1) YUV420toYUV444

Usage:YUV420toYUV444.exe inputfile outputfile width height

### 2.6��YUV422P��YUV422SP�໥ת��

(1) YUV422PtoNV16

Usage: YUV422PtoNV16.exe input.yuv width height


## 3��Ŀ¼�ṹ˵��

bin			: windowsƽ̨�µĿ�ִ���ļ�

Projects	: ��ɫ�ռ�ת�����ߵ�windowsƽ̨vs2013���� 