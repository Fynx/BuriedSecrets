
set (Anims_SRCS
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
	AnimatorDisassemble.cpp
	AnimatorEffects.cpp
	AnimatorMobAttitude.cpp
)

set (Anims_HDRS
	AnimatorManager.hpp
)

qt5_wrap_cpp (Anims_SRCS ${Anims_HDRS})

add_library (Animators ${Anims_SRCS})
target_link_libraries (Animators GameObjects ${Qt5Widgets_LIBRARIES})

if (BUILD_TESTS)
	add_subdirectory (tests)
endif (BUILD_TESTS)
