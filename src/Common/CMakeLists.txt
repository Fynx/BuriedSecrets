set (Common_SRCS
	Enums.cpp
	Geometry.cpp
)

set (Common_HDRS
)

# qt5_wrap_cpp (Common_SRCS ${Common_HDRS})

add_library (Common ${Common_SRCS})
target_link_libraries (Common ${Qt5Widgets_LIBRARIES})

if (BUILD_TESTS)
	add_subdirectory (tests)
endif (BUILD_TESTS)
