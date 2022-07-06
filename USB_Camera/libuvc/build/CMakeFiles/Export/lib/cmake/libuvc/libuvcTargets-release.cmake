#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "LibUVC::UVCShared" for configuration "Release"
set_property(TARGET LibUVC::UVCShared APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(LibUVC::UVCShared PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libuvc.so.0.0.6"
  IMPORTED_SONAME_RELEASE "libuvc.so.0"
  )

list(APPEND _IMPORT_CHECK_TARGETS LibUVC::UVCShared )
list(APPEND _IMPORT_CHECK_FILES_FOR_LibUVC::UVCShared "${_IMPORT_PREFIX}/lib/libuvc.so.0.0.6" )

# Import target "LibUVC::UVCStatic" for configuration "Release"
set_property(TARGET LibUVC::UVCStatic APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(LibUVC::UVCStatic PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libuvc.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS LibUVC::UVCStatic )
list(APPEND _IMPORT_CHECK_FILES_FOR_LibUVC::UVCStatic "${_IMPORT_PREFIX}/lib/libuvc.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
