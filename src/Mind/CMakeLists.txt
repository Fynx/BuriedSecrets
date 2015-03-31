add_subdirectory(MapManager)
add_subdirectory(Animators)

set (Mind_SRCS
	Effect.cpp
	Event.cpp
	Mind.cpp
	ItemConstructor.cpp
	ObjectEffectData.cpp
	ObjectRadiusEffectData.cpp
	PointEffectData.cpp
	PointToPointEffectData.cpp
)

set (Mind_HDRS
	Mind.hpp
)

qt5_wrap_cpp (Mind_SRCS ${Mind_HDRS})

add_library (Mind ${Mind_SRCS})
target_link_libraries (Mind GameObjects Animators ${Qt5Widgets_LIBRARIES})

if (BUILD_TESTS)
	add_subdirectory (tests)
endif (BUILD_TESTS)
