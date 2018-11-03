#include "linked_list.h"

int add_to_list(linked_list*ll, char*s) {
	if (ll) {
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
		char *data = (char *)malloc(strlen(s) * sizeof(char) + 1);
		data = strdup(s);
		element->data = data;
		element->next = NULL;
		element->index = current->index + 1;
		return element->index;
	}
	else {
		printf("\n\n\n Dont come there");
		char *data = (char *)malloc(strlen(s) * sizeof(char) + 1);
		data = strdup(s);
		ll->data = data;
		ll->next = NULL;
		ll->index = 0;
		return ll->index;
	}
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
		current = ll;
		display_list(ll);
		while (current) {
			current->index -= 1;
			current = current->next;
		}
		return count - 1;
	}
	else {
		current = ll;
		/*for (int i = 0; i < index - 1; i++) { //Other method that also works
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
	linked_list *current = ll;
	int count = 0;
	while (ll) {
		count++;
		current = ll;
		ll = ll->next;
		free(current);
	}
	return count;
}
int swap_items(linked_list *f, linked_list *s) {
	if (!f) return -1;
	else if (!s) return -1;
	else {
		linked_list *current = f;
		if (f->index < s->index) {
			for (int i = 0; i < s->index - f->index; i++) {
				current = current->next;
			}
			if (current != s) return -1;
		}
		else {
			current = s;
			for (int i = 0; i < f->index - s->index; i++) {
				current = current->next;
			}
			if (current != f) return -1;
		}
		char *data = (char *)malloc(strlen(f->data) * sizeof(char) + 1);
		data = strdup(f->data);
		f->data = s->data;
		s->data = data;
		return 0;
	}
}
int sort_list(linked_list *ll) {
	if(!ll) return -1;
	linked_list *current = ll;
	char *temp_str;
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
int linkedlist_status(linked_list *ll) {
	linked_list *current = ll;
	int count = 0;
	while(current){
		count++;
		current = current->next;
	}
	return count;
}