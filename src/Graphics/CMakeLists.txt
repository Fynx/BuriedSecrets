set (Graphics_SRCS
	AnimatedGraphicalEntity.cpp
	Animation.cpp
	AnimationSet.cpp
	BasePolygonEffect.cpp
	Camera.cpp
	GraphicalEntity.cpp
	GraphicalEntityFactory.cpp
	Graphics.cpp
	GraphicsDataManager.cpp
	GraphicsWidget.cpp
	SelectionEffect.cpp
	SpriteGraphicalEntity.cpp
	StaticGraphicalEntity.cpp
)

set (Graphics_HDRS
	Graphics.hpp
	GraphicsWidget.hpp
)

qt5_wrap_cpp (Graphics_SRCS ${Graphics_HDRS})

add_library (Graphics ${Graphics_SRCS})
target_link_libraries (Graphics ${Qt5Widgets_LIBRARIES})

if (BUILD_TESTS)
	add_subdirectory (tests)
endif (BUILD_TESTS)
