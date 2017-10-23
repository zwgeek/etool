###
 # Copyright 2017, Geeks Road.  All rights reserved.
 # Makefile
###

ifeq ($(PLATFORM), )
$(warning no input PLATFORM, like 'make PLATFORM = xxx')
$(warning use default compile mode...)
ALLDONE = @make -f Config.mk SRCS_PATH=$(SRCS_PATH) INCLUDES=$(INCLUDES) TEST_SRCS_PATH=$(TEST_SRCS_PATH);
CLEANDONE = @make -f Config.mk clean;
endif

SRCS_PATH = src
INCLUDES = -lsrc
TEST_SRCS_PATH = test

all :
	$(ALLDONE)
	@for platform in $(PLATFORM); do make -f Config.mk SRCS_PATH=$(SRCS_PATH) INCLUDES=$(INCLUDES) TEST_SRCS_PATH=$(TEST_SRCS_PATH) CROSS=$$platform-; done

clean :
	$(CLEANDONE)
	@for platform in $(PLATFORM); do make -f Config.mk clean CROSS=$$platform-; done
