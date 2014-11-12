set (SoundsManager_SRCS
	SoundsManager.cpp
)

set (SoundsManager_HDRS
)

qt5_wrap_cpp (SoundsManager_SRCS ${SoundsManager_HDRS})

add_library (SoundsManager ${SoundsManager_SRCS})
target_link_libraries (SoundsManager ${Qt5Widgets_LIBRARIES})

if (BUILD_TESTS)
	add_subdirectory (tests)
endif (BUILD_TESTS)
