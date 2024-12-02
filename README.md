# SimpleNavigator_v1.0
CLI Implementation of the s21_graph library for Ubuntu/Macos

![](https://github.com/Apsaraconda/SimpleNavigator_v1.0/blob/main/misc/gif/preview.gif)

## Basic properties:

Graphs must meet the following requirements:
- Edge weights are natural numbers only.
- There may be loops.
- Weights can be different on all edges.
- Only a non-zero connected graph.


Implementation of the s21_graph library:  
* The library developed in C++ language of C++17 standard.
* The library represented as a `Graph` class that stores information about the graph using an **adjacency matrix**.
* The program builds with Makefile.
* The class `Graph` contains the following public methods:
    + `LoadGraphFromFile(string filename)` — loading a graph from a file in the adjacency matrix format.
    + `ExportGraphToDot(string filename)`- exporting a graph to a dot file.

Implementation of the s21_graph_algorithms library:  
* The library developed in C++ language of C++17 standard.
* The class ` GraphAlgorithms ` contains the following public methods:
    + `DepthFirstSearch(Graph &graph, int start_vertex)` — a *non-recursive* depth-first search in the graph from a given vertex. The function returns an array that contains the traversed vertices in the order they were traversed. When implementing this function, used the *self-written* data structure **stack**.
    + `BreadthFirstSearch(Graph &graph, int start_vertex)` — breadth-first search in the graph from a given vertex. The function returns an array that contains the traversed vertices in the order they were traversed. When implementing this function, used the *self-written* data structure **queue**.
* There is *self-written* helper classes `Stack` and `Queue`. These classes contains the following methods:
    + `Stack()` — creating an empty stack;
    + `Queue()` — creating an empty queue;
    + `Push(value)` — adding an element to the stack/queue;
    + `Pop()` — getting an element from the stack/queue followed by its removal from the stack/queue;
    + `Top()` — getting an element from the stack without its removal from the stack;
    + `Front()` — getting the first element from the queue without its removal from the queue;
    + `Back()` — getting the last element from the queue without its removal from the queue.

*Vertex numbers start from 1.*

## Finding the shortest paths in a graph

* There is two methods in the `GraphAlgorithms` class:
    + `GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2)` — searching for the shortest path between two vertices in a graph using *Dijkstra's algorithm*. The function accepts as input the numbers of two vertices and returns a numerical result equal to the smallest distance between them.
    + `GetShortestPathsBetweenAllVertices(Graph &graph)` — searching for the shortest paths between all pairs of vertices in a graph using the *Floyd-Warshall algorithm*. As a result, the function returns the matrix of the shortest paths between all vertices of the graph.

## Finding the minimum spanning tree

* There is a method in the `GraphAlgorithms` class:
    + `GetLeastSpanningTree(Graph &graph)` — searching for the minimal spanning tree in a graph using *Prim's algorithm*. As a result, the function returns the adjacency matrix for the minimal spanning tree.

## Traveling salesman problem

* There is a method to the `GraphAlgorithms` class:
    + `SolveTravelingSalesmanProblem(Graph &graph)` — solving the traveling salesman's problem using the *ant colony algorithm*.
The method finds the shortest path that goes through all vertices of the graph at least once, followed by a return to the original vertex. As a result, the function returns the `TsmResult` structure described below:
    ```cpp
    struct TsmResult {
        std::vector<int> vertices;    // an array with the route you are looking for (with the vertex traverse order).
        double distance;  // the length of this route
    }
    ``` 

*If it is impossible to solve the problem with a given graph, the program outputs an error.*

## Console interface

* The main program is a console application for testing the functionality of the implemented s21_graph and s21_graph_algorithms libraries. 
* The console interface provides the following functionality:
    1. Load the original graph from a file.
    2. Traverse the graph in breadth and print the result to the console.   
    3. Traverse the graph in depth and print the result to the console.
    4. Find the shortest path between any two vertices and print the result to the console.
    5. Find the shortest paths between all pairs of vertices in the graph and print the result matrix to the console.
    6. Search for the minimum spanning tree in the graph and print the resulting adjacency matrix to the console.
    7. Solve the Salesman problem, with output of the resulting route and its length to the console.
    8. Display a comparison of the speed of solving the Salesman problem using three algorithms: ant colony, greedy algorithm and brute force.";
## Comparison of methods for solving the traveling salesman problem

* The program is able to perform a comparison of speed of the three algorithms (the ant colony algorithm, greedy algorithm and brute force algorithm):
    + The study starts for a graph that was previously loaded from a file.
    + As part of the study the program keeps track of the time it took to solve the salesman's problem `N` times in a row, by each of the algorithms. Where `N` is set from the keyboard.
    + The results of the time measurement displays in the console in microseconds.

*Example:* For `N = 1000` it will measure how long it will take to solve the traveling salesman problem 1000 times for the current given graph by an ant colony algorithm, greedy algorithm and brute force algorithm.

## Compilation:

Requirements:
+ Ubuntu or MacOS.
+ gcc v.12+.
+ make

Use "make" command:
```
make all
```
or
```
make app
```
## Uninstall:
```
make clean
```
Or delete app's manually.

## Run:
```
make run
```
Or manually open "SimpleNavigator" file.
