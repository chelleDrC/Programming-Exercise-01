//Written by: Richelle de Arce and Klaire Napolitano
//This code accepts only integers(int) variable type for input

#include <stdio.h>
#include <stdlib.h>

// Define a structure for a Node
typedef struct Node {
    int data;
    struct Node* nextAddress; // Pointer to the next node
} Node;

//Function prototype
int choiceMade();
void displayNodes(Node* head);
void addNodeEnd(Node** head, int val);
void addNodeStart(Node** head, int val);
void addNodePosition(Node** head, int val, int position);
void addItem(Node** head);
void deleteItem(Node** head);
void deleteList(Node** head);
void displayMenu();

int main() {
    Node* head = NULL;
    int choice;

    do {
        displayMenu();
        choice = choiceMade();

        switch (choice) {
            case 1:
                addItem(&head); // Call addItem function
                break;
            case 2:
                deleteItem(&head); // Call deleteItem function
                break;
            case 3:
                displayNodes(head); // Call displayNodes function
                break;
            case 4:
                deleteList(&head); // Call deleteList function
                break;
            case 0:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 0);

    return 0;
}

// Function to prompt the user for a choice
int choiceMade() {
    int option;
    printf("Enter choice: ");
    scanf("%d", &option);
    return option;
}

// Function to display all nodes in the list
void displayNodes(Node* head) {
    int i = 0;
    printf("===DISPLAY===\n");
    for (Node* cur = head; cur != NULL; cur = cur->nextAddress) {
        i++;
        printf("[%d]%d ", i, cur->data);
    }
    printf("\n");
}

// Function to add a node at the end of the list
void addNodeEnd(Node** head, int val) {
    // Allocate memory for the new node
    Node* node = malloc(sizeof(Node));
    if (node == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Set the data and nextAddress of the new node
    node->nextAddress = NULL;
    node->data = val;

    // If the list is empty, make the new node the head
    if (*head == NULL) {
        *head = node;
    } else {
        // Traverse the list to find the last node
        Node* cur = *head;
        while (cur->nextAddress != NULL) {
            cur = cur->nextAddress;
        }
        // Attach the new node to the last node
        cur->nextAddress = node;
    }

    // Display the updated list
    displayNodes(*head);
}

// Function to add a node at the start of the list
void addNodeStart(Node** head, int val) {
    // Allocate memory for the new node
    Node* node = malloc(sizeof(Node));
    if (node == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Set the data and nextAddress of the new node
    node->nextAddress = *head;
    node->data = val;
    *head = node;

    // Display the updated list
    displayNodes(*head);
}

// Function to add a node at a specific position in the list
void addNodePosition(Node** head, int val, int position) {
    if (position <= 0) {
        printf("Invalid position.\n");
        return;
    }

    // Allocate memory for the new node
    Node* node = malloc(sizeof(Node));
    if (node == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Set the data of the new node
    node->data = val;

    // If position is 1, add node at the start
    if (position == 1) {
        node->nextAddress = *head;
        *head = node;
    } else {
        // Traverse to the node just before the desired position
        Node* cur = *head;
        for (int i = 1; i < position - 1 && cur != NULL; i++) {
            cur = cur->nextAddress;
        }

        // If the position is invalid, print an error message and free memory
        if (cur == NULL) {
            printf("Invalid position.\n");
            free(node);
            return;
        }

        // Insert the new node at the desired position
        node->nextAddress = cur->nextAddress;
        cur->nextAddress = node;
    }

    // Display the updated list
    displayNodes(*head);
}

// Function to prompt user for adding an item and call appropriate add function
void addItem(Node** head) {
    int choose;
    int numberToAdd;

    printf("Please enter the item to be added:\n\n");
    printf("[1] Start of the list\n");
    printf("[2] End of the list\n");
    printf("[3] Specific position\n");
    printf("[0] Cancel\n");

    choose = choiceMade();

    switch (choose) {
        case 1:
            printf("Enter item at the start: ");
            scanf("%d", &numberToAdd);
            addNodeStart(head, numberToAdd); // Call addNodeStart function
            break;
        case 2:
            printf("Enter item at the end: ");
            scanf("%d", &numberToAdd);
            addNodeEnd(head, numberToAdd); // Call addNodeEnd function
            break;
        case 3:
            printf("Enter item: ");
            scanf("%d", &numberToAdd);
            printf("Enter position: ");
            int position;
            scanf("%d", &position);
            addNodePosition(head, numberToAdd, position); // Call addNodePosition function
            break;
        case 0:
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
}

// Function to delete an item from the list
void deleteItem(Node** head) {
    int itemToDelete;
    printf("Enter item to delete: ");
    scanf("%d", &itemToDelete);

    Node* cur = *head;
    Node* prev = NULL;

    // Traverse the list to find the node to delete
    while (cur != NULL && cur->data != itemToDelete) {
        prev = cur;
        cur = cur->nextAddress;
    }

    // If the item is not found, print an error message
    if (cur == NULL) {
        printf("Item not found.\n");
        return;
    }

    // If the item is found, delete it
    if (prev == NULL) {
        // Deleting the first node
        *head = cur->nextAddress;
    } else {
        // Deleting a node other than the first one
        prev->nextAddress = cur->nextAddress;
    }

    // Free the memory occupied by the deleted node
    free(cur);
    printf("Item deleted successfully.\n");
}

// Function to delete the entire list
void deleteList(Node** head) {
    while (*head != NULL) {
        Node* temp = *head;
        *head = (*head)->nextAddress;
        free(temp);
    }
}

// Function to display the menu of options
void displayMenu() {
    printf("List MENU\n\n");
    printf("[1] Add Item\n");
    printf("[2] Delete Item\n");
    printf("[3] Display List\n");
    printf("[4] Delete List\n");
    printf("[0] Exit Program\n");
}
