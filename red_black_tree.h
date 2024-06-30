#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

using namespace std;

typedef enum { RED, BLACK } Color;

namespace dll
{
    template <typename T>
    struct Node {
        T data;// Dados do nó
        Color color;      // Cor do nó (RED ou BLACK)
        Node *left, *right, *parent; // Ponteiros para o filho esquerdo, direito e pai
    };

    template <typename T>
    Node<T>* createNode(T);   

    template <typename T>
    Node<T>* rotateLeft(Node<T>*, Node<T>*);

    template <typename T>
    Node<T>* rotateRight(Node<T>*, Node<T>*);

    template <typename T>
    Node<T>* insertFixUp(Node<T>*, Node<T>*);

    template <typename T>
    Node<T>* insert(Node<T>*, Node<T>*);

    template <typename T>
    Node<T>* minimum(Node<T>*);

    template <typename T>
    Node<T>* maximum(Node<T>*);

    template <typename T>
    int height(Node<T>*);

    template <typename T>
    void inorder(Node<T>*);

    template <typename T>
    Node<T>* transplant(Node<T>*, Node<T>*, Node<T>*);

    template <typename T>
    Node<T>* deleteFixUp(Node<T>*, Node<T>*);

    template <typename T>
    Node<T>* deleteNode(Node<T>*, Node<T>*);

    template <typename T>
    Node<T>* search(Node<T>*, T);

    template <typename T>
    void freeTree(Node<T>*);

    template <typename T>
    bool isRedBlackTree(Node<T>*, int, int&);

    template <typename T>
    bool validateRedBlackTree(Node<T>*);
}   

#include "red_black_tree.tpp"

#endif