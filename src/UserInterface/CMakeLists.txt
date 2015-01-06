set (UserInterface_SRCS
	IsometricPerspective.cpp
	GameWindow.cpp
	MainMenuWindow.cpp
	Perspective.cpp
	UserInterface.cpp
	Viewport.cpp
	UnitsPanel.cpp
	UnitWidget.cpp
)

set (UserInterface_HDRS
	GameWindow.hpp
	MainMenuWindow.hpp
	UserInterface.hpp
	UnitsPanel.hpp
	UnitWidget.hpp
)

qt5_wrap_cpp (UserInterface_SRCS ${UserInterface_HDRS})

add_library (UserInterface ${UserInterface_SRCS})
target_link_libraries (UserInterface ${Qt5Widgets_LIBRARIES})

if (BUILD_TESTS)
	add_subdirectory (tests)
endif (BUILD_TESTS)
