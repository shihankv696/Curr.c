#ifndef GRAPH_H
#define GRAPH_H

#include "utils.h"
#include "memory.h"

typedef struct adjNode {
    int vertex;
    struct AdjNode *next;
} AdjNode;

typedef struct {
    size_t num_vertices;
    AdjNode **adj_list;
    void **vertex_data;
} Graph;

Graph *graph_create(size_t num_vertices);
void graph_destroy(Graph *g, void (*free_data)(void *));

dbool graph_add_edge(Graph *g, int u, int v);
dbool graph_remove_edge(Graph *g, int u, int v);
dbool graph_set_vertex_data(Graph *g, int v, void *data);
void *graph_get_vertex_data(const Graph *g, int v);

size_t graph_num_vertices(const Graph *g);

#endif