# cmake_minimum_required(VERSION 3.10)
# project(DHW)

# set(CMAKE_CXX_STANDARD 17)

# file(GLOB SOURCES "src/*.cpp")
# file(GLOB HEADERS "include/*.h")

# add_executable(dhw ${SOURCES} ${HEADERS})

# target_include_directories(dhw PRIVATE include)
# target_link_libraries(dhw PRIVATE pqxx pq)
# cmake_minimum_required(VERSION 3.10)
# project(dhw)
# set(CMAKE_CXX_STANDARD 17)
# add_executable(dhw main.cpp)
# target_link_libraries(dhw PRIVATE pqxx::pqxx)

# add_custom_command(
#     TARGET dhw POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#         ${CMAKE_CURRENT_SOURCE_DIR}/products.csv
#         ${CMAKE_CURRENT_BINARY_DIR}/products.csv
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#         ${CMAKE_CURRENT_SOURCE_DIR}/customers.csv
#         ${CMAKE_CURRENT_BINARY_DIR}/customers.csv
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#         ${CMAKE_CURRENT_SOURCE_DIR}/sales.csv
#         ${CMAKE_CURRENT_BINARY_DIR}/sales.csv
#     COMMENT "Копирование CSV файлов в папку сборки"
# )
cmake_minimum_required(VERSION 3.10)
project(dhw)

set(CMAKE_CXX_STANDARD 17)

set(PQXX_INCLUDE_DIR "C:/msys64/mingw64/include")
set(PQXX_LIBRARY "C:/msys64/mingw64/lib/libpqxx.dll.a")
set(PQ_LIBRARY "C:/msys64/mingw64/lib/libpq.dll.a")

add_executable(dhw main.cpp)

target_include_directories(dhw PRIVATE ${PQXX_INCLUDE_DIR})

target_link_libraries(dhw PRIVATE ${PQXX_LIBRARY} ${PQ_LIBRARY})

add_custom_command(
    TARGET dhw POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/products.csv
        ${CMAKE_CURRENT_BINARY_DIR}/products.csv
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/customers.csv
        ${CMAKE_CURRENT_BINARY_DIR}/customers.csv
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/sales.csv
        ${CMAKE_CURRENT_BINARY_DIR}/sales.csv
    COMMENT "Копирование CSV файлов"
)