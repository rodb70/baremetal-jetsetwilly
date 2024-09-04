# Makefile

YEAR = $(shell date +'%Y')

#CROSS_COMPILE := 

COMPILER := gcc

CPU := host
BLD_TARGET := jetsetwilly
BLD_TYPE := debug

USE_AUDIO := n

ifeq ($(CPU),rpi1)
PROJ_DIRS := rpi1
endif
ifeq ($(CPU),host)
PROJ_DIRS := host
EXTRA_LIBS := -lSDL2
SHORT_ENUMS := n

endif

PROJ_DIRS += src

CFLAGS := -DBUILD=\"v1.0.$(YEAR)\"
CFLAGS += -DNOCODES

include makefiles/main.mk

distclean:
	rm -rf build

