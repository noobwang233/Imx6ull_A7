#定义变量
TARGET = main
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
CSRCS = $(wildcard $(SRC_DIR)/*.c)
SSRCS = $(wildcard $(SRC_DIR)/*.s)
#目标文件（*.o）
SOBJS = $(patsubst %.s, $(BUILD_DIR)/%.o, $(notdir $(SSRCS)))
COBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(notdir $(CSRCS)))
OBJS = $(COBJS) $(SOBJS)
#头文件
DEPS = $(wildcard $(INC_DIR)/*.h)

#指定头文件的路径
INCLUDE = $(patsubst %, -I %, $(INC_DIR))
# $(BUILD_DIR)/$(TARGET).bin:
# 	@echo $(SOBJS) $(BUILD_DIR)/%.o $(SRC_DIR)/%.s
#目标文件
$(BUILD_DIR)/$(TARGET).bin: $(OBJS)
	$(LD) -Timx6ull.lds -o $(BUILD_DIR)/$(TARGET).elf $^
	$(OBJCOPY) -O binary -S $(BUILD_DIR)/$(TARGET).elf $@
	$(OBJDUMP) -D -m arm $(BUILD_DIR)/$(TARGET).elf > $(BUILD_DIR)/$(TARGET).dis
	mkimx $(BUILD_DIR)/$(TARGET).bin

#*.o文件的生成规则
$(BUILD_DIR)/%.o : $(SRC_DIR)/%.s
#创建一个编译目录，用于存放过程文件
#命令前带“@”,表示不在终端上输出
	@mkdir -p $(BUILD_DIR)
	bear -- $(CC) -Wall -nostdlib -c -O2 $(INCLUDE) -o $@ $<
$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	bear -- $(CC) -Wall -nostdlib -c -O2 $(INCLUDE) -o $@ $<

#伪目标
.PHONY: clean copy
clean:
	rm -rf $(TARGET).elf $(TARGET).dis $(TARGET).bin $(COBJS) $(SOBJS)
copy:
	cp $(BUILD_DIR)/%.imx ~/Linux/OSD_share