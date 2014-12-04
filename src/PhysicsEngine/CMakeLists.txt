set (PhysicsEngine_SRCS
	PhysicsEngine.cpp
	Box2DEngine.cpp
	ContactListener.cpp
	RayCallback.cpp
	AABBCallback.cpp
)

set (PhysicsEngine_HDRS
)

qt5_wrap_cpp (PhysicsEngine_SRCS ${PhysicsEngine_HDRS})

add_library (PhysicsEngine ${PhysicsEngine_SRCS})
target_link_libraries (PhysicsEngine Box2D ${Qt5Widgets_LIBRARIES})

if (BUILD_TESTS)
	add_subdirectory (tests)
endif (BUILD_TESTS)
