#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "wavelib::wavelib" for configuration "RelWithDebInfo"
set_property(TARGET wavelib::wavelib APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(wavelib::wavelib PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "C"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/wavelib.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS wavelib::wavelib )
list(APPEND _IMPORT_CHECK_FILES_FOR_wavelib::wavelib "${_IMPORT_PREFIX}/lib/wavelib.lib" )

# Import target "wavelib::wauxlib" for configuration "RelWithDebInfo"
set_property(TARGET wavelib::wauxlib APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(wavelib::wauxlib PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "C"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELWITHDEBINFO "wavelib::wavelib"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/wauxlib.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS wavelib::wauxlib )
list(APPEND _IMPORT_CHECK_FILES_FOR_wavelib::wauxlib "${_IMPORT_PREFIX}/lib/wauxlib.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
