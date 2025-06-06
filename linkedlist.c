#include "game.h"

// Append new node with given value at end of list
void append_node(Node** head, Word word) {
    Node* new_node = malloc(sizeof(Node));
	if (new_node == NULL) {
		gotoxy(0, 0);
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	strcpy(new_node->word.text, word.text);
	new_node->word.x = word.x;
	new_node->word.y = word.y;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    Node* curr = *head;
    while (curr->next != NULL)
        curr = curr->next;
    curr->next = new_node;
}

// Delete all nodes at bottom
int delete_bottom(Node** head, int* heart) {
	if (*head == NULL) return 0;
	int if_deleted = 0;
    while ((*head)->word.y == START_Y + 20) {
        Node* tmp = *head;
        *head = (*head)->next;
        free(tmp); // free formal first node
		(*heart)--;
		if_deleted = 1;
    }

    Node* curr = *head;
    while (curr->next) {
        if (curr->next->word.y == START_Y + 20) {
            Node* tmp = curr->next;
            curr->next = tmp->next;
            free(tmp);
			(*heart)--;
			if_deleted = 1;
        }
        else {
            curr = curr->next;
        }
    }
	return if_deleted;
}

int delete_node(Node** head, char* str) {
	if (*head == NULL) return 0;
	while (strcmp((*head)->word.text, str) == 0) {
		Node* tmp = *head;
		*head = (*head)->next; // delete first node
		free(tmp);
		return 1;
	}
	Node* prev = *head;
	Node* curr = (*head)->next;
	while (curr) {
		if (strcmp(curr->word.text, str) == 0) {
			prev->next = curr->next; // delete current node
			free(curr);
			return 1;
		}
		prev = curr;
		curr = curr->next;
	}
	return 0; // no node with str found
}

// Free all nodes
void free_list(Node** head) {
	if (*head == NULL) return;
	Node* curr = *head;
    while (curr) {
        Node* tmp = curr;
        curr = curr->next;
        free(tmp);
    }
}

// Subtract 1 from all nodes' data
void move_down(Node* head) {
	if (head == NULL) return;
    Node* curr = head;
    while (curr) {
        curr->word.y++;
        curr = curr->next;
    }
}

// Print all elements in the list
void print_list(Node* head) {
	if (head == NULL) return;
	printf("List: ");
	Node* curr = head;
    while (curr) {
        printf("(%s, %d, %d) -> ", curr->word.text, curr->word.x, curr->word.y);
        curr = curr->next;
    }
    printf("NULL\n");
}

void print_word_text(Node* head) {
	if (head == NULL) return;
    Node* curr = head;
	while (curr) {
		gotoxy(curr->word.x, curr->word.y);
		printf("%s", curr->word.text);
		curr = curr->next;
	}
}

void unprint_word_text(Node* head) {
	if (head == NULL) return;
	Node* curr = head;
	while (curr) {
		gotoxy(curr->word.x, curr->word.y);
		printf("          "); // Clear the word text
		curr = curr->next;
	}
}