# 用法:
#   make                      本地编译运行
#   make CROSS=arm32          动态链接 ARM32（依赖目标设备的 glibc）
#   make CROSS=arm32 STATIC=1 静态链接 ARM32（推荐，无依赖）
#   make CROSS=arm64 STATIC=1 ARM64 静态链接

CC      ?= gcc
CROSS   ?=
STATIC  ?=

# ARM32 (armhf) — 全志 TinaLinux / 树莓派 等
ifeq ($(CROSS),arm32)
  CC      := arm-linux-gnueabihf-gcc
  SYSROOT := $(HOME)/.local/armhf-toolchain
  CFLAGS  += --sysroot=$(SYSROOT)
  LDFLAGS += --sysroot=$(SYSROOT)
  TARGET  := _arm
endif

# ARM64 (aarch64)
ifeq ($(CROSS),arm64)
  CC      := aarch64-linux-gnu-gcc
  SYSROOT := $(HOME)/.local/aarch64-toolchain
  CFLAGS  += --sysroot=$(SYSROOT)
  LDFLAGS += --sysroot=$(SYSROOT)
  TARGET  := _arm
endif

# 静态链接（解决目标设备 glibc 版本不匹配问题）
ifeq ($(STATIC),1)
  LDFLAGS += -static
endif

main: hello.c unit.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o main$(TARGET) hello.c unit.c
ifeq ($(CROSS),)
	./main
	@echo "输出: main (x86-64)"
else ifeq ($(STATIC),1)
	@echo "输出: main_arm (静态链接) → 可独立运行"
else
	@echo "输出: main_arm (动态链接) → 需要设备 glibc 匹配"
endif

execl: execl.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o execl$(TARGET) execl.c
ifeq ($(CROSS),)
	./execl
	rm execl
endif

clean:
	rm -f main main_arm execl execl_arm