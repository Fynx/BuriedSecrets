# set (Tools_SRCS
# )
#
# set (Tools_HDRS
# )

# qt5_wrap_cpp (Tools_SRCS ${Tools_HDRS})

# add_library (Tools ${Tools_SRCS})
# target_link_libraries (Tools ${Qt5Widgets_LIBRARIES})

if (BUILD_TESTS)
	add_subdirectory (tests)
endif (BUILD_TESTS)

add_executable(AnimationCreator AnimationCreator.cpp)
add_executable(TextureCreator TextureCreator.cpp)
