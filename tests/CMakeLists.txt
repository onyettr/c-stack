cmake_minimum_required(VERSION 3.28)

set(CSTACK_TEST_LIB_TARGET test)

project(${CSTACK_TEST_LIB_TARGET}
    DESCRIPTION     "test library"
    LANGUAGES       C ASM)

add_library(${CSTACK_TEST_LIB_TARGET} STATIC)

target_include_directories(${CSTACK_TEST_LIB_TARGET}
           PRIVATE
           ${PROJECT_SOURCE_DIR}/tests
           )

target_sources(${CSTACK_TEST_LIB_TARGET}
    PRIVATE
    ${CMAKE_SOURCE_DIR}/tests/test_empty.c
    ${CMAKE_SOURCE_DIR}/tests/test_push.c
    ${CMAKE_SOURCE_DIR}/tests/test_size.c
    ${CMAKE_SOURCE_DIR}/tests/test_pop.c
    ${CMAKE_SOURCE_DIR}/tests/test_top.c
    ${CMAKE_SOURCE_DIR}/tests/test_swap.c
#    ${CMAKE_SOURCE_DIR}/test/test01.c
    )

#message(STATUS "CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR})
#message(STATUS "****************************************************")
message(STATUS "Library                 : " ${CSTACK_LIB_TARGET})
#message(STATUS "CMAKE_SYSTEM_PROCESSOR  : " ${CMAKE_SYSTEM_PROCESSOR})
#message(STATUS "CMAKE_SYSTEM_ARCH       : " ${CMAKE_SYSTEM_ARCH})
#message(STATUS "****************************************************")
