#ifndef SNAKELIST_H
#define SNAKELIST_H

// UP- 0, RIGHT- 1, DOWN- 2, LEFT- 3
const float directions[4][2] = {{0, 0.1}, {0.1, 0}, {0, -0.1}, {-0.1, 0}};

typedef struct Node{
	float x, y;
	Node *next;
} Node;

class SnakeList{
private:
	Node* create_node(float x, float y){
		Node *node = new Node();
		node->x = x;
		node->y = y;
		node->next = 0;
		
		return node;
	}

	void push_node(float x, float y){
		Node *node = create_node(x, y);
		node->next = initialNode;
		initialNode = node;
	}

	void delete_node(){
		Node *curr = initialNode;
		while(curr->next->next != 0){
			curr = curr->next;
		}
		delete curr->next;
		curr->next = 0;
	}

public:
	Node *initialNode;
	Node *foodNode;
	int dir;
	
	SnakeList();
	~SnakeList();

	void move(bool growing);
	void turn(int turn);
	bool on_food();
	bool game_over();
};

#endif
