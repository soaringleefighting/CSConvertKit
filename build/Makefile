#########################################################################
## Function: makefile for CSConvertKit project
## Platform: linux, macOS
## Author: 	 lipeng
## Modified: 2021.7.2 created
#########################################################################

platform ?= x86_64
PUREC 	 ?= 1
DEBUG 	 ?= 0

#包含编译配置(系统或架构相关宏以及编译链接选项等配置)
include config.mk

#指定后缀名和伪目标
.SUFFIXES: .c,.o,.cpp,.S,.s  
.PHONY	 : all,clean

#设置相关路径
vpath %.h ./../../src
ROOTSRC  = ./../Projects
INCLUDES = ./../Projects

#设置工具的相关参数
BIN_TARGET = $(BIN_YUV420PtoMonoY) $(BIN_YUV420PtoRGB24) $(BIN_YUV420PtoYUV422P) $(BIN_YUV420toYUV444) $(BIN_YUV422PtoNV16) \
			 $(BIN_I420toNV12) $(BIN_I420toNV21) $(BIN_I420toYV12) $(BIN_NV12toI420) $(BIN_NV12toYV12) $(BIN_NV12toYVYU)    \
			 $(BIN_NV21toYV12) $(BIN_RGB24toYUV420P) $(BIN_NV21toBGR24)
BIN_YUV420PtoMonoY     = ./../bin/$(OS)/YUV420PtoMonoY
BIN_I420toNV12		   = ./../bin/$(OS)/I420toNV12
BIN_I420toNV21  	   = ./../bin/$(OS)/I420toNV21
BIN_I420toYV12		   = ./../bin/$(OS)/I420toYV12
BIN_NV12toI420 		   = ./../bin/$(OS)/NV12toI420
BIN_NV12toYV12 		   = ./../bin/$(OS)/NV12toYV12
BIN_NV12toYVYU		   = ./../bin/$(OS)/NV12toYVYU 
BIN_NV21toYV12		   = ./../bin/$(OS)/NV21toYV12 

BIN_YUV420PtoRGB24     = ./../bin/$(OS)/YUV420PtoRGB24
BIN_RGB24toYUV420P     = ./../bin/$(OS)/RGB24toYUV420P
BIN_NV21toBGR24		   = ./../bin/$(OS)/NV21toBGR24
BIN_YUV420PtoYUV422P   = ./../bin/$(OS)/YUV420PtoYUV422P
BIN_YUV420toYUV444     = ./../bin/$(OS)/YUV420toYUV444
BIN_YUV422PtoNV16      = ./../bin/$(OS)/YUV422PtoNV16

#可执行文件目录
BIN_DIR = ./../bin/$(OS)

#设置编译的相关参数
CFLAGS := -Wall -std=c99 -fno-stack-protector  $(DEBUG_FLAGS) -I$(INCLUDES)
CFLAGS += $(EXTRA_CFLAGS) 

CXXFLAGS := -Wall  $(DEBUG_FLAGS) -I$(INCLUDES)
CXXFLAGS += $(EXTRA_CFLAGS)

LDFLAGS := -Wall
LDFLAGS += $(EXTRA_LFLAGS)
 
ARFLAGS := -crus

ASMFLAGS += $(EXTRA_AFLAGS)

#以下获取OBJS文件的方式适用于含有少量文件的编译
SRCS1 = $(ROOTSRC)/YUV420PtoMonoY/YUV420PtoMonoY/YUV420PtoMonoY.cpp
SRCS2 = $(ROOTSRC)/YUV420PtoYUV420SP/I420toNV12/I420toNV12/I420toNV12.cpp
SRCS3 = $(ROOTSRC)/YUV420toRGB24/YUV420ptoRGB24/YUV420ptoRGB24/yuv420torgb24.cpp
SRCS4 = $(ROOTSRC)/YUV420toYUV422/YUV420PtoYUV422P/YUV420PtoYUV422P/YUV420PtoYUV422P.cpp
SRCS5 = $(ROOTSRC)/YUV420toYUV444/YUV420toYUV444/yuv420toyuv444.c
SRCS6 = $(ROOTSRC)/YUV422PtoYUV422SP/YUV422PtoNV16/YUV422PtoNV16/yuv422pToNV16.c

SRCS7 = $(ROOTSRC)/YUV420PtoYUV420SP/I420toNV21/I420toNV21/I420toNV21.c
SRCS8 = $(ROOTSRC)/YUV420PtoYUV420SP/I420toYV12/I420toYV12/I420toYV12.cpp
SRCS9 = $(ROOTSRC)/YUV420PtoYUV420SP/NV12toI420/NV12toI420/NV12toI420.cpp
SRCSa = $(ROOTSRC)/YUV420PtoYUV420SP/NV12toYV12/NV12toYV12/NV12toYV12.cpp
SRCSb = $(ROOTSRC)/YUV420PtoYUV420SP/NV12toYVYU/NV12toYVYU/nv12toyvyu.c
SRCSc = $(ROOTSRC)/YUV420PtoYUV420SP/NV21toYV12/NV21toYV12/NV21toYV12.cpp
SRCSd = $(ROOTSRC)/YUV420toRGB24/BGR24toYUV420P/BGR24toYUV420P/BGR2YUV.cpp
SRCSe = $(ROOTSRC)/YUV420toRGB24/NV21toBGR24/NV21toBGR24/NV21toBGR24.cpp

#OBJS = $(patsubst %.S,%.o, $(patsubst %.asm,%.o, $(patsubst %.cpp,%.o, $(patsubst %.c,%.o,$(SRCS)))))

OBJS1 = $(ROOTSRC)/YUV420PtoMonoY/YUV420PtoMonoY/YUV420PtoMonoY.o
OBJS2 = $(ROOTSRC)/YUV420PtoYUV420SP/I420toNV12/I420toNV12/I420toNV12.o
OBJS3 = $(ROOTSRC)/YUV420toRGB24/YUV420ptoRGB24/YUV420ptoRGB24/yuv420torgb24.o
OBJS4 = $(ROOTSRC)/YUV420toYUV422/YUV420PtoYUV422P/YUV420PtoYUV422P/YUV420PtoYUV422P.o
OBJS5 = $(ROOTSRC)/YUV420toYUV444/YUV420toYUV444/yuv420toyuv444.o
OBJS6 = $(ROOTSRC)/YUV422PtoYUV422SP/YUV422PtoNV16/YUV422PtoNV16/yuv422pToNV16.o

OBJS7 = $(ROOTSRC)/YUV420PtoYUV420SP/I420toNV21/I420toNV21/I420toNV21.o
OBJS8 = $(ROOTSRC)/YUV420PtoYUV420SP/I420toYV12/I420toYV12/I420toYV12.o
OBJS9 = $(ROOTSRC)/YUV420PtoYUV420SP/NV12toI420/NV12toI420/NV12toI420.o
OBJSa = $(ROOTSRC)/YUV420PtoYUV420SP/NV12toYV12/NV12toYV12/NV12toYV12.o
OBJSb = $(ROOTSRC)/YUV420PtoYUV420SP/NV12toYVYU/NV12toYVYU/nv12toyvyu.o
OBJSc = $(ROOTSRC)/YUV420PtoYUV420SP/NV21toYV12/NV21toYV12/NV21toYV12.o
OBJSd = $(ROOTSRC)/YUV420toRGB24/BGR24toYUV420P/BGR24toYUV420P/BGR2YUV.o
OBJSe = $(ROOTSRC)/YUV420toRGB24/NV21toBGR24/NV21toBGR24/NV21toBGR24.o

#编译规则
all: clean mkdr $(BIN_TARGET)
mkdr: #自动创建库目录LIB_DIR
	if [ ! -d $(BIN_DIR) ];then mkdir -p $(BIN_DIR); echo "$(BIN_DIR) create successfully!"; else echo "$(BIN_DIR) already exists!"; fi

$(BIN_YUV420PtoMonoY): $(OBJS1)
	$(CC) -o $@ $(OBJS1) $(LDFLAGS)

$(BIN_I420toNV12): $(OBJS2)
	$(CC) -o $@ $(OBJS2) $(LDFLAGS)

$(BIN_YUV420PtoRGB24): $(OBJS3)
	$(CC) -o $@ $(OBJS3) $(LDFLAGS)

$(BIN_RGB24toYUV420P):	$(OBJSd)
	$(CC) -o $@ $(OBJSd) $(LDFLAGS)

$(BIN_NV21toBGR24): $(OBJSe)
	$(CC) -o $@ $(OBJSe) $(LDFLAGS)	

$(BIN_YUV420PtoYUV422P): $(OBJS4)
	$(CC) -o $@ $(OBJS4) $(LDFLAGS)

$(BIN_YUV420toYUV444): $(OBJS5)
	$(CC) -o $@ $(OBJS5) $(LDFLAGS)

$(BIN_YUV422PtoNV16): $(OBJS6)
	$(CC) -o $@ $(OBJS6) $(LDFLAGS)

$(BIN_I420toNV21): $(OBJS7)
	$(CC) -o $@ $(OBJS7) $(LDFLAGS)

$(BIN_I420toYV12): $(OBJS8)
	$(CC) -o $@ $(OBJS8) $(LDFLAGS)

$(BIN_NV12toI420): $(OBJS9)
	$(CC) -o $@ $(OBJS9) $(LDFLAGS)

$(BIN_NV12toYV12): $(OBJSa)
	$(CC) -o $@ $(OBJSa) $(LDFLAGS)

$(BIN_NV12toYVYU): $(OBJSb)
	$(CC) -o $@ $(OBJSb) $(LDFLAGS)

$(BIN_NV21toYV12): $(OBJSc)
	$(CC) -o $@ $(OBJSc) $(LDFLAGS)	

%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@
%.o: %.cpp
	$(CXX) -c $< $(CXXFLAGS) -o $@
		
%.o:%.asm
	$(ASM) $< $(ASMFLAGS) -o $@	
%.o:%.S
	$(ASM) $< $(ASMFLAGS) -c -o $@
%.o:%.s
	$(ASM) $< $(ASMFLAGS) -c -o $@	
		
clean:
	-rm	$(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5) $(OBJS6) $(OBJS7) $(OBJS8) $(OBJS9) $(OBJSa) $(OBJSb) $(OBJSc) $(OBJSd) $(OBJSe)
	-rm $(BIN_TARGET)
