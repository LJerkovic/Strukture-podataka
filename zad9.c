#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;


Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


Node* insert(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    }
    else {
        root->right = insert(root->right, data);
    }
    return root;
}


void inorder(Node* root, FILE* file) {
    if (root != NULL) {
        inorder(root->left, file);
        fprintf(file, "%d ", root->data);
        inorder(root->right, file);
    }
}


int sumSubtree(Node* root) {
    if (root == NULL) {
        return 0;
    }
    int leftSum = sumSubtree(root->left);
    int rightSum = sumSubtree(root->right);
    int currentData = root->data;
    root->data = leftSum + rightSum;
    return currentData + root->data;
}


void replace(Node* root) {
    sumSubtree(root);
}


int main() {
    Node* root = NULL;
    int i, n = 10, randomNumbers[10];
    FILE* file;

    srand(time(NULL));
    for (i = 0; i < n; i++) {
        randomNumbers[i] = rand() % 81 + 10; 
    }

    
    for (i = 0; i < n; i++) {
        root = insert(root, randomNumbers[i]);
    }

   
    file = fopen("output.txt", "w");
    if (file == NULL) {
        printf("Greska pri otvaranju datoteke\n");
        return 1;
    }

    
    fprintf(file, "Inorder prije : ");
    inorder(root, file);
    fprintf(file, "\n");

    
    replace(root);

    
    fprintf(file, "Inorder nakon : ");
    inorder(root, file);
    fprintf(file, "\n");

    
    fclose(file);

    printf("Rezultati su upisani \n");
    return 0;
}
