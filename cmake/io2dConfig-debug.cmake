#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "io2d::io2d_core" for configuration "Debug"
set_property(TARGET io2d::io2d_core APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(io2d::io2d_core PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libio2d_core.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS io2d::io2d_core )
list(APPEND _IMPORT_CHECK_FILES_FOR_io2d::io2d_core "${_IMPORT_PREFIX}/lib/libio2d_core.a" )

# Import target "io2d::io2d_cairo" for configuration "Debug"
set_property(TARGET io2d::io2d_cairo APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(io2d::io2d_cairo PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libio2d_cairo.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS io2d::io2d_cairo )
list(APPEND _IMPORT_CHECK_FILES_FOR_io2d::io2d_cairo "${_IMPORT_PREFIX}/lib/libio2d_cairo.a" )

# Import target "io2d::io2d_cairo_xlib" for configuration "Debug"
set_property(TARGET io2d::io2d_cairo_xlib APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(io2d::io2d_cairo_xlib PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libio2d_cairo_xlib.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS io2d::io2d_cairo_xlib )
list(APPEND _IMPORT_CHECK_FILES_FOR_io2d::io2d_cairo_xlib "${_IMPORT_PREFIX}/lib/libio2d_cairo_xlib.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
