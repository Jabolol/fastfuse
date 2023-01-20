##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## This is just a Makefile
##

NAME = main
TEST_BINARY = unit_tests
LIB_NAME = libmy.a
DEV_NAME = dev
ANTMAN_NAME = antman
ANTMAN_DIR = antman
GIANTMAN_NAME = giantman
GIANTMAN_DIR = giantman
CC = gcc
FLAGS = -c
DEV_FLAGS = -o $(DEV_NAME) -g -Wall -Wextra
SOURCE_DIR = sources
LIB_DIR = lib
TEST_FLAGS = --coverage -lcriterion
TEST_FILE = test.c
TEST_DIR = tests
GCOVR_PATH = /usr/local/bin/gcovr
DOCKER_PATH = /usr/local/bin/docker
MV_PATH = /bin/mv
MKDIR_PATH = /bin/mkdir
DIST_DIR = dist

NORMAL = \033[0m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m

SHARED_DIR = shared
LIB_FILES =	${SHARED_DIR}/${LIB_DIR}/*.c

SOURCE_FILES = ${SOURCE_DIR}/*.c

TEST_FILES = ${SOURCE_DIR}/*.c

# credit: https://github.com/mooreryan/valgrind_docker
THIS_DIR = $(dir $(realpath $(firstword $(MAKEFILE_LIST))))

all:
	@ printf '${PURPLE}Executing ${GREEN}all${PURPLE} rule.${NORMAL}\n'
	@ make $(LIB_NAME)
	@ make $(DEV_NAME)

$(LIB_NAME):
	@ printf '${PURPLE}Building ${GREEN}${LIB_NAME}${PURPLE}...${NORMAL}\n'
	@ $(CC) -c ${LIB_FILES}
	@ $(AR) rc $(LIB_NAME) *.o
	@ $(MV_PATH) ${LIB_NAME} ${SHARED_DIR}
	@ $(MAKE) clean

$(DEV_NAME):
	@ $(MKDIR_PATH) -p ${DIST_DIR}
	@ printf '${PURPLE}Executing ${GREEN}${DEV_NAME}${PURPLE} rule.${NORMAL}\n'
	@ $(MAKE) -C ${ANTMAN_DIR} all
	@ $(MAKE) -C ${GIANTMAN_DIR} all

clean:
	@ printf '${PURPLE}Executing ${GREEN}clean${PURPLE} rule.${NORMAL}\n'
	@ printf '${YELLOW}Removing object files...${NORMAL}\n'
	$(RM) *.o

fclean:
	@ printf '${PURPLE}Executing ${GREEN}fclean${PURPLE} rule.${NORMAL}\n'
	@ printf '${YELLOW}Removing ${ANTMAN_NAME} binary...${NORMAL}\n'
	$(RM) ${DIST_DIR}/${ANTMAN_NAME}
	@ $(MAKE) -C ${ANTMAN_DIR} fclean
	@ printf '${YELLOW}Removing ${GIANTMAN_NAME} binary...${NORMAL}\n'
	$(RM) ${DIST_DIR}/${GIANTMAN_NAME}
	@ $(MAKE) -C ${GIANTMAN_DIR} fclean
	@ printf '${YELLOW}Removing ${LIB_NAME} library...${NORMAL}\n'
	@ $(RM) ${DIST_DIR}/${LIB_NAME}

re:
	@ printf '${PURPLE}Executing ${GREEN}re${PURPLE} rule.${NORMAL}\n'
	$(MAKE) fclean
	$(MAKE) all

# credit: https://github.com/mooreryan/valgrind_docker
docker:
	@ printf '${BLUE}Compiling source files, target debug...${NORMAL}\n'
	@ $(DOCKER_PATH) run --rm --workdir $(HOME) --entrypoint $(CC) -v \
	$(THIS_DIR):$(HOME) mooreryan/valgrind ${DEV_FLAGS} \
	${SOURCE_FILES}

valgrind:
	@ printf '${PURPLE}Executing ${GREEN}docker${PURPLE} rule.${NORMAL}\n'
	@ $(MAKE) docker
	@ printf '${BLUE}Executing valgrind${NORMAL}\n'
	@ $(DOCKER_PATH) run --rm --workdir $(HOME) -v $(THIS_DIR):$(HOME) \
	mooreryan/valgrind --leak-check=full --show-leak-kinds=all \
	--track-origins=yes ./$(DEV_NAME) $(BSQ_ARGS)

dev_clean:
	@ ${MAKE} fclean
	@ printf '${YELLOW}Removing test binary...${NORMAL}\n'
	$(RM) ${TEST_BINARY}
	@ printf '${YELLOW}Removing test files...${NORMAL}\n'
	$(RM) *.gc*

unit_tests:
	$(MAKE) fclean
	$(MAKE) $(LIB_NAME)
	@ printf '${BLUE}Compiling test binary...${NORMAL}\n'
	$(CC) -o $(TEST_BINARY) ${TEST_FILES} ${LIB_NAME} \
	$(TEST_DIR)/$(TEST_FILE) $(TEST_FLAGS)

tests_run:
	@ printf '${PURPLE}Executing ${GREEN}tests_run${PURPLE} rule.${NORMAL}\n'
	@ $(MAKE) unit_tests
	@ printf '${BLUE}Executing test report...${NORMAL}\n'
	./$(TEST_BINARY) 1 3 2 -1
	$(GCOVR_PATH) --exclude $(TEST_DIR)
	$(MAKE) fclean

pre_commit:
	@ rg "FIXME" .
