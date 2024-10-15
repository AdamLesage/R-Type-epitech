##
## EPITECH PROJECT, 2024
## R-Type-epitech [WSL: Ubuntu]
## File description:
## Makefile
##

.PHONY: all clean fclean re tests_run release

# Colors
GREEN = \033[1;32m
YELLOW = \033[1;33m
RED = \033[1;31m
RESET = \033[0m

# Messages
RUNNING = [$(YELLOW)~$(RESET)]
SUCCESS = [$(GREEN)✔$(RESET)]
FAILURE = [$(RED)✘$(RESET)]

all:
	@echo "$(RUNNING) Starting project build"
	@mkdir -p build
	@cd build && cmake .. && make
	@cp build/r-type_server build/r-type_client build/r-type_asset_editor ./
	@cp build/libNetworkEngine.so build/libGameEngine.so build/libRenderingEngine.so build/libPhysicEngine.so build/libAudioEngine.so lib/
	@echo "$(SUCCESS) Project compiled successfully"

re: fclean all

release:
	@echo "$(RUNNING) Starting project build (release mode)"
	@mkdir -p release/build
	@cd release/build && cmake -DCMAKE_TOOLCHAIN_FILE=$(VCPKG_ROOT)/scripts/buildsystems/vcpkg.cmake .. && make
	@cp release/build/r-type_server release/build/r-type_client ./
	@cp release/build/libNetworkEngine.so release/build/libGameEngine.so release/build/libRenderingEngine.so release/build/libPhysicEngine.so release/build/libAudioEngine.so lib/
	@echo "$(SUCCESS) Project compiled successfully (release mode)"

clean:
	@echo "$(RUNNING) Cleaning build directory"
	@rm -rf build release/build
	@echo "$(SUCCESS) Cleaned successfully"

fclean: clean
	@echo "$(RUNNING) Removing binaries and libraries"
	@rm -f r-type_server r-type_client
	@rm -f lib/libNetworkEngine.so lib/libGameEngine.so lib/libRenderingEngine.so lib/libPhysicEngine.so lib/libAudioEngine.so
	@echo "$(SUCCESS) Binaries and libraries removed successfully"

re: fclean all

linter:
	@echo "$(RUNNING) Checking coding style"
	@find ./ -name "*.cpp" -o -name "*.hpp" | xargs clang-format --dry-run -Werror

format:
	@echo "$(RUNNING) Formatting code"
	@find ./ -name "*.cpp" -o -name "*.hpp" | xargs clang-format -i
	@echo "$(SUCCESS) Code formatted successfully"

tests_run:
	@echo "$(RUNNING) Compiling and running tests"
	@mkdir -p tests/build
	@cd tests/build && cmake .. && make
	@./tests/build/tests_client
	@echo "$(SUCCESS) Tests executed successfully"
