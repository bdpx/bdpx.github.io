project(highlighter)

set(CMAKE_CXX_STANDARD 17)

####################################################################################################
# detect PkgConfig
####################################################################################################
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CheckIncludeFiles)

find_package(PkgConfig REQUIRED)

find_package(LibXml2 REQUIRED)
find_package(Boost REQUIRED COMPONENTS system filesystem regex)

add_executable(${PROJECT_NAME}
    highlighter.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE ${PROJECT_SOURCE_DIR}
    SYSTEM ${LIBXML2_INCLUDE_DIR}
    SYSTEM ${Boost_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    atomic
    pthread
    ${LIBXML2_LIBRARIES}
    source-highlight
    boost_regex
)

add_compile_options(
    -Wall
    -Wcast-align
    -Wcast-qual
    -Wdate-time
    -Wformat=2
    -Wextra
    -Winit-self
    -Winline
    -Wmissing-field-initializers
    -Wmissing-include-dirs
    -Wno-address-of-packed-member
    -Wpedantic
    -Wpointer-arith
    -Wredundant-decls
    -Wshadow
    -Wundef
    -Wuninitialized
    -Wunreachable-code
    -Wunused-macros
    -Wwrite-strings
    -std=c++17
    -pipe
    -fvisibility-inlines-hidden   # FIXME: maybe for release only
    -fvisibility=hidden           # FIXME: maybe for release only
    -fno-plt
)
