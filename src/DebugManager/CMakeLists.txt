set (DebugManager_SRCS
	DebugManager.cpp
)

set (DebugManager_HDRS
)

qt5_wrap_cpp (DebugManager_SRCS ${DebugManager_HDRS})

add_library (DebugManager ${DebugManager_SRCS})
target_link_libraries (DebugManager ${Qt5Widgets_LIBRARIES})

if (BUILD_TESTS)
	add_subdirectory (tests)
endif (BUILD_TESTS)
