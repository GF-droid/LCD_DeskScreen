# ARM64 (aarch64) 交叉编译工具链 — 树莓派 3+/4/5 等
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

set(triple aarch64-linux-gnu)
set(CMAKE_C_COMPILER    ${triple}-gcc)
set(CMAKE_CXX_COMPILER  ${triple}-g++)

set(TOOLCHAIN_HOME $ENV{HOME}/.local/aarch64-toolchain)
set(CMAKE_SYSROOT ${TOOLCHAIN_HOME})

# 让交叉编译器的子工具（as/ld）能找到自身依赖的 .so
set(ENV{LD_LIBRARY_PATH} "${TOOLCHAIN_HOME}/usr/lib/x86_64-linux-gnu:$ENV{LD_LIBRARY_PATH}")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
