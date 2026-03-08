# Hydrogen Makefile
# 通过 CMake 编译项目的前端包装器

# ========== 配置 ==========
BUILD_DIR = build
CMAKE_FLAGS = -DCMAKE_BUILD_TYPE=Release
CMAKE_BUILD_FLAGS = -j$(shell nproc)
PROJECT_ROOT = $(shell pwd)

# ========== 默认目标 ==========
.PHONY: all
all: setup
	@echo "🔨 Building project..."
	@cmake --build $(BUILD_DIR) -- $(CMAKE_BUILD_FLAGS)
	@echo "✓ Build complete"
	@echo ""
	@echo "Build outputs:"
	@ls -lh $(BUILD_DIR)/bin/ 2>/dev/null || echo "  (bin directory not found)"

# ========== 初始化构建目录 ==========
.PHONY: setup
setup:
	@if [ ! -d "$(BUILD_DIR)" ]; then \
		echo "📁 Creating build directory..."; \
		cmake -S $(PROJECT_ROOT) -B $(BUILD_DIR) $(CMAKE_FLAGS); \
		echo "✓ CMake configuration complete"; \
	else \
		echo "✓ Build directory exists"; \
	fi

# ========== Debug 构建 ==========
.PHONY: debug
debug:
	@echo "🐛 Configuring Debug build..."
	@cmake -S $(PROJECT_ROOT) -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Debug
	@echo "🔨 Building Debug..."
	@cmake --build $(BUILD_DIR) -- $(CMAKE_BUILD_FLAGS)
	@echo "✓ Debug build complete"

# ========== Release 构建 ==========
.PHONY: release
release:
	@echo "🚀 Configuring Release build..."
	@cmake -S $(PROJECT_ROOT) -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Release
	@echo "🔨 Building Release..."
	@cmake --build $(BUILD_DIR) -- $(CMAKE_BUILD_FLAGS)
	@echo "✓ Release build complete"

# ========== 清理 ==========
.PHONY: clean
clean:
	@echo "🗑️  Cleaning build artifacts..."
	@rm -rf $(BUILD_DIR)
	@rm -rf bin obj
	@echo "✓ Clean complete"

# ========== 完全重新构建 ==========
.PHONY: rebuild
rebuild: clean all

# ========== 运行测试 ==========
.PHONY: test
test: setup
	@echo "🧪 Running tests..."
	@cd $(BUILD_DIR) && ctest --output-on-failure
	@echo "✓ Tests complete"

# ========== 详细输出 ==========
.PHONY: verbose
verbose: setup
	@echo "🔨 Building with verbose output..."
	@cmake --build $(BUILD_DIR) --verbose $(CMAKE_BUILD_FLAGS)

# ========== 安装 ==========
.PHONY: install
install: all
	@echo "📦 Installing..."
	@cd $(BUILD_DIR) && sudo cmake --install .
	@echo "✓ Installation complete"

# ========== 运行 hdg_clt ==========
.PHONY: run
run: all
	@echo "▶️  Running hdg_clt..."
	@$(BUILD_DIR)/bin/hdg_clt

# ========== 格式化代码 ==========
.PHONY: format
format:
	@echo "🎨 Formatting code..."
	@find hydrogen clt shell -type f \( -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \) -exec clang-format -i {} \; 2>/dev/null || echo "  (clang-format not available)"
	@echo "✓ Format complete"

# ========== 静态分析 ==========
.PHONY: analyze
analyze: setup
	@echo "🔍 Running static analysis..."
	@cd $(BUILD_DIR) && cppcheck --enable=all --suppress=missingIncludeSystem ../hydrogen ../clt ../shell 2>/dev/null || echo "  (cppcheck not available)"
	@echo "✓ Analysis complete"

# ========== 内存检查 ==========
.PHONY: memcheck
memcheck: all
	@echo "🧠 Running memory check..."
	@cd $(BUILD_DIR) && valgrind --leak-check=full --show-leak-kinds=all ./bin/hdg_clt 2>/dev/null || echo "  (valgrind not available)"
	@echo "✓ Memory check complete"

# ========== 查看依赖 ==========
.PHONY: depends
depends: setup
	@echo "📊 Showing dependency graph..."
	@cd $(BUILD_DIR) && cmake --graphviz=deps.dot .. && dot -Tpng deps.dot -o deps.png 2>/dev/null || echo "  (graphviz not available)"
	@echo "✓ Dependencies graph generated"

# ========== CMake UI ==========
.PHONY: ui
ui: setup
	@echo "🖥️  Launching CMake GUI..."
	@cd $(BUILD_DIR) && ccmake .. 2>/dev/null || cmake-gui .. 2>/dev/null || echo "  (CMake GUI not available)"

# ========== 帮助信息 ==========
.PHONY: help
help:
	@echo "Hydrogen Makefile - CMake 前端包装器"
	@echo ""
	@echo "用法: make [目标]"
	@echo ""
	@echo "📦 构建目标:"
	@echo "  make (或 make all)  - 配置并编译项目（Release 模式）"
	@echo "  make debug          - 编译 Debug 版本"
	@echo "  make release        - 编译 Release 版本"
	@echo "  make rebuild        - 清理并重新编译"
	@echo "  make clean          - 清理编译产物"
	@echo ""
	@echo "🧪 测试与运行:"
	@echo "  make test           - 运行测试"
	@echo "  make run            - 运行 hdg_clt"
	@echo ""
	@echo "🔧 工具:"
	@echo "  make verbose        - 详细输出编译"
	@echo "  make install        - 安装到系统（需要 sudo）"
	@echo "  make format         - 格式化代码"
	@echo "  make analyze        - 静态代码分析"
	@echo "  make memcheck       - 内存泄漏检查"
	@echo "  make depends        - 生成依赖图"
	@echo "  make ui             - 启动 CMake GUI"
	@echo ""
	@echo "📋 信息:"
	@echo "  make help           - 显示此帮助信息"
	@echo ""
	@echo "环境变量:"
	@echo "  BUILD_DIR=$(BUILD_DIR)"
	@echo "  CMAKE_FLAGS=$(CMAKE_FLAGS)"
