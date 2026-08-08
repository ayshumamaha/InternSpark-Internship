TASK 2: ROUTE OPTIMIZATION SYSTEM
Abstract

The Route Optimization System is an advanced C programming project developed to demonstrate graph-based problem solving and route analysis. The application represents a network using a weighted graph and implements Breadth-First Search (BFS), Depth-First Search (DFS), and Dijkstra's shortest-path algorithm. The project provides practical experience in graph representation, traversal, shortest-path computation, recursion, dynamic memory allocation, and algorithmic complexity.

Introduction

Route optimization is an important computational problem used in transportation, navigation, logistics, robotics, and computer networks. A network can be represented as a graph in which locations are represented as nodes and connections between locations are represented as edges.

This project models such a network using an adjacency-list representation. Different algorithms are then applied to explore the network and determine routes between selected source and destination nodes.

Objectives

The main objectives of the project are:

Represent a network using a graph.
Implement an adjacency-list structure.
Implement BFS traversal.
Implement DFS traversal.
Implement Dijkstra's shortest-path algorithm.
Calculate weighted route costs.
Reconstruct and display selected routes.
Compare different algorithmic approaches.
Measure basic execution time.
Practice dynamic memory allocation.
Implementation

The system represents each location as a graph vertex and each connection as a weighted edge. BFS explores connected nodes level by level, while DFS explores a path deeply before backtracking. Dijkstra's algorithm considers edge weights and determines the minimum-cost route between the selected source and destination.

A parent array is used during shortest-path calculation to reconstruct the final route. The system can therefore display both the route and its associated cost.

Features

The application allows users to display the network, select source and destination nodes, execute BFS and DFS, calculate the shortest weighted route using Dijkstra's algorithm, and compare the behavior of the implemented algorithms.

The program also includes input validation, memory management, route reconstruction, and basic runtime measurement.

Complexity Analysis

BFS and DFS operate in O(V + E) time when an adjacency-list representation is used. The implemented basic version of Dijkstra's algorithm operates approximately in O(V² + E), making it suitable for demonstrating shortest-path computation and algorithmic analysis.

Applications

Graph-based route optimization is used in GPS navigation, railway and airline planning, logistics, network routing, robotics, autonomous vehicles, delivery systems, and game pathfinding.

Conclusion

The project provides practical understanding of graph structures, traversal algorithms, shortest-path algorithms, recursion, pointers, dynamic memory allocation, and complexity analysis. It demonstrates how different algorithms can be applied to solve network routing problems.

Author

M. Ayshwarya
