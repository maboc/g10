## A Double Linked List (DLL)

Below a graphical repsrenstation of a doubly linked list.


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
