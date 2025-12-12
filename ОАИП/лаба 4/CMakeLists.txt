cmake_minimum_required(VERSION 3.12)
project(library_manager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBPQXX REQUIRED libpqxx)

include_directories(include)
include_directories(${LIBPQXX_INCLUDE_DIRS})

set(SOURCES
    src/Database.cpp
    src/Logger.cpp
    src/Author.cpp
    src/Book.cpp
    src/User.cpp
    src/BorrowedBook.cpp
    src/LibraryManager.cpp
)

add_executable(library_manager main.cpp ${SOURCES})

target_compile_features(library_manager PRIVATE cxx_std_17)
target_link_libraries(library_manager ${LIBPQXX_LIBRARIES})

if(WIN32)
    target_link_libraries(library_manager ws2_32)
endif()