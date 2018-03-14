#
#       !!!! Do not edit this makefile with an editor which replace tabs by spaces !!!!
#
##############################################################################################
# 
# On command line:
#
# make all              =   Create project
# make clean            =   Clean project files.
# To rebuild project    =   Do make clean" and "make all".
#
##############################################################################################
#
#Start of default section

TOOLCHAIN = arm-none-eabi-

CC          = $(TOOLCHAIN)gcc
CP          = $(TOOLCHAIN)objcopy
AS          = $(TOOLCHAIN)gcc -x assembler-with-cpp
HEX         = $(CP) -O ihex
BIN         = $(CP) -O binary
FILESIZE    = $(TOOLCHAIN)size

MCU             = cortex-m3
MCFLAGS         = -mcpu=$(MCU)
C_COMPILER_STD  = -std=gnu99

# Define optimisation level here
OPT = -O0

#End of default section
#
###############################################################################################
#
#Start of user section

#Include other files here
include ./make_symbols.mk

#Define Debug mode
DEBUG   =   1

#Define name of the application
TARGET_NAME = app

#Define user warninig(#warning directive) mode
WARNING_ENABLE = 1

#User directory list
#ROOTDIR : From here the makefile will get fire
ROOTDIR_PATH    =  .
INCLUDEDIR_PATH =  $(ROOTDIR_PATH)/include
SOURCEDIR_PATH  =  $(ROOTDIR_PATH)/source

#User output directory
TARGET_PATH = Build/Hex
OBJ_PATH    = Build/Obj
DEP_PATH    = Build/.dep

# List C source files here
# Use forward slash(/) to specify directory path
SRC =	$(SOURCEDIR_PATH)/app.c					\
		$(SOURCEDIR_PATH)/appConfig.c			\
		$(SYSCLK)/sysClk.c						\
		$(LPC1768_SRC)/pin_lpc1768.c			\
		$(LPC1768_SRC)/vectors_lpc1768.c		\
		$(SYSCLK_LPC1768)/sysClk_lpc1768.c		\
		$(GPIO_LPC1768)/gpio_lpc1768.c			\
		$(GPIO)/gpio.c			\
		$(UART_LPC1768)/uart_lpc1768.c			\
		$(UART)/uart.c			\
		$(UTILS)/epcf_fifo.c			\
		$(UTILS)/epcf_string.c
		
#		$(GPIO_LPC1768)/gpio_lpc1768.c				
#		$(GPIO)/gpio.c							\
		

# List ASM source files here
ASRC =

# List all user directories here
UINCDIR =   $(INCLUDEDIR_PATH)   \
            $(PCF_DIR)/include

# List the user directory to look for the libraries here
ULIBS =

# List user debug libraries path
ULIBDIR_DEBUG =

# List user release libraries path
ULIBDIR_RELEASE =

# List the linker script for the project
LDSCRIPT = ./lpc1768_flash.ld

# List user defines in debug mode
UDEFS_DEBUG = 

# List user defines in release mode
UDEFS_RELEASE = 

# List the user compiler flags to pass to the compiler
# Commonly used flags:
UCPFLAGS = 

# List the user assembler flags to pass to the assembler
# Commonly used flags:
UASFLAGS = 

# List the user linker flags to pass to the linker
# Commonly used flags: -u _printf_float
ULDFLAGS =

#End of user section
#
###############################################################################################
#
#Don't modify or edit this section

#Compiler Flags
CPFLAGS = $(UCPFLAGS) $(MCFLAGS) $(OPT) -mthumb -fomit-frame-pointer -Wall $(WARNING_FLAG) -fverbose-asm -Wa,-ahlms=$(@:.o=.lst) $(C_COMPILER_STD) $(DEFS)

# Generate dependency information
CPFLAGS += -MD -MP -MF $(DEP_PATH)/$(@F).d

#Assembler Flags
ASFLAGS = $(UASFLAGS) $(MCFLAGS) -Wa,-amhls=$(@:.o=.lst)))

#Linker Flags
LDFLAGS = $(ULDFLAGS) $(MCFLAGS) -mthumb --specs=nano.specs --specs=nosys.specs -nostartfiles -T$(LDSCRIPT) -Wl,-Map=$(TARGET).map,--cref,--no-warn-mismatch

ifeq ($(DEBUG),1)

OBJDIR      =   $(OBJ_PATH)/Debug
TARGETDIR   =   $(TARGET_PATH)/Debug
LIBDIR      =   $(patsubst %,-L%,$(ULIBDIR_DEBUG))
ASFLAGS     +=  -gdwarf-2
CPFLAGS     +=  -gdwarf-2 
DEFS        =   $(UDEFS_DEBUG)

else

OBJDIR      =   $(OBJ_PATH)/Release
TARGETDIR   =   $(TARGET_PATH)/Release
LIBDIR      =   $(patsubst %,-L%,$(ULIBDIR_RELEASE))
DEFS        =   $(UDEFS_RELEASE)
endif

ifeq ($(WARNING_ENABLE),1)
WARNING_FLAG = -Wno-cpp
endif

#Final target path
TARGET  = $(TARGETDIR)/$(TARGET_NAME)

INCDIR  = $(patsubst %,-I%,$(UINCDIR))
OBJS    = $(patsubst %.c,$(OBJDIR)/%.o,$(notdir $(SRC)))
LIBS    = $(ULIBS)

#Resolving VPATH variable. All $(SRC) paths are added in VPATH variable seperated by a colon.
# VPATH is used by the makefile to find source files.
VPATH   = $(patsubst %/,%:,$(dir $(SRC)))

#End of the section
#
###############################################################################################
#
# makefile rules
#
.PHONY: all
all: echo makedir $(OBJS) $(TARGET).elf $(TARGET).hex

echo:
	@echo "******************************************"
	@echo "MESSAGE PRINTING"
	@echo "INCLUDE      : $(INCDIR)"
	@echo "SOURCE       : $(SRC)"
	@echo "OBJS         : $(OBJS)"
	@echo "HEX_PATH     : $(TARGET)"
	@echo "SOURCE_PATH  : $(VPATH)"
	@echo "SYSTEM_NAME	: $(S_USER)"

makedir:
	@echo "******************************************"
	@echo "Creating  Directories"
	mkdir -p $(OBJDIR)
	mkdir -p $(TARGETDIR)

$(OBJDIR)/%.o : %.c
	@echo "******************************************"
	@echo "Building $@"
	$(CC) -c $(CPFLAGS) -I . $(INCDIR) $< -o $@

$(OBJDIR)/%.o : %.s
	@echo "******************************************"
	@echo "Building $@"
	$(AS) -c $(ASFLAGS) $< -o $@

%.elf: $(OBJS)
	@echo "******************************************"
	@echo "Creating $@"
	$(CC) $(OBJS) $(LDFLAGS) $(LIBDIR) $(LIBS) -o $@
	$(FILESIZE) $@

%.hex: %.elf
	@echo "******************************************"
	@echo "Creating $@"
	$(HEX) $< $@
	$(FILESIZE) $@

%.bin: %.elf
	@echo "******************************************"
	@echo "Creating $@"
	$(BIN) $< $@

clean: cleanobj cleanhex

cleanobj:
	-rm -rf $(OBJDIR)
	-rm -f  $(SRC:.c=.lst)
	-rm -f  $(ASRC:.s=.s.bak)
	-rm -f  $(ASRC:.s=.lst)
	-rm -fR $(DEP_PATH)

cleanhex:
	-rm -rf $(TARGET).map
	-rm -rf $(TARGET).elf
	-rm -rf $(TARGET).hex
	-rm -rf $(TARGETDIR)

#
# Include the dependency files, should be the last of the makefile
-include $(shell mkdir -p $(DEP_PATH) 2>/dev/null) $(wildcard $(DEP_PATH)/*)

# *** EOF ***
