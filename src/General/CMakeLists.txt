set (BuriedSecrets_SRCS
	General.cpp
	main.cpp
)

set (BuriedSecrets_HDRS
	General.h
)

qt5_wrap_cpp (BuriedSecrets_SRCS ${BuriedSecrets_HDRS})

add_executable (BuriedSecrets ${BuriedSecrets_SRCS})
target_link_libraries (BuriedSecrets
	${Qt5Widgets_LIBRARIES}
	DataManager
	DebugManager
# 	GameObjects
	Graphics
	Mind
	PhysicsEngine
	SoundsManager
	UserInterface
)
