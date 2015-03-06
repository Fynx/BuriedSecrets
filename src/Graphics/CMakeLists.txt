add_subdirectory(Common)
add_subdirectory(Entities)
add_subdirectory(Effects)

set (Graphics_SRCS
	Camera.cpp
	GraphicalFogOfWar.cpp
	Graphics.cpp
	GraphicsDataManager.cpp
	GraphicsWidget.cpp
)

set (Graphics_HDRS
	Graphics.hpp
	GraphicsWidget.hpp
)

qt5_wrap_cpp (Graphics_SRCS ${Graphics_HDRS})

add_library (Graphics ${Graphics_SRCS})
target_link_libraries (Graphics Entities Effects GraphicsCommon ${Qt5Widgets_LIBRARIES})

if (BUILD_TESTS)
	add_subdirectory (tests)
endif (BUILD_TESTS)
