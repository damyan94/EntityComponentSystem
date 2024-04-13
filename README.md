The inspiration comes from wanting to have an ECS to improve data organization and reduce memory fragmentation and my recent experience with Unity Engine

Features:
* Simple API for creation of entities, adding, modifying or removing components
* In theory, fast execution and low memory fragmentation since all component data is stored in contiguous memory

How to: Add a new component class
* Add a new entry to EComponentType
* Add the new component class (copy/paste of an existing component and then rename)
* Change the static const Type in the header to the new entry in EComponentType
* Initialize the new component system in EntityManager::Init()

Notes
* All entities have the Transform component and it should not be removed
* In order to change the maximum number of entities or components, edit the defines in Defines.h
