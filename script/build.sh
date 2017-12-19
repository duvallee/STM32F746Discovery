#!/bin/bash
#
#

# --------------------------------------------------------------------------------------
# get cpu core number
export CPU_JOB_NUM=$(grep processor /proc/cpuinfo | awk '{field=$NF};END{print field+2}')
export ARCH=arm

# --------------------------------------------------------------------------------------
# set configuration for debug output device
#export DEBUG_OUTPUT_DEVICE=UART
export DEBUG_OUTPUT_DEVICE=USB

# --------------------------------------------------------------------------------------
export BUILD_ROOT=`pwd`
export TOOLCHAIN_PATH="${BUILD_ROOT}/toolchain/gcc-arm-none-eabi-6-2017-q1-update/bin"
export TOOLCHAIN_PREFIX="arm-none-eabi"


# --------------------------------------------------------------------------------------
# add tool-chain bin directory to PATH
echo $TOOLCHAIN_PATH
 export PATH=${TOOLCHAIN_PATH}:$PATH

# --------------------------------------------------------------------------------------
# check gcc compiler
${TOOLCHAIN_PREFIX}-gcc -v
if [ $? != 0 ]
then
   echo
   echo "Not found tool-chain for ARM Cortex-M !!!"
   echo
   exit 1
fi

# --------------------------------------------------------------------------------------
# build

# comment out the BINPATH in the Makefile
make clean
if [ ${DEBUG_OUTPUT_DEVICE} == UART ]
then
	echo "DEBUG OUTPUT DDEVICE = UART"
elif [ ${DEBUG_OUTPUT_DEVICE} == USB ]
then
	echo "DEBUG OUTPUT DDEVICE = USB"
else
	echo "Not found DEBUG_OUTPUT_DEVICE"
	exit 1
fi

make -j${CPU_JOB_NUM} BINPATH=${TOOLCHAIN_PATH}



