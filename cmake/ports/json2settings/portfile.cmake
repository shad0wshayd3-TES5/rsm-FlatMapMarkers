vcpkg_from_github(
	OUT_SOURCE_PATH SOURCE_PATH
	REPO shad0wshayd3/Json2Settings
	REF f2ff94eb8cecc6018204dfdeee13225b135a5cdd
	SHA512 41fa1a8600b71c790da7a540e3c80db9dcea3c3c89a75aaa7d86846e59dc210a177cf01040822d5451c6242885ee6f986b931ac8333724f0908b00e510892348
	HEAD_REF master
)

vcpkg_cmake_configure(SOURCE_PATH ${SOURCE_PATH})
vcpkg_cmake_install()
vcpkg_cmake_config_fixup(CONFIG_PATH lib/cmake/Json2Settings)

file(REMOVE_RECURSE
	${CURRENT_PACKAGES_DIR}/debug
	${CURRENT_PACKAGES_DIR}/lib
)

vcpkg_install_copyright(FILE_LIST ${SOURCE_PATH}/LICENSE)
