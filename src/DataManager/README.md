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


## Resource files

TODO update json!

Deprecation:

The main file with the list of all resources is data/ResourcesList.txt. It contains a newline-separated list of
relative (to data/) paths to .res files. Each .res file describes a list of resources. Any resources file can contain any number of resources of any supported types.
The format of Texture or Font in a resource file is as follows:


	Resource name
	Resource type ('Texture' or 'Font')
	Relative path to the resource data


Another type of resource is an animation. The format for an animation is:
```
Animation name
A string 'Animation'
State no_frames id11 id12 id13 ... id21 id22 id23 ... id81 ...
```
where idxy are names of the textures loaded from any resource. All animations can have frames for different amount of directions, but it is verified by the Graphics during runtime
what number is needed. In our current implementation, with isometric view, we need 8 directions for every animation.
There must be the same number of frames for every direction (no_frames).
The State in animation is an Object::State name for which the animation should be displayed.


## Map files

data/maps/*.json

#### Required fields

- "mapName" - unique name of the map
- "mapDesc" - path to description of the map (grid, etc.)

For each object in "objects"
- "type"
- "name"
- "animators" - array
- "x", "y" - coordinates

#### Example

	{
		"mapName": "ExampleMap",
		"mapDesc": "ExampleMap.wtf",
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

