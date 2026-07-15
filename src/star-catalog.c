#include <stdio.h>
#include <stdlib.h>
#include "helper.h"
#include <string.h>


int main(){
    struct Node* root = NULL;
    while(1){
        struct CelestialObject* obj;
        char name[50];
        float distance_ly;
        char type[20];
        int discovery_year;

        printf("Enter celestial object details (name distance_ly type discovery_year) or 'exit' to quit:\n");
        if (scanf("%s", name) != 1 || strcmp(name, "exit") == 0) {
            break; // Exit the loop if user types 'exit'
        }
        scanf("%f %s %d", &distance_ly, type, &discovery_year);

        if (CelestialObject_create(&obj, name, distance_ly, type, discovery_year) != 0) {
            printf("Failed to create celestial object.\n");
            continue; // Skip to the next iteration
        }

        if (data_entry(&root, *obj) != 0) {
            printf("Failed to insert celestial object into the tree.\n");
            free(obj); // Free the allocated memory for obj
            continue; // Skip to the next iteration
        }
        printf("Celestial object '%s' inserted successfully.\n", name);
        free(obj); // Free the allocated memory for obj after insertion
    }

}


