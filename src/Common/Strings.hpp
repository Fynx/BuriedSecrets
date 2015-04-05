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
	const QString Animation        = "AnimatorAnimation";
	const QString ApplyDamage      = "AnimatorApplyDamage";
	const QString Consume          = "AnimatorConsume";
	const QString Die              = "AnimatorDie";
	const QString Move             = "AnimatorMove";
	const QString PhysicsUpdate    = "AnimatorPhysicsUpdate";
	const QString Test             = "AnimatorTest";
	const QString UpdatePath       = "AnimatorUpdatePath";
	const QString Regenerate       = "AnimatorRegenerate";
	const QString GoPsycho         = "AnimatorGoPsycho";
	const QString Heal             = "AnimatorHeal";
	const QString Assemble         = "AnimatorAssemble";
	const QString EnterBuilding    = "AnimatorEnterBuilding";
	const QString LeaveBuilding    = "AnimatorLeaveBuilding";
	const QString Attack           = "AnimatorAttack";
	const QString Weapon           = "AnimatorWeapon";
	const QString UpdateFOV        = "AnimatorUpdateFOV";
	const QString NearCamp         = "AnimatorNearCamp";
	const QString WatchTarget      = "AnimatorWatchTarget";
	const QString Disassemble      = "AnimatorDisassemble";
	const QString Effects          = "AnimatorEffects";
	const QString MobAttitude      = "AnimatorMobAttitude";
	const QString BuildingDmg      = "AnimatorBuildingDmg";
	const QString AggressiveAtt    = "AnimatorAggressiveAtt";
	const QString Result           = "AnimatorResult";
	const QString GuardAtt         = "AnimatorGuardAtt";
	const QString BAggressiveAtt   = "AnimatorBAggressiveAtt";
	const QString NearestEnemy     = "AnimatorNearestEnemy";
	const QString KickOut          = "AnimatorKickOut";
}

namespace Attributes {                                 // Converted into class fields
	const QString Attitude         = "attitude";
	const QString CampId           = "campId";			// Faction, converted to pointer
	const QString CampRange        = "campRange";		// Faction
	const QString Command          = "command";
	const QString DelayTime        = "delayTime";       // Item
	const QString Equipment        = "equipment";
	const QString ExitX            = "exitX";           // Location, optional exitPoint
	const QString ExitY            = "exitY";
	const QString Faction          = "faction";
	const QString Food             = "food";
	const QString HP               = "hp";
	const QString Items            = "items";
	const QString PatrolRoute      = "patrolRoute";
	const QString Psychosis        = "psychosis";
	const QString Relations        = "relations";
	const QString SearchDifficulty = "searchDifficulty";
	const QString Slots            = "slots";
	const QString Uid              = "uid";
	const QString Units            = "units";
	const QString UsesLeft         = "UsesLeft";          // Item
}

namespace Data {
	const QString Animators     = "animators";
	const QString Data          = "data";
	const QString Objects       = "objects";
	const QString Properties    = "properties";
	const QString Path          = "path";
	const QString Rows          = "rows";
	const QString Columns       = "columns";
	const QString Textures      = "textures";
	const QString TextureSet    = "textureSet";
}

namespace Effects {
	const QString BasePolygon     = "BasePolygonEffect";	// Display base polygon and other debug info.
	const QString EnterCommand    = "EnterCommand";
	const QString FriendlyCommand = "FriendlyCommand";
	const QString HostileCommand  = "HostileCommand";
	const QString MoveCommand     = "MoveCommand";
	const QString Selection       = "SelectionEffect";	// Unit selection.
	const QString Shot            = "ShotEffect";
	const QString Antipsychosis   = "AntipsychosisEffect";
	const QString ShowPath        = "ShowPathEffect";
}

namespace MapProperties {
	const QString MapDesc       = "mapDesc";
	const QString MapName       = "mapName";
	const QString MapWidth      = "mapWidth";
	const QString MapHeight     = "mapHeight";
}

namespace Resources {
	const QString Font          = "font";
	const QString Image         = "image";
	const QString Texture       = "texture";
	const QString ArrowDownCursor = "ArrowDown";
	const QString TextureSet    = "TextureSet";
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
	const QString Description   = "description";       // Item description
	const QString DefAnimators  = "defAnimators";
	const QString Defense       = "defense";           // Armor
	const QString Dispersion    = "dispersion";        // Weapon
	const QString Encumbrance   = "encumbrance";       // max for Unit
	const QString Engineering   = "engineering";       // base for Unit
	const QString FoodDemand    = "foodDemand";        // base for Unit
	const QString Healing       = "healing";           // base for Unit
	const QString HP            = "hp";                // max for Unit
	const QString Ingredients   = "ingredients";       // Item
	const QString ItemTypes     = "itemTypes";
	const QString MagazineSize  = "magazineSize";      // Weapon
	const QString MovementSpeed = "movementSpeed";     // Unit
	const QString Name          = "name";
	const QString Obstacle      = "obstacle";
	const QString OptimalRange  = "optimalRange";      // Weapon
	const QString OffsetX       = "offsetX";           // For building
	const QString OffsetY       = "offsetY";           // For building
	const QString Perception    = "perception";        // base for Unit
	const QString Picture       = "picture";           // base for Unit
	const QString Profession    = "profession";        // base for Unit
	const QString Psychosis     = "psychosis";         // max for Unit ??
	const QString Quote         = "quote";             // base for Unit
	const QString Quality       = "quality";           // Item quality
	const QString Range         = "range";             // Weapon
	const QString Regeneration  = "regeneration";      // Unit
	const QString ReloadTime    = "reloadTime";        // Weapon
	const QString ShotsInterval = "shotsInterval";     // Weapon
	const QString SightRange    = "sightRange";        // base for Unit
	const QString Slots         = "slots";
	const QString SmallDefBonus = "smallDefBonus";     // Bonus from location
	const QString SpawnedType   = "spawnedType";       // Item - Fortification
	const QString Transparent   = "transparent";
	const QString Type          = "type";
	const QString Weight        = "weight";
}

namespace BasicPrototypes {
	const QString BasicEquipment = "BasicEquipment";
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
	const QString RunBase   = "RunBase";
	const QString IdleBase  = "IdleBase";
	const QString Shoot     = "Shoot";
}

namespace TempData {                                   // kept in GO's map
	const QString Damage        = "damage";
	const QString NearCamp      = "nearCamp";
	const QString NearestDist   = "nearestDist";
	const QString State         = "state";
	const QString X             = "x";
	const QString Y             = "y";
}

namespace Types {
	const QString Invalid     = "invalid";
	const QString Item        = "item";
	const QString Environment = "environment";
	const QString Equipment   = "equipment";
	const QString Faction     = "faction";
	const QString Journal     = "journal";
	const QString Location    = "location";
	const QString Unit        = "unit";
}

namespace ItemTypes {
	const QString Armor         = "Armor";
	const QString Fortification = "Fortification";
	const QString Invalid       = "Invalid";
	const QString Junk          = "Junk";
	const QString Medicament    = "Medicament";
	const QString Perception    = "Perception";
	const QString Tool          = "Tool";
	//Weapons
	const QString AssaultRifle  = "Assault rifle";
	const QString DualPistols   = "Dual pistols";
	const QString Melee         = "Melee";
	const QString Pistol        = "Pistol";
	const QString Shotgun       = "Shotgun";
	const QString SniperRifle   = "Sniper rifle";
}
