#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define MAX_VERTICES 50
#define INF 1000000000

typedef struct Edge {
    int destination;
    int weight;
    struct Edge *next;
} Edge;

typedef struct {
    int vertices;
    Edge *adj[MAX_VERTICES];
} Graph;

/* Create graph */
void initialize_graph(Graph *graph, int vertices) {
    graph->vertices = vertices;

    for (int i = 0; i < vertices; i++)
        graph->adj[i] = NULL;
}

/* Add directed edge */
void add_edge(Graph *graph, int source, int destination, int weight) {
    Edge *new_edge =
        (Edge *)malloc(sizeof(Edge));

    if (new_edge == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    new_edge->destination = destination;
    new_edge->weight = weight;
    new_edge->next = graph->adj[source];

    graph->adj[source] = new_edge;
}

/* Add undirected edge */
void add_undirected_edge(
    Graph *graph,
    int source,
    int destination,
    int weight
) {
    add_edge(graph, source, destination, weight);
    add_edge(graph, destination, source, weight);
}

/* Display graph */
void display_graph(Graph *graph) {
    printf("\n===== NETWORK GRAPH =====\n");

    for (int i = 0; i < graph->vertices; i++) {
        printf("Node %d: ", i);

        Edge *current = graph->adj[i];

        while (current != NULL) {
            printf("-> %d(%d) ",
                   current->destination,
                   current->weight);

            current = current->next;
        }

        printf("\n");
    }
}

/* Reconstruct path */
void print_path(int parent[], int source, int destination) {
    int path[MAX_VERTICES];
    int count = 0;
    int current = destination;

    while (current != -1 && count < MAX_VERTICES) {
        path[count++] = current;

        if (current == source)
            break;

        current = parent[current];
    }

    if (path[count - 1] != source) {
        printf("No path found.\n");
        return;
    }

    printf("Path: ");

    for (int i = count - 1; i >= 0; i--) {
        printf("%d", path[i]);

        if (i != 0)
            printf(" -> ");
    }

    printf("\n");
}

/* BFS */
void bfs(Graph *graph, int source, int destination) {
    int visited[MAX_VERTICES] = {0};
    int parent[MAX_VERTICES];

    for (int i = 0; i < graph->vertices; i++)
        parent[i] = -1;

    int queue[MAX_VERTICES];
    int front = 0;
    int rear = 0;

    queue[rear++] = source;
    visited[source] = 1;

    int explored = 0;
    int found = 0;

    while (front < rear) {
        int current = queue[front++];
        explored++;

        if (current == destination) {
            found = 1;
            break;
        }

        Edge *edge = graph->adj[current];

        while (edge != NULL) {
            if (!visited[edge->destination]) {
                visited[edge->destination] = 1;
                parent[edge->destination] = current;
                queue[rear++] = edge->destination;
            }

            edge = edge->next;
        }
    }

    printf("\n===== BFS =====\n");
    printf("Explored Nodes: %d\n", explored);

    if (found)
        print_path(parent, source, destination);
    else
        printf("No route found.\n");
}

/* DFS */
int dfs_recursive(
    Graph *graph,
    int current,
    int destination,
    int visited[],
    int parent[],
    int *explored
) {
    visited[current] = 1;
    (*explored)++;

    if (current == destination)
        return 1;

    Edge *edge = graph->adj[current];

    while (edge != NULL) {
        int next = edge->destination;

        if (!visited[next]) {
            parent[next] = current;

            if (dfs_recursive(
                    graph,
                    next,
                    destination,
                    visited,
                    parent,
                    explored))
                return 1;
        }

        edge = edge->next;
    }

    return 0;
}

void dfs(Graph *graph, int source, int destination) {
    int visited[MAX_VERTICES] = {0};
    int parent[MAX_VERTICES];

    for (int i = 0; i < graph->vertices; i++)
        parent[i] = -1;

    int explored = 0;

    int found = dfs_recursive(
        graph,
        source,
        destination,
        visited,
        parent,
        &explored
    );

    printf("\n===== DFS =====\n");
    printf("Explored Nodes: %d\n", explored);

    if (found)
        print_path(parent, source, destination);
    else
        printf("No route found.\n");
}

/* Find minimum distance vertex */
int min_distance(int distance[], int visited[], int vertices) {
    int minimum = INF;
    int index = -1;

    for (int i = 0; i < vertices; i++) {
        if (!visited[i] && distance[i] < minimum) {
            minimum = distance[i];
            index = i;
        }
    }

    return index;
}

/* Dijkstra */
void dijkstra(Graph *graph, int source, int destination) {
    int distance[MAX_VERTICES];
    int visited[MAX_VERTICES] = {0};
    int parent[MAX_VERTICES];

    for (int i = 0; i < graph->vertices; i++) {
        distance[i] = INF;
        parent[i] = -1;
    }

    distance[source] = 0;

    int explored = 0;

    for (int count = 0;
         count < graph->vertices;
         count++) {

        int current =
            min_distance(
                distance,
                visited,
                graph->vertices
            );

        if (current == -1)
            break;

        visited[current] = 1;
        explored++;

        if (current == destination)
            break;

        Edge *edge = graph->adj[current];

        while (edge != NULL) {
            int next = edge->destination;

            if (!visited[next] &&
                distance[current] != INF &&
                distance[current] + edge->weight <
                distance[next]) {

                distance[next] =
                    distance[current] + edge->weight;

                parent[next] = current;
            }

            edge = edge->next;
        }
    }

    printf("\n===== DIJKSTRA =====\n");

    if (distance[destination] == INF) {
        printf("No route found.\n");
        return;
    }

    printf("Shortest Cost: %d\n",
           distance[destination]);

    printf("Explored Nodes: %d\n", explored);

    print_path(parent, source, destination);
}

/* Calculate route cost */
int calculate_path_cost(
    Graph *graph,
    int parent[],
    int source,
    int destination
) {
    int cost = 0;
    int current = destination;

    while (current != source) {

        int previous = parent[current];

        if (previous == -1)
            return -1;

        Edge *edge = graph->adj[previous];

        while (edge != NULL) {
            if (edge->destination == current) {
                cost += edge->weight;
                break;
            }

            edge = edge->next;
        }

        current = previous;
    }

    return cost;
}

/* Compare algorithms */
void compare_algorithms(
    Graph *graph,
    int source,
    int destination
) {
    clock_t start, end;

    printf("\n===== PERFORMANCE COMPARISON =====\n");

    start = clock();

    dijkstra(graph, source, destination);

    end = clock();

    double time_taken =
        ((double)(end - start) /
         CLOCKS_PER_SEC) * 1000.0;

    printf("Dijkstra Runtime: %.6f ms\n",
           time_taken);

    printf("\nBFS and DFS provide traversal-based routes, "
           "while Dijkstra considers edge weights.\n");
}

/* Free graph memory */
void free_graph(Graph *graph) {
    for (int i = 0; i < graph->vertices; i++) {

        Edge *current = graph->adj[i];

        while (current != NULL) {
            Edge *next = current->next;
            free(current);
            current = next;
        }

        graph->adj[i] = NULL;
    }
}

/* Main */
int main() {
    Graph graph;

    initialize_graph(&graph, 10);

    /*
        Example transportation network
        Edge weights represent route cost.
    */

    add_undirected_edge(&graph, 0, 1, 4);
    add_undirected_edge(&graph, 0, 2, 2);
    add_undirected_edge(&graph, 1, 3, 5);
    add_undirected_edge(&graph, 2, 3, 1);
    add_undirected_edge(&graph, 2, 4, 7);
    add_undirected_edge(&graph, 3, 5, 3);
    add_undirected_edge(&graph, 4, 5, 2);
    add_undirected_edge(&graph, 5, 6, 4);
    add_undirected_edge(&graph, 6, 7, 1);
    add_undirected_edge(&graph, 7, 8, 6);
    add_undirected_edge(&graph, 8, 9, 2);
    add_undirected_edge(&graph, 6, 9, 5);

    int choice;
    int source;
    int destination;

    printf("===== ROUTE OPTIMIZATION SYSTEM =====\n");

    while (1) {

        printf("\n===== MENU =====\n");
        printf("1. Display Network\n");
        printf("2. BFS Route\n");
        printf("3. DFS Route\n");
        printf("4. Dijkstra Shortest Route\n");
        printf("5. Compare Algorithms\n");
        printf("6. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice >= 2 && choice <= 5) {

            printf("Enter source node (0-9): ");
            scanf("%d", &source);

            printf("Enter destination node (0-9): ");
            scanf("%d", &destination);

            if (source < 0 || source >= 10 ||
                destination < 0 || destination >= 10) {

                printf("Invalid node.\n");
                continue;
            }
        }

        switch (choice) {

            case 1:
                display_graph(&graph);
                break;

            case 2:
                bfs(&graph, source, destination);
                break;

            case 3:
                dfs(&graph, source, destination);
                break;

            case 4:
                dijkstra(&graph, source, destination);
                break;

            case 5:
                compare_algorithms(
                    &graph,
                    source,
                    destination
                );
                break;

            case 6:
                free_graph(&graph);
                printf("Program terminated.\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}