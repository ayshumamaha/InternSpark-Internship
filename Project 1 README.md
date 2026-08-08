PROJECT 1: LRU CACHE IMPLEMENTATION
Abstract

The LRU Cache Implementation is an advanced C programming project developed to demonstrate efficient data storage and retrieval using a combination of a hash table and a doubly linked list. The system follows the Least Recently Used (LRU) cache replacement strategy, where the least recently accessed entry is automatically removed when the cache reaches its maximum capacity. The project focuses on practical implementation of data structures, pointers, dynamic memory allocation, and algorithmic efficiency.

Introduction

Caching is an important technique used in computing systems to store frequently accessed information for faster retrieval. An LRU cache ensures that recently used information remains available while older unused information is removed when storage becomes limited.

This project implements an LRU cache completely in C without relying on built-in cache structures. A hash table provides efficient key-based searching, while a doubly linked list maintains the order of recently used entries.

Objectives

The main objectives of the project are:

Implement an LRU cache using C.
Apply hash table concepts for efficient searching.
Implement a doubly linked list for usage tracking.
Perform insertion, retrieval, updating, and deletion.
Implement automatic LRU-based eviction.
Track cache hits and misses.
Calculate cache hit ratio.
Practice pointers and dynamic memory management.
Analyze the complexity of cache operations.
Implementation

The cache stores key-value pairs and maintains two important positions: Most Recently Used (MRU) and Least Recently Used (LRU). Whenever an entry is accessed, it is moved to the front of the doubly linked list. When the cache becomes full, the node at the rear of the list is removed.

The hash table allows the program to locate entries efficiently using their keys. Combining these two structures allows the main cache operations to achieve O(1) average-time performance.

Features

The application provides options to insert and update entries, retrieve values, delete entries, display the current cache, view cache statistics, and clear the cache. It also records the total number of requests, successful cache hits, cache misses, and hit ratio.

Applications

LRU caching is commonly used in operating systems, web browsers, database systems, file systems, content delivery systems, and other applications where frequently accessed data needs to be retrieved efficiently.

Conclusion

The project provides practical experience in hash tables, doubly linked lists, pointers, dynamic memory allocation, and algorithmic complexity. It demonstrates how multiple data structures can be combined to develop an efficient real-world system.

Author

M. Ayshwarya
