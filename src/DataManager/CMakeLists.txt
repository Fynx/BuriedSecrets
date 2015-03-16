set (DataManager_SRCS
	AnimationData.cpp
	DataManager.cpp
	Prototype.cpp
	Resource.cpp
	TextureData.cpp
	TextureSet.cpp
)

set (DataManager_HDRS
)

qt5_wrap_cpp (DataManager_SRCS ${DataManager_HDRS})

add_library (DataManager ${DataManager_SRCS})
target_link_libraries (DataManager ${Qt5Widgets_LIBRARIES})

if (BUILD_TESTS)
	add_subdirectory (tests)
endif (BUILD_TESTS)
