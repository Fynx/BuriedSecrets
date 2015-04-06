GameObjects
=======
This module separates the code for logical representations of game objects from the rest of the repository.

While adding new fields to the Object subclass, updating corresponding loadFromJson and saveToJson implementations is required.
Fields xxxUids in Objects are solely for convenience while binding Objects and should not be used afterwards.

Every Object has it's faction.
Faction of faction itself is the factionId of this faction (it might be a factionous and factional faction of factions).
