#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

typedef struct Node {
    int data;
    Color color;
    struct Node *left, *right, *parent;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->color = RED;
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

Node* rotateLeft(Node* root, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NULL) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
    return root;
}

Node* rotateRight(Node* root, Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != NULL) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL) root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
    return root;
}

Node* insertFixUp(Node* root, Node* z) {
    while (z->parent != NULL && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    root = rotateLeft(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                root = rotateRight(root, z->parent->parent);
            }
        } else {
            Node* y = z->parent->parent->left;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    root = rotateRight(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                root = rotateLeft(root, z->parent->parent);
            }
        }
    }
    root->color = BLACK;
    return root;
}

Node* insert(Node* root, Node* z) {
    Node* y = NULL;
    Node* x = root;
    while (x != NULL) {
        y = x;
        if (z->data < x->data) x = x->left;
        else x = x->right;
    }
    z->parent = y;
    if (y == NULL) root = z;
    else if (z->data < y->data) y->left = z;
    else y->right = z;
    return insertFixUp(root, z);
}

Node* minimum(Node* node) {
    while (node->left != NULL) node = node->left;
    return node;
}

Node* maximum(Node* node) {
    while (node->right != NULL) node = node->right;
    return node;
}

int height(Node* node) {
    if (node == NULL) return 0;
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

Node* transplant(Node* root, Node* u, Node* v) {
    if (u->parent == NULL) root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    if (v != NULL) v->parent = u->parent;
    return root;
}

Node* deleteFixUp(Node* root, Node* x) {
    while (x != root && (x == NULL || x->color == BLACK)) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                root = rotateLeft(root, x->parent);
                w = x->parent->right;
            }
            if ((w->left == NULL || w->left->color == BLACK) && (w->right == NULL || w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right == NULL || w->right->color == BLACK) {
                    if (w->left != NULL) w->left->color = BLACK;
                    w->color = RED;
                    root = rotateRight(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->right != NULL) w->right->color = BLACK;
                root = rotateLeft(root, x->parent);
                x = root;
            }
        } else {
            Node* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                root = rotateRight(root, x->parent);
                w = x->parent->left;
            }
            if ((w->right == NULL || w->right->color == BLACK) && (w->left == NULL || w->left->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left == NULL || w->left->color == BLACK) {
                    if (w->right != NULL) w->right->color = BLACK;
                    w->color = RED;
                    root = rotateLeft(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->left != NULL) w->left->color = BLACK;
                root = rotateRight(root, x->parent);
                x = root;
            }
        }
    }
    if (x != NULL) x->color = BLACK;
    return root;
}

Node* deleteNode(Node* root, Node* z) {
    Node* y = z;
    Node* x;
    Color yOriginalColor = y->color;
    if (z->left == NULL) {
        x = z->right;
        root = transplant(root, z, z->right);
    } else if (z->right == NULL) {
        x = z->left;
        root = transplant(root, z, z->left);
    } else {
        y = minimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x != NULL) x->parent = y;
        } else {
            root = transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        root = transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (yOriginalColor == BLACK) root = deleteFixUp(root, x);
    free(z);
    return root;
}

Node* search(Node* root, int data) {
    while (root != NULL && data != root->data) {
        if (data < root->data) root = root->left;
        else root = root->right;
    }
    return root;
}

int isRedBlackTree(Node* root, int blackCount, int* pathBlackCount) {
    if (root == NULL) {
        if (*pathBlackCount == -1) *pathBlackCount = blackCount;
        return blackCount == *pathBlackCount;
    }
    if (root->color == BLACK) blackCount++;
    if (root->color == RED && ((root->left != NULL && root->left->color == RED) || (root->right != NULL && root->right->color == RED)))
        return 0;
    return isRedBlackTree(root->left, blackCount, pathBlackCount) && isRedBlackTree(root->right, blackCount, pathBlackCount);
}

int validateRedBlackTree(Node* root) {
    int pathBlackCount = -1;
    return root == NULL || (root->color == BLACK && isRedBlackTree(root, 0, &pathBlackCount));
}

void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    Node* root = NULL;

    // Inserção de nós
    root = insert(root, createNode(10));
    root = insert(root, createNode(20));
    root = insert(root, createNode(30));
    root = insert(root, createNode(15));
    root = insert(root, createNode(25));

    // Percurso em ordem simétrica
    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");

    // Verificação da árvore rubro-negra
    if (validateRedBlackTree(root))
        printf("The tree is a valid red-black tree.\n");
    else
        printf("The tree is NOT a valid red-black tree.\n");

    // Buscar um nó
    Node* found = search(root, 15);
    if (found != NULL)
        printf("Node with data 15 found.\n");
    else
        printf("Node with data 15 not found.\n");

    // Encontrar máximo e mínimo
    Node* min = minimum(root);
    Node* max = maximum(root);
    printf("Minimum: %d\n", min->data);
    printf("Maximum: %d\n", max->data);

    // Calcular altura
    printf("Height: %d\n", height(root));

    // Remover um nó
    Node* nodeToRemove = search(root, 15);
    if (nodeToRemove != NULL)
        root = deleteNode(root, nodeToRemove);
    printf("Inorder traversal after deletion: ");
    inorder(root);
    printf("\n");

    freeTree(root);

    return 0;
}

