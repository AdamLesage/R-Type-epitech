##
## EPITECH PROJECT, 2024
## R-Type-epitech [WSL: Ubuntu]
## File description:
## Makefile
##

.PHONY: all clean fclean re tests_run

# Colors
GREEN = \033[1;32m
YELLOW = \033[1;33m
RED = \033[1;31m
RESET = \033[0m

# Messages
RUNNING = [$(YELLOW)~$(RESET)]
SUCCESS = [$(GREEN)✔$(RESET)]
FAILURE = [$(RED)✘$(RESET)]

# Targets
all:
	@echo "$(RUNNING) Starting project build"
	@mkdir -p build
	@cd build && cmake .. && make
	@cp build/r-type_server build/r-type_client .
	@cp build/libNetworkEngine.so build/libGameEngine.so build/libRenderingEngine.so build/libPhysicEngine.so build/libAudioEngine.so lib/
	@echo "$(SUCCESS) Project compiled successfully"

rebuild: fclean all

clean:
	@echo "$(RUNNING) Cleaning build directory"
	@rm -rf build
	@echo "$(SUCCESS) Cleaned successfully"

fclean: clean
	@echo "$(RUNNING) Removing binaries and libraries"
	@rm -f r-type_server r-type_client
	@rm -f lib/libNetworkEngine.so lib/libGameEngine.so lib/libRenderingEngine.so lib/libPhysicEngine.so lib/libAudioEngine.so
	@echo "$(SUCCESS) Binaries and libraries removed successfully"

re: fclean all

tests_run:
	@echo "$(RUNNING) Compiling and running tests"
	@mkdir -p tests/build
	@cd tests/build && cmake .. && make
	@./tests/build/tests_client
	@echo "$(SUCCESS) Tests executed successfully"
