set (GameObjects_SRCS
	Building.cpp
	Camp.cpp
	Equipment.cpp
	Faction.cpp
	Fortification.cpp
	Item.cpp
	Journal.cpp
	JournalEntry.cpp
	Location.cpp
	Object.cpp
	QuestLog.cpp
	Unit.cpp
	World.cpp
)

set (GameObjects_HDRS
)

qt5_wrap_cpp (GameObjects_SRCS ${GameObjects_HDRS})

add_library (GameObjects ${GameObjects_SRCS})
target_link_libraries (GameObjects ${Qt5Widgets_LIBRARIES})

if (BUILD_TESTS)
	add_subdirectory (tests)
endif (BUILD_TESTS)
