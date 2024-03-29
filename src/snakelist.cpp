#include "snakelist.h"
#include <cmath>
#include <cstdlib>

SnakeList::SnakeList(){
	initialNode = create_node(-0.8, -0.8);
	push_node(-0.7, -0.8);

	foodNode = create_node(0.0, 0.0);
	dir = 1;
}

SnakeList::~SnakeList(){
	Node *next;
	while(initialNode != 0){
		next = initialNode->next;
		delete initialNode;
		initialNode = next;
	}
	delete foodNode;
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

bool SnakeList::on_food(){
	if(fabs(initialNode->x - foodNode->x) < 0.001 && fabs(initialNode->y - foodNode->y) < 0.001){
		foodNode->x = float((rand()%20)-10)/10;
		foodNode->y = float((rand()%20)-10)/10;
		return true;
	}
	return false;
}

bool SnakeList::game_over(){
	float head_x = initialNode->x;
	float head_y = initialNode->y;

	Node *curr = initialNode->next;
	while(curr != 0){
		if(curr->x == head_x && curr->y == head_y)
			return true;

		curr = curr->next;
	}

	return false;
}
