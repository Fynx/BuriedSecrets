# DataManager

This module is responsible for loading and saving raw data of objects and resources.


## Prototype file

data/prototypes.js

Each json object in this file describes a prototype;
In each of the prototypes there is a map from string to json value.

#### Example

	{"palace": {
		"type": "building",
		"searchTime": 10
	}}

## Map files

data/maps/*.json

#### Required fields

- "mapName" - unique name of the map

For each object in "objects"
- "type"
- "name"
- "animators" - array
- "x", "y" - coordinates

#### Example

	{
		"mapName": "ExampleMap",
		"objects": {
			"ExampleObject": {
				"type": "building",
				"animators": [
					"AnimatorTest"
				],
				"x": 0.0,
				"y": 0.0
			}
		}
	}

