set (UserInterface_SRCS
	CampPanel.cpp
	CampEquipmentWindow.cpp
	GameWindow.cpp
	IsometricPerspective.cpp
	JournalWindow.cpp
	MainMenuWindow.cpp
	Perspective.cpp
	UnitsPanel.cpp
	UnitWidget.cpp
	UserInterface.cpp
	Viewport.cpp
)

set (UserInterface_HDRS
	CampPanel.hpp
	GameWindow.hpp
	MainMenuWindow.hpp
	UserInterface.hpp
)

qt5_wrap_cpp (UserInterface_SRCS ${UserInterface_HDRS})

add_library (UserInterface ${UserInterface_SRCS})
target_link_libraries (UserInterface ${Qt5Widgets_LIBRARIES})

if (BUILD_TESTS)
	add_subdirectory (tests)
endif (BUILD_TESTS)
