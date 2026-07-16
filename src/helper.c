#include <stdio.h>
#include <stdlib.h>
#include "helper.h"
#include <string.h>


int CelestialObject_create(struct CelestialObject** obj, const char* name, float distance_ly, const char* type, int discovery_year) {
    *obj = (struct CelestialObject*)malloc(sizeof(struct CelestialObject));
    if (*obj == NULL) {
        printf("Memory allocation failed for CelestialObject\n");
        return -1; // Memory allocation failed
    }
    strcpy((*obj)->name ,name);
    (*obj)->distance_ly = distance_ly;
    strcpy((*obj)->type ,type);
    (*obj)->discovery_year = discovery_year;

    return 0; // Success
}

void inorderTraversal(struct Node* node) {
    if (node == NULL) {
        return;
    }
    inorderTraversal(node->left);
    printf("Name: %s, Distance: %.2f ly, Type: %s, Discovery Year: %d\n",
           node->data.name, node->data.distance_ly, node->data.type, node->data.discovery_year);
    inorderTraversal(node->right);
}

int createNode(struct Node** node, struct CelestialObject data) {
    *node = (struct Node*)malloc(sizeof(struct Node));
    if (*node == NULL) {
        return -1; // Memory allocation failed
    }
    
    (*node)->data = data;
    (*node)->left = NULL;
    (*node)->right = NULL;
    
    return 0; // Success
}


int data_entry(struct Node** node, struct CelestialObject data) {
    if (*node == NULL) {
        int result = createNode(node, data);
        return result; // Return the result of node creation
    }
    if (data.distance_ly < (*node)->data.distance_ly) {
        return data_entry(&((*node)->left), data);
    }else if (data.distance_ly > (*node)->data.distance_ly) {
        return data_entry(&((*node)->right), data);
    }else {
        // Distances are equal, so use name as a tie-breaker.
        if (strcmp(data.name, (*node)->data.name) < 0)
            return data_entry(&((*node)->left), data);
        else
            return data_entry(&((*node)->right), data);
    }
        
  
}
