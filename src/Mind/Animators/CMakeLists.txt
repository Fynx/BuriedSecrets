
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
	AnimatorBuildingDmg.cpp
	AnimatorAggressiveAtt.cpp
	AnimatorGuardAtt.cpp
	AnimatorResult.cpp
	AnimatorBAggressiveAtt.cpp
	AnimatorNearestEnemy.cpp
	AnimatorKickOut.cpp
	AnimatorQuest.cpp
)

set (Anims_HDRS
	AnimatorManager.hpp
)

qt5_wrap_cpp (Anims_SRCS ${Anims_HDRS})

add_library (Animators ${Anims_SRCS})
target_link_libraries (Animators GameObjects Mind ${Qt5Widgets_LIBRARIES})

if (BUILD_TESTS)
	add_subdirectory (tests)
endif (BUILD_TESTS)
