## A Double Linked List (DLL)

Below a graphical repsrenstation of a doubly linked list.

A DLL consists of three items:
- A pointer to the previous entry in the list (or NULL if we are on the first entry of the list)
- A pointer to the next  entry in the list (or NULL if we are on the last entry of the list)
- A pointer to a payload (Can be anything. However, in G10 it will probably be a base, node, attribute or relation)


Graphical representation of a DDL item 

             +---------+
             | prev    | --> Pointer to previous entry in the list
             | payload | --> pointer to the thing we care about
             | next    | --> Pointer to the next entry in the list
             +---------+

And a grpahical representation of a DDL with some items:

             +---------+
    NULL <---| prev    |
             | payload |---> <some payload (node/relation/attribute)>
             | next    |---+
             +---------+   |
                ^          |
        +-------+  +-------+	    
        |          v
        |    +---------+
        +----| prev    |
             | payload |---> <some payload (node/relation/attribute)>
             | next    |---+
             +---------+   |
                ^          |
        +-------+  +-------+
        |          v
        |    +---------+
        +----| prev    |
             | payload |---> <some payload (node/relation/attribute)>
             | next    |---+
             +---------+   |
                ^          |
        +-------+  +-------+
        |          v
        |    +---------+
        +----| prev    |
             | payload |---> <some payload (node/relation/attribute)>
             | next    |---> NULL
             +---------+   
