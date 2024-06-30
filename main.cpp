#include <iostream>
#include <cstdlib>

using namespace std;

typedef enum { RED, BLACK } Color;

template <typename T>
struct Node {
    T data;
    Color color;
    Node *left, *right, *parent;
};

template <typename T>
Node<T>* createNode(T data) {
    Node<T>* newNode = (Node<T>*)malloc(sizeof(Node<T>));
    if (!newNode) {
        exit(1);
    }
    newNode->data = data;
    newNode->color = RED;
    newNode->left = newNode->right = newNode->parent = nullptr;
    return newNode;
}

template <typename T>
Node<T>* rotateLeft(Node<T>* root, Node<T>* x) {
    Node<T>* y = x->right;
    if (!y) return root; // Safety check
    x->right = y->left;
    if (y->left != nullptr) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
    return root;
}

template <typename T>
Node<T>* rotateRight(Node<T>* root, Node<T>* x) {
    Node<T>* y = x->left;
    if (!y) return root; // Safety check
    x->left = y->right;
    if (y->right != nullptr) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr) root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
    return root;
}

template <typename T>
Node<T>* insertFixUp(Node<T>* root, Node<T>* z) {
    while (z->parent != nullptr && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node<T>* y = z->parent->parent->right;
            if (y != nullptr && y->color == RED) {
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
            Node<T>* y = z->parent->parent->left;
            if (y != nullptr && y->color == RED) {
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

template <typename T>
Node<T>* insert(Node<T>* root, Node<T>* z) {
    Node<T>* y = nullptr;
    Node<T>* x = root;
    while (x != nullptr) {
        y = x;
        if (z->data < x->data) x = x->left;
        else x = x->right;
    }
    z->parent = y;
    if (y == nullptr) root = z;
    else if (z->data < y->data) y->left = z;
    else y->right = z;
    return insertFixUp(root, z);
}

template <typename T>
Node<T>* minimum(Node<T>* node) {
    while (node->left != nullptr) node = node->left;
    return node;
}

template <typename T>
Node<T>* maximum(Node<T>* node) {
    while (node->right != nullptr) node = node->right;
    return node;
}

template <typename T>
int height(Node<T>* node) {
    if (node == nullptr) return 0;
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

template <typename T>
void inorder(Node<T>* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

template <typename T>
Node<T>* transplant(Node<T>* root, Node<T>* u, Node<T>* v) {
    if (u->parent == nullptr) root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    if (v != nullptr) v->parent = u->parent;
    return root;
}

template <typename T>
Node<T>* deleteFixUp(Node<T>* root, Node<T>* x) {
    while (x != root && (x == nullptr || x->color == BLACK)) {
        if (x != nullptr && x->parent != nullptr && x == x->parent->left) {
            Node<T>* w = x->parent->right;
            if (w != nullptr && w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                root = rotateLeft(root, x->parent);
                w = x->parent->right;
            }
            if ((w == nullptr || w->left == nullptr || w->left->color == BLACK) && 
                (w == nullptr || w->right == nullptr || w->right->color == BLACK)) {
                if (w != nullptr) w->color = RED;
                x = x->parent;
            } else {
                if (w != nullptr && (w->right == nullptr || w->right->color == BLACK)) {
                    if (w->left != nullptr) w->left->color = BLACK;
                    w->color = RED;
                    root = rotateRight(root, w);
                    w = x->parent->right;
                }
                if (w != nullptr) w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->right != nullptr) w->right->color = BLACK;
                root = rotateLeft(root, x->parent);
                x = root;
            }
        } else {
            Node<T>* w = x != nullptr && x->parent != nullptr ? x->parent->left : nullptr;
            if (w != nullptr && w->color == RED) {
                w->color = BLACK;
                if (x != nullptr && x->parent != nullptr) x->parent->color = RED;
                root = rotateRight(root, x->parent);
                w = x->parent->left;
            }
            if ((w == nullptr || w->right == nullptr || w->right->color == BLACK) && 
                (w == nullptr || w->left == nullptr || w->left->color == BLACK)) {
                if (w != nullptr) w->color = RED;
                x = x->parent;
            } else {
                if (w != nullptr && (w->left == nullptr || w->left->color == BLACK)) {
                    if (w->right != nullptr) w->right->color = BLACK;
                    w->color = RED;
                    root = rotateLeft(root, w);
                    w = x->parent->left;
                }
                if (w != nullptr) w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->left != nullptr) w->left->color = BLACK;
                root = rotateRight(root, x->parent);
                x = root;
            }
        }
    }
    if (x != nullptr) x->color = BLACK;
    return root;
}

template <typename T>
Node<T>* deleteNode(Node<T>* root, Node<T>* z) {
    Node<T>* y = z;
    Node<T>* x = nullptr;
    Color yOriginalColor = y->color;
    if (z->left == nullptr) {
        x = z->right;
        root = transplant(root, z, z->right);
    } else if (z->right == nullptr) {
        x = z->left;
        root = transplant(root, z, z->left);
    } else {
        y = minimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x != nullptr) x->parent = y;
        } else {
            root = transplant(root, y, y->right);
            y->right = z->right;
            if (y->right != nullptr) y->right->parent = y;
        }
        root = transplant(root, z, y);
        y->left = z->left;
        if (y->left != nullptr) y->left->parent = y;
        y->color = z->color;
    }
    if (yOriginalColor == BLACK) root = deleteFixUp(root, x);
    free(z);
    return root;
}

template <typename T>
Node<T>* search(Node<T>* root, T data) {
    while (root != nullptr && data != root->data) {
        if (data < root->data) root = root->left;
        else root = root->right;
    }
    return root;
}

template <typename T>
int isRedBlackTree(Node<T>* root, int blackCount, int* pathBlackCount) {
    if (root == nullptr) {
        if (*pathBlackCount == -1) *pathBlackCount = blackCount;
        return blackCount == *pathBlackCount;
    }
    if (root->color == BLACK) blackCount++;
    if (root->color == RED && ((root->left != nullptr && root->left->color == RED) || (root->right != nullptr && root->right->color == RED)))
        return 0;
    return isRedBlackTree(root->left, blackCount, pathBlackCount) && isRedBlackTree(root->right, blackCount, pathBlackCount);
}

template <typename T>
int validateRedBlackTree(Node<T>* root) {
    int pathBlackCount = -1;
    return root == nullptr || (root->color == BLACK && isRedBlackTree(root, 0, &pathBlackCount));
}

template <typename T>
void freeTree(Node<T>* root) {
    if (root == nullptr) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    Node<int>* root = nullptr;

    root = insert(root, createNode(10));
    root = insert(root, createNode(20));
    root = insert(root, createNode(30));
    root = insert(root, createNode(15));
    root = insert(root, createNode(25));

    cout << "Inorder traversal: ";
    inorder(root);
    cout << "\n";

    if (validateRedBlackTree(root))
        cout << "The tree is a valid red-black tree.\n";
    else
        cout << "The tree is NOT a valid red-black tree.\n";

    Node<int>* found = search(root, 25);
    if (found != nullptr)
        cout << "Node with data 25 found.\n";
    else
        cout << "Node with data 25 not found.\n";

    // Encontrar máximo e mínimo
    Node<int>* min = minimum(root);
    Node<int>* max = maximum(root);
    cout << "Minimum: " << min->data << endl;
    cout << "Maximum: " << max->data << endl;

    // Calcular altura
    cout << "Height: " << height(root) << endl;

    // Remover um nó
    Node<int>* nodeToRemove = search(root, 15);
    if (nodeToRemove != nullptr)
        root = deleteNode(root, nodeToRemove);
    cout << "Inorder traversal after deletion: ";
    inorder(root);
    cout << "\n";

    // Inserir mais nós para testes adicionais
    root = insert(root, createNode(5));
    root = insert(root, createNode(35));
    root = insert(root, createNode(40));
    root = insert(root, createNode(1));

    cout << "Inorder traversal after more insertions: ";
    inorder(root);
    cout << "\n";

    // Verificar  a árvore rubro-negra após inserções adicionais
    if (validateRedBlackTree(root))
        cout << "The tree is a valid red-black tree after more insertions.\n";
    else
        cout << "The tree is NOT a valid red-black tree after more insertions.\n";

    // Remover nós adicionais
    nodeToRemove = search(root, 10);
    if (nodeToRemove != nullptr)
        root = deleteNode(root, nodeToRemove);
    cout << "Inorder traversal after deleting 10: ";
    inorder(root);
    cout << "\n";

    // OBS: Ao inserir um número entre 20 e 29 o delete do 20 funciona
    root = insert(root, createNode(27));

    // deleção apenas do 20 não funciona
    nodeToRemove = search(root, 20);
    if (nodeToRemove != nullptr)
        root = deleteNode(root, nodeToRemove);
    cout << "Inorder traversal after deleting 20: ";
    inorder(root);
    cout << "\n";

    freeTree(root);
    
    return 0;
}
