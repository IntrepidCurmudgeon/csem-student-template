cmake_minimum_required(VERSION 3.15)
project(csem C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-g -O0 -DDEBUG -Wpointer-to-int-cast")
add_definitions(-DLEFTTORIGHT)
add_definitions(-DSPARC)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(BISON_EXECUTABLE /usr/local/opt/bison/bin/bison)
endif()

find_package(BISON)
BISON_TARGET(MyParser cgram.y ${CMAKE_BINARY_DIR}/cgram.tab.c
        DEFINES_FILE ${CMAKE_BINARY_DIR}/cgram.tab.h)

set (PROJECT_NAME_SOURCES
        ${PROJECT_NAME_SOURCES}
        ${CMAKE_BINARY_DIR}/cgram.tab.c
        semdum.c
        sym.c
        scan.c
        semutil.c
        )

set (PROJECT_NAME_HEADERS
        ${PROJECT_NAME_HEADERS}
        cc.h
        scan.h
        sem.h
        semutil.h
        sym.h
        ${CMAKE_BINARY_DIR}/cgram.tab.h
        )

include_directories(${CMAKE_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR})
add_executable(csem ${PROJECT_NAME_SOURCES} ${PROJECT_NAME_HEADERS}
        ${BISON_MyParser_OUTPUTS})

#set(BISON_LIBRARIES /usr/local/opt/bison/lib/liby.a)
target_link_libraries(csem ${BISON_LIBRARIES})
