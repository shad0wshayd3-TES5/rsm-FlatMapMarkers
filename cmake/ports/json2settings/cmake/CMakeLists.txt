cmake_minimum_required(VERSION 3.22)

project(
	json2settings
	LANGUAGES CXX
)

include(GNUInstallDirs)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
	message(FATAL_ERROR "in-source builds are not allowed")
endif()

find_package(nlohmann_json REQUIRED CONFIG)

set(headers include/Json2Settings.h)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${headers})

add_library(
	${PROJECT_NAME}
	INTERFACE
	${headers}
	.clang-format
)

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_compile_features(
	${PROJECT_NAME}
	INTERFACE
		cxx_std_20
)

target_include_directories(
	${PROJECT_NAME}
	INTERFACE
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
	"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_link_libraries(
	${PROJECT_NAME}
	INTERFACE
		nlohmann_json::nlohmann_json
)

# ---- Create an installable target ----

install(
	TARGETS ${PROJECT_NAME}
	EXPORT ${PROJECT_NAME}-targets
)

install(
	DIRECTORY include/
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

configure_file(
	config.cmake.in
	${PROJECT_NAME}Config.cmake
	@ONLY
)

install(
	FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

install(
	EXPORT ${PROJECT_NAME}-targets
	NAMESPACE ${PROJECT_NAME}::
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
