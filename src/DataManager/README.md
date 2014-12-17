# DataManager

This module is responsible for loading and saving raw data of objects and resources.


## Prototype file

data/prototypes.txt

#### Format

    type
    key value
    key value
    ...

Where 'value' is
- an int: 123
- a string: string
- a map from strings to strings: [key value, key value, ...]

Lines starting with '#' shall be ignored.

Warning:
Every prototype must have a non-empty field with key name and string as a value. Otherwise the prototype is invalid!

#### Example

    unit
    name SampleUnit
    attack 10
    defense 10
    hp 100
    psychosis 100
    healing 5


## Resource files

The main file with the list of all resources is data/ResourcesList.txt. It contains a newline-separated list of
relative (to data/) paths to .res files. Each .res file describes a resource. The format for a .res file is:

	Resource name
	Resource type ('Texture' or 'Font')
	Relative path to the resource data


## Map files

#### Format

	MapName
	BackgroundTextureName

	objectA
	animator animator ...
	key value
	key value
	...

	objectB
	animator animator ...
	key value
	key value
	...

Lines starting with '#' shall be ignored.

EVERY object must have at least one animator (TODO).
