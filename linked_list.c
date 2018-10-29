#include "linked_list.h"

int add_to_list(linked_list*ll, char*s) {
	linked_list *current = ll;
	while (current->next) {
		current = current->next;
	}
	linked_list *element = (struct linked_list *)malloc(sizeof(linked_list));
	if (!element) {
		free(element);
		return -1;
	}
	current->next = element;
	char *data = (char *)malloc(strlen(s) * sizeof(char)+1);
	data = strdup(s);
	element->data = data;
	element->next = NULL;
	element->index = current->index + 1;
	return element->index;
}
int display_item(linked_list *ll) {
	if (!ll) return -1;
	else {
		printf("\nIndex %d: %s\n", ll->index, ll->data);
		return 0;
	}
}
int display_list(linked_list *ll) {
	int count = 0;
	linked_list *current = ll;
	while (current) {
		count++;
		display_item(current);
		current = current->next;
	}
	return count;
}
linked_list * search_from_list(linked_list *ll, char *s) {
	linked_list *current = ll;
	while (current) {
		if (strcmp(current->data, s) == 0) {
			return current;
		}
		else
			current = current->next;
	}
	return NULL;
}
int delete_from_list(linked_list *ll, int index) {
	int count = 0;
	linked_list *current = ll;
	linked_list *previous = ll;
	while (current) {
		count++;
		current = current->next;
	}
	if (index > count - 1 || index < 0) return -1;
	else if (index == 0) {
		ll = ll->next;
		free(previous);
	}
	else {
		current = ll;
		/*for (int i = 0; i < index - 1; i++) { //Other working method
			current = current->next;
		}
		if (current->next->index == index) {
			previous = current;
			current = current->next;
			previous->next = current->next;
			free(current);
			while (previous->next) {
				previous->next->index = previous->index + 1;
				previous = previous->next;
			}
			return count - 1;
		}
		else return -1;*/
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
		else return -1;
	}
	return -1;
}
int empty_list(linked_list *ll) {
	
}
int swap_items(linked_list *f, linked_list *s) {
	
}
int sort_list(linked_list *ll) {

}
int linkedlist_status(linked_list *ll) {

}