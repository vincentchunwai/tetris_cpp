#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "SFML::Network" for configuration "RelWithDebInfo"
set_property(TARGET SFML::Network APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(SFML::Network PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "CXX"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/sfml-network-s.lib"
  )

list(APPEND _cmake_import_check_targets SFML::Network )
list(APPEND _cmake_import_check_files_for_SFML::Network "${_IMPORT_PREFIX}/lib/sfml-network-s.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
