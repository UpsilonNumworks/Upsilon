CC = nspire-gcc
CXX = nspire-g++
LD = nspire-ld
GDB = arm-none-eabi-gdb
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size
AS = nspire-as
GENZEHN = genzehn

SFLAGS += -U__STRICT_ANSI__ -D_NSPIRE -marm
