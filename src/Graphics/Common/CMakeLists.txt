set (GraphicsCommon_SRCS
	LineShape.cpp
)

set (GraphicsCommon_HDRS
)

qt5_wrap_cpp (GraphicsCommon_SRCS ${GraphicsCommon_HDRS})

add_library (GraphicsCommon ${GraphicsCommon_SRCS})
target_link_libraries (GraphicsCommon ${Qt5Widgets_LIBRARIES})

if (BUILD_TESTS)
	add_subdirectory (tests)
endif (BUILD_TESTS)