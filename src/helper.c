#include <stdio.h>
#include <stdlib.h>
#include "helper.h"




int data_entry(struct Node** node, struct CelestialObject data) {
    if (*node == NULL) {
        int result = createNode(node, data);
        
        return result;
        
    }
  
    return 0; // Success
}
