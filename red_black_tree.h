#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

using namespace std;

// Enumeração para cores dos nós da árvore
typedef enum { RED, BLACK } Color;

namespace rbt
{
    // Estrutura de um nó da árvore
    template <typename T>
    struct Node {
        T key;            // Chave do nó
        Node<T>* parent;  // Ponteiro para o pai
        Node<T>* left;    // Ponteiro para o filho à esquerda
        Node<T>* right;   // Ponteiro para o filho à direita
        Color color;      // Cor do nó (vermelho ou preto)
    };

    // Estrutura da árvore vermelho-preta
    template <typename T>
    struct RedBlackTree {
        Node<T>* root;    // Raiz da árvore
        Node<T>* TNULL;   // Nó nulo (NIL)
    };

    template <typename T>
    Node<T>* createTNULL();

    template <typename T>
    Node<T>* createNode(T, Node<T>*);   

    template <typename T>
    void leftRotate(RedBlackTree<T>*, Node<T>*);

    template <typename T>
    void rightRotate(RedBlackTree<T>*, Node<T>*);

    template <typename T>
    void fixInsert(RedBlackTree<T>*, Node<T>*);

    template <typename T>
    void insert(RedBlackTree<T>*, T);

    template <typename T>
    Node<T>* minimum(RedBlackTree<T>*, Node<T>*);

    template <typename T>
    Node<T>* maximum(RedBlackTree<T>*, Node<T>*);

    template <typename T>
    int height(Node<T>*);

    template <typename T>
    void inorderHelper(Node<T>*, Node<T>*);

    template <typename T>
    void inorder(RedBlackTree<T>*);

    template <typename T>
    void rbTransplant(RedBlackTree<T>*, Node<T>*, Node<T>*);

    template <typename T>
    void deleteFixUp(RedBlackTree<T>*, Node<T>*);

    template <typename T>
    void deleteNodeHelper(RedBlackTree<T>*, Node<T>*, T);

    template <typename T>
    void deleteNode(RedBlackTree<T>*, T);

    template <typename T>
    Node<T>* searchTreeHelper(Node<T>*, T, Node<T>*);

    template <typename T>
    Node<T>* searchTree(RedBlackTree<T>*, T);

    template <typename T>
    int checkRedBlackPropertiesHelper(Node<T>*, Node<T>*, int, int*);

    template <typename T>
    int isValidRedBlackTree(RedBlackTree<T>*);

    template <typename T>
    void printIndented(Node<T>*, char*, T);

    template <typename T>
    void visualizeRedBlackTree(Node<T>*);

    template <typename T>
    void freeTree(Node<T>*);

    template <typename T>
    Node<T>* createRandomList(int, int, int, RedBlackTree<T>*);

    template <typename T>
    void testFunctionSearch(string, Node<T>* (*searchFunc)(RedBlackTree<T>*, T));

    template <typename T>
    void testFunctionMaxMin(string, Node<T>* (*searchFunc)(RedBlackTree<T>*, Node<T>*));
}   

#include "red_black_tree.tpp"

#endif