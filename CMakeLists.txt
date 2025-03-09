cmake_minimum_required(VERSION 3.15)

project(
	ccope
	VERSION 1.0
	DESCRIPTION "c generator"
	LANGUAGES C
	)
# generate compile_compands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(srcfiles main.c lexer.c hashmap.c tokens.c log_impl.c stringstruct.c external/sds.c)

add_executable(ccope ${srcfiles})

target_include_directories(ccope PRIVATE string/ external/)
target_compile_options(ccope PRIVATE -Wall -g)
