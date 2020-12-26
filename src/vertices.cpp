#include "vertices.h"
#include "snakelist.h"

Vertex calcVertices(Node *initialNode, Node *foodNode, int squares){

	float *positions = new float[squares*8];
	unsigned int *vertices = new unsigned int[squares*6];

	Node *curr = initialNode;
	foodNode->next = curr;
	curr = foodNode;
	
	int i = 0;

	while(curr != 0){
		int pindex = i * 8;
		int vindex = i * 6;
		int vertexpos = i * 4;

		positions[pindex]  =  curr->x + 0.005;
		positions[pindex+1] = curr->y + 0.005;
		positions[pindex+2] = curr->x + 0.095;
		positions[pindex+3] = curr->y + 0.005;
		positions[pindex+4] = curr->x + 0.095;
		positions[pindex+5] = curr->y + 0.095;
		positions[pindex+6] = curr->x + 0.005;
		positions[pindex+7] = curr->y + 0.095;

		vertices[vindex]  =  0 + vertexpos;
		vertices[vindex+1] = 1 + vertexpos;
		vertices[vindex+2] = 2 + vertexpos;
		vertices[vindex+3] = 2 + vertexpos;
		vertices[vindex+4] = 3 + vertexpos;
		vertices[vindex+5] = 0 + vertexpos;

		curr = curr->next;
		i++;
	}

	Vertex vert;
	vert.positions = positions;
	vert.vertices = vertices;
	vert.psize = sizeof(float) * 8 * squares;
	vert.vsize = sizeof(unsigned int) * 6 * squares;

	return vert;
}
