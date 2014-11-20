set (Mind_SRCS
	Animator.cpp
	AnimatorManager.cpp
	AnimatorTest.cpp
	Event.cpp
	Mind.cpp
)

set (Mind_HDRS
	AnimatorManager.hpp
	Mind.hpp
)

qt5_wrap_cpp (Mind_SRCS ${Mind_HDRS})

add_library (Mind ${Mind_SRCS})
target_link_libraries (Mind ${Qt5Widgets_LIBRARIES})

if (BUILD_TESTS)
	add_subdirectory (tests)
endif (BUILD_TESTS)
