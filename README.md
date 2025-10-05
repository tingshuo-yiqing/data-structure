# 数据结构与算法学习项目

这是一个用C语言实现的数据结构与算法学习项目，包含了常见数据结构的实现、测试用例以及学习笔记。

## 📁 项目目录结构

```
DataStruct/
├── 📁 Chapter/                    # 学习笔记章节
│   ├── 📁 chapter1/               # 第一章
│   │   ├── 📁 code/               # 示例代码
│   │   └── 📁 note/               # 学习笔记
│   └── ...                        # 更多章节
├── 📁 include/                    # 头文件目录
│   ├── list.h                     # 链表数据结构
│   └── myfunction.h               # 通用工具函数
|   
├── 📁 src/                        # 源代码目录
│   ├── list.c                     # 链表实现
│   | main.c                     # 主程序入口
├── 📁 tests/                      # 测试文件目录
│   ├── test_list.c                # 链表测试
│   |
├── 📁 Misc/                       # 杂项学习资料
│   ├── 📁 C_learn/                # C语言学习
│   ├── 📁 git_learn/              # Git学习
│   └── 📁 json_learn/             # JSON学习
├── 📁 build/                      # 构建输出目录
├── makefile                       # 构建配置文件
├── .gitignore                     # Git忽略文件
└── README.md                      # 项目说明文档
```

### 构建命令
```bash
# 构建所有目标（默认）
make

# 构建调试版本
make debug

# 构建发布版本
make release

# 运行主程序
make run

# 构建所有程序和测试
make all 

# 运行所有测试
make test

# 清理构建文件
make clean

# 显示帮助信息
make help
```

### 快速开始
1. 克隆项目到本地
2. 使用 `make` 命令构建项目
3. 使用 `make test` 运行测试验证功能
4. 查看 `Chapter/` 目录中的学习笔记

