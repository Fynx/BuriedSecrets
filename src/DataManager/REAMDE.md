DataManager
=======
This module is responsible for loading and saving raw data of objects and resources.

Resource files
------
The main file with the list of all resources is data/ResourcesList.txt. It contains a newline-separated list of
relative (to data/) paths to .res files. Each .res file describes a resource. The format for a .res file is:
```     
Resource name    
Resource type ('Texture' or 'Font')    
Relative path to the resource data
```
