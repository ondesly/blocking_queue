#
#  CMakeLists.txt
#  blocking_queue
#
#  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 29.08.2021.
#  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
#

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(blocking_queue
        VERSION 1.0.0
        LANGUAGES CXX)

##########
# Source #
##########

add_library(blocking_queue INTERFACE)
add_library(oo::blocking_queue ALIAS blocking_queue)

#

set(INCLUDE_DIR
        ${CMAKE_CURRENT_LIST_DIR}/include)

set(PUBLIC_HEADERS
        ${INCLUDE_DIR}/blocking_queue/blocking_queue.h)

target_include_directories(blocking_queue INTERFACE
        $<BUILD_INTERFACE:${INCLUDE_DIR}>
        $<INSTALL_INTERFACE:include>)

###########
# Install #
###########

include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}-config
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}${INSTALL_SUFFIX}/${PROJECT_NAME})

install(FILES ${PUBLIC_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}${INSTALL_SUFFIX}/${PROJECT_NAME})

install(EXPORT ${PROJECT_NAME}-config DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

###########
# Testing #
###########

enable_testing()

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    add_subdirectory(tests)
endif ()