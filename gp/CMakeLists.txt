cmake_minimum_required(VERSION 3.10)

project(gp VERSION 0.0.1)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

find_package(fmt CONFIG REQUIRED)
add_library(${PROJECT_NAME}_headers INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME}_headers ALIAS ${PROJECT_NAME}_headers)
target_include_directories(${PROJECT_NAME}_headers INTERFACE $<BUILD_INTERFACE:${gp_INCLUDE_DIR}> $<INSTALL_INTERFACE:gp/${CMAKE_INSTALL_INCLUDEDIR}>)
target_compile_features(${PROJECT_NAME}_headers INTERFACE cxx_std_23)

add_library(${PROJECT_NAME} SHARED src/gp.cc)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PUBLIC gp_headers)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
set_target_properties(${PROJECT_NAME} PROPERTIES
  LINK_FLAGS  '-Wl,--allow-shlib-undefined')

set(CMAKE_INSTALL_DATAROOT "${PROJECT_NAME}")

set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_DATAROOT}")

set(LIB_INSTALL_DIR ${CMAKE_INSTALL_DATAROOT} CACHE PATH "Lib path")

configure_package_config_file(
	${PROJECT_NAME}Config.cmake.in "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
	INSTALL_DESTINATION "${CMAKE_INSTALL_DATAROOT}/share/cmake/${PROJECT_NAME}"
      PATH_VARS LIB_INSTALL_DIR
	)

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/gpConfigVersion.cmake
  VERSION 0.0.1
  COMPATIBILITY SameMajorVersion )

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/gpConfig.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/gpConfigVersion.cmake
	      DESTINATION "${CMAKE_INSTALL_DATAROOT}/share/cmake/${PROJECT_NAME}"
	      )

set(GP_EXPORT_NAME "${PROJECT_NAME}Targets")

install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_headers EXPORT "${GP_EXPORT_NAME}"
	LIBRARY DESTINATION ${CMAKE_INSTALL_DATAROOT}
	RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOT}
	)

install(FILES src/gp.hh DESTINATION "${CMAKE_INSTALL_DATAROOT}/include")

install(
	EXPORT "${GP_EXPORT_NAME}"
	NAMESPACE "gp::"
	DESTINATION "${CMAKE_INSTALL_DATAROOT}/share/cmake/${PROJECT_NAME}"
)
