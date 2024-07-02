#include <iostream>
#include <cstdlib>
#include <chrono>

using namespace std;
using chrono::high_resolution_clock;
using chrono::duration_cast;
using chrono::nanoseconds;

enum Color { RED, BLACK };

template <typename T>
struct Node {
    T data;
    Color color;
    Node *left, *right, *parent;
};

template <typename T>
Node<T>* createNode(T data) {
    Node<T>* newNode = new Node<T>();
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
    if (!y) return root;
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
    if (!y) return root;
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
    return 1 + max(leftHeight, rightHeight);
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
        if (x == x->parent->left) {
            Node<T>* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                root = rotateLeft(root, x->parent);
                w = x->parent->right;
            }
            if ((w->left == nullptr || w->left->color == BLACK) &&
                (w->right == nullptr || w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right == nullptr || w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    root = rotateRight(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                root = rotateLeft(root, x->parent);
                x = root;
            }
        } else {
            Node<T>* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                root = rotateRight(root, x->parent);
                w = x->parent->left;
            }
            if ((w->right == nullptr || w->right->color == BLACK) &&
                (w->left == nullptr || w->left->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left == nullptr || w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    root = rotateLeft(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
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
    Node<T> *y = z, *x = nullptr;
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
            if (x) x->parent = y;
        } else {
            root = transplant(root, y, y->right);
            y->right = z->right;
            if (y->right) y->right->parent = y;
        }
        root = transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (yOriginalColor == BLACK && x != nullptr) 
        root = deleteFixUp(root, x);
    delete z;
    return root;
}


template <typename T>
Node<T>* search(Node<T>* root, T key) {
    if (root == nullptr || root->data == key) return root;
    if (key < root->data) return search(root->left, key);
    return search(root->right, key);
}

template <typename T>
void freeTree(Node<T>* root) {
    if (root == nullptr) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

template <typename T>
bool isValidRedBlackTree(Node<T>* root) {
    if (root == nullptr) return true;

    if (root->color == RED) {
        if (root->left && root->left->color == RED)
            return false;
        if (root->right && root->right->color == RED)
            return false;
    }

    return isValidRedBlackTree(root->left) && isValidRedBlackTree(root->right);
}

/*
// Função para criar uma lista de nós com valores aleatórios e inseri-los na árvore rubro-negra
Node<int>* createRandomList(int iLength, int start, int stop) {
    if (iLength <= 0 || start >= stop) {
        return nullptr; 
    }

    srand((unsigned)time(0)); 

    Node<int>* root = nullptr; 

    for (int i = 0; i < iLength; ++i) {
        int randomValue = (rand() % (stop - start)) + start; 
        Node<int>* newNode = createNode(randomValue); 
        root = insert(root, newNode); 
    }

    return root; 
} 
*/   

// Função para criar uma lista de nós com valores aleatórios e inseri-los na árvore rubro-negra
Node<int>* createRandomList(int iLength, int start, int stop) {
    if (iLength <= 0 || start >= stop) {
        return nullptr; 
    }

    Node<int>* root = nullptr; 

    for (int i = 0; i < iLength; ++i) {
        int randomValue = (rand() % (stop - start)) + start; 
        Node<int>* newNode = createNode(randomValue); 
        root = insert(root, newNode); 
    }

    return root; 
}

/*
void testFunctionSearch(string function_name, Node<int>* (*searchFunc)(Node<int>*, int)) {
    int mean = 0;
    auto timeStart = high_resolution_clock::now();
    auto timeStop = high_resolution_clock::now();
    auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);

    Node<int>* current_head = nullptr;

    cout << function_name << ",";
    for(int i = 0; i < 100; i++) {
        srand(i);
        current_head = createRandomList(10000, 1, 10000);
        for (int j = 0; j < 1000; j++) { // Executa 1000 buscas para ter uma média melhor
            int random_key = (rand() % 10000) + 1; // Gera uma chave aleatória
            timeStart = high_resolution_clock::now();
            searchFunc(current_head, random_key);
            timeStop = high_resolution_clock::now();
            timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
            cout << timeDuration.count() << ",";

            mean += timeDuration.count();
        }

        mean /= 1000; // Média das 1000 buscas
    }

    cout << mean << endl;
}
*/

void testFunctionSearch(string function_name, Node<int>* (*searchFunc)(Node<int>*, int)) {
    const int numIterations = 10;
    const int numSearches = 1000;

    long long totalMean = 0;

    // Inicializa a semente de randomização uma vez
    srand((unsigned)time(0));

    cout << function_name << ",";
    for(int i = 0; i < numIterations; i++) {
        Node<int>* current_head = createRandomList(10000, 1, 10000);
        long long mean = 0;

        for (int j = 0; j < numSearches; j++) {
            int random_key = (rand() % 10000) + 1; // Gera uma chave aleatória

            auto timeStart = high_resolution_clock::now();
            searchFunc(current_head, random_key);
            auto timeStop = high_resolution_clock::now();
            auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
            cout << timeDuration.count() << ",";

            mean += timeDuration.count();
        }

        mean /= numSearches; // Calcula a média dos tempos de busca
    }
     
    cout << totalMean << endl;
}

int main() {
    Node<int>* root = nullptr;

    root = insert(root, createNode(7));
    root = insert(root, createNode(3));
    root = insert(root, createNode(18));
    root = insert(root, createNode(10));
    root = insert(root, createNode(22));
    root = insert(root, createNode(8));
    root = insert(root, createNode(11));
    root = insert(root, createNode(26));

    cout << "Árvore Rubro-Negra (inorder traversal): ";
    inorder(root);
    cout << endl;

    root = deleteNode(root, search(root, 18));

    cout << "Árvore Rubro-Negra após remover o nó 18 (inorder traversal): ";
    inorder(root);
    cout << endl;

    root = insert(root, createNode(5));
    root = insert(root, createNode(15));
    root = insert(root, createNode(30));

    cout << "Árvore Rubro-Negra após inserir 5, 15, 30 (inorder traversal): ";
    inorder(root);
    cout << endl;

    root = deleteNode(root, search(root, 7));

    cout << "Árvore Rubro-Negra após remover o nó 8 (inorder traversal): ";
    inorder(root);
    cout << endl;

    cout << "Altura da árvore: " << height(root) << endl;

    if (isValidRedBlackTree(root)) {
        cout << "Árvore Rubro-Negra válida." << endl;
    } else {
        cout << "Árvore Rubro-Negra inválida." << endl;
    }

    freeTree(root);

    // Testes para o tempo de busca do search
    //testFunctionSearch("Search", search<int>);

    /*
    auto timeStart = high_resolution_clock::now();
    search(root, 40);
    auto timeStop = high_resolution_clock::now();
    auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
    cout << timeDuration.count() << ",";
    */

    return 0;
}
