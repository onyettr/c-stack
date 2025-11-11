cmake_minimum_required(VERSION 3.28)

set(CSTACK_LIB_TARGET stack)

project(${CSTACK_LIB_TARGET}
    DESCRIPTION     "stack library"
    LANGUAGES       C ASM)

add_library(${CSTACK_LIB_TARGET} STATIC)

target_include_directories(${CSTACK_LIB_TARGET}
           PRIVATE
           ${PROJECT_SOURCE_DIR}/src
           )

target_sources(${CSTACK_LIB_TARGET}
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src/stack.c
    ${CMAKE_SOURCE_DIR}/src/trap.c
    )

#message(STATUS "CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR})
#message(STATUS "****************************************************")
message(STATUS "Library                 : " ${CSTACK_LIB_TARGET})
#message(STATUS "CMAKE_SYSTEM_PROCESSOR  : " ${CMAKE_SYSTEM_PROCESSOR})
#message(STATUS "CMAKE_SYSTEM_ARCH       : " ${CMAKE_SYSTEM_ARCH})
#message(STATUS "****************************************************")
