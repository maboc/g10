## A Double Linked List (DLL)

Below a graphical repsrenstation of a doubly linked list.

A DLL consists of three items:
- A pointer to the previous entry in the list (or NULL if we are on the first entry of the list)
- A pointer to the next  entry in the list (or NULL if we are on the last entry of the list)
- A pointer to a payload (Can be anything. HOwever, in G10 it will probably be a base, node, attribute or relation)


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
