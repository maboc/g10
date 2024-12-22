## Commands
1. base add attribute <key> <value>
   - add an attribute to the active base
     - key   : the key of the attribute
     - value : the value of the attribute
2. base update attribute <swid> <new key> <new value>
   - Update an attribute of the active base
     - Swid : swid of the attribute which should be updated
     - New key   : the new key of the attribute to be updated
     - new value : the new value of the attribute to be updated
1. base display
   - displays a full base
   - potentially very expensive
2. bases list
   - lists all bases in the system
3. base new
   - creates a new base
4. config display
   - displays the configuration
5. node add
   - add a node to the active base
6. node add attribute <node swid> <key> <value>
   - adds an attribute to a node
   - node is searched on the active base
7. node add relation <node from> <node to>
   - node from is the swid of the node from which the relation is pointing
   - node to is the swid of the node to which this relation is pointing
8. node search <key> <value>
   - search a node based on a key and a value
9. relation add attribute <node> <relation> <key> <value)
   - node is the swid of the node on which the relation is defined
   - relation is the swid of the relation to which the attribute should be added
   - key is the key of the attribute
   - value is the value of the attribute
10. use <swid>
   - uses <swid> as the active base
   - (the base on which operations are executed)
