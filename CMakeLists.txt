cmake_minimum_required (VERSION 2.7)
project (dakaraserver)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion -pedantic -std=c++11 -ggdb -fstack-protector -D_GLIBCXX_DEBUG")

    if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -rdynamic -Wno-unused-local-typedefs")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -ggdb -rdynamic -fstack-protector ")
    endif()

    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} ")

elseif (MSVC)

    if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()

endif()

#set(Boost_USE_STATIC_LIBS      OFF)
set(Boost_USE_MULTITHREADED     ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

# boost_locale requires 1.48.0+
find_package( Boost 1.49.0 REQUIRED COMPONENTS date_time filesystem system locale )
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

# libevent
find_package( Libevent2 REQUIRED )
include_directories(${LIBEVENT2_INCLUDE_DIR})

# sockets
if(WIN32)
  set(DAKARA_SOCKETS "ws2_32")
else()
  set(DAKARA_SOCKETS "")
endif()

file(GLOB_RECURSE DAKARA_SOURCES "src/*.cpp")
file(GLOB_RECURSE DAKARA_HEADERS "src/*.h")

add_executable(${PROJECT_NAME} ${DAKARA_SOURCES})

# -levent -levent_core -levent_extra
target_link_libraries(${PROJECT_NAME} ${LIBEVENT2_LIBRARIES} ${LIBEVENT2_CORE_LIBRARIES} ${LIBEVENT2_EXTRA_LIBRARIES} ${Boost_LIBRARIES} ${DAKARA_SOCKETS})

