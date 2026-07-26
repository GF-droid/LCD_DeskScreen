# ============================================================
# 用法:
#   本地编译:     cmake -B build && cmake --build build
#   ARM32 交叉:   cmake -B build_arm -DCROSS=arm32 -DSTATIC=ON && cmake --build build_arm
#   ARM64 交叉:   cmake -B build_arm -DCROSS=arm64 -DSTATIC=ON && cmake --build build_arm
# ============================================================

# CMAKE_TOOLCHAIN_FILE 必须在 project() 之前设置
if(DEFINED CROSS)
  set(TOOLCHAIN_DIR "${CMAKE_CURRENT_LIST_DIR}/../../cmake")
  if(CROSS STREQUAL "arm32")
    set(CMAKE_TOOLCHAIN_FILE "${TOOLCHAIN_DIR}/armhf-toolchain.cmake"
        CACHE STRING "" FORCE)
  elseif(CROSS STREQUAL "arm64")
    set(CMAKE_TOOLCHAIN_FILE "${TOOLCHAIN_DIR}/aarch64-toolchain.cmake"
        CACHE STRING "" FORCE)
  else()
    message(FATAL_ERROR "CROSS 必须是 arm32 或 arm64，当前: ${CROSS}")
  endif()
endif()

cmake_minimum_required(VERSION 3.16)
project(main C)

option(STATIC "静态链接（消除 glibc 版本依赖）" OFF)

aux_source_directory(. SRCS)
add_executable(main ${SRCS})

if(STATIC)
  target_link_options(main PRIVATE -static)
endif()
