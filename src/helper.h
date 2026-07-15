#ifndef QUEUE_TREE_H
#define QUEUE_TREE_H



struct  CelestialObject {
    char name[50];
    float distance_ly; // Distance in light-years
    char type[20]; // Type of celestial object (e.g., star, planet, galaxy)
    int discovery_year; // Year of discovery
};

struct Node {
    struct CelestialObject data;
    struct Node* left;
    struct Node* right;
};

int createNode(struct Node** node, struct CelestialObject data);
int data_entry(struct Node** node, struct CelestialObject data);


#endif // QUEUE_TREE_H