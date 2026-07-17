#include <stdio.h>
#include <stdlib.h>
#include "helper.h"
#include <string.h>

static struct queueNode* front=NULL;
static struct queueNode* rear=NULL;


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

int load_data_from_csv(struct Node** root, const char* filename){
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return -1; // File opening failed
    }
    char lines[256];
    // Skip the header line
    fgets(lines, sizeof(lines), file);
    while(fgets(lines,sizeof(lines),file)){
        struct CelestialObject* obj;
        char name[50];
        float distance_ly;
        char type[20];
        int discovery_year;

        if (sscanf(lines, "%49[^,],%f,%19[^,],%d", name, &distance_ly, type, &discovery_year) != 4) {
            printf("Invalid line format: %s", lines);
            continue; // Skip to the next line
        }

        if (CelestialObject_create(&obj, name, distance_ly, type, discovery_year) != 0) {
            printf("Failed to create celestial object from line: %s", lines);
            continue; // Skip to the next line
        }

        if (data_entry(root, *obj) != 0) {
            printf("Failed to insert celestial object into the tree from line: %s", lines);
            free(obj); // Free the allocated memory for obj
            continue; // Skip to the next line
        }

    }
    return 0; // Success

}

int search_by_exact_distance(struct Node* node, float distance_ly) {
    if (node == NULL) {
        return 1; // Not found
    }
    if (node->data.distance_ly == distance_ly) {
        printf("Found: Name: %s, Distance: %.2f ly, Type: %s, Discovery Year: %d\n",
               node->data.name, node->data.distance_ly, node->data.type, node->data.discovery_year);
        return 0; // Found
    } else if (distance_ly < node->data.distance_ly) {
        return search_by_exact_distance(node->left, distance_ly);
    } else {
        return search_by_exact_distance(node->right, distance_ly);
    }

}
static int enqueue(struct Node* node){

    if(node==NULL){
        printf("x--------------Empety tree---------------x");
        return 1;
    }
    if(front==NULL){
        front=(struct queueNode*)malloc(sizeof(struct queueNode));
        front->treeNode=node;
        front->next=NULL;
        rear=front;
    }else{
        struct queueNode* newNode=(struct queueNode*)malloc(sizeof(struct queueNode));
        newNode->treeNode=node;
        newNode->next=NULL;
        rear->next=newNode;
        rear=newNode;
    }
    return 0;

}
static int dequeue(){
    if(front==NULL){
        printf("Queue is empty. Cannot dequeue.\n");
        return 1;
    }
    struct queueNode* temp=front;
    front=front->next;
    free(temp);
    if(front==NULL){
        rear=NULL;
    }
    return 0;
}
int leveorderTraversal(struct Node* node){
    if(node==NULL){
        printf("Tree is empty.\n");
        return 1;
    }
    enqueue(node);
    while(front!=NULL){
        struct Node* current=front->treeNode;
        printf("Name: %s, Distance: %.2f ly, Type: %s, Discovery Year: %d\n",
               current->data.name, current->data.distance_ly, current->data.type, current->data.discovery_year);
        if(current->left!=NULL){
            enqueue((current->left));
        }
        if(current->right!=NULL){
            enqueue((current->right));
        }
        dequeue();
    }

    return 0;
}
int distance_range_search(struct Node* node, float min_distance, float max_distance) {
    if (node == NULL) {
        return 1; // Not found
    }
    if (node->data.distance_ly >= min_distance && node->data.distance_ly <= max_distance) {
        printf("Found: Name: %s, Distance: %.2f ly, Type: %s, Discovery Year: %d\n",
               node->data.name, node->data.distance_ly, node->data.type, node->data.discovery_year);
    }
    distance_range_search(node->left, min_distance, max_distance);
    distance_range_search(node->right, min_distance, max_distance);
    return 0; // Success
}
int deleteObj(struct Node** root, float distance_ly) {
    if(*root==NULL){
        return 1; // Not found
    }
    while(1){
        if(distance_ly < (*root)->data.distance_ly){
            root = &((*root)->left);
        }else if(distance_ly > (*root)->data.distance_ly){
            root = &((*root)->right);
        }else{
            strcmp((*root)->data.name, (*root)->data.name) == 0; // Check for name match
            
        }
    }
    struct Node* temp = *root;
    if(temp->left == NULL){
        *root = temp->right;
    }else if(temp->right == NULL){
        *root = temp->left;
    }else{
        struct Node* successor = temp->right;
        while(successor->left != NULL){
            successor = successor->left;
        }
        temp->data = successor->data;
        deleteObj(&temp->right, successor->data.distance_ly);
    }
    free(temp);
    return 0; // Success
}