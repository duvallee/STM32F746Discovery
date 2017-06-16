#!/bin/bash
#
#

# --------------------------------------------------------------------------------------
# get cpu core number
export CPU_JOB_NUM=$(grep processor /proc/cpuinfo | awk '{field=$NF};END{print field+2}')
export ARCH=arm

# --------------------------------------------------------------------------------------
export BUILD_ROOT=`pwd`
export TOOLCHAIN_PATH="${BUILD_ROOT}/toolchain/gcc-arm-none-eabi-6-2017-q1-update/bin"
export TOOLCHAIN_PREFIX="arm-none-eabi"


# --------------------------------------------------------------------------------------
# add tool-chain bin directory to PATH
echo $TOOLCHAIN_PATH
 export PATH=${TOOLCHAIN_PATH}:$PATH

# --------------------------------------------------------------------------------------
# excute gdb 
${TOOLCHAIN_PREFIX}-gdb ./build/STM32F746Discovery.elf

if [ $? != 0 ]
then
   echo
   echo "Not found gdb for ARM Cortex-M !!!"
   echo
   exit 1
fi



