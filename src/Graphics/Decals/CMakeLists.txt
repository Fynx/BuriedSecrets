set (Decals_SRCS
	BloodDecal.cpp
	Decal.cpp
	DecalManager.cpp
)

set (Decals_HDRS
)

qt5_wrap_cpp (Decals_SRCS ${Decals_HDRS})

add_library (Decals ${Decals_SRCS})
target_link_libraries (Decals ${Qt5Widgets_LIBRARIES})

if (BUILD_TESTS)
	add_subdirectory (tests)
endif (BUILD_TESTS)
