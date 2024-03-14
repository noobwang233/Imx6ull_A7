#定义变量
TARGET = main
CROSS_COMPILE ?= arm-none-linux-gnueabihf-
#CROSS_COMPILE ?= arm-linux-gnueabihf

#CC := $(CROSS_COMPILE)gcc
CC := $(CROSS_COMPILE)gcc -fgnu89-inline
LD := $(CROSS_COMPILE)ld
OBJCOPY := $(CROSS_COMPILE)objcopy
OBJDUMP := $(CROSS_COMPILE)objdump

#LIBPATH := -lgcc -L /home/wta3wx/Linux/Tools/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/lib/gcc/arm-linux-gnueabihf/4.9.4
LIBPATH := -lgcc -L /usr/local/arm/gcc-arm-9.2-2019.12-x86_64-arm-none-linux-gnueabihf/lib/gcc/arm-none-linux-gnueabihf/9.2.1/

#存放中间文件的路径
BUILD_DIR = build

#存放stdio文件的文件夹
STD_DIR = stdio

STD_CSRCS = $(wildcard $(STD_DIR)/lib/*.c)
STD_SSRCS = $(wildcard $(STD_DIR)/lib/*.S)
STD_COBJS = $(patsubst %.c, $(STD_DIR)/%.o, $(notdir $(STD_CSRCS))) #获取.c文件的目标文件.o文件
STD_SOBJS = $(patsubst %.S, $(STD_DIR)/%.o, $(notdir $(STD_SSRCS))) #获取.S文件的目标文件.o文件
STD_OBJS = $(STD_COBJS) $(STD_SOBJS)
STD_INC = stdio/include

#存放BSP文件的文件夹
BSP_DIR = bsp
BSP_TARGET = clk\
			delay\
			epittimer\
			gpio\
			int\
			key\
			keyfilter\
			led\
			beep\
			uart\
			lcd\
#源文件
BSP_SRCS = $(foreach bsps, $(BSP_TARGET), $(wildcard $(BSP_DIR)/$(bsps)/*.c)) 
BSP_OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(notdir $(BSP_SRCS))) #获取.c文件的目标文件.o文件


#存放启动文件的文件夹
IMX6_DIR = imx6ull
IMX6_TARGET = start
#源文件
IMX6_SRCS = $(foreach imx6, $(IMX6_TARGET), $(IMX6_DIR)/$(imx6).s)
IMX6_OBJS = $(patsubst %.s, $(BUILD_DIR)/%.o, $(notdir $(IMX6_SRCS))) #获取.s文件的目标文件.o文件

PROG_DIR = prog

#所有头文件
INCS = $(shell find -name *.h) 	 #所有的头文件
INC_PATH =$(sort $(dir $(INCS))) #所有的头文件目录
INC_PATH += $(STD_INC)
#指定头文件的路径
INCLUDE = $(patsubst %, -I %, $(INC_PATH))

OBJS = $(IMX6_OBJS) $(BSP_OBJS) $(STD_OBJS)

#make xxx, xxx依赖xxx.imx
$(TARGET): $(BUILD_DIR)/$(TARGET).imx

#xxx.imx依赖 $(BUILD_DIR)/xxx.bin
$(BUILD_DIR)/$(TARGET).imx: $(BUILD_DIR)/$(TARGET).bin
#生成.imx文件
	mkimage -n imximage.cfg.cfgtmp -T imximage -e 0x87800000 -d $(BUILD_DIR)/$(TARGET).bin $(BUILD_DIR)/$(TARGET).imx

#$(BUILD_DIR)/xxx.bin 依赖 $(BUILD_DIR)/xxx.elf
$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
#生成最终目标文件
	$(OBJCOPY) -O binary -S $(BUILD_DIR)/$(TARGET).elf $@
#反汇编elf
	$(OBJDUMP) -D -m arm $(BUILD_DIR)/$(TARGET).elf > $(BUILD_DIR)/$(TARGET).dis

#$(BUILD_DIR)/xxx.elf 依赖所有的.o文件
$(BUILD_DIR)/$(TARGET).elf: $(OBJS) $(BUILD_DIR)/$(TARGET).o
#链接所有的目标文件
	$(LD) -Timx6ull.lds -o $(BUILD_DIR)/$(TARGET).elf $^ $(LIBPATH)

#*.o文件的生成规则
$(BUILD_DIR)/%.o: $(IMX6_DIR)/%.s  $(INCS)
	@mkdir -p $(BUILD_DIR)
	$(CC) -Wall -nostdlib -fno-builtin -c -O2 $(INCLUDE) -o $@ $<

$(BUILD_DIR)/%.o: $(BSP_DIR)/**/%.c  $(INCS)
	@mkdir -p $(BUILD_DIR)
	$(CC) -Wall -nostdlib -fno-builtin -c -O2 $(INCLUDE) -o $@ $<

$(BUILD_DIR)/$(TARGET).o: $(PROG_DIR)/$(TARGET).c $(INCS)
	@mkdir -p $(BUILD_DIR)
	$(CC) -Wall -nostdlib -fno-builtin -c -O2 $(INCLUDE) -o $@ $<

#库文件的生成规则
$(STD_DIR)/%.o: $(STD_DIR)/lib/%.c $(STD_INC)/*.h
	$(CC) -Wall -Wa,-mimplicit-it=thumb -nostdlib -fno-builtin -c -O2 $(INCLUDE) -o $@ $<
$(STD_DIR)/%.o: $(STD_DIR)/lib/%.S $(STD_INC)/*.h
	$(CC) -Wall -Wa,-mimplicit-it=thumb -nostdlib -fno-builtin -c -O2 $(INCLUDE) -o $@ $<

#伪目标
.PHONY: distclean copy clean
distclean:
	rm -rf $(BUILD_DIR) $(STD_DIR)/*.o
clean:
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/*.dis $(BUILD_DIR)/*.elf $(STD_DIR)/*.o
copy:
	rm -rf ~/OSD_share/*.imx
	cp $(BUILD_DIR)/*.imx ~/OSD_share