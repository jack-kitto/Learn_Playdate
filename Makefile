HEAP_SIZE      = 8388208
STACK_SIZE     = 61800

PRODUCT = Learn_Playdate.pdx

# Locate the SDK
SDK = ${PLAYDATE_SDK_PATH}
ifeq ($(SDK),)
	SDK = $(shell egrep '^\s*SDKRoot' ~/.Playdate/config | head -n 1 | cut -c9-)
endif

ifeq ($(SDK),)
$(error SDK path not found; set ENV value PLAYDATE_SDK_PATH)
endif

######
# IMPORTANT: You must add your source folders to VPATH for make to find them
# ex: VPATH += src1:src2
######

VPATH += src

# List C source files here
SRC = 	\
        src/main.c \
        src/game/game.c \
        src/input/input.c \
        src/graphics/graphics.c \
        src/level/level.c \

# List all user directories here
UINCDIR = 

# List user asm files
UASRC = 

# List all user C define here, like -D_DEBUG=1
UDEFS = 

# Define ASM defines here
UADEFS = 

# List the user directory to look for the libraries here
ULIBDIR =

# List all user libraries here
ULIBS =

include $(SDK)/C_API/buildsupport/common.mk

CFLAGS += -I$(PLAYDATE_SDK_PATH)/C_API
LDFLAGS += -L$(PLAYDATE_SDK_PATH)/lib

# Target to clean build artifacts
.PHONY: clean
clean:
	rm -rf $(PRODUCT) $(SRC:.c=.o) $(UASRC:.s=.o)
	rm -rf build

# Target to build and package for uploading
.PHONY: package
package: $(PRODUCT)
	@echo "Packaging $(PRODUCT) for upload..."
	zip -r $(PRODUCT).zip $(PRODUCT)
