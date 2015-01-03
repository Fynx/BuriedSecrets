set (MapManager_SRCS
        MapManager.cpp
	Map.cpp
)

set (MapManager_HDRS
)

qt5_wrap_cpp (MapManager_SRCS ${MapManager_HDRS})

add_library (MapManager ${MapManager_SRCS})
target_link_libraries (MapManager ${Qt5Widgets_LIBRARIES})

if (BUILD_TESTS)
        add_subdirectory (tests)
endif (BUILD_TESTS)

