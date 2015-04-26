cmake_minimum_required (VERSION 2.6)
project (dakaraserver)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11 -ggdb -rdynamic -march=native -Wno-unused-local-typedefs -fstack-protector -D_GLIBCXX_DEBUG  ")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -ggdb -rdynamic -fstack-protector ")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
endif()

set(Boost_USE_STATIC_LIBS       OFF)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package( Boost 1.46.0 REQUIRED COMPONENTS date_time filesystem system locale )
include_directories(${Boost_INCLUDE_DIRS})

find_package( Libevent2 REQUIRED )
include_directories(${LIBEVENT2_INCLUDE_DIR})

file(GLOB_RECURSE DAKARA_SOURCES "src/*.cpp")
file(GLOB_RECURSE DAKARA_HEADERS "src/*.h")

add_executable(${PROJECT_NAME} ${DAKARA_SOURCES})

# -levent -levent_core -levent_extra
target_link_libraries(${PROJECT_NAME} ${LIBEVENT2_LIBRARIES} ${LIBEVENT2_CORE_LIBRARIES} ${LIBEVENT2_EXTRA_LIBRARIES} ${Boost_LIBRARIES} )

