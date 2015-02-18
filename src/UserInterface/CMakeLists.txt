set (UserInterface_SRCS
	BoardWidget.cpp
	CampEquipmentWindow.cpp
	CampPanel.cpp
	GameWindow.cpp
	IsometricPerspective.cpp
	JournalWindow.cpp
	MainMenuWindow.cpp
	Perspective.cpp
	SelectionManager.cpp
	UnitsPanel.cpp
	UnitWidget.cpp
	UnitWindow.cpp
	UserInterface.cpp
	Viewport.cpp
)

set (UserInterface_HDRS
	BoardWidget.hpp
	CampEquipmentWindow.hpp
	CampPanel.hpp
	GameWindow.hpp
	JournalWindow.hpp
	MainMenuWindow.hpp
	SelectionManager.hpp
	UnitsPanel.hpp
	UnitWidget.hpp
	UnitWindow.hpp
	UserInterface.hpp
)

qt5_wrap_cpp (UserInterface_SRCS ${UserInterface_HDRS})

add_library (UserInterface ${UserInterface_SRCS})
target_link_libraries (UserInterface ${Qt5Widgets_LIBRARIES})

if (BUILD_TESTS)
	add_subdirectory (tests)
endif (BUILD_TESTS)
