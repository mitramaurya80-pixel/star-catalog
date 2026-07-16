#include <stdio.h>
#include <stdlib.h>
#include "helper.h"
#include <string.h>


int main(){
    struct Node* root = NULL;
    // Load data from CSV file into the binary tree
    if (load_data_from_csv(&root, "data/processed/cleaned_data.csv") != 0) {
        printf("Failed to load data from CSV file.\n");
        return -1;
    }
    inorderTraversal(root);
    free(root); // Free the allocated memory for the tree
    return 0;

}


