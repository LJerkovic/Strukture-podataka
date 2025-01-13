#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node* Position;
typedef struct node {
    int value;
    Position left;
    Position right;
}Node;

Position insert(Position root, int value);
int inorder(Position root);
int preorder(Position root);
int postorder(Position root);
int levelOrder(Position root);
Position delete(Position root, int value);
Position find(Position root, int value);

Position insert(Position root, int value) {
    if (root == NULL) {
        root = (Position)malloc(sizeof(Node));
        if (root == NULL) {
            printf("Memory allocation failed!\n");
            return NULL;
        }
        root->value = value;
        root->left = root->right = NULL;
    }
    else if (value < root->value)
        root->left = insert(root->left, value);
    else if (value > root->value)
        root->right = insert(root->right, value);
    return root;
}

int inorder(Position root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->value);
        inorder(root->right);
    }
    return EXIT_SUCCESS;
}

int preorder(Position root) {
    if (root) {
        printf("%d ", root->value);
        preorder(root->left);
        preorder(root->right);
    }
    return EXIT_SUCCESS;
}

int postorder(Position root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->value);
    }
    return EXIT_SUCCESS;
}

int levelOrder(Position root) {
    if (!root) return EXIT_SUCCESS;
    Position queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;
    while (front < rear) {
        Position current = queue[front++];
        printf("%d ", current->value);
        if (current->left) queue[rear++] = current->left;
        if (current->right) queue[rear++] = current->right;
    }
    return EXIT_SUCCESS;
}

Position delete(Position root, int value) {
    if (root == NULL || root->value == value) {
        return root;
    }

    if (value < root->value) {
        root->left = delete(root->left, value);
    }
    else if (value > root->value) {
        root->right = delete(root->right, value);
    }
    else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        else if (root->left == NULL) {
            Position temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Position temp = root->left;
            free(root);
            return temp;
        }
        else {
            Position temp = root->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            root->value = temp->value;
            root->right = delete(root->right, temp->value);
        }
    }

    return root;
}

Position find(Position root, int value) {
    if (root == NULL || root->value == value)
        return root;
    if (value < root->value)
        return find(root->left, value);
    return find(root->right, value);
}

int main() {
    Position root = NULL;
    int choice, value;

    do {
        printf("\n1. Insert\n2. Inorder\n3. Preorder\n4. Postorder\n5. Level Order\n6. Delete\n7. Find\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &value);
            root = insert(root, value);
            break;
        case 2:
            inorder(root);
            printf("\n");
            break;
        case 3:
            preorder(root);
            printf("\n");
            break;
        case 4:
            postorder(root);
            printf("\n");
            break;
        case 5:
            levelOrder(root);
            printf("\n");
            break;
        case 6:
            printf("Enter value to delete: ");
            scanf("%d", &value);
            root = delete(root, value);
            break;
        case 7:
            printf("Enter value to find: ");
            scanf("%d", &value);
            if (find(root, value))
                printf("Value %d found in tree.\n", value);
            else
                printf("Value %d not found.\n", value);
            break;
        }
    } while (choice != 8);

    return EXIT_SUCCESS;
}
