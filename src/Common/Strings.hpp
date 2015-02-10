/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include <QtCore>

namespace AnimationProperties {
	const QString Frames        = "frames";
	const QString FramesNumber  = "framesNumber";
}

namespace Animators {
	const QString Animation     = "AnimatorAnimation";
	const QString ApplyDamage   = "AnimatorApplyDamage";
	const QString Consume       = "AnimatorConsume";
	const QString Die           = "AnimatorDie";
	const QString Move          = "AnimatorMove";
	const QString PhysicsUpdate = "AnimatorPhysicsUpdate";
	const QString Test          = "AnimatorTest";
	const QString UpdatePath    = "AnimatorUpdatePath";
	const QString Regenerate    = "AnimatorRegenerate";
	const QString GoPsycho      = "AnimatorGoPsycho";
	const QString Heal          = "AnimatorHeal";
	const QString Construct     = "AnimatorConstruct";
	const QString EnterBuilding = "AnimatorEnterBuilding";
	const QString LeaveBuilding = "AnimatorLeaveBuilding";
}

namespace Attributes {
	const QString Bullets       = "bullets";           // Weapon
	const QString Faction       = "faction";
	const QString Food          = "food";
	const QString HP            = "hp";
	const QString OffsetX       = "offsetX";
	const QString OffsetY       = "offsetY";
	const QString Psychosis     = "psychosis";
	const QString DelayTime     = "delayTime";         // Item
	const QString Uid           = "uid";
	const QString Units         = "units";
}

namespace Data {
	const QString Animations    = "animations";
	const QString Animators     = "animators";
	const QString Data          = "data";
	const QString Objects       = "objects";
	const QString Properties    = "properties";
}

namespace MapProperties {
	const QString MapDesc       = "mapDesc";
	const QString MapName       = "mapName";
	const QString MapWidth      = "mapWidth";
	const QString MapHeight     = "mapHeight";
}

namespace Resources {
	const QString Animation     = "animation";
	const QString Font          = "font";
	const QString Texture       = "texture";
}

namespace Properties {
	const QString Attack        = "attack";            // base for Unit
	const QString Damage        = "damage";            // Weapon
	const QString DamageControl = "damageControl";     // base for Unit
	const QString DefAnimators  = "defAnimators";
	const QString Defense       = "defense";           // base for Unit
	const QString Dispersion    = "dispersion";        // Weapon
	const QString Encumbrance   = "encumbrance";       // max for Unit
	const QString Engineering   = "engineering";       // base for Unit
	const QString FoodDemand    = "foodDemand";        // base for Unit
	const QString Healing       = "healing";           // base for Unit
	const QString HP            = "hp";                // max for Unit ??
	const QString Ingredients   = "ingredients";       // Item
	const QString MagazineSize  = "magazineSize";      // Weapon
	const QString MovementSpeed = "movementSpeed";     // Unit
	const QString Name          = "name";
	const QString OptimalRange  = "optimalRange";      // Weapon
	const QString Perception    = "perception";        // base for Unit
	const QString Psychosis     = "psychosis";         // max for Unit ??
	const QString Range         = "range";             // Weapon
	const QString Regeneration  = "regeneration";      // Unit
	const QString ReloadTime    = "reloadTime";        // Weapon
	const QString ShotsInterval = "shotsInterval";     // Weapon
	const QString SightRange    = "sightRange";        // base for Unit
	const QString SpawnedType   = "spawnedType";       // Item - Fortification
	const QString Type          = "type";
}

namespace TempData {
	const QString Damage        = "damage";
	const QString IsSelected    = "isSelected";
	const QString State         = "state";
	const QString X             = "x";
	const QString Y             = "y";
}
