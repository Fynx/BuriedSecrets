set (UserInterface_SRCS
	BoardWidget.cpp
	CampConstructorTab.cpp
	CampEquipmentTab.cpp
	CampWindow.cpp
	DeadSection.cpp
	FactionPanel.cpp
	GameWindow.cpp
	IsometricPerspective.cpp
	ItemsDisplay.cpp
	ItemsListWidget.cpp
	ItemWidget.cpp
	JournalWindow.cpp
	MainMenuWindow.cpp
	Perspective.cpp
	Resources.cpp
	SelectionManager.cpp
	SlotWidget.cpp
	UnitsPanel.cpp
	UnitEquipmentTab.cpp
	UnitHistoryTab.cpp
	UnitSection.cpp
	UnitWindow.cpp
	UserInterface.cpp
	Viewport.cpp
)

set (UserInterface_HDRS
	BoardWidget.hpp
	CampEquipmentTab.hpp
	CampConstructorTab.hpp
	CampWindow.hpp
	FactionPanel.hpp
	GameWindow.hpp
	ItemsDisplay.hpp
	ItemsListWidget.hpp
	JournalWindow.hpp
	MainMenuWindow.hpp
	SelectionManager.hpp
	SlotWidget.hpp
	UnitsPanel.hpp
	UnitSection.hpp
	UnitWindow.hpp
	UserInterface.hpp
)

qt5_wrap_cpp (UserInterface_SRCS ${UserInterface_HDRS})

add_library (UserInterface ${UserInterface_SRCS})
target_link_libraries (UserInterface Xcursor UI_Data ${Qt5Widgets_LIBRARIES})

if (BUILD_TESTS)
	add_subdirectory (tests)
endif (BUILD_TESTS)
