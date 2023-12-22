
cmake_minimum_required(VERSION 3.15)

project(dpsys)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -fPIC -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated-declarations")

include(cmake/util.cmake)

include_directories(.)

set(LIB_SRC
        dpsys/log.cpp
        )

set(LIBS
        dpsys
        )

add_library(dpsys SHARED ${LIB_SRC})

#add_executable(test_log tests/test_log.cpp)
#add_dependencies(test_log dpsys)
#target_link_libraries(test_log dpsys)
dpsys_add_executable(test_log tests/test_log.cpp dpsys ${LIBS})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)





