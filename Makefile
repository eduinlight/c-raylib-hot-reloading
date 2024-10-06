SHELL=/bin/bash

PROJECT_NAME=acm
OUTPUT=./out
DEBUG_OUTPUT=${OUTPUT}/debug
RELEASE_OUTPUT=${OUTPUT}/release
DCMAKE_USER_MAKE_RULES_OVERRIDE=./ClangOverrides.txt

build: clang
	@cd ${DEBUG_OUTPUT} && make

configure: clang clean cmake-configure-debug

run:
	@${DEBUG_OUTPUT}/${PROJECT_NAME}

run-release:
	@${RELEASE_OUTPUT}

clean:
	@rm -rf ${OUTPUT}

release: clang clean cmake-configure-release build

# utils
clang:
	@export CC=/usr/bin/clang
	@export CXX=/usr/bin/clang++

cmake-configure-release:
	@PROJECT_NAME=${PROJECT_NAME} \
	cmake \
		-D_CMAKE_TOOLCHAIN_PREFIX=llvm- \
		-DCMAKE_BUILD_TYPE=Release \
		-DCMAKE_USER_MAKE_RULES_OVERRIDE=${DCMAKE_USER_MAKE_RULES_OVERRIDE} \
		-S . \
		-B ${RELEASE_OUTPUT}

cmake-configure-debug:
	@PROJECT_NAME=${PROJECT_NAME} \
	cmake \
		-D_CMAKE_TOOLCHAIN_PREFIX=llvm- \
		-DCMAKE_BUILD_TYPE=Debug \
		-DCMAKE_USER_MAKE_RULES_OVERRIDE=${DCMAKE_USER_MAKE_RULES_OVERRIDE} \
		-S . \
		-B ${DEBUG_OUTPUT}
