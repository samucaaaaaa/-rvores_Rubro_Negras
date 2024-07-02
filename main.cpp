#include <iostream>
#include <cstdlib>
#include <string> 
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
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != nullptr) {
        v->parent = u->parent;
    }
    return root;
}
template <typename T>
Node<T>* deleteFixUp(Node<T>* root, Node<T>* x) {
    while (x != root && (x == nullptr || x->color == BLACK)) {
        if (x == x->parent->left) {
            Node<T>* w = x->parent->right;
            if (w != nullptr && w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                root = rotateLeft(root, x->parent);
                w = x->parent->right;
            }
            if (w == nullptr ||
                (w->left == nullptr || w->left->color == BLACK) &&
                (w->right == nullptr || w->right->color == BLACK)) {
                if (w != nullptr) w->color = RED;
                x = x->parent;
            } else {
                if (w == nullptr || w->right == nullptr || w->right->color == BLACK) {
                    if (w != nullptr && w->left != nullptr) w->left->color = BLACK;
                    if (w != nullptr) w->color = RED;
                    root = rotateRight(root, w);
                    w = x->parent->right;
                }
                if (w != nullptr) w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w != nullptr && w->right != nullptr) w->right->color = BLACK;
                root = rotateLeft(root, x->parent);
                x = root;
            }
        } else {
            Node<T>* w = x->parent->left;
            if (w != nullptr && w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                root = rotateRight(root, x->parent);
                w = x->parent->left;
            }
            if (w == nullptr ||
                (w->right == nullptr || w->right->color == BLACK) &&
                (w->left == nullptr || w->left->color == BLACK)) {
                if (w != nullptr) w->color = RED;
                x = x->parent;
            } else {
                if (w == nullptr || w->left == nullptr || w->left->color == BLACK) {
                    if (w != nullptr && w->right != nullptr) w->right->color = BLACK;
                    if (w != nullptr) w->color = RED;
                    root = rotateLeft(root, w);
                    w = x->parent->left;
                }
                if (w != nullptr) w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w != nullptr && w->left != nullptr) w->left->color = BLACK;
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
    if (yOriginalColor == BLACK && x != nullptr) {
        root = deleteFixUp(root, x);
    }
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
    int blackHeight = -1; // Inicialização com valor inválido
    bool isRootBlack = (root == nullptr) || (root->color == BLACK);

    return validateRedBlackTree(root, blackHeight) && isRootBlack;
}

// Função auxiliar recursiva para validar a árvore Rubro-Negra
template <typename T>
bool validateRedBlackTree(Node<T>* node, int& blackHeight) {
    if (node == nullptr) {
        blackHeight = 0; // Nó nulo contribui com altura preta 0
        return true;
    }

    // Verifica se nenhum nó vermelho tem filhos vermelhos
    if (node->color == RED) {
        if ((node->left && node->left->color == RED) || (node->right && node->right->color == RED)) {
            std::cout << "Red node " << node->data << " has red child." << std::endl;
            return false;
        }

        // Verifica se o pai de um nó vermelho não é vermelho
        if (node->parent && node->parent->color == RED) {
            std::cout << "Node " << node->data << " and parent " << node->parent->data << " are both RED." << std::endl;
            return false;
        }
    }

    // Verifica se o nó atual está apontando corretamente para o pai
    if (node->left && node->left->parent != node) {
        std::cout << "Node " << node->left->data << " has wrong parent, expected " << node->data << std::endl;
        return false;
    }
    if (node->right && node->right->parent != node) {
        std::cout << "Node " << node->right->data << " has wrong parent, expected " << node->data << std::endl;
        return false;
    }

    // Verifica a altura dos nós pretos nos caminhos da raiz até as folhas
    int leftBlackHeight, rightBlackHeight;
    bool leftValid = validateRedBlackTree(node->left, leftBlackHeight);
    bool rightValid = validateRedBlackTree(node->right, rightBlackHeight);

    if (leftValid && rightValid && leftBlackHeight == rightBlackHeight) {
        blackHeight = leftBlackHeight + (node->color == BLACK ? 1 : 0);
        return true;
    } else {
        std::cout << "Black height mismatch for node " << node->data << std::endl;
        return false;
    }
}


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

template <typename T>
void printIndented(Node<T>* root, std::string indent = "", bool last = true) {
    if (root == nullptr) {
        return;
    }

    std::cout << indent;
    if (last) {
        std::cout << "└─";
        indent += "  ";
    } else {
        std::cout << "├─";
        indent += "│ ";
    }

    std::cout << root->data;
    if (root->color == RED) {
        std::cout << " (RED)";
    } else {
        std::cout << " (BLACK)";
    }
    std::cout << std::endl;

    printIndented(root->right, indent, false);
    printIndented(root->left, indent, true);
}

template <typename T>
void visualizeRedBlackTree(Node<T>* root) {
    std::cout << "Árvore Rubro-Negra (visualização top-down):" << std::endl;
    printIndented(root);
}

int main() {
    Node<int>* root = nullptr;

    // Inserção de nós
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

    // Verifica a validade da árvore após inserção inicial
    if (isValidRedBlackTree(root)) {
        cout << "Árvore Rubro-Negra VÁLIDA após inserções iniciais." << endl;
    } else {
        cout << "Árvore Rubro-Negra inválida após inserções iniciais." << endl;
    }

    // Inserção de mais nós
    root = insert(root, createNode(5));
    root = insert(root, createNode(15));
    root = insert(root, createNode(30));
    root = insert(root, createNode(2));
    root = insert(root, createNode(1));
    visualizeRedBlackTree(root);

    cout << "Árvore Rubro-Negra após mais inserções (inorder traversal): ";
    inorder(root);
    cout << endl;

    // Verifica a validade da árvore após mais inserções
    if (isValidRedBlackTree(root)) {
        cout << "Árvore Rubro-Negra VÁLIDA após mais inserções." << endl;
    } else {
        cout << "Árvore Rubro-Negra INVÁLIDA após mais inserções." << endl;
    }

    // Exclusão de nós
    Node<int>* nodeToDelete = search(root, 18);
    if (nodeToDelete) {
        deleteNode(root, nodeToDelete);
    } else {
        cout << "Node 18 not found for deletion." << endl;
    }

    cout << "Árvore Rubro-Negra após remover o nó 18 (inorder traversal): ";
    inorder(root);
    cout << endl;

    // Verifica a validade da árvore após a remoção de 18
    if (isValidRedBlackTree(root)) {
        cout << "Árvore Rubro-Negra VÁLIDA após remoção de 18." << endl;
    } else {
        cout << "Árvore Rubro-Negra INVÁLIDA após remoção de 18." << endl;
    }

    // Mais exclusões
    nodeToDelete = search(root, 26);
    if (nodeToDelete) {
        deleteNode(root, nodeToDelete);
    } else {
        cout << "Node 26 not found for deletion." << endl;
    }

    cout << "Árvore Rubro-Negra após remover o nó 26 (inorder traversal): ";
    inorder(root);
    cout << endl;

    if (isValidRedBlackTree(root)) {
        cout << "Árvore Rubro-Negra VÁLIDA após remoção de 26." << endl;
    } else {
        cout << "Árvore Rubro-Negra INVÁLIDA após remoção de 26." << endl;
    }
    // Testando casos de borda
    root = insert(root, createNode(40)); 
    root = insert(root, createNode(50));


    cout << "Árvore Rubro-Negra após inserir 40 e 50 (inorder traversal): ";
    inorder(root);
    cout << endl;

    if (isValidRedBlackTree(root)) {
        cout << "Árvore Rubro-Negra VÁLIDA após inserções de 40 e 50." << endl;
    } else {
        cout << "Árvore Rubro-Negra INVÁLIDA após inserções de 40 e 50." << endl;
    }

    nodeToDelete = search(root, 2);
    if (nodeToDelete) {
        deleteNode(root, nodeToDelete);
    } else {
        cout << "Node 2 not found for deletion." << endl;
    }

    cout << "Árvore Rubro-Negra após remover o nó 2 (inorder traversal): ";
    inorder(root);
    cout << endl;

    if (isValidRedBlackTree(root)) {
        cout << "Árvore Rubro-Negra VÁLIDA após remoção de 2." << endl;
    } else {
        cout << "Árvore Rubro-Negra INVÁLIDA após remoção de 2." << endl;
    }

    nodeToDelete = search(root, 30);
    if (nodeToDelete) {
        deleteNode(root, nodeToDelete);
    } else {
        cout << "Node 30 not found for deletion." << endl;
    }

    cout << "Árvore Rubro-Negra após remover o nó 30 (inorder traversal): ";
    inorder(root);
    cout << endl;

    if (isValidRedBlackTree(root)) {
        cout << "Árvore Rubro-Negra VÁLIDA após remoção de 30." << endl;
    } else {
        cout << "Árvore Rubro-Negra INVÁLIDA após remoção de 30." << endl;
    }

    root = insert(root, createNode(30)); 
    root = insert(root, createNode(2));
    cout << "Árvore Rubro-Negra após após adição do 30 e 2 (inorder traversal): ";
    inorder(root);
    cout << endl;

   if (isValidRedBlackTree(root)) {
        cout << "Árvore Rubro-Negra VÁLIDA após adição do 30 e 2." << endl;
    } else {
        cout << "Árvore Rubro-Negra INVÁLIDA após adição d0 30 e 2." << endl;
    }

    nodeToDelete = search(root, 8);
    if (nodeToDelete) {
        deleteNode(root, nodeToDelete);
    } else {
        cout << "Node 8 not found for deletion." << endl;
    }
    visualizeRedBlackTree(root);

    cout << "Árvore Rubro-Negra após remover o nó 8 (inorder traversal): ";
    inorder(root);
    cout << endl;
    if (isValidRedBlackTree(root)) {
        cout << "Árvore Rubro-Negra VÁLIDA após remoção de 8." << endl;
    } else {
        cout << "Árvore Rubro-Negra INVÁLIDA após remoção de 8." << endl;
    }
    visualizeRedBlackTree(root);
    return 0;
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


/*
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
*/

    // Testes para o tempo de busca do search
    //testFunctionSearch("Search", search<int>);

    /*
    auto timeStart = high_resolution_clock::now();
    search(root, 40);
    auto timeStop = high_resolution_clock::now();
    auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
    cout << timeDuration.count() << ",";
    */
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
