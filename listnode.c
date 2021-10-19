#include <string.h>
#include "duplicates.h"

#if	defined(__linux__)
extern	char	*strdup(char *string);
#endif

// Create a new empty list
LISTNODE *list_new(void) {
    return NULL;
}

// Check if file's sha2hash is already in list, return listnode where found or null
LISTNODE *list_find(LISTNODE *listnode, FILES *file) {
    while (listnode != NULL) {
        // traverse listnodes till end, return the listnode if it has the sha2hash we are looking for
        if (strcmp(listnode->sha2hash, file->hash)) {
            return listnode;
        }
        listnode = listnode->next;
    }
    return NULL;
}

// Allocate space for a new item
LISTNODE *create_empty_listnode(FILES *file) {
    LISTNODE *new = calloc(1, sizeof(LISTNODE));
    CHECK_ALLOC(new);
    new->sha2hash = strdup(file->hash);
    CHECK_ALLOC(new->sha2hash); //this may cause errors
    new->next = NULL;
    return new;
}

// Add a file to the files array within an existing listnode 
void add_file_to_listnode(LISTNODE *listnode, FILES *file) {
    // Allocate additional space for a new FILES * in array
    listnode->files = realloc(listnode->files, (listnode->nfiles + 1) * sizeof(listnode->files[0]));// if this fails try size(file));
    CHECK_ALLOC(listnode->files);
    
    // Add pathname
    listnode->files[listnode->nfiles].pathname = strdup(file->pathname);
    CHECK_ALLOC(listnode->files[listnode->nfiles].pathname);
    // Add filesize
    listnode->files[listnode->nfiles].size = file->size;
    // add sha2 (is redundant but whatever)
    listnode->files[listnode->nfiles].hash = strdup(file->hash);
    CHECK_ALLOC(listnode->files[listnode->nfiles].hash);

    //printf("\t file %s added! has sha2hash %s\n", listnode->files[listnode->nfiles].pathname, listnode->files[listnode->nfiles].hash);
    ++listnode->nfiles;
}

// Adds a file to the listnode for its sha2hash, or creates a new listnode and then adds file to it
LISTNODE *list_add(LISTNODE *listnode, FILES *file) {
    
    LISTNODE *foundlistnode;
    if ((foundlistnode = list_find(listnode, file)) != NULL) {
        // if we find there is a listnode for this sha2hash, add file to it
        add_file_to_listnode(foundlistnode, file);
        return listnode;
    } else {
        // if no listnode exists for this sha2hash, create one and add file to it.
        LISTNODE *new = create_empty_listnode(file);
        add_file_to_listnode(new, file);
        new->next = listnode;
        return new;
    }
}