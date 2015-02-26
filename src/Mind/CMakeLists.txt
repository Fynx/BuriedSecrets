add_subdirectory(MapManager)

set (Mind_SRCS
	AnimationAnimator.cpp
	Animator.cpp
	AnimatorManager.cpp
	AnimatorConsume.cpp
	AnimatorDie.cpp
	AnimatorApplyDamage.cpp
	AnimatorRegenerate.cpp
	AnimatorMove.cpp
	AnimatorTest.cpp
	AnimatorPhysicsUpdate.cpp
	AnimatorUpdatePath.cpp
	AnimatorGoPsycho.cpp
	AnimatorHeal.cpp
	AnimatorAssemble.cpp
	AnimatorEnterBuilding.cpp
	AnimatorLeaveBuilding.cpp
	AnimatorAttack.cpp
	AnimatorWeapon.cpp
	AnimatorUpdateFOV.cpp
	AnimatorNearCamp.cpp
	AnimatorWatchTarget.cpp
	Effect.cpp
	Event.cpp
	Mind.cpp
	ItemConstructor.cpp
	ObjectEffectData.cpp
)

set (Mind_HDRS
	AnimatorManager.hpp
	Mind.hpp
)

qt5_wrap_cpp (Mind_SRCS ${Mind_HDRS})

add_library (Mind ${Mind_SRCS})
target_link_libraries (Mind GameObjects ${Qt5Widgets_LIBRARIES})

if (BUILD_TESTS)
	add_subdirectory (tests)
endif (BUILD_TESTS)
