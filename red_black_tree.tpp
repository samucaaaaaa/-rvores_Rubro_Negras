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
        Node<T>* TNULL = (Node<T>*)malloc(sizeof(Node<T>));
        if (TNULL == nullptr) {
            cerr << "Falha na alocação de memória" << endl;
            exit(1);
        }
        TNULL->key = T();        // Inicializa a chave com o valor padrão de T
        TNULL->color = BLACK;    // Nó nulo é sempre preto
        TNULL->parent = nullptr;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        return TNULL;
    }

    // Função para criar um novo nó com chave especificada e cor vermelha
    template <typename T>
    Node<T>* createNode(T key, Node<T>* TNULL) {
        Node<T>* node = (Node<T>*)malloc(sizeof(Node<T>));
        node->key = key;
        node->parent = nullptr;
        node->left = TNULL;
        node->right = TNULL;
        node->color = RED;  // Novo nó é inicializado como vermelho
        return node;
    }

    // Função para realizar rotação à esquerda em torno do nó x
    template <typename T>
    void leftRotate(RedBlackTree<T>* tree, Node<T>* x) {
        Node<T>* y = x->right;
        x->right = y->left;
        if (y->left != tree->TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            tree->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    // Função para realizar rotação à direita em torno do nó x
    template <typename T>
    void rightRotate(RedBlackTree<T>* tree, Node<T>* x) {
        Node<T>* y = x->left;
        x->left = y->right;
        if (y->right != tree->TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            tree->root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    // Função para corrigir a árvore vermelho-preta após a inserção de um novo nó k
    template <typename T>
    void fixInsert(RedBlackTree<T>* tree, Node<T>* k) {
        while (k->parent->color == RED) {
            if (k->parent == k->parent->parent->right) {
                Node<T>* u = k->parent->parent->left;
                if (u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(tree, k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    leftRotate(tree, k->parent->parent);
                }
            } else {
                Node<T>* u = k->parent->parent->right;
                if (u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(tree, k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rightRotate(tree, k->parent->parent);
                }
            }
            if (k == tree->root) {
                break;
            }
        }
        tree->root->color = BLACK;  // Garante que a raiz seja preta
    }

    // Função para inserir um novo nó com chave especificada na árvore vermelho-preta
    template <typename T>
    void insert(RedBlackTree<T>* tree, T key) {
        Node<T>* node = createNode(key, tree->TNULL);
        Node<T>* y = nullptr;
        Node<T>* x = tree->root;

        while (x != tree->TNULL) {
            y = x;
            if (node->key < x->key) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            tree->root = node;
        } else if (node->key < y->key) {
            y->left = node;
        } else {
            y->right = node;
        }

        if (node->parent == nullptr) {
            node->color = BLACK;  // Se o novo nó é raiz, garante que seja preto
            return;
        }

        if (node->parent->parent == nullptr) {
            return;
        }

        fixInsert(tree, node);  // Corrige a árvore após a inserção
    }

    // Função para encontrar o nó com valor mínimo na árvore a partir de um dado nó
    template <typename T>
    Node<T>* minimum(RedBlackTree<T>* tree, Node<T>* node) {
        while (node->left != tree->TNULL) {
            node = node->left;
        }
        return node;
    }

    // Função para encontrar o nó com valor máximo na árvore a partir de um dado nó
    template <typename T>
    Node<T>* maximum(RedBlackTree<T>* tree, Node<T>* node) {
        while (node->right != tree->TNULL) {
            node = node->right;
        }
        return node;
    }

    // Função para calcular a altura da árvore
    template <typename T>
    int height(Node<T>* node) {
        if (node == nullptr) return 0;
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        return 1 + max(leftHeight, rightHeight);
    }

    // Função auxiliar para imprimir a árvore em ordem
    template <typename T>
    void inorderHelper(Node<T>* node, Node<T>* TNULL) {
        if (node != TNULL) {
            inorderHelper(node->left, TNULL);
            cout << node->key << " ";
            inorderHelper(node->right, TNULL);
        }
    }

    // Função para percorrer e imprimir a árvore em ordem
    template <typename T>
    void inorder(RedBlackTree<T>* tree) {
        inorderHelper(tree->root, tree->TNULL);
    }

    // Função para realizar a substituição de um nó u por um nó v na árvore vermelho-preta
    template <typename T>
    void rbTransplant(RedBlackTree<T>* tree, Node<T>* u, Node<T>* v) {
        if (u->parent == nullptr) {
            tree->root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    // Função para corrigir a árvore vermelho-preta após a remoção de um nó x
    template <typename T>
    void deleteFixUp(RedBlackTree<T>* tree, Node<T>* x) {
        while (x != tree->root && x->color == BLACK) {
            if (x == x->parent->left) {
                Node<T>* s = x->parent->right;
                if (s->color == RED) {
                    s->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(tree, x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == BLACK && s->right->color == BLACK) {
                    s->color = RED;
                    x = x->parent;
                } else {
                    if (s->right->color == BLACK) {
                        s->left->color = BLACK;
                        s->color = RED;
                        rightRotate(tree, s);
                        s = x->parent->right;
                    }

                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->right->color = BLACK;
                    leftRotate(tree, x->parent);
                    x = tree->root;
                }
            } else {
                Node<T>* s = x->parent->left;
                if (s->color == RED) {
                    s->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(tree, x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == BLACK && s->left->color == BLACK) {
                    s->color = RED;
                    x = x->parent;
                } else {
                    if (s->left->color == BLACK) {
                        s->right->color = BLACK;
                        s->color = RED;
                        leftRotate(tree, s);
                        s = x->parent->left;
                    }

                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->left->color = BLACK;
                    rightRotate(tree, x->parent);
                    x = tree->root;
                }
            }
        }
        x->color = BLACK;  // Garante que x seja preto após a correção
    }

    // Função auxiliar para deletar um nó com chave especificada na árvore
    template <typename T>
    void deleteNodeHelper(RedBlackTree<T>* tree, Node<T>* node, T key) {
        Node<T>* z = tree->TNULL;
        Node<T>* x, *y;
        while (node != tree->TNULL) {
            if (node->key == key) {
                z = node;
            }

            if (node->key <= key) {
                node = node->right;
            } else {
                node = node->left;
            }
        }

        if (z == tree->TNULL) {
            cout << "Chave não encontrada na árvore" << endl;
            return;
        }

        y = z;
        Color y_original_color = y->color;
        if (z->left == tree->TNULL) {
            x = z->right;
            rbTransplant(tree, z, z->right);
        } else if (z->right == tree->TNULL) {
            x = z->left;
            rbTransplant(tree, z, z->left);
        } else {
            y = minimum(tree, z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                rbTransplant(tree, y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            rbTransplant(tree, z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        free(z);
        if (y_original_color == BLACK) {
            deleteFixUp(tree, x);
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

    template <typename T>
    void freeTree(Node<T>* root) {
        if (root == nullptr) return;
        freeTree(root->left);
        freeTree(root->right);
        free(root);
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

            // Limpeza da árvore atual
            freeTree(tree.root);
        }

        // Calcula a média total dos tempos
        totalMean /= numIterations; 
        cout << "Media Total dos tempos: " << totalMean << "ns" << endl; 
    }
}