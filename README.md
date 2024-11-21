## What?
g10 is my attempt to create a network database.
I do not have much theoretical knowledge about graph theory, so naming is different from what is found in textbooks

## Good to know
Nothing in this software is ready for anyone else then me to see it.
Why then have it on public available github? Well..I needed a place where I can park it outside home :-) Preferably on a system which is capable of tracking versions etc. ...GitHub is a usual suspect then I guess 

## Why?
- To improve my c-skills. I'm not very skilled at C so an width project seems a nice way to improve myself.
- Profesionally I'm a Oracle DBA. I really like to explore other fields of databases. Creating my own database seems like a nice opportunity.
- I like the nitty-gritty details of (technical) systems. No better way then to fall in all traps developers allready felled in so many times. (I'm an avid believer in reinventing the wheel over and over again, as a learning exercise.
  
## How?
- There are bases.
- These bases have nodes
- These nodes have attributes
- These nodes have also relations (to other nodes)
- The relations also have attributes

In a lot of writing you may find the term swid. This is a System Wide Identifier. Every item (base/node/relation/attribute) in the system has a unique swid

[Commands](docs/commands.md)


## Commands
Commands that now actually work:
1. base display
   - displays a full base
   - potentially very expensive
2. bases list
   - lists all bases in the system
3. config display
   - displays the configuration
4. node add
   - add a node to the active base
5. node add attribute <node swid> <key> <value>
   - adds an attribute to a node
   - node is searched on the active base
6. node add relation <node from> <node to>
   - node from is the swid of the node from which the relation is pointing
   - node to is the swid of the node to which this relation is pointing
7. node search <key> <value>
   - search a node based on a key and a value
8. relation add attribute <node> <relation> <key> <value)
   - node is the swid of the node on which the relation is defined
   - relation is the swid of the relation to which the attribute should be added
   - key is the key of the attribute
   - value is the value of the attribute
7. use <swid>
   - uses <swid> as the active base
   - (the base on which operations are executed)
