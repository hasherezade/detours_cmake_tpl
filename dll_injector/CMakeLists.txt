cmake_minimum_required (VERSION 2.8)

project ( dll_injector )

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")


set (srcs
	main.cpp
	dll_injection.cpp
	process_privilege.cpp
)
set (hdrs
	dll_injection.h
	process_privilege.h
)

add_executable ( ${PROJECT_NAME} ${hdrs} ${srcs} )

INSTALL( TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX} COMPONENT ${PROJECT_NAME} )
