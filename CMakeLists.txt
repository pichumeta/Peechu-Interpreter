cmake_minimum_required(VERSION 3.27)
project(Peechu_Interpreter)

set(CMAKE_CXX_STANDARD 23)

add_executable(Peechu_Interpreter main.cpp
        src/utils/Utils.h
        src/utils/String.h
        src/Any.cpp
        src/Any.h
        src/semantics/Semantics.h
        src/semantics/Tokens.h)
