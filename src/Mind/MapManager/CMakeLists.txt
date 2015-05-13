set (MapManager_SRCS
	AccessibilityMap.cpp
	AStarPathFinder.cpp
	DiffVisibilityMap.cpp
	DynamicAccessibilityMap.cpp
	HPAStarPathFinder.cpp
	ImageVisibilityMap.cpp
	MapManager.cpp
	Map.cpp
	PathFinder.cpp
	PrecomputedAccessibilityMap.cpp
	VisibilityMap.cpp
)

set (MapManager_HDRS
)

qt5_wrap_cpp (MapManager_SRCS ${MapManager_HDRS})

add_library (MapManager ${MapManager_SRCS})
target_link_libraries (MapManager ${Qt5Widgets_LIBRARIES})

if (BUILD_TESTS)
        add_subdirectory (tests)
endif (BUILD_TESTS)

