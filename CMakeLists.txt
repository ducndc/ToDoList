cmake_minimum_required(VERSION 3.10)
project(ToDoList)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

add_definitions(${GTKMM_CFLAGS_OTHER})

add_executable(todo main.cc todo_app.cc)
target_link_libraries(todo ${GTKMM_LIBRARIES})