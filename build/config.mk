##说明：
#包含编译配置(系统或架构相关宏以及编译链接选项等配置)

#检测系统
OS = $(shell uname)

#设置是否调试
ifeq ($(DEBUG), 0)
	DEBUG_FLAGS := -O3
else
	DEBUG_FLAGS := -g
endif

#########################################
############linux系统 ###################
ifeq ($(findstring Linux, $(OS)), Linux)
	CROSS 			?= 
	CC				:= $(CROSS)gcc
       #	-fPIC -DPIC
	CPP				:= $(CROSS)g++ -fPIC -DPIC
	LD				:= $(CROSS)ld
	AR				:= $(CROSS)ar
	#ASM			:=	yasm -DPIC
	
###ARM32架构	
ifeq ($(platform), arm32)
	ARCH_DEF		:= -DARCH_ARM=1 
	arch			:= arm
	ASM				:= $(CROSS)gcc
	EXTRA_CFLAGS 	:= -march=armv7-a -marm -mfloat-abi=softfp -mfpu=neon $(ARCH_DEF)
	EXTRA_LFLAGS 	:= -march=armv7-a -marm -pie -fPIE
	EXTRA_AFLAGS 	:= -march=armv7-a $(ARCH_DEF)
	EXTRA_LFLAGS_SO := -shared
	LIB_DIR			:= ./../../out/$(OS)_$(arch)_$(platform)
	OUT_DIR			:= ./../../bin/$(OS)_$(arch)_$(platform)
endif

###ARM64架构	
ifeq ($(platform), arm64)
	ARCH_DEF		:= -DARCH_AARCH64=1 -DHAVE_NEON=1
	arch			:= aarch64
	ASM				:= $(CROSS)gcc
	EXTRA_CFLAGS 	:= -march=armv8-a  $(ARCH_DEF)
	EXTRA_LFLAGS 	:= -march=armv8-a  -pie -fPIE
	EXTRA_AFLAGS 	:= -march=armv8-a $(ARCH_DEF)
	EXTRA_LFLAGS_SO := -shared
	LIB_DIR			:= ./../../out/$(OS)_$(arch)_$(platform)
	OUT_DIR			:= ./../../bin/$(OS)_$(arch)_$(platform)
endif

###X86_32架构	
ifeq ($(platform), x86_32)
	ARCH_DEF		:= -DARCH_X86=1 -DARCH_ARM=0 -DARCH_AARCH64=0 -DARCH_MIPS=0 
	arch			:= x86
	ASM				:= yasm -DPIC
	EXTRA_CFLAGS 	:= -m32 $(ARCH_DEF)
	EXTRA_LFLAGS 	:= -m32
	EXTRA_LFLAGS_SO := -shared
	EXTRA_AFLAGS 	:= -m x86 -DHAVE_ALIGNED_STACK=1 -DARCH_X86_64=0  -DBIT_DEPTH=8 -DHIGH_BIT_DEPTH=0 -f elf32
	LIB_DIR			:= ./../../out/$(OS)_$(arch)_$(platform)
	OUT_DIR			:= ./../../bin/$(OS)_$(arch)_$(platform)
endif


###X86_64架构	
ifeq ($(platform), x86_64)
	ARCH_DEF		:= -DARCH_X86=1 -DARCH_ARM=0 -DARCH_AARCH64=0 -DARCH_MIPS=0 -DARCH_X86_64=1 
	arch			:= x86
	ASM				:= yasm -DPIC
	EXTRA_CFLAGS 	:= -m64 $(ARCH_DEF)
	EXTRA_LFLAGS 	:= -m64 
	EXTRA_LFLAGS_SO := -shared
	EXTRA_AFLAGS 	:= -m amd64 -DHAVE_ALIGNED_STACK=1 -DHAVE_CPUNOP=0 -DSTACK_ALIGNMENT=32 -DHIGH_BIT_DEPTH=0 -DBIT_DEPTH=8 -f elf64 $(ARCH_DEF)
	LIB_DIR			:= ./../../out/$(OS)_$(arch)_$(platform)
	OUT_DIR			:= ./../../bin/$(OS)_$(arch)_$(platform)
endif

###X86_32 WASM架构	
ifeq ($(platform), wasm_32)
	CC				:= $(CROSS)emcc
       #	-fPIC -DPIC
	CPP				:= $(CROSS)em++ -fPIC -DPIC
	LD				:= $(CROSS)ld
	AR				:= $(CROSS)emar
	
	ARCH_DEF		:= -DARCH_X86=1 -DARCH_ARM=0 -DARCH_AARCH64=0 -DARCH_MIPS=0 
	arch			:= x86
	ASM				:= emcc -DPIC
	EXTRA_CFLAGS 	:= -m32 $(ARCH_DEF) -msimd128 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1
	EXTRA_LFLAGS 	:= -m32
	EXTRA_LFLAGS_SO := -shared
	EXTRA_AFLAGS 	:= -m x86 -DHAVE_ALIGNED_STACK=1 -DARCH_X86_64=0  -DBIT_DEPTH=8 -DHIGH_BIT_DEPTH=0 -f elf32 
	LIB_DIR			:= ./../../out/$(OS)_$(arch)_$(platform)
	OUT_DIR			:= ./../../bin/$(OS)_$(arch)_$(platform)
endif

###X86_64 WASM架构	
ifeq ($(platform), wasm_64)
	CC				:= $(CROSS)emcc
       #	-fPIC -DPIC
	CPP				:= $(CROSS)em++ -fPIC -DPIC
	LD				:= $(CROSS)ld
	AR				:= $(CROSS)emar

	ARCH_DEF		:= -DARCH_X86=1 -DARCH_ARM=0 -DARCH_AARCH64=0 -DARCH_MIPS=0 -DARCH_X86_64=1 
	arch			:= x86
	ASM				:= yasm -DPIC
	EXTRA_CFLAGS 	:= -m64 $(ARCH_DEF) -msimd128 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1
	EXTRA_LFLAGS 	:= -mwasm64
	EXTRA_LFLAGS_SO := -shared
	EXTRA_AFLAGS 	:= -m amd64 -DHAVE_ALIGNED_STACK=1 -DHAVE_CPUNOP=0 -DSTACK_ALIGNMENT=32 -DHIGH_BIT_DEPTH=0 -DBIT_DEPTH=8 -f elf64 $(ARCH_DEF)
	LIB_DIR			:= ./../../out/$(OS)_$(arch)_$(platform)
	OUT_DIR			:= ./../../bin/$(OS)_$(arch)_$(platform)
endif

endif

#########################################
############MAC/IOS系统 ###################
ifeq ($(findstring Darwin, $(OS)), Darwin) 

###MAC平台
ifeq ($(target_plat), mac)
	CROSS 			?= 
	CC				:= $(CROSS)gcc -fPIC -DPIC
	CPP				:= $(CROSS)g++ -fPIC -DPIC
	AR				:= $(CROSS)ar
	ASM				:=	yasm -DPIC
	
##X86_32架构
ifeq ($(platform), x86_32)
	ARCH_DEF 		:= -DMAC32
	arch			:= x86
	EXTRA_CFLAGS	:= -m32 -arch i386 $(ARCH_DEF)
	EXTRA_LFLAGS	:= -m32 -dynamiclib -Wl, -dynamic  #-read_only_relocs
	EXTRA_AFLAGS	:= -f macho32 -m x86  -DHAVE_ALIGNED_STACK=1 -DARCH_X86_64=0 -DHAVE_CPUNOP=0 -DPREFIX $(ARCH_DEF)
	EXTRA_LFLAGS_SO := -dynamiclib -Wl, -dynamic
	LIB_DIR			:= ./../../out/$(OS)_$(arch)_$(platform)
	OUT_DIR			:= ./../../bin/$(OS)_$(arch)_$(platform)
endif

##X86_64架构
ifeq ($(platform), x86_64)
	ARCH_DEF 		:= -DMAC64
	arch			:= x86
	EXTRA_CFLAGS	:= -m64 $(ARCH_DEF)
	EXTRA_LFLAGS	:= -m64 
	EXTRA_LFLAGS_SO := -dynamiclib -Wl, -dynamic
	EXTRA_AFLAGS	:= -f macho64 -m amd64 -DHAVE_ALIGNED_STACK=1 -DARCH_X86_64=1 -DHAVE_CPUNOP=0  -DPREFIX $(ARCH_DEF)
	LIB_DIR			:= ./../../out/$(OS)_$(arch)_$(platform)
	OUT_DIR			:= ./../../bin/$(OS)_$(arch)_$(platform)
endif

## Apple Silicon arm64架构
ifeq ($(platform), arm64)
#	CC				:= xcrun -sdk $(CROSS)os clang
	CPP 			:= g++
	AR				:= ar
	ASM				:= xcrun -sdk macosx11.3 clang -arch arm64
# perl gas-preprocessor.pl -arch aarch64 -as-type apple-clang --$(CC)

	ARCH_DEF	 	:= -DARM64
	arch		 	:= aarch64
	EXTRA_CFLAGS 	:= -arch arm64 $(ARCH_DEF)
	EXTRA_LFLAGS 	:= -arch arm64
	EXTRA_LFLAGS_SO	:= -shared
	EXTRA_AFLAGS 	:= -DPREFIX $(ARCH_DEF)
	LIB_DIR		 	:= ./../../out/$(OS)_$(arch)_$(platform)
	OUT_DIR		 	:= ./../../bin/$(OS)_$(arch)_$(platform)
endif

endif

###IOS平台
ifeq ($(target_plat), ios)
	CROSS 			:= iphone
ifeq ($(platform), ios32)
	CC				:= xcrun -sdk $(CROSS)os clang
	CPP				:= g++
	AR				:= ar
	ASM				:= perl gas-preprocessor.pl -arch arm -as-type apple-clang --$(CC)
	
	ARCH_DEF		:= -DIOS32
	arch			:= arm
	EXTRA_CFLAGS 	:= -arch armv7 -mios-version-min=6.0 $(ARCH_DEF)
	EXTRA_LFLAGS 	:= -arch armv7 -mios-version-min=6.0 -shared
	EXTRA_AFLAGS 	:= -arch armv7 -mios-version-min=6.0 -DPREFIX $(ARCH_DEF)
	LIB_DIR			:= ./../../out/$(OS)_$(arch)_$(platform)
	OUT_DIR			:= ./../../bin/$(OS)_$(arch)_$(platform)
endif

ifeq ($(platform), ios64)
	CC				:= xcrun -sdk $(CROSS)os clang
	CPP 			:= g++
	AR				:= ar
	ASM				:= perl gas-preprocessor.pl -arch aarch64 -as-type apple-clang --$(CC)
	
	ARCH_DEF		:= -DIOS64
	arch			:= aarch64
	EXTRA_CFLAGS 	:= -arch arm64 -mios-version-min=6.0 $(ARCH_DEF)
	EXTRA_LFLAGS 	:= -arch arm64 -mios-version-min=6.0 -shared
	EXTRA_AFLAGS 	:= -arch arm64 -mios-version-min=6.0 $(ARCH_DEF)
	LIB_DIR			:= ./../../out/$(OS)_$(arch)_$(platform)
	OUT_DIR			:= ./../../bin/$(OS)_$(arch)_$(platform)
endif 

ifeq ($(platform), ios_sim32)
	CC				:= xcrun -sdk $(CROSS)simulators clang
	CPP				:= g++
	AR				:= ar
	ASM				:= yasm
	
	ARCH_DEF	 	:=
	arch		 	:= x86
	EXTRA_CFLAGS 	:= -arch i386 -mios-simulator-version-min=6.0 $(ARCH_DEF)
	EXTRA_LFLAGS 	:= -arch i386 -mios-simulator-version-min=6.0 -Wl, -Bsymbolic-functions -read_only_relocs suppress
	EXTRA_AFLAGS 	:= -f macho32 -m x86 $(ARCH_DEF)
	LIB_DIR			:= ./../../out/$(OS)_$(arch)_$(platform)
	OUT_DIR			:= ./../../bin/$(OS)_$(arch)_$(platform)
endif 

ifeq ($(platform), ios_sim64)
	CC				:= xcrun -sdk $(CROSS)simulators clang
	CPP				:= g++
	AR				:= ar
	ASM				:= yasm
	
	ARCH_DEF	 	:=
	arch		 	:= x86
	EXTRA_CFLAGS 	:= -arch x86_64 -mios-simulator-version-min=6.0 $(ARCH_DEF)
	EXTRA_LFLAGS 	:= -arch x86_64 -mios-simulator-version-min=6.0
	EXTRA_AFLAGS 	:= -f macho64 -m amd64 $(ARCH_DEF)
	LIB_DIR			:= ./../../out/$(OS)_$(arch)_$(platform)
	OUT_DIR			:= ./../../bin/$(OS)_$(arch)_$(platform)
endif 

endif ##ifeq ($(target_plat), ios)

endif

######GIT版本获取#########
GIT=$(shell git rev-list -n 1 HEAD | cut -c 1-7)

######汇编宏的配置#######
ifeq ($(PUREC), 0)
ifeq ($(findstring Linux, $(OS)), Linux)
###X86_32架构	
ifeq ($(platform), x86_32)
EXTRA_CFLAGS+=-DARCH_X86_64=0 -msse2 -mssse3 -msse4.1 
endif

###X86_64架构	
ifeq ($(platform), x86_64)
EXTRA_CFLAGS+=-DARCH_X86_64=1 -msse2 -mssse3 -msse4.1
endif

###ARM32架构	
ifeq ($(platform), arm32)
EXTRA_CFLAGS += -DARCH_ARM=1
endif

###ARM64架构	
ifeq ($(platform), arm64)
EXTRA_CFLAGS += -DARCH_AARCH64=1
endif
endif


ifeq ($(findstring Darwin, $(OS)), Darwin) 

###MAC32架构	
ifeq ($(platform), x86_32)
EXTRA_CFLAGS+=-DARCH_X86_64=0 -DARCH_ARM=0 -DARCH_AARCH64=0
endif

###MAC64架构	
ifeq ($(platform), x86_64)
EXTRA_CFLAGS+=-DARCH_X86_64=1 -DARCH_ARM=0 -DARCH_AARCH64=0
endif

## Apple Silicon arm64架构
ifeq ($(platform), arm64)
EXTRA_CFLAGS+=-DARCH_X86_64=0 -DARCH_ARM=0 -DARCH_AARCH64=1
endif

###IOS平台
ifeq ($(target_plat), ios)
ifeq ($(platform), ios32)
EXTRA_CFLAGS += -DARCH_ARM=1
endif
ifeq ($(platform), ios64)
EXTRA_CFLAGS += -DARCH_AARCH64=1
endif

endif
endif
endif
