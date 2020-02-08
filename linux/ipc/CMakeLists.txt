cmake_minimum_required(VERSION 3.0)

find_package(Boost REQUIRED date_time system filesystem thread)

include_directories(${BOOST_INCLUDE_DIRS})

message("boost lib: ${Boost_LIBRARIES}")
message("boost inc:${Boost_INCLUDE_DIR}")

add_executable(arr arr.cpp)
add_executable(shm shm.cpp)
add_executable(atom_shm atom_shm.cpp)

target_link_libraries(arr ${Boost_LIBRARIES} )
target_link_libraries(shm ${Boost_LIBRARIES} rt)
target_link_libraries(atom_shm ${Boost_LIBRARIES} rt)
