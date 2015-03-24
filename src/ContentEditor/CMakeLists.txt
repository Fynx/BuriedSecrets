set (ContentEditor_SRCS
	ContentEditor.cpp
	PrototypesEditor.cpp
	main.cpp
)

set (ContentEditor_HDRS
	ContentEditor.hpp
	PrototypesEditor.hpp
)

qt5_wrap_cpp (ContentEditor_SRCS ${ContentEditor_HDRS})

add_executable (ContentEditor ${ContentEditor_SRCS})
target_link_libraries (ContentEditor
	${Qt5Widgets_LIBRARIES}
# 	${SFML_LIBRARIES}
# 	Xcursor
# 	DataManager
# 	DebugManager
# 	GameObjects
# 	Graphics
# 	UserInterface
# 	Mind
# 	PhysicsEngine
# 	SoundsManager
# 	MapManager
# 	Common
)