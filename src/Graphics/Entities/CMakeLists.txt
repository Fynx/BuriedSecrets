set (Entities_SRCS
	Animation.cpp
	AnimationSet.cpp
	AnimatedGraphicalEntity.cpp
	EffectGraphicalEntity.cpp
	GraphicalEntity.cpp
	GraphicalEntityFactory.cpp
	MoveCommandEffectGraphicalEntity.cpp
	ShotEffectGraphicalEntity.cpp
	SpriteGraphicalEntity.cpp
	StaticGraphicalEntity.cpp
	UnitGraphicalEntity.cpp
)

set (Entities_HDRS
)

qt5_wrap_cpp (Entities_SRCS ${Entities_HDRS})

add_library (Entities ${Entities_SRCS})
target_link_libraries (Entities ${Qt5Widgets_LIBRARIES})

if (BUILD_TESTS)
	add_subdirectory (tests)
endif (BUILD_TESTS)