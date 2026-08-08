# Project 1: LRU Cache Implementation

## Project Overview

This project is a menu-driven C application that implements a Least Recently Used (LRU) Cache. It uses a hash table for fast key-based lookup and a doubly linked list to maintain the order of recently accessed cache entries. The system automatically removes the least recently used item when the cache reaches its capacity.

## Features

- Insert key-value pairs into the cache
- Retrieve values using keys
- Automatic LRU-based eviction
- Delete cache entries
- Display cache contents
- Track cache hits and misses
- Calculate cache hit ratio
- Clear the cache
- Dynamic memory management
- Input validation and error handling

## Technologies Used

- C
- GCC
- Hash Table
- Doubly Linked List
- Dynamic Memory Allocation
- Git & GitHub

## Files

- `project1_lru.c` – Main C program
- `README.md` – Project documentation

## Run

```bash
gcc project1_lru.c -o project1
./project1
