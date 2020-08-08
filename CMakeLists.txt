cmake_minimum_required(VERSION 3.10)

PROJECT(JILInterpreter)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_EXTENSIONS OFF)

SET(UTILS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Utils)
SET(MEAT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Meat)
SET(POTATOES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Potatoes)
SET(FILE_IO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/FileReading)

SET(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Interpreter.cpp
    
    ${UTILS_DIR}/Utils.cpp
    
    ${MEAT_DIR}/Meat.cpp
    ${MEAT_DIR}/Lexy.cpp
    
    ${POTATOES_DIR}/Potatoes.cpp
    ${POTATOES_DIR}/Tokenizer.cpp

    ${FILE_IO_DIR}/JeffFile.cpp
    )

SET(HEADERS    
    ${UTILS_DIR}/Utils.h
    ${UTILS_DIR}/CommonIncludes.h
    ${UTILS_DIR}/DataTypes.h
    ${UTILS_DIR}/Defines.h

    ${MEAT_DIR}/Meat.h
    ${MEAT_DIR}/Lexy.h 
    
    ${POTATOES_DIR}/Potatoes.h 
    ${POTATOES_DIR}/Tokenizer.h 

    ${FILE_IO_DIR}/JeffFile.h 
    )

ADD_EXECUTABLE(JILInterpreter ${SOURCES} ${HEADERS})