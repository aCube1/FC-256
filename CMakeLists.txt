cmake_minimum_required(VERSION 3.21)
project(fc256 C)

include(cmake/base.cmake)
include(cmake/warnings.cmake)
include(cmake/debug.cmake)

add_executable(${PROJECT_NAME})

target_compile_features(
	${PROJECT_NAME}
	PRIVATE
		c_std_17
)

target_sources(
	${PROJECT_NAME}
	PRIVATE
		src/log/log.c
		src/cpu.c
		src/main.c
		src/opcode.c
		src/operand.c
)

target_precompile_headers(
	${PROJECT_NAME}
	PRIVATE
		include/log/log.h
		include/types.h
)

target_include_directories(
	${PROJECT_NAME}
	PRIVATE
		${PROJECT_SOURCE_DIR}/include
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set_debug_options(${PROJECT_NAME})
else()
	target_compile_options(${PROJECT_NAME} PRIVATE -g0 -O3)
endif()

set_default_warnings(${PROJECT_NAME})
