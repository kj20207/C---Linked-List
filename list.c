#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void main(){
	int i;
	struct linked_list *ll;
	list_create(&ll);
	
	printf("---- Inserting Items ----\n");
	for(i = 1; i <= 5; i++){ list_insert(&ll, i);}
	printf("---- Checking Items ----\n");
	for(i = 1; i <= 5; i++){ list_contains(&ll, i);}
	printf("---- Removing Items ----\n");
	for(i = 1; i <= 5; i++){ list_remove(&ll, i);}
	printf("---- Checking Items 2 ----\n");
	for(i = 1; i <= 5; i++){ list_contains(&ll, i);}
	
	list_destroy(&ll);
	
}

int list_create(struct linked_list **list){
	// Allocate the memory for the LL
	*list = malloc(sizeof(struct linked_list));
	
	// Allocate memory for the head and tail nodes of LL 
	(*list)->head = malloc(sizeof(struct linked_node));
	(*list)->tail = malloc(sizeof(struct linked_node));
	// Initialize size to 0
	(*list)->size = 0;
	
	// Set head -> next to tail
	(*list)->head->next = (*list)->tail;
	// Tail -> next ALWAYS == NULL
	(*list)->tail->next = NULL;
	
	// Debugging Line
	printf("%p %p %d %p\n", (*list)->head, (*list)->tail, (*list)->size, (*list)->head->next);
	
	return 1;
}

// Inserts the given value into the list in a node directly before the tail
int list_insert(struct linked_list **list, int value){
	
	// Create memory for the node to be inserted, and set its value to the parameter value
	struct linked_node *node = malloc(sizeof(linked_node));
	node->value = value;
	
	// If there is nothing in the list, insert node directly behind the head of the list
	if(list_size(list) == 0){
		(*list)->head->next = node;
		node->next = (*list)->tail;
	}
	// Other items in the list, iterate through list, inserting item directly before tail
	else{
		// Current pointer
		struct linked_node *curr = (*list)->head->next;
		// Iterate through pointers until node is found whose *next value is the tail of the list
		while(curr->next != (*list)->tail){
			curr = curr->next;
		}
		curr->next = node;
		node->next = (*list)->tail;
	}
	
	// Increment the size of the list for the newly inserted value
	(*list)->size += 1;
	
	// Debugging Line
	printf("Inserted value: %d. Size of List: %d\n", value, list_size(list));
	
	return 1;
}

// Removes the first instance of "value" within the list, and returns 1 if the value is removed from the list
// Returns 0 if the value does not exist within the list
int list_remove(struct linked_list **list, int value){
	
	// value does not exist within list.
	if(!list_contains(list, value)){
		
		// Debugging line
		printf("Value not found. Nothing removed.");
		return 0;
	}
	else{
		// Find the node prior to the node to be removed
		struct linked_node *curr = (*list)->head;
		while(curr->next->value != value){
			curr = curr->next;
		}
		
		// Temporary node for changing pointers
		struct linked_node *removal = curr->next;
		// overlap node to be removed
		curr->next = removal->next;
		// free memory
		free(removal);
		// Decrement size
		(*list)->size -= 1;
		
		// Debugging line
		printf("Removed value: %d.\n", value);
		
	}
	return 1;
}

// Returns 1 if the given value exists within this list
// Returns 0 if the value is not contained within the list
int list_contains(struct linked_list **list, int value){
	
	// index for debugging. Used to show where item exists within list
	int index = 0;
	
	// temporary pointer to first item in list
	struct linked_node *node = (*list)->head->next;
	// go until current node is not the tail
	while(node != (*list)->tail){
		
		// if current node value is equal to value, it's within the list
		if(node->value == value){
			// Debugging line
			printf("Found value: %d. Found at index: %d.\n", value, index); 
			return 1;
		}
		// value not found, check next node.
		node = node->next;
		// 
		index++;
	}
	
	// Debugging line
	printf("Value of %d does not exist within this list.\n", value);
	return 0;
}

// Returns the size value stored within the list
int list_size(struct linked_list **list){
	return (*list)->size;
}

// Removes all items from list, and frees all memory from the list
int list_destroy(struct linked_list **list){
	
	// Debugging line
	printf("Destroying list. Size: %d.\n", list_size(list));
	// Temporary pointer to head of list
	struct linked_node *front = (*list)->head;
	
	// If items need to be removed, remove them first
	if(list_size(list) > 0){
		// While items are in list
		while(list_size(list) > 0){
			// Temp node pointer for item after head (node being removed)
			struct linked_node *temp = front->next;
			// set head->next to be node after removed node
			front->next = front->next->next;
			// free temporary node
			free(temp);
			// decrement size
			(*list)->size -= 1;
		}
	}
	printf("All nodes removed & freed.\n");
	
	// Free the memory spaces for the Tail, head, and list
	free((*list)->tail);
	free((*list)->head);
	free(*list);
	
	// Confirmation of destruction
	printf("Head and Tail of list freed. List destroyed!\n\n");
	return 1;
}