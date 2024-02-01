cmake_minimum_required(VERSION 3.27)
project(Peechu_Interpreter)

set(CMAKE_CXX_STANDARD 23)

add_executable(Peechu_Interpreter main.cpp
        src/utils/Utils.h
        src/utils/String.h
        src/Any.cpp
        src/Any.h
        src/semantics/Semantics.h
        src/semantics/Tokens.h
        src/interpreter/Token.h
        src/semantics/Types.h
        src/Variable.h
        src/Variable.cpp
        src/interpreter/Lexer.h
        src/interpreter/Lexer.cpp
        src/Inbuilt.h
        src/interpreter/Parser.h
        src/interpreter/Parser.cpp
        src/interpreter/Error.h
        src/interpreter/Scope.h
        src/interpreter/Scope.cpp
        src/interpreter/Function.h
        src/interpreter/Function.cpp
        src/interpreter/Loop.h
        src/interpreter/Loop.cpp
        src/semantics/ControlFlow.h
        src/interpreter/Interpreter.h
        src/utils/File.h)
