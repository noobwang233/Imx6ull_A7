#定义变量
CROSS_COMPILE ?= arm-linux-gnueabihf-

CC := $(CROSS_COMPILE)gcc
LD := $(CROSS_COMPILE)ld
OBJCOPY := $(CROSS_COMPILE)objcopy
OBJDUMP := $(CROSS_COMPILE)objdump

#存放中间文件的路径
BUILD_DIR = build
#存放源文件的文件夹
SRC_DIR = **/src
#存放头文件的文件夹
INC_DIR = **/inc

#源文件
CSRCS = $(wildcard $(SRC_DIR)/*.c) #所有的.c文件
SSRCS = $(wildcard $(SRC_DIR)/*.s) #所有的.s文件

#目标文件（*.o）
SOBJS = $(patsubst %.s, $(BUILD_DIR)/%.o, $(notdir $(SSRCS))) #获取.s文件的目标文件.o文件
COBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(notdir $(CSRCS))) #获取.c文件的目标文件.o文件
OBJS = $(COBJS) $(SOBJS) #所有的通用目标文件

#头文件
DEPS = $(wildcard $(INC_DIR)/*.h) #所有的头文件
INC_PATH = $(wildcard $(INC_DIR)) #所有的头文件目录
#指定头文件的路径
INCLUDE = $(patsubst %, -I %, $(INC_PATH))

test:
	@echo $(CSRCS)


#make xxx, xxx依赖xxx.imx
%: $(BUILD_DIR)/%.imx

#xxx.imx依赖 $(BUILD_DIR)/xxx.bin
$(BUILD_DIR)/%.imx: $(BUILD_DIR)/%.bin
#生成.imx文件
	mkimage -n ~/Linux/Tools/imximage.cfg.cfgtmp -T imximage -e 0x87800000 -d $(BUILD_DIR)/%.bin $(BUILD_DIR)/%.imx

#$(BUILD_DIR)/xxx.bin 依赖 $(BUILD_DIR)/xxx.elf
$(BUILD_DIR)/%.bin: $(OBJS) $(BUILD_DIR)/%.elf
#生成最终目标文件
	$(OBJCOPY) -O binary -S $(BUILD_DIR)/%.elf $@
#反汇编elf
	$(OBJDUMP) -D -m arm $(BUILD_DIR)/%.elf > $(BUILD_DIR)/%.dis

#$(BUILD_DIR)/xxx.elf 依赖所有的.o文件
$(BUILD_DIR)/%.elf: $(OBJS) $(BUILD_DIR)/%.o
#链接所有的目标文件
	$(LD) -Timx6ull.lds -o $(BUILD_DIR)/%.elf $^

#*.o文件的生成规则
$(BUILD_DIR)/%.o : $(SRC_DIR)/%.s
#创建一个编译目录，用于存放过程文件
#命令前带“@”,表示不在终端上输出
	@mkdir -p $(BUILD_DIR)
	bear -- $(CC) -Wall -nostdlib -c -O2 $(INCLUDE) -o $@ $<
$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c $(INC_DIR)/*.h #TODO
	@mkdir -p $(BUILD_DIR)
	bear -- $(CC) -Wall -nostdlib -c -O2 $(INCLUDE) -o $@ $<

#伪目标
.PHONY: distclean copy clean
distclean:
	rm -rf $(BUILD_DIR)
clean:
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/*.dis $(BUILD_DIR)/*.elf
copy:
	rm -rf ~/OSD_share/*.imx
	cp *.imx ~/OSD_share