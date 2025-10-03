# 编译器设置
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -std=c99
DEBUG_CFLAGS = -g -DDEBUG
RELEASE_CFLAGS = -O2

# 目录设置
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
BUILD_OBJ_DIR = $(BUILD_DIR)/obj
BUILD_BIN_DIR = $(BUILD_DIR)/bin
TEST_DIR = tests

# 自动收集源文件（排除main.c）
SRC_FILES = $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c))
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_OBJ_DIR)/%.o,$(SRC_FILES))

# 自动收集测试文件
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
TEST_BINS = $(patsubst $(TEST_DIR)/%.c,$(BUILD_BIN_DIR)/test_%,$(TEST_SRCS))

# 主程序目标
MAIN_TARGET = $(BUILD_BIN_DIR)/main
MAIN_OBJ = $(BUILD_OBJ_DIR)/main.o

# 默认目标
all: $(MAIN_TARGET) $(TEST_BINS)

# 调试版本
debug: CFLAGS += $(DEBUG_CFLAGS)
debug: all

# 发布版本
release: CFLAGS += $(RELEASE_CFLAGS)
release: all

# 创建构建目录
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_OBJ_DIR): $(BUILD_DIR)
	@mkdir -p $(BUILD_OBJ_DIR)

$(BUILD_BIN_DIR): $(BUILD_DIR)
	@mkdir -p $(BUILD_BIN_DIR)

# 主程序构建规则
$(MAIN_TARGET): $(MAIN_OBJ) $(OBJ_FILES) | $(BUILD_BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# 主程序目标文件
$(MAIN_OBJ): $(SRC_DIR)/main.c | $(BUILD_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# 测试程序通用构建规则
$(BUILD_BIN_DIR)/test_%: $(TEST_DIR)/%.c $(OBJ_FILES) | $(BUILD_BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# 目标文件构建规则
$(BUILD_OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# 运行主程序
run: $(MAIN_TARGET)
	./$(MAIN_TARGET)

# 运行所有测试
test: $(TEST_BINS)
	@for test in $(TEST_BINS); do \
		echo "Running $$test..."; \
		./$$test; \
	done

# 清理构建文件
clean:
	rm -rf $(BUILD_DIR)/*

# 彻底清理（包括备份文件等）
distclean: clean
	rm -f *~ $(SRC_DIR)/*~ $(INCLUDE_DIR)/*~ $(TEST_DIR)/*~

# 安装（如果需要）
install: all
	@echo "安装功能待实现"

# 显示帮助信息
help:
	@echo "可用目标:"
	@echo "  all        - 构建主程序和所有测试（默认）"
	@echo "  debug      - 构建调试版本"
	@echo "  release    - 构建发布版本"
	@echo "  run        - 运行主程序"
	@echo "  test       - 运行所有测试"
	@echo "  clean      - 清理构建文件"
	@echo "  distclean  - 彻底清理"
	@echo "  install    - 安装程序"
	@echo "  help       - 显示此帮助信息"

# 伪目标声明
.PHONY: all debug release run test clean distclean install help
