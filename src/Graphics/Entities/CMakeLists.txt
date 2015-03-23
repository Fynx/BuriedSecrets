set (Entities_SRCS
	EffectGraphicalEntity.cpp
	GraphicalEntity.cpp
	GraphicalEntityFactory.cpp
	LocationGraphicalEntity.cpp
	MoveCommandEffectGraphicalEntity.cpp
	ShotEffectGraphicalEntity.cpp
	SpriteGraphicalEntity.cpp
	StaticGraphicalEntity.cpp
	TexturedGraphicalEntity.cpp
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