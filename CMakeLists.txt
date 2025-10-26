#*******************************************************************************
# File name        : CMakeLists.txt
# File description : C Stack implementation
# Author           : ronyett
#*******************************************************************************

cmake_minimum_required(VERSION 3.10)
project(Stack C)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Build options
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic")
set(CMAKE_C_FLAGS_DEBUG "-g")

# Optional profiling and coverage flags
option(ENABLE_COVERAGE "Enable code coverage" OFF)
option(ENABLE_PROFILING "Enable profiling" OFF)

if(ENABLE_COVERAGE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

if(ENABLE_PROFILING)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pg")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
endif()

# Optional debug trace and exception handling
option(DEBUG_TRACE "Enable deep trace per function" OFF)
option(USE_EXCEPTION "Use real exceptions with try in test harness" OFF)

if(DEBUG_TRACE)
    add_definitions(-DDEBUG_TRACE)
endif()

if(USE_EXCEPTION)
    add_definitions(-DEXCEPTION)
endif()

# Create output directory for objects (handled automatically by CMake)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#*******************************************************************************
# Library: libstack.a
# Built from trap handling and the stack implementation
#*******************************************************************************

add_library(stack STATIC
    stack.c
    trap.c
)

#*******************************************************************************
# Executable: stack.exe
# Main test executable
#*******************************************************************************

add_executable(stack_exe
    main.c
    test_empty.c
    test_push.c
    test_size.c
    test_swap.c
    test_pop.c
    test_top.c
)

target_link_libraries(stack_exe stack)
set_target_properties(stack_exe PROPERTIES OUTPUT_NAME "stack.exe")

#*******************************************************************************
# Unity test harness
#*******************************************************************************

option(BUILD_UNITY_TESTS "Build Unity test harness" ON)

if(BUILD_UNITY_TESTS)
    add_executable(unitytest
        unity/unity.c
        unitytest.c
    )
    
    target_include_directories(unitytest PRIVATE unity)
    target_link_libraries(unitytest stack)
    set_target_properties(unitytest PROPERTIES OUTPUT_NAME "unitytest.exe")
endif()

#*******************************************************************************
# Check test harness (optional - requires checkmk)
#*******************************************************************************

option(BUILD_CHECK_TESTS "Build Check test harness (requires checkmk)" OFF)

if(BUILD_CHECK_TESTS)
    find_program(CHECKMK_EXECUTABLE checkmk)
    
    if(CHECKMK_EXECUTABLE)
        # Generate stack_check.c from stack_check.ts
        add_custom_command(
            OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/stack_check.c
            COMMAND ${CHECKMK_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/stack_check.ts > ${CMAKE_CURRENT_BINARY_DIR}/stack_check.c
            DEPENDS stack_check.ts
            COMMENT "Generating stack_check.c from stack_check.ts"
        )
        
        add_executable(stack_check
            ${CMAKE_CURRENT_BINARY_DIR}/stack_check.c
        )
        
        target_link_libraries(stack_check stack check)
        set_target_properties(stack_check PROPERTIES OUTPUT_NAME "stack_check.exe")
    else()
        message(WARNING "checkmk command not found. Check test harness will not be built.")
    endif()
endif()

#*******************************************************************************
# Code checking with splint (custom target)
#*******************************************************************************

find_program(SPLINT_EXECUTABLE splint)

if(SPLINT_EXECUTABLE)
    add_custom_target(splint
        COMMAND ${SPLINT_EXECUTABLE} -showfunc -mustfreefresh -nullpass -nullret -noeffect main.c
        COMMAND ${SPLINT_EXECUTABLE} -showfunc -mustfreefresh -nullpass -nullret -noeffect trap.c
        COMMAND ${SPLINT_EXECUTABLE} -showfunc -mustfreefresh -nullpass -nullret -noeffect test01.c
        COMMAND ${SPLINT_EXECUTABLE} -showfunc -mustfreefresh -nullpass -nullret -noeffect stack.c
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Running splint code checker"
    )
endif()

#*******************************************************************************
# Clean target (CMake handles most cleanup automatically)
# For additional cleanup of coverage/profiling files, use: cmake --build . --target clean-extra
#*******************************************************************************

add_custom_target(clean-extra
    COMMAND ${CMAKE_COMMAND} -E remove -f *.gcno *.gcda gmon.out core
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Cleaning extra files (coverage, profiling, core dumps)"
)

#
# Fin
#
