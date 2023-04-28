cmake_minimum_required ( VERSION 3.0 )
project ( detoured_test )

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")

include_directories (
  include
)
# modules:
set ( M_DETOURS_LIB "libdetours" )

set (DETOURS_DIR "${CMAKE_SOURCE_DIR}/${M_DETOURS_LIB}" CACHE PATH "Detours main path")
# libs
add_subdirectory ( libdetours )
set ( DETOURS_LIB $<TARGET_FILE:libdetours> CACHE PATH "Detours library path" )

# main project
add_subdirectory ( project_tpl )
add_subdirectory ( hooking_dll_tpl )
add_subdirectory ( test_app )