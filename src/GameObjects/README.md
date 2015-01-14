GameObjects
=======
This module separates the code for logical representations of game objects from the rest of the repository.

While adding new fields to the Object subclass, updating corresponding loadFromJson and saveToJson implementations is required.

Every Object has it's faction.
Faction of faction itself is the factionId of this faction (it might be a factionous and factional faction of factions).
