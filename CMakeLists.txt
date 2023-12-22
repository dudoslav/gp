cmake_minimum_required(VERSION 3.10)

project(gp)

find_package(fmt CONFIG REQUIRED)

add_library(${PROJECT_NAME} src/gp.cc)

target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)

install(TARGETS ${PROJECT_NAME} DESTINATION .)
