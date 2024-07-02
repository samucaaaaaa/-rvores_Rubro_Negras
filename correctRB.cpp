#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Enumeração para cores dos nós da árvore
typedef enum { RED, BLACK } Color;

// Estrutura de um nó da árvore
typedef struct Node {
    int key;            // Chave do nó
    struct Node *parent;  // Ponteiro para o pai
    struct Node *left;    // Ponteiro para o filho à esquerda
    struct Node *right;   // Ponteiro para o filho à direita
    Color color;        // Cor do nó (vermelho ou preto)
} Node;

// Estrutura da árvore vermelho-preta
typedef struct {
    Node *root;         // Raiz da árvore
    Node *TNULL;        // Nó nulo (NIL)
} RedBlackTree;

// Função para criar um nó nulo (NIL) com cor preta
Node* createTNULL() {
    Node* TNULL = (Node*)malloc(sizeof(Node));
    TNULL->color = BLACK;  // Nó nulo é sempre preto
    TNULL->left = NULL;
    TNULL->right = NULL;
    return TNULL;
}

// Função para criar um novo nó com chave especificada e cor vermelha
Node* createNode(int key, Node* TNULL) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->parent = NULL;
    node->left = TNULL;
    node->right = TNULL;
    node->color = RED;  // Novo nó é inicializado como vermelho
    return node;
}

// Função para encontrar o nó com valor mínimo na árvore a partir de um dado nó
Node* minimum(RedBlackTree* tree, Node* node) {
    while (node->left != tree->TNULL) {
        node = node->left;
    }
    return node;
}

// Função para realizar rotação à esquerda em torno do nó x
void leftRotate(RedBlackTree* tree, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != tree->TNULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
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
void rightRotate(RedBlackTree* tree, Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != tree->TNULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
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
void fixInsert(RedBlackTree* tree, Node* k) {
    while (k->parent->color == RED) {
        if (k->parent == k->parent->parent->right) {
            Node* u = k->parent->parent->left;
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
            Node* u = k->parent->parent->right;
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
void insert(RedBlackTree* tree, int key) {
    Node* node = createNode(key, tree->TNULL);
    Node* y = NULL;
    Node* x = tree->root;

    while (x != tree->TNULL) {
        y = x;
        if (node->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    node->parent = y;
    if (y == NULL) {
        tree->root = node;
    } else if (node->key < y->key) {
        y->left = node;
    } else {
        y->right = node;
    }

    if (node->parent == NULL) {
        node->color = BLACK;  // Se o novo nó é raiz, garante que seja preto
        return;
    }

    if (node->parent->parent == NULL) {
        return;
    }

    fixInsert(tree, node);  // Corrige a árvore após a inserção
}

// Função para realizar a substituição de um nó u por um nó v na árvore vermelho-preta
void rbTransplant(RedBlackTree* tree, Node* u, Node* v) {
    if (u->parent == NULL) {
        tree->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

// Função para corrigir a árvore vermelho-preta após a remoção de um nó x
void deleteFix(RedBlackTree* tree, Node* x) {
    while (x != tree->root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node* s = x->parent->right;
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
            Node* s = x->parent->left;
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

// Função auxiliar para encontrar o nó com chave especificada na árvore
Node* searchTreeHelper(Node* node, int key, Node* TNULL) {
    if (node == TNULL || key == node->key) {
        return node;
    }

    if (key < node->key) {
        return searchTreeHelper(node->left, key, TNULL);
    }

    return searchTreeHelper(node->right, key, TNULL);
}

// Função para buscar um nó com chave especificada na árvore vermelho-preta
Node* searchTree(RedBlackTree* tree, int key) {
    return searchTreeHelper(tree->root, key, tree->TNULL);
}


// Função para encontrar o nó com valor máximo na árvore a partir de um dado nó
Node* maximum(RedBlackTree* tree, Node* node) {
    while (node->right != tree->TNULL) {
        node = node->right;
    }
    return node;
}

// Função auxiliar para deletar um nó com chave especificada na árvore
void deleteNodeHelper(RedBlackTree* tree, Node* node, int key) {
    Node* z = tree->TNULL;
    Node* x, *y;
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
        printf("Key not found in the tree\n");
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
        deleteFix(tree, x);
    }
}

// Função para deletar um nó com chave especificada na árvore vermelho-preta
void deleteNode(RedBlackTree* tree, int key) {
    deleteNodeHelper(tree, tree->root, key);
}

// Função auxiliar para imprimir a árvore em ordem
void inOrderHelper(Node* node, Node* TNULL) {
    if (node != TNULL) {
        inOrderHelper(node->left, TNULL);
        printf("%d ", node->key);
        inOrderHelper(node->right, TNULL);
    }
}

// Função para percorrer e imprimir a árvore em ordem
void inorder(RedBlackTree* tree) {
    inOrderHelper(tree->root, tree->TNULL);
}

int checkRedBlackPropertiesHelper(Node* node, Node* TNULL, int height, int* black_height) {
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

int isValidRedBlackTree(RedBlackTree* tree) {
    if (tree == NULL || tree->root == tree->TNULL) {
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
void printIndented(Node* root, char* indent, int last) {
    if (root != NULL) {
        printf("%s", indent);
        if (last) {
            printf("└─");
            strcat(indent, "  ");
        } else {
            printf("├─");
            strcat(indent, "| ");
        }
        printf("%d (%s)\n", root->key, root->color == RED ? "RED" : "BLACK");
        printIndented(root->left, indent, 0);
        printIndented(root->right, indent, 1);
        indent[strlen(indent) - 2] = '\0';
    }
}

// Função para visualizar a árvore vermelho-preta
void visualizeRedBlackTree(Node* root) {
    if (root == NULL) {
        printf("Empty tree.\n");
        return;
    }
    char indent[1024] = "";
    printIndented(root, indent, 1);
}

int main() {
    RedBlackTree tree;
    tree.TNULL = createTNULL();
    tree.root = tree.TNULL;

    int keys[] = {7, 3, 18, 10, 22, 8, 11, 26};
    int i;
    for (i = 0; i < sizeof(keys) / sizeof(keys[0]); i++) {
        insert(&tree, keys[i]);
    }

    printf("Árvore Rubro-Negra (inorder traversal):\n");
    inorder(&tree);
    printf("\n");

    if (isValidRedBlackTree(&tree)) {
        printf("Árvore Rubro-Negra VÁLIDA após inserções iniciais.\n");
    } else {
        printf("Árvore Rubro-Negra inválida após inserções iniciais.\n");
    }

    visualizeRedBlackTree(tree.root);

    int more_keys[] = {5, 15, 30, 2, 1};
    for (i = 0; i < sizeof(more_keys) / sizeof(more_keys[0]); i++) {
        insert(&tree, more_keys[i]);
    }

    printf("Árvore Rubro-Negra após mais inserções (inorder traversal):\n");
    inorder(&tree);
    printf("\n");

    if (isValidRedBlackTree(&tree)) {
        printf("Árvore Rubro-Negra VÁLIDA após mais inserções.\n");
    } else {
        printf("Árvore Rubro-Negra INVÁLIDA após mais inserções.\n");
    }

    visualizeRedBlackTree(tree.root);

    deleteNode(&tree, 18);

    printf("Árvore Rubro-Negra após remover o nó 18 (inorder traversal):\n");
    inorder(&tree);
    printf("\n");

    if (isValidRedBlackTree(&tree)) {
        printf("Árvore Rubro-Negra VÁLIDA após remoção de 18.\n");
    } else {
        printf("Árvore Rubro-Negra INVÁLIDA após remoção de 18.\n");
    }

    visualizeRedBlackTree(tree.root);

    deleteNode(&tree, 26);

    printf("Árvore Rubro-Negra após remover o nó 26 (inorder traversal):\n");
    inorder(&tree);
    printf("\n");

    if (isValidRedBlackTree(&tree)) {
        printf("Árvore Rubro-Negra VÁLIDA após remoção de 26.\n");
    } else {
        printf("Árvore Rubro-Negra INVÁLIDA após remoção de 26.\n");
    }

    visualizeRedBlackTree(tree.root);

    insert(&tree, 40);
    insert(&tree, 50);

    printf("Árvore Rubro-Negra após inserir 40 e 50 (inorder traversal):\n");
    inorder(&tree);
    printf("\n");

    if (isValidRedBlackTree(&tree)) {
        printf("Árvore Rubro-Negra VÁLIDA após inserções de 40 e 50.\n");
    } else {
        printf("Árvore Rubro-Negra INVÁLIDA após inserções de 40 e 50.\n");
    }

    visualizeRedBlackTree(tree.root);

    deleteNode(&tree, 2);

    printf("Árvore Rubro-Negra após remover o nó 2 (inorder traversal):\n");
    inorder(&tree);
    printf("\n");

    if (isValidRedBlackTree(&tree)) {
        printf("Árvore Rubro-Negra VÁLIDA após remoção de 2.\n");
    } else {
        printf("Árvore Rubro-Negra INVÁLIDA após remoção de 2.\n");
    }

    visualizeRedBlackTree(tree.root);

    deleteNode(&tree, 30);

    printf("Árvore Rubro-Negra após remover o nó 30 (inorder traversal):\n");
    inorder(&tree);
    printf("\n");

    if (isValidRedBlackTree(&tree)) {
        printf("Árvore Rubro-Negra VÁLIDA após remoção de 30.\n");
    } else {
        printf("Árvore Rubro-Negra INVÁLIDA após remoção de 30.\n");
    }

    visualizeRedBlackTree(tree.root);

    insert(&tree, 30);
    insert(&tree, 2);

    printf("Árvore Rubro-Negra após adicionar 30 e 2 (inorder traversal):\n");
    inorder(&tree);
    printf("\n");

    if (isValidRedBlackTree(&tree)) {
        printf("Árvore Rubro-Negra VÁLIDA após adição de 30 e 2.\n");
    } else {
        printf("Árvore Rubro-Negra INVÁLIDA após adição de 30 e 2.\n");
    }

    visualizeRedBlackTree(tree.root);

    deleteNode(&tree, 8);

    printf("Árvore Rubro-Negra após remover o nó 8 (inorder traversal):\n");
    inorder(&tree);
    printf("\n");

    if (isValidRedBlackTree(&tree)) {
        printf("Árvore Rubro-Negra VÁLIDA após remoção de 8.\n");
    } else {
        printf("Árvore Rubro-Negra INVÁLIDA após remoção de 8.\n");
    }

    deleteNode(&tree, 22);
    deleteNode(&tree, 40);
    deleteNode(&tree, 30);
    deleteNode(&tree, 7);

    printf("Árvore Rubro-Negra após remover o nós  22,40,30, 7(inorder traversal):\n");
    inorder(&tree);
    printf("\n");

    if (isValidRedBlackTree(&tree)) {
        printf("Árvore Rubro-Negra VÁLIDA após remoção de 22,40,30 e 7.\n");
    } else {
        printf("Árvore Rubro-Negra INVÁLIDA após remoção de 22,40,30 e 7.\n");
    }

    visualizeRedBlackTree(tree.root);

    return 0;
}
