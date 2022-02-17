#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Inspection" for configuration ""
set_property(TARGET Inspection APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(Inspection PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "/home/vincents/Documents/Cours/OperatingSystems/Inspection/lib/libInspection.so"
  IMPORTED_SONAME_NOCONFIG "libInspection.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS Inspection )
list(APPEND _IMPORT_CHECK_FILES_FOR_Inspection "/home/vincents/Documents/Cours/OperatingSystems/Inspection/lib/libInspection.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
