#include <iostream>
#include <cstdlib>
#include <chrono>
#include <string.h>
#include "red_black_tree.h"

using chrono::high_resolution_clock;
using chrono::duration_cast;
using chrono::nanoseconds;

namespace rbt
{
    // Função para criar e inicializar um nó nulo (NIL)
    template <typename T>
    Node<T>* createTNULL() {
        Node<T>* nullNode = (Node<T>*)malloc(sizeof(Node<T>));
        if (nullNode == nullptr) {
            cerr << "Falha na alocação de memória" << endl;
            exit(1);
        }
        nullNode->key = T();        // Inicializa a chave com o valor padrão de T
        nullNode->color = BLACK;    // Nó nulo é sempre preto
        nullNode->parent = nullptr;
        nullNode->left = nullptr;
        nullNode->right = nullptr;
        return nullNode;
    }

    // Função para criar um novo nó com chave especificada e cor vermelha
    template <typename T>
    Node<T>* createNode(T key, Node<T>* nullNode) {
        Node<T>* newNode = (Node<T>*)malloc(sizeof(Node<T>));
        newNode->key = key;
        newNode->parent = nullptr;
        newNode->left = nullNode;
        newNode->right = nullNode;
        newNode->color = RED;  // Novo nó é inicializado como vermelho
        return newNode;
    }

    // Função para realizar rotação à esquerda em torno do nó x
    template <typename T>
    void leftRotate(RedBlackTree<T>* tree, Node<T>* nodeX) {
        Node<T>* nodeY = nodeX->right;
        nodeX->right = nodeY->left;
        if (nodeY->left != tree->TNULL) {
            nodeY->left->parent = nodeX;
        }
        nodeY->parent = nodeX->parent;
        if (nodeX->parent == nullptr) {
            tree->root = nodeY;
        } else if (nodeX == nodeX->parent->left) {
            nodeX->parent->left = nodeY;
        } else {
            nodeX->parent->right = nodeY;
        }
        nodeY->left = nodeX;
        nodeX->parent = nodeY;
    }

    // Função para realizar rotação à direita em torno do nó x
    template <typename T>
    void rightRotate(RedBlackTree<T>* tree, Node<T>* nodeX) {
        Node<T>* nodeY = nodeX->left;
        nodeX->left = nodeY->right;
        if (nodeY->right != tree->TNULL) {
            nodeY->right->parent = nodeX;
        }
        nodeY->parent = nodeX->parent;
        if (nodeX->parent == nullptr) {
            tree->root = nodeY;
        } else if (nodeX == nodeX->parent->right) {
            nodeX->parent->right = nodeY;
        } else {
            nodeX->parent->left = nodeY;
        }
        nodeY->right = nodeX;
        nodeX->parent = nodeY;
    }

    // Função para corrigir a árvore vermelho-preta após a inserção de um novo nó
    template <typename T>
    void fixInsert(RedBlackTree<T>* tree, Node<T>* newNode) {
        while (newNode->parent->color == RED) {
            if (newNode->parent == newNode->parent->parent->right) {
                Node<T>* uncleNode = newNode->parent->parent->left;
                if (uncleNode->color == RED) {
                    uncleNode->color = BLACK;
                    newNode->parent->color = BLACK;
                    newNode->parent->parent->color = RED;
                    newNode = newNode->parent->parent;
                } else {
                    if (newNode == newNode->parent->left) {
                        newNode = newNode->parent;
                        rightRotate(tree, newNode);
                    }
                    newNode->parent->color = BLACK;
                    newNode->parent->parent->color = RED;
                    leftRotate(tree, newNode->parent->parent);
                }
            } else {
                Node<T>* uncleNode = newNode->parent->parent->right;
                if (uncleNode->color == RED) {
                    uncleNode->color = BLACK;
                    newNode->parent->color = BLACK;
                    newNode->parent->parent->color = RED;
                    newNode = newNode->parent->parent;
                } else {
                    if (newNode == newNode->parent->right) {
                        newNode = newNode->parent;
                        leftRotate(tree, newNode);
                    }
                    newNode->parent->color = BLACK;
                    newNode->parent->parent->color = RED;
                    rightRotate(tree, newNode->parent->parent);
                }
            }
            if (newNode == tree->root) {
                break;
            }
        }
        tree->root->color = BLACK;  // Garante que a raiz seja preta
    }

    // Função para inserir um novo nó com chave especificada na árvore vermelho-preta
    template <typename T>
    void insert(RedBlackTree<T>* tree, T key) {
        Node<T>* newNode = createNode(key, tree->TNULL);
        Node<T>* parentNode = nullptr;
        Node<T>* currentNode = tree->root;

        while (currentNode != tree->TNULL) {
            parentNode = currentNode;
            if (newNode->key < currentNode->key) {
                currentNode = currentNode->left;
            } else {
                currentNode = currentNode->right;
            }
        }

        newNode->parent = parentNode;
        if (parentNode == nullptr) {
            tree->root = newNode;
        } else if (newNode->key < parentNode->key) {
            parentNode->left = newNode;
        } else {
            parentNode->right = newNode;
        }

        if (newNode->parent == nullptr) {
            newNode->color = BLACK;  // Se o novo nó é raiz, garante que seja preto
            return;
        }

        if (newNode->parent->parent == nullptr) {
            return;
        }

        fixInsert(tree, newNode);  // Corrige a árvore após a inserção
    }

    // Função para encontrar o nó com valor mínimo na árvore a partir de um dado nó
    template <typename T>
    Node<T>* minimum(RedBlackTree<T>* tree, Node<T>* currentNode) {
        while (currentNode->left != tree->TNULL) {
            currentNode = currentNode->left;
        }
        return currentNode;
    }

    // Função para encontrar o nó com valor máximo na árvore a partir de um dado nó
    template <typename T>
    Node<T>* maximum(RedBlackTree<T>* tree, Node<T>* currentNode) {
        while (currentNode->right != tree->TNULL) {
            currentNode = currentNode->right;
        }
        return currentNode;
    }

    // Função para calcular a altura da árvore
    template <typename T>
    int height(Node<T>* currentNode) {
        if (currentNode == nullptr) return 0;
        int leftHeight = height(currentNode->left);
        int rightHeight = height(currentNode->right);
        return 1 + max(leftHeight, rightHeight);
    }

    // Função auxiliar para imprimir a árvore em ordem
    template <typename T>
    void inorderHelper(Node<T>* currentNode, Node<T>* nullNode) {
        if (currentNode != nullNode) {
            inorderHelper(currentNode->left, nullNode);
            cout << currentNode->key << " ";
            inorderHelper(currentNode->right, nullNode);
        }
    }

    // Função para percorrer e imprimir a árvore em ordem
    template <typename T>
    void inorder(RedBlackTree<T>* tree) {
        inorderHelper(tree->root, tree->TNULL);
    }

    // Função para realizar a substituição de um nó por outro nó na árvore vermelho-preta
    template <typename T>
    void rbTransplant(RedBlackTree<T>* tree, Node<T>* nodeU, Node<T>* nodeV) {
        if (nodeU->parent == nullptr) {
            tree->root = nodeV;
        } else if (nodeU == nodeU->parent->left) {
            nodeU->parent->left = nodeV;
        } else {
            nodeU->parent->right = nodeV;
        }
        nodeV->parent = nodeU->parent;
    }

    // Função para corrigir a árvore vermelho-preta após a remoção de um nó 
    template <typename T>
    void deleteFixUp(RedBlackTree<T>* tree, Node<T>* nodeX) {
        while (nodeX != tree->root && nodeX->color == BLACK) {
            if (nodeX == nodeX->parent->left) {
                Node<T>* siblingNode = nodeX->parent->right;
                if (siblingNode->color == RED) {
                    siblingNode->color = BLACK;
                    nodeX->parent->color = RED;
                    leftRotate(tree, nodeX->parent);
                    siblingNode = nodeX->parent->right;
                }

                if (siblingNode->left->color == BLACK && siblingNode->right->color == BLACK) {
                    siblingNode->color = RED;
                    nodeX = nodeX->parent;
                } else {
                    if (siblingNode->right->color == BLACK) {
                        siblingNode->left->color = BLACK;
                        siblingNode->color = RED;
                        rightRotate(tree, siblingNode);
                        siblingNode = nodeX->parent->right;
                    }
                    siblingNode->color = nodeX->parent->color;
                    nodeX->parent->color = BLACK;
                    siblingNode->right->color = BLACK;
                    leftRotate(tree, nodeX->parent);
                    nodeX = tree->root;
                }
            } else {
                Node<T>* siblingNode = nodeX->parent->left;
                if (siblingNode->color == RED) {
                    siblingNode->color = BLACK;
                    nodeX->parent->color = RED;
                    rightRotate(tree, nodeX->parent);
                    siblingNode = nodeX->parent->left;
                }

                if (siblingNode->right->color == BLACK && siblingNode->right->color == BLACK) {
                    siblingNode->color = RED;
                    nodeX = nodeX->parent;
                } else {
                    if (siblingNode->left->color == BLACK) {
                        siblingNode->right->color = BLACK;
                        siblingNode->color = RED;
                        leftRotate(tree, siblingNode);
                        siblingNode = nodeX->parent->left;
                    }
                    siblingNode->color = nodeX->parent->color;
                    nodeX->parent->color = BLACK;
                    siblingNode->left->color = BLACK;
                    rightRotate(tree, nodeX->parent);
                    nodeX = tree->root;
                }
            }
        }
        nodeX->color = BLACK;
    }

    // Função auxiliar para deletar um nó com chave especificada na árvore
    template <typename T>
    void deleteNodeHelper(RedBlackTree<T>* tree, Node<T>* node, T key) {
        Node<T>* nodeZ = tree->TNULL;
        Node<T>* currentNode = tree->root;
        Node<T>* nodeY;
        Node<T>* nodeX;

        while (currentNode != tree->TNULL) {
            if (currentNode->key == key) {
                nodeZ = currentNode;
            }
            if (currentNode->key <= key) {
                currentNode = currentNode->right;
            } else {
                currentNode = currentNode->left;
            }
        }

        if (nodeZ == tree->TNULL) {
            cout << "Nó com chave " << key << " não encontrado na árvore." << endl;
            return;
        }

        nodeY = nodeZ;
        int originalColor = nodeY->color;
        if (nodeZ->left == tree->TNULL) {
            nodeX = nodeZ->right;
            rbTransplant(tree, nodeZ, nodeZ->right);
        } else if (nodeZ->right == tree->TNULL) {
            nodeX = nodeZ->left;
            rbTransplant(tree, nodeZ, nodeZ->left);
        } else {
            nodeY = minimum(tree, nodeZ->right);
            originalColor = nodeY->color;
            nodeX = nodeY->right;
            if (nodeY->parent == nodeZ) {
                nodeX->parent = nodeY;
            } else {
                rbTransplant(tree, nodeY, nodeY->right);
                nodeY->right = nodeZ->right;
                nodeY->right->parent = nodeY;
            }
            rbTransplant(tree, nodeZ, nodeY);
            nodeY->left = nodeZ->left;
            nodeY->left->parent = nodeY;
            nodeY->color = nodeZ->color;
        }
        free(nodeZ);
        if (originalColor == BLACK) {
            deleteFixUp(tree, nodeX);
        }
    }

    // Função para deletar um nó com chave especificada na árvore vermelho-preta
    template <typename T>
    void deleteNode(RedBlackTree<T>* tree, T key) {
        deleteNodeHelper(tree, tree->root, key);
    }

    // Função auxiliar para encontrar o nó com chave especificada na árvore
    template <typename T>
    Node<T>* searchTreeHelper(Node<T>* node, T key, Node<T>* TNULL) {
        if (node == TNULL || key == node->key) {
            return node;
        }

        if (key < node->key) {
            return searchTreeHelper(node->left, key, TNULL);
        }

        return searchTreeHelper(node->right, key, TNULL);
    }

    // Função para buscar um nó com chave especificada na árvore vermelho-preta
    template <typename T>
    Node<T>* searchTree(RedBlackTree<T>* tree, T key) {
        return searchTreeHelper(tree->root, key, tree->TNULL);
    }

    // Função para verificar se uma árvore binária atende às propriedades de uma árvore rubro-negra
    template <typename T>
    int checkRedBlackPropertiesHelper(Node<T>* node, Node<T>* TNULL, int height, int* black_height) {
        if (node == TNULL) {
            if (*black_height == -1) {
                *black_height = height;
            } else if (height != *black_height) {
                return 0;
            }
            return 1;
        }

        // Verifica se um nó vermelho tem dois filhos vermelhos
        if (node->color == RED) {
            if ((node->left != TNULL && node->left->color == RED) ||
                (node->right != TNULL && node->right->color == RED)) {
                return 0;
            }
        }

        if (node->color == BLACK) {
            height++;
        }

        return checkRedBlackPropertiesHelper(node->left, TNULL, height, black_height) &&
            checkRedBlackPropertiesHelper(node->right, TNULL, height, black_height);
    }

    // Função para verificar se uma árvore rubro-negra é válida de acordo com as suas propriedades fundamentais
    template <typename T>
    int isValidRedBlackTree(RedBlackTree<T>* tree) {
        if (tree == nullptr || tree->root == tree->TNULL) {
            return 1;
        }

        // Verifica se a raiz é preta
        if (tree->root->color != BLACK) {
            return 0;
        }

        int black_height = -1;
        return checkRedBlackPropertiesHelper(tree->root, tree->TNULL, 0, &black_height);
    }

    // Função auxiliar para imprimir a árvore com indentação
    template <typename T>
    void printIndented(Node<T>* root, char* indent, T last) {
        if (root != nullptr) {
            printf("%s", indent);
            if (last) {
                printf("└─");
                strcat(indent, "  ");
            } else {
                printf("├─");
                strcat(indent, "| ");
            }
            cout << root->key << " (" << (root->color == RED ? "RED" : "BLACK") << ")" << endl;
            printIndented(root->left, indent, 0);
            printIndented(root->right, indent, 1);
            indent[strlen(indent) - 2] = '\0';
        }
    }

    // Função para visualizar a árvore vermelho-preta
    template <typename T>
    void visualizeRedBlackTree(Node<T>* root) {
        if (root == nullptr) {
            cout << "Árvore vazia." << endl;
            return;
        }
        char indent[1024] = "";
        printIndented(root, indent, 1);
    }

    // Função para criar uma lista de nós com valores aleatórios
    template <typename T>
    Node<T>* createRandomList(int iLength, int start, int stop, RedBlackTree<T>* tree) {
        if (iLength <= 0 || start >= stop) {
            return tree->TNULL; 
        }

        srand((unsigned)time(0)); 

        for (int i = 0; i < iLength; ++i) {
            int randomValue = (rand() % (stop - start)) + start; 
            insert(tree, randomValue); 
        }

        return tree->root; 
    }

    // Função para obter os tempos que a função de busca leva para encontrar vários nós
    template <typename T>
    void testFunctionSearch(string function_name, Node<T>* (*searchFunc)(RedBlackTree<T>*, T)) {
        const int numIterations = 30;
        const int numSearches = 10000;

        long long totalMean = 0;

        // Inicializa a semente de randomização uma vez
        srand((unsigned)time(0));
        cout << "TESTES PARA OS TEMPOS DA FUNCAO searchTree:\n" << endl;
        for(int i = 0; i < numIterations; i++) {
            // Cria uma nova árvore rubro-negra para cada iteração
            RedBlackTree<int> tree;
            tree.TNULL = createTNULL<T>();
            tree.root = tree.TNULL;

            Node<T>* current_head = createRandomList(100000, 1, 100000, &tree);
            long long mean = 0;

            for (int j = 0; j < numSearches; j++) {
                int random_key = (rand() % 100000) + 1; // Gera uma chave aleatória

                auto timeStart = high_resolution_clock::now();
                searchFunc(&tree, random_key);
                auto timeStop = high_resolution_clock::now();
                auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);

                mean += timeDuration.count();
            }

            mean /= numSearches; // Calcula a média dos tempos de busca
            totalMean += mean;
            cout << "Tempo Medio da iteracao " << i << ": " << mean << "ns" << endl; // Imprime a média para esta iteração
        }

        totalMean /= numIterations; // Calcula a média total das médias
        cout << "Media Total dos tempos: " << totalMean << "ns" << endl; // Imprime a média total
    }

    // Função para obter os tempos que as funções maximum e minimum levam para encontrar os nós de várias árvores
    template <typename T>
    void testFunctionMaxMin(string function_name, Node<T>* (*searchFunc)(RedBlackTree<T>*, Node<T>*)) {
        const int numIterations = 30;
        const int numNodes = 100000;
        const int numRepetitions = 10000; 

        long long totalMean = 0;

        // Inicializa a semente de randomização uma vez
        srand(static_cast<unsigned>(time(0)));
        cout << "TESTES PARA OS TEMPOS DA FUNCAO " << function_name << ":\n" << endl;

        for (int i = 0; i < numIterations; i++) {
            // Cria uma nova árvore rubro-negra para cada iteração
            RedBlackTree<T> tree;
            tree.TNULL = createTNULL<T>();
            tree.root = tree.TNULL;

            Node<T>* current_head = createRandomList(numNodes, 1, numNodes, &tree);
            long long mean = 0;

            // Executa a função de busca várias vezes por iteração
            auto timeStart = high_resolution_clock::now();
            for (int j = 0; j < numRepetitions; j++) {
                searchFunc(&tree, tree.root);
            }
            auto timeStop = high_resolution_clock::now();
            auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);

            mean = timeDuration.count() / numRepetitions;

            totalMean += mean;
            cout << "Tempo da iteracao " << i << ": " << mean << "ns" << endl; 
        }

        // Calcula a média total dos tempos
        totalMean /= numIterations; 
        cout << "Media Total dos tempos: " << totalMean << "ns" << endl; 
    }
}