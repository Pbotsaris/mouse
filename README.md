# My Mouse
My mouse finds the shortest path in the two dimension maze. 

## Building

Compile:

    $ make

Clean:

    $ make clean

Compile without `fsanitize` for debugging: 

    $ make let_leak


## Creating a maze

    ruby script/make_maze.rb 100 100 "* o12" > map_name.txt

where `*` is obstacle `<space>` is open space, `o` is the path `1` in the entrypoint and `2` is the exit.


## Details on the implementation

This program uses breadth-first search implementation to find the shortest path between entrypoint and exit. 
When a mazed is loaded in, it is handled by the `maze` struct which parses through the file and formats the data to be stored in
a graph data structure. Which square of the map is represented by a node in the graph. 

###  Data structure

Considering this map

             *1***
             *X ** 
             **  *
             ***2*


Let's examine the position `x` as a node in our graph. Looking at its position, this node would be then connected to
four other nodes/edges like so:
     
              top
             -----
             | 1 |
             -----
      left     |    right
      -----  -----  -----
      | * |--| x |--|   | (empty space)
      -----  -----  -----
               |
             -----
             | * |
             -----
            bottom



### Searching

The search algorithm is performed by using a combination of the graph above mentioned and a queue implemented in `queue.c`.
Most of the search algorithm happens in the `graph->seach_path` method. 

The algorithm go through the map, starting from the entrypoint (`1`), adding the node the queue and looking for a clear path on its edges.
When a clear path is found, it repeats the same process until the exist is found or the queue is empty. In this case, path was found.

Note that we mark visited nodes as `visited = true` to not repeat already visted nodes.
