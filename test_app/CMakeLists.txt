cmake_minimum_required ( VERSION 3.0 )

project ( test_app )

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")


set (srcs
	main.cpp
)
set (hdrs
#put your headers here
)

add_executable ( ${PROJECT_NAME} ${exe_hdrs} ${srcs} main.cpp )

INSTALL( TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX} COMPONENT ${PROJECT_NAME} )
