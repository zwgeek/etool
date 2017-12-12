###
 # Copyright 2017, PaPa.  All rights reserved.
 # Makefile
###

ifeq ($(PLATFORM), )
$(warning no input PLATFORM, like 'make PLATFORM = xxx')
$(warning use default compile mode...)
ALLDONE = @make -f Config.mk SYSTEM=$(SYSTEM) SRCS_PATH=$(SRCS_PATH) INCLUDES=$(INCLUDES) TEST_SRCS_PATH=$(TEST_SRCS_PATH);
DEBUGDONE = @make -f Config.mk SYSTEM=$(SYSTEM) SRCS_PATH=$(SRCS_PATH) INCLUDES=$(INCLUDES) TEST_SRCS_PATH=$(TEST_SRCS_PATH) debug;
CLEANDONE = @make -f Config.mk clean;
endif

#linux mac android ios windows
SYSTEM = windows
SRCS_PATH = src
INCLUDES = src
TEST_SRCS_PATH = test

all :
	$(ALLDONE)
	@for platform in $(PLATFORM); do make -f Config.mk SYSTEM=$(SYSTEM) SRCS_PATH=$(SRCS_PATH) INCLUDES=$(INCLUDES) TEST_SRCS_PATH=$(TEST_SRCS_PATH) CROSS=$$platform-; done

debug :
	$(DEBUGDONE)
	@for platform in $(PLATFORM); do make -f Config.mk SYSTEM=$(SYSTEM) SRCS_PATH=$(SRCS_PATH) INCLUDES=$(INCLUDES) TEST_SRCS_PATH=$(TEST_SRCS_PATH) CROSS=$$platform- debug; done

clean :
	$(CLEANDONE)
	@for platform in $(PLATFORM); do make -f Config.mk clean CROSS=$$platform-; done
