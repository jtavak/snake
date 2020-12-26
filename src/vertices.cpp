#include "vertices.h"
#include "snakelist.h"

Vertex* calcVertices(Node *initialNode, Node *foodNode, int squares, Vertex *vert){

	Node *curr = initialNode;
	foodNode->next = curr;
	curr = foodNode;
	
	int i = 0;

	while(curr != 0){
		int pindex = i * 8;
		int vindex = i * 6;
		int vertexpos = i * 4;

		vert->positions[pindex]  =  curr->x + 0.005;
		vert->positions[pindex+1] = curr->y + 0.005;
		vert->positions[pindex+2] = curr->x + 0.095;
		vert->positions[pindex+3] = curr->y + 0.005;
		vert->positions[pindex+4] = curr->x + 0.095;
		vert->positions[pindex+5] = curr->y + 0.095;
		vert->positions[pindex+6] = curr->x + 0.005;
		vert->positions[pindex+7] = curr->y + 0.095;

		vert->vertices[vindex]  =  0 + vertexpos;
		vert->vertices[vindex+1] = 1 + vertexpos;
		vert->vertices[vindex+2] = 2 + vertexpos;
		vert->vertices[vindex+3] = 2 + vertexpos;
		vert->vertices[vindex+4] = 3 + vertexpos;
		vert->vertices[vindex+5] = 0 + vertexpos;

		curr = curr->next;
		i++;
	}

	vert->psize = sizeof(float) * 8 * squares;
	vert->vsize = sizeof(unsigned int) * 6 * squares;

	return vert;
}
