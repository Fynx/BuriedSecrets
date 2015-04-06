set (UserInterface_SRCS
	BoardWidget.cpp
	Resources.cpp
	UserInterface.cpp

	Game/GameCommands.cpp
	Game/GameInterface.cpp
	Game/GameSelections.cpp
	Game/GameViewport.cpp
	Game/GameWindows.cpp

	Menus/MainMenu.cpp
	Menus/PostGameMenu.cpp

	Panels/DeadSection.cpp
	Panels/FactionPanel.cpp
	Panels/NotificationPanel.cpp
	Panels/NotificationWidget.cpp
	Panels/UnitsPanel.cpp
	Panels/UnitSection.cpp

	Viewport/IsometricPerspective.cpp
	Viewport/Perspective.cpp
	Viewport/Viewport.cpp

	Windows/CampWindow.cpp
	Windows/JournalWindow.cpp
	Windows/UnitWindow.cpp

	Windows/Tabs/CampConstructorTab.cpp
	Windows/Tabs/CampEquipmentTab.cpp
	Windows/Tabs/UnitEquipmentTab.cpp
	Windows/Tabs/UnitHistoryTab.cpp

	Windows/Tabs/Item/ItemsDisplay.cpp
	Windows/Tabs/Item/ItemsListWidget.cpp
	Windows/Tabs/Item/ItemWidget.cpp
	Windows/Tabs/Item/SlotWidget.cpp

	JournalEntryWidget.cpp
)

set (UserInterface_HDRS
	BoardWidget.hpp
	UserInterface.hpp

	Game/GameCommands.hpp
	Game/GameInterface.hpp
	Game/GameSelections.hpp
	Game/GameViewport.hpp
	Game/GameWindows.hpp

	Menus/MainMenu.hpp
	Menus/PostGameMenu.hpp

	Panels/FactionPanel.hpp
	Panels/UnitsPanel.hpp
	Panels/UnitSection.hpp
	Panels/NotificationPanel.hpp
	Panels/NotificationWidget.hpp

	Windows/CampWindow.hpp
	Windows/JournalWindow.hpp
	Windows/UnitWindow.hpp

	Windows/Tabs/CampEquipmentTab.hpp
	Windows/Tabs/CampConstructorTab.hpp

	Windows/Tabs/Item/ItemsDisplay.hpp
	Windows/Tabs/Item/ItemsListWidget.hpp
	Windows/Tabs/Item/SlotWidget.hpp
)

qt5_wrap_cpp (UserInterface_SRCS ${UserInterface_HDRS})

add_library (UserInterface ${UserInterface_SRCS})
target_link_libraries (UserInterface Xcursor UI_Data ${Qt5Widgets_LIBRARIES})

if (BUILD_TESTS)
	add_subdirectory (tests)
endif (BUILD_TESTS)
