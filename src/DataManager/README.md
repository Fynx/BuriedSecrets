# DataManager

This module is responsible for loading and saving raw data of objects and resources.

## Prototype file

data/prototypes.txt

#### Format

    type
    key value
    key value
    ...

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
```
Resource name
Resource type ('Texture' or 'Font')
Relative path to the resource data
```
