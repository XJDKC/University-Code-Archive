cmake_minimum_required(VERSION 3.14)
project(PP3)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(PP3
        src/ast.cc
        src/ast.h
        src/ast_decl.cc
        src/ast_decl.h
        src/ast_expr.cc
        src/ast_expr.h
        src/ast_stmt.cc
        src/ast_stmt.h
        src/ast_type.cc
        src/ast_type.h
        src/errors.cc
        src/errors.h
        src/hashtable.cc
        src/hashtable.h
        src/list.h
        src/location.h
        src/main.cc
        src/parser.h
        src/scanner.h
        src/utility.cc
        src/utility.h)
