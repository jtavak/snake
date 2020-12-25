#include "snakelist.h"

SnakeList::SnakeList(){
	initialNode = create_node(-0.8, -0.8);
	push_node(-0.7, -0.8);
	push_node(-0.6, -0.8);
	push_node(-0.5, -0.8);
	push_node(-0.4, -0.8);
	push_node(-0.3, -0.8);
	push_node(-0.2, -0.8);
	push_node(-0.1, -0.8);
	push_node(0.0, -0.8);
	push_node(0.1, -0.8);
	dir = 1;
}

SnakeList::~SnakeList(){
	Node *next;
	while(initialNode != 0){
		next = initialNode->next;
		delete initialNode;
		initialNode = next;
	}
}

void SnakeList::move(bool growing){
	push_node((initialNode->x)+directions[dir][0], (initialNode->y)+directions[dir][1]);
	if(!growing){
		delete_node();
	}
}

void SnakeList::turn(int turn){
	dir += turn;

	if(dir == 4)
		dir = 0;
	else if(dir == -1)
		dir = 3;
	
}

bool SnakeList::game_over(){
	int head_x = initialNode->x;
	int head_y = initialNode->y;

	Node *curr = initialNode;
	while(curr != 0){
		if(curr->x == head_x && curr->y == head_y)
			return true;

		curr = curr->next;
	}

	return false;
}
