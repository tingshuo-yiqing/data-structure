# ===============================
# 编译器设置
# ===============================
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -std=c99
DEBUG_CFLAGS = -g -DDEBUG
RELEASE_CFLAGS = -O2

# ===============================
# 目录结构
# ===============================
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
BUILD_OBJ_DIR = $(BUILD_DIR)/obj
BUILD_BIN_DIR = $(BUILD_DIR)/bin
TEST_DIR = tests

# ===============================
# 文件自动收集
# ===============================
SRC_FILES = $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c))
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_OBJ_DIR)/%.o,$(SRC_FILES))

# memmgr 作为公共模块，所有使用内存分配的目标都需要链接
MEMMGR_OBJ = $(BUILD_OBJ_DIR)/memmgr.o

TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
TEST_BINS = $(patsubst $(TEST_DIR)/%.c,$(BUILD_BIN_DIR)/test_%,$(TEST_SRCS))

MAIN_TARGET = $(BUILD_BIN_DIR)/main
MAIN_OBJ = $(BUILD_OBJ_DIR)/main.o

# ===============================
# 默认目标
# ===============================
all: $(MAIN_TARGET) $(TEST_BINS)

debug: CFLAGS += $(DEBUG_CFLAGS)
debug: all

release: CFLAGS += $(RELEASE_CFLAGS)
release: all

# ===============================
# 目录创建
# ===============================
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_OBJ_DIR): $(BUILD_DIR)
	@mkdir -p $(BUILD_OBJ_DIR)

$(BUILD_BIN_DIR): $(BUILD_DIR)
	@mkdir -p $(BUILD_BIN_DIR)

# ===============================
# 主程序编译
# ===============================
$(MAIN_TARGET): $(MAIN_OBJ) $(OBJ_FILES) | $(BUILD_BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(MAIN_OBJ): $(SRC_DIR)/main.c | $(BUILD_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ===============================
# 测试规则（通用）
# ===============================
$(BUILD_BIN_DIR)/test_%: $(TEST_DIR)/%.c $(OBJ_FILES) | $(BUILD_BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# ===============================
# 分模块测试目标（仅编译相关模块）
# ===============================
test_stack: $(BUILD_BIN_DIR)/test_stack
$(BUILD_BIN_DIR)/test_stack: $(TEST_DIR)/test_stack.c $(BUILD_OBJ_DIR)/stack.o | $(BUILD_BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

test_queue: $(BUILD_BIN_DIR)/test_queue
$(BUILD_BIN_DIR)/test_queue: $(TEST_DIR)/test_queue.c $(BUILD_OBJ_DIR)/queue.o | $(BUILD_BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

test_tree: $(BUILD_BIN_DIR)/test_tree
$(BUILD_BIN_DIR)/test_tree: $(TEST_DIR)/test_tree.c $(BUILD_OBJ_DIR)/tree.o $(BUILD_OBJ_DIR)/queue.o $(BUILD_OBJ_DIR)/memmgr.o | $(BUILD_BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^


# ===============================
# 通用对象文件规则
# ===============================
$(BUILD_OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ===============================
# ▶运行命令
# ===============================
run: $(MAIN_TARGET)
	./$(MAIN_TARGET)

test: $(TEST_BINS)
	@for test in $(TEST_BINS); do \
		echo "Running $$test..."; \
		./$$test; \
	done

# ===============================
# 清理命令
# ===============================
clean:
	rm -rf $(BUILD_DIR)/*

distclean: clean
	rm -f *~ $(SRC_DIR)/*~ $(INCLUDE_DIR)/*~ $(TEST_DIR)/*~

# ===============================
# 安装（占位）
# ===============================
install: all
	@echo "安装功能待实现"

# ===============================
# ℹ帮助信息
# ===============================
help:
	@echo "可用目标:"
	@echo "  all           - 构建主程序和所有测试（默认）"
	@echo "  debug         - 构建调试版本"
	@echo "  release       - 构建发布版本"
	@echo "  run           - 运行主程序"
	@echo "  test          - 运行所有测试"
	@echo "  test_stack    - 仅测试栈模块"
	@echo "  test_queue    - 仅测试队列模块"
	@echo "  test_tree     - 仅测试二叉树模块"
	@echo "  clean         - 清理构建文件"
	@echo "  distclean     - 彻底清理"
	@echo "  install       - 安装程序"
	@echo "  help          - 显示此帮助信息"

.PHONY: all debug release run test clean distclean install help \
        test_stack test_queue test_tree test_memmgr
