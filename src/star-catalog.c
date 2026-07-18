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
        if(scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number between 1 and 9.\n");
            // Clear the input buffer
            while(getchar() != '\n');
            continue;
        }
        switch (choice) {
            case 1:
                // Add object
                struct CelestialObject new_object;
                printf("Enter name, distance (in light-years), type, and discovery year: ");
                if(scanf("%49s %f %19s %d",new_object.name, &new_object.distance_ly,new_object.type, &new_object.discovery_year) == 4) {
                    // Add the new object to the tree
                    if(data_entry(&root, new_object) != 0) {
                        printf("Failed to add the object to the tree.\n");
                    } else {
                        printf("Object added successfully.\n");
                    }
                } else {
                    printf("Error reading input.\n");
                }
                printf("#---------------------------------#\n");
                break;
            case 2:
                // Search by exact distance
                float search_distance;
                printf("Enter the distance to search for: ");
                if(scanf("%f", &search_distance) == 1) {
                    struct msg     *result = search_by_exact_distance(root, search_distance);
                    if(result->node == NULL) {
                        printf("Object with distance %.2f not found.\n", search_distance);
                    } else {
                        printf("Found object: Name: %s, Distance: %.2f ly, Type: %s, Discovery Year: %d\n",
                               (*(result->node))->data.name, (*(result->node))->data.distance_ly, (*(result->node))->data.type, (*(result->node))   ->data.discovery_year);
                    }
                    free(result->node);
                    free(result);
                } else {
                    printf("Error reading input.\n");
                } 
                printf("#---------------------------------#\n");

                break;
            case 3:
                // Display all (Inorder)
                inorderTraversal(root);
                printf("#---------------------------------#\n");
                break;
            case 4:
                // Display level order
                leveorderTraversal(root);
                printf("#---------------------------------#\n");
                break;
            case 5:
                // Search by distance range
                float min_distance, max_distance;
                printf("Searching for objects within the distance range of 0 to 100 light-years:\n");
                scanf("%f %f", &min_distance, &max_distance);
                distance_range_search(root, min_distance, max_distance);
                printf("#---------------------------------#\n");
                break;
            case 6:
                // Delete object
                float delete_distance;
                char delete_name[50];
                printf("Enter the name and distance of the object to delete: ");
                if(scanf("%49s %f", delete_name, &delete_distance) == 2) {
                    if(deleteObj(&root, delete_name, delete_distance) != 0) {
                        printf("Object with name %s and distance %.2f not found.\n", delete_name, delete_distance);
                    } else {
                        printf("Object deleted successfully.\n");
                    }
                } else {
                    printf("Error reading input.\n");
                }
                printf("#---------------------------------#\n");
                break;
            case 7:
                // Save to CSV
                FILE* file = fopen("data/processed/saved_data.csv", "w");
                if (file == NULL) {
                    printf("Could not open file for writing.\n");

                } else {
                    fprintf(file, "Name,Distance_ly,Type,Discovery_Year\n"); // Write header
                    save_to_csv(root, file);
                    fclose(file);
                    printf("Data saved to data/processed/saved_data.csv successfully.\n");
                }
                printf("#---------------------------------#\n");
                break;
            case 8: 
                // Load from CSV
                printf("Enter location of the CSV file to load (e.g., data/processed/saved_data.csv): ");
                char filename[100];
                if(scanf("%99s", filename) == 1) {
                    if (load_data_from_csv(&root, filename) != 0) {
                        printf("Failed to load data from CSV file %s.\n", filename);
                    } else {
                        printf("Data loaded from %s successfully.\n", filename);
                    }
                } else {
                    printf("Error reading input.\n");
                }
                printf("#---------------------------------#\n");
                break;
            case 9:
                // Exit
                printf("Exiting the program.\n");
                return 0;
                break;
            default:
                printf("Invalid choice. Please try again.\n");
    }
    
    }
    freeTree(root); // Free the allocated memory for the tree
    return 0;
}


