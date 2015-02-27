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
	const QString Assemble      = "AnimatorAssemble";
	const QString EnterBuilding = "AnimatorEnterBuilding";
	const QString LeaveBuilding = "AnimatorLeaveBuilding";
	const QString Attack        = "AnimatorAttack";
	const QString Weapon        = "AnimatorWeapon";
	const QString UpdateFOV     = "AnimatorUpdateFOV";
	const QString NearCamp      = "AnimatorNearCamp";
	const QString WatchTarget   = "AnimatorWatchTarget";
}

namespace Attributes {                                 // Converted into class fields
	const QString Attitude      = "attitude";
	const QString Command       = "command";
	const QString DelayTime     = "delayTime";         // Item
	const QString Equipment     = "equipment";
	const QString Faction       = "faction";
	const QString Food          = "food";
	const QString HP            = "hp";
	const QString Items         = "items";
	const QString OffsetX       = "offsetX";
	const QString OffsetY       = "offsetY";
	const QString Psychosis     = "psychosis";
	const QString Relations     = "relations";
	const QString Slots         = "slots";
	const QString Uid           = "uid";
	const QString Units         = "units";
	const QString UsesLeft      = "UsesLeft";          // Item
}

namespace Data {
	const QString Animations    = "animations";
	const QString Animators     = "animators";
	const QString Data          = "data";
	const QString Objects       = "objects";
	const QString Properties    = "properties";
}

namespace Effects {
	const QString Selection     = "SelectionEffect";	// Unit selection.
	const QString BasePolygon   = "BasePolygonEffect";	// Display base polygon and other debug info.
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
	const QString Image         = "image";
	const QString Texture       = "texture";
}

namespace Properties {                                 // for Prototypes
	const QString Age           = "age";               // base for Unit
	const QString Assemblable   = "assemblable";
	const QString Attack        = "attack";            // base for Unit
	const QString Avatar        = "avatar";            // base for Unit
	const QString Background    = "background";        // base for Unit
	const QString BaseCentre    = "baseCentre";
	const QString BasePolygon   = "basePolygon";
	const QString BaseRadius    = "baseRadius";
	const QString BigDefBonus   = "bigDefBonus";       // Bonus from location
	const QString BigAttBonus   = "bigAttBonus";       // Bonus from location
	const QString BigRangeBonus = "bigRangeBonus";     // Bonus from location
	const QString Capacity      = "capacity";
	const QString Damage        = "damage";            // Weapon
	const QString DamageControl = "damageControl";     // base for Unit
	const QString DefAnimators  = "defAnimators";
	const QString Defense       = "defense";           // Armor
	const QString Dispersion    = "dispersion";        // Weapon
	const QString Encumbrance   = "encumbrance";       // max for Unit
	const QString Engineering   = "engineering";       // base for Unit
	const QString FireRate      = "fireRate";
	const QString FoodDemand    = "foodDemand";        // base for Unit
	const QString Healing       = "healing";           // base for Unit
	const QString HP            = "hp";                // max for Unit ??
	const QString Ingredients   = "ingredients";       // Item
	const QString ItemType      = "itemType";
	const QString MagazineSize  = "magazineSize";      // Weapon
	const QString MovementSpeed = "movementSpeed";     // Unit
	const QString Name          = "name";
	const QString OptimalRange  = "optimalRange";      // Weapon
	const QString Perception    = "perception";        // base for Unit
	const QString Picture       = "picture";           // base for Unit
	const QString Profession    = "profession";        // base for Unit
	const QString Psychosis     = "psychosis";         // max for Unit ??
	const QString Quote         = "quote";             // base for Unit
	const QString Range         = "range";             // Weapon
	const QString Regeneration  = "regeneration";      // Unit
	const QString ReloadTime    = "reloadTime";        // Weapon
	const QString ShotsInterval = "shotsInterval";     // Weapon
	const QString SightRange    = "sightRange";        // base for Unit
	const QString SmallDefBonus = "smallDefBonus";       // Bonus from location
	const QString SpawnedType   = "spawnedType";       // Item - Fortification
	const QString Transparent   = "transparent";
	const QString Type          = "type";
	const QString Weight        = "weight";
}

namespace Slots {
	const QString Armor         = "armor";
	const QString Fortification = "fortification";
	const QString Invalid       = "invalid";
	const QString Medicament    = "medicament";
	const QString Perception    = "perception";
	const QString Tool          = "tool";
	const QString Weapon        = "weapon";
}

namespace States {
	const QString Attack    = "Attack";
	const QString Delay     = "Delay";
	const QString Heal      = "Heal";
	const QString Idle      = "Idle";
	const QString Inside    = "Inside";
	const QString Invalid   = "Invalid";
	const QString Run       = "Run";
	const QString RunAttack = "RunAttack";
	const QString Shoot     = "Shoot";
}

namespace TempData {                                   // kept in GO's map
	const QString Damage        = "damage";
	const QString IsSelected    = "isSelected";
	const QString NearCamp      = "nearCamp";
	const QString ShotAngle     = "shotAngle";
	const QString State         = "state";
	const QString X             = "x";
	const QString Y             = "y";
}

namespace Types {
	const QString Invalid   = "invalid";
	const QString Item      = "item";
	const QString Equipment = "equipment";
	const QString Faction   = "faction";
	const QString Journal   = "journal";
	const QString Location  = "location";
	const QString Unit      = "unit";
}
