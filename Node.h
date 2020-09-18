#ifndef NODE
#define NODE

class Node {
public:	
    Node(char tile, Node* next);
	Node(Node& other);
    
    char tile;
    Node* next;
};

#endif //NODE