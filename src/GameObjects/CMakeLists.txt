set (GameObjects_SRCS
)

set (GameObjects_HDRS
)

# qt5_wrap_cpp (GameObjects_SRCS ${GameObjects_HDRS})

# add_library (GameObjects ${GameObjects_SRCS})
# target_link_libraries (GameObjects ${Qt5Widgets_LIBRARIES})

if (BUILD_TESTS)
	add_subdirectory (tests)
endif (BUILD_TESTS)
