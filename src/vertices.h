#ifndef VERTICES_H
#define VERTICES_H

#include "snakelist.h"

typedef struct{
	float *positions;
	unsigned int *vertices;
	int psize, vsize;
} Vertex;

Vertex* calcVertices(Node *initialNode, Node *foodNode, int squares, Vertex *vert);

#endif
