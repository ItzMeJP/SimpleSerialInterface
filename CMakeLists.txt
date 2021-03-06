cmake_minimum_required(VERSION 3.16)

project(simple_serial
        VERSION 08.07.2021
        DESCRIPTION
        "Simple serial API to C++")

# Set if it will have export lib capabilities
# If the lib is placed inside the project folder, it nos needed to install it.

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 14)

#External packages
find_package(Boost COMPONENTS date_time system REQUIRED) # To serial communication
find_package(Threads REQUIRED)

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
        include/simple_serial
        ${BOOST_INCLUDE_DIRS}
)

## Declare a C++ library
add_library(${PROJECT_NAME} SHARED
        src/simple_serial.cpp)

## Set dependencies of the library
target_link_libraries(${PROJECT_NAME}
        ${BOOST_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        )


# To export the lib and install it
set_target_properties(${PROJECT_NAME} PROPERTIES
        VERSION ${PROJECT_VERSION}
        PUBLIC_HEADER include/simple_serial/simple_serial.h
        )

target_include_directories(${PROJECT_NAME} PRIVATE .)

configure_file(simple_serial.pc.in simple_serial.pc @ONLY)

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/simple_serial
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/simple_serial)

install(FILES ${CMAKE_BINARY_DIR}/simple_serial.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)


## Define an executable
add_executable(reader_serial_test
        examples/reader_serial_test.cpp)

## Define an executable
add_executable(writer_serial_test
        examples/writer_serial_test.cpp)

## Define the executable dependencies
target_link_libraries(reader_serial_test
        simple_serial
        )

## Define the executable dependencies
target_link_libraries(writer_serial_test
        simple_serial
        )
