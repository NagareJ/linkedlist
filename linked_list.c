#include "linked_list.h"

/*ADDING ELEMENT TO LINKED LIST*/
/*	*This function adds an element to the last of the linked list
	*Return last element index on success
	*Return -1 when memory allocation for the new element fails
*/
int add_to_list(linked_list*ll, char*s) {
	linked_list *current = ll;
	while (current->next) {
		current = current->next;
	}
	linked_list *element = (struct linked_list *)malloc(sizeof(linked_list));
	if (!element) {
		free(element);
		return -1;	//ERROR: Can not allocate memory for new element
	}
	current->next = element;
	char *data = (char *)malloc(strlen(s) * sizeof(char) + 1);
	data = strdup(s);
	element->data = data;
	element->next = NULL;
	element->previous = current;
	element->index = current->index + 1;
	return element->index;
}

/*	DISPLAY A SINGLE ELEMENT FROM THE LINKED LIST
	*Return 0 when success
	*Return -1 when element can't be found
*/
int display_item(linked_list *ll) {
	if (!ll) return -1;	//ERORR: NULL element
	else {
		printf("\nIndex %d: %s\n", ll->index, ll->data);
		return 0;
	}
}

/*	DISPLAY THE WHOLE LINKED LIST
	*Display the whole linked list that the element passed in the parameter belongs to
	*Return the total number of elements that belong to the linked list on success
*/
int display_list(linked_list *ll) {
	int count = 0;
	if (!ll) return -1; //ERROR: No element
	linked_list *current = ll;
	while (current->previous) {
		current = current->previous;
	}
	while (current) {
		count++;
		display_item(current);
		current = current->next;
	}
	return count;
}

/*	SEARCH FOR AN ELEMENT IN LINKED LIST
	*Search for an element that matches with the data string
	*Return pointer to the element on success
	*Return NULL if not found
*/

linked_list * search_from_list(linked_list *ll, char *s) {
	linked_list *current = ll;
	while (current) {
		if (strcmp(current->data, s) == 0) {
			return current;
		}
		else
			current = current->next;
	}
	current = ll;
	while (current) {
		if (strcmp(current->data, s) == 0) {
			return current;
		}
		else
			current = current->previous;
	}
	return NULL;
}

/*	DELETE AN ELEMENT FROM LINKED LIST
	*Return the remain number of elements of the linked list on success
	*Return -1 on error
*/

int delete_from_list(linked_list *ll, int index) {
	int count = 0;
	linked_list *current = ll;
	linked_list *previous = ll;
	while (current) {
		count++;
		current = current->next;
	}
	if (index > count - 1 || index < 0) return -1;	//ERORR: Index out of range
	else if (index == 0) {
		ll = ll->next;
		free(previous);
		current = ll;
		current->previous = NULL;
		while (current) {
			current->index -= 1;
			current = current->next;
		}
		return count - 1;
	}
	else {
		current = ll;
		while (current->index != index) {
			previous = current;
			current = current->next;
		}
		if (current->index == index) {
			previous->next = current->next;
			free(current);
			while (previous->next) {
				previous->next->index = previous->index + 1;
				previous = previous->next;
			}
			return count - 1;
		}
		else return -1;	// UNEXPECTED ERROR
	}
}

/*	EMPTY LINKED LIST
	*Free the memory of every element of the linked list
	*Return the number of element freed
*/

int empty_list(linked_list *ll) {
	linked_list *current = ll;
	int count = 0;
	if (!ll) return -1; //ERROR: No element
	while (ll->previous) {
		ll = ll->previous;
	}
	while (ll) {
		count++;
		current = ll;
		ll = ll->next;
		free(current);
	}
	return count;
}

/*	SWAP TWO ELEMENTS
	*Swap the data of two element of the same linked list
	*Return 0 on success
	*Return -1 on error
*/

int swap_items(linked_list *f, linked_list *s) {
	if (!f) return -1;	//ERORR: element not found
	else if (!s) return -1; //ERORR: element not found
	else {
		linked_list *current = f;
		if (f->index < s->index) {	//Search from f element to s element
			for (int i = 0; i < s->index - f->index; i++) {
				if (current->next)
					current = current->next;
				else return -1;	//ERORR: Not belongs to the same linked list
			}
			if (current != s) return -1;	//ERORR: Not belongs to the same linked list
		}
		else {	//Search from s element to f element
			current = s;
			for (int i = 0; i < f->index - s->index; i++) {
				if(current->next)
					current = current->next;
				else return -1; //ERORR: Not belongs to the same linked list
			}
			if (current != f) return -1;	//ERORR: Not belongs to the same linked list
		}
		char *data = (char *)malloc(strlen(f->data) * sizeof(char) + 1);
		data = strdup(f->data);
		f->data = s->data;
		s->data = data;
		return 0;
	}
}
/*	SORT LINKED LIST IN ASCENDING ORDER
	*Sort the linked list that the element passed into parameter belongs to in ascending order based on data string
	*Return 0 on success
	*Return -1 on error
*/

int sort_list(linked_list *ll) {
	if(!ll) return -1;	//ERROR: NULL element
	linked_list *current = ll;
	char *temp_str;
	while (ll->previous) {
		ll = ll->previous;
	}
	int len = linkedlist_status(ll);
	for(int i = len; i > 0; i--){
		for(int j = 0; j < i-1; j++){
			if(strcmp(current->data, current->next->data)>0){
				temp_str = current->data;
				current->data = current->next->data;
				current->next->data = temp_str;
			}
		current = current->next;
		}
		current = ll;
	}
	while(current->next){
		if(strcmp(current->data, current->next->data)>0){
			temp_str = current->data;
			current->data = current->next->data;
			current->next->data = temp_str;
		}
		current = current->next;
	}
	return 0;
}

/*	CHECK THE STATUS OF LINKED LIST
	*Check the status of linked list based on total number of elements
	*Return total number of elements belongs the the linked list
*/
int linkedlist_status(linked_list *ll) {
	linked_list *current = ll;
	int count = 0;
	if (!ll) return -1;  //ERROR: No element
	while (current) {
		count++;
		current = current->next;
	}
	if (ll->previous) {
		current = ll->previous;
		while (current) {
			count++;
			current = current->previous;
		}
	}
	return count;
}