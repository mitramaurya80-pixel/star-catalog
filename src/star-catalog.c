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
    
    while(1){
        /*1. Add object
        2. Search by exact distance
        3. Display all (Inorder)
        4. Display level order
        5. Search by distance range
        6. Delete object
        7. Save to CSV
        8. Load from CSV
        9. Exit*/
        printf("\nMenu:\n");
        printf("1. Add object\n");
        printf("2. Search by exact distance\n");
        printf("3. Display all (Inorder)\n");
        printf("4. Display level order\n");
        printf("5. Search by distance range\n");
        printf("6. Delete object\n");
        printf("7. Save to CSV\n");
        printf("8. Load from CSV\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                // Add object
                struct CelestialObject new_object;
                printf("Enter name, distance (in light-years), type, and discovery year: ");
                if(scanf("%49s %f %19s %d",&new_object.name, &new_object.distance_ly,&new_object.type, &new_object.discovery_year) == 4) {
                    // Add the new object to the tree
                    if(data_entry(&root, new_object) != 0) {
                        printf("Failed to add the object to the tree.\n");
                    } else {
                        printf("Object added successfully.\n");
                    }
                } else {
                    printf("Error reading input.\n");
                }
                break;
            case 2:
                // Search by exact distance
                float search_distance;
                printf("Enter the distance to search for: ");
                if(scanf("%f", &search_distance) == 1) {
                    if (search_by_exact_distance(root, search_distance) != 0) {
                        printf("No object found at the specified distance.\n");
                    }
                } else {
                    printf("Error reading input.\n");
                }

                break;
            case 3:
                // Display all (Inorder)
                inorderTraversal(root);
                break;
            case 4:
                // Display level order
                leveorderTraversal(root);
                break;
            case 5:
                // Search by distance range
                float min_distance, max_distance;
                printf("Searching for objects within the distance range of 0 to 100 light-years:\n");
                scanf("%f %f", &min_distance, &max_distance);
                distance_range_search(root, min_distance, max_distance);
                break;
            case 6:
                // Delete object
                float delete_distance;
                printf("Enter the distance of the object to delete: ");
                scanf("%f", &delete_distance);
                if (deleteObj(&root, delete_distance) != 0) {
                    printf("Object not found or could not be deleted.\n");
                } else {
                    printf("Object deleted successfully.\n");
                }
                break;
            case 7:
                // Save to CSV
                break;
            case 8: 
                // Load from CSV
                break;
            case 9:
                // Exit
                break;
            default:
                printf("Invalid choice. Please try again.\n");
    }
    
    }
    free(root); // Free the allocated memory for the tree
    return 0;
}


