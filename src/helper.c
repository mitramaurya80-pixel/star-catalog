#include <stdio.h>
#include <stdlib.h>
#include "../include/helper.h"
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
    printf("Name: %s, Distance: %.3f ly, Type: %s, Discovery Year: %d\n",
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
        free(obj); // Free the allocated memory for obj after insertion

    }
    fclose(file);
    return 0; // Success

}

struct msg * search_by_exact_distance(struct Node* node, float distance_ly) {
    struct Node* prev = NULL;
    struct msg* msg_=(struct msg*)malloc(sizeof(struct msg));
    if(msg_==NULL){
        printf("Memory allocation failed for msg\n");
        return NULL; // Memory allocation failed
    }
   
    struct Node* current = node;
    while(current !=NULL && current->data.distance_ly != distance_ly) {
        prev = current;
        if(distance_ly < current->data.distance_ly) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    if(current != NULL) {
        printf("Found: Name: %s, Distance: %.3f ly, Type: %s, Discovery Year: %d\n",
               current->data.name, current->data.distance_ly, current->data.type, current->data.discovery_year);
    }else{
        printf("Object with distance %.2f not found.\n", distance_ly);
    }

    msg_->node =(struct Node**)malloc(sizeof(struct Node*));
    if(msg_->node==NULL){
        free(msg_);
        return NULL; // Memory allocation failed
    }
    *(msg_->node) = current;
    msg_->prev = prev;
    return msg_;

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
static struct Node* findMin(struct Node* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}
static struct Node* delete_recursive(struct Node* root,const char* name, float distance_ly,int* found) {
    if (root == NULL) {
        return root; // Not found
    }
    if (distance_ly < root->data.distance_ly) {
        root->left = delete_recursive(root->left, name, distance_ly, found);
    } else if (distance_ly > root->data.distance_ly) {
        root->right = delete_recursive(root->right, name, distance_ly, found);
    } else {
        // Found the node to be deleted
        int name_match = strcmp(name, root->data.name);
        if (name_match<0) {
            // Names do not match, continue searching in the right subtree
            root->left = delete_recursive(root->left, name, distance_ly, found);
        }else if (name_match>0) {
            // Names do not match, continue searching in the left subtree
            root->right = delete_recursive(root->right, name, distance_ly, found);
        } else {
            *found = 1; // Mark as found
        

        // Node with only one child or no child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        // Node with two children: Get the inorder successor (smallest in the right subtree)
        struct Node* temp = findMin(root->right);
        // Copy the inorder successor's content to this node
        root->data = temp->data;
        // Delete the inorder successor
        root->right = delete_recursive(root->right, temp->data.name, temp->data.distance_ly, found);
    }
    }

    return root;
}
int deleteObj(struct Node** root,const char* name, float distance_ly) {
    if(*root==NULL){
        return 1; // Not found
    }
    int found = 0;
    *root = delete_recursive(*root, name, distance_ly, &found);

    return found ? 0 : 1; // Return 0 if found and deleted, 1 if not found
}

int save_to_csv(struct Node* node, FILE* file) {
    if (node == NULL) {
        return 1; // Not found
    }
    fprintf(file, "%s,%.3f,%s,%d\n", node->data.name, node->data.distance_ly, node->data.type, node->data.discovery_year);
    save_to_csv(node->left, file);
    save_to_csv(node->right, file);
    return 0; // Success
}

int freeTree(struct Node* node) {
    if (node == NULL) {
        return 1; // Not found
    }
    freeTree(node->left);
    freeTree(node->right);
    free(node);
    return 0; // Success
}
