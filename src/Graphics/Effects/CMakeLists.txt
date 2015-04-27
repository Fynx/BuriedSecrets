set (Effects_SRCS
	AntipsychosisEffect.cpp
	BasePolygonEffect.cpp
	CircleEffect.cpp
	GraphicalEffectFactory.cpp
	GraphicalEffect.cpp
	SelectionEffect.cpp
	ShowPathEffect.cpp
	UnitShadowEffect.cpp
)

set (Effects_HDRS
)

qt5_wrap_cpp (Effects_SRCS ${Effects_HDRS})

add_library (Effects ${Effects_SRCS})
target_link_libraries (Effects ${Qt5Widgets_LIBRARIES})

if (BUILD_TESTS)
	add_subdirectory (tests)
endif (BUILD_TESTS)
