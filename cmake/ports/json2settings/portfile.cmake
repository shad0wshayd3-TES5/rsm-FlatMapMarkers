vcpkg_from_github(
	OUT_SOURCE_PATH SOURCE_PATH
	REPO Ryan-rsm-McKenzie/Json2Settings
	REF 231d4c5b210881a4ccdf04dbfa06d2d653fc26ae
	SHA512 6dd16e13e7ad7a988a4e4c468c02b47265b13467900cf381c8c802c671f195f1af67867fc8b697970708bd73597b703ae43971ad4c2b03f720467096ebde0e91
	HEAD_REF master
)

file(
	COPY
		${CMAKE_CURRENT_LIST_DIR}/cmake/CMakeLists.txt
		${CMAKE_CURRENT_LIST_DIR}/cmake/config.cmake.in
	DESTINATION
		${SOURCE_PATH}
)

vcpkg_cmake_configure(SOURCE_PATH ${SOURCE_PATH})
vcpkg_cmake_install()
vcpkg_cmake_config_fixup(CONFIG_PATH lib/cmake/json2settings)

file(REMOVE_RECURSE
	${CURRENT_PACKAGES_DIR}/debug
	${CURRENT_PACKAGES_DIR}/lib
)

file(INSTALL ${SOURCE_PATH}/LICENSE DESTINATION ${CURRENT_PACKAGES_DIR}/share/${PORT} RENAME copyright)
