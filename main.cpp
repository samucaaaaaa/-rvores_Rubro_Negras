#include <iostream>
#include <cstdlib>

using namespace std;

enum Color {RED, BLACK};

template <typename T>
struct Node
{
    T payload;
    Color color;
    Node* ptrLeft;
    Node* ptrRight;
    Node* parent;
};

template <typename T>
Node<T>* createNode(T payload) 
{
    Node<T>* newNode = (Node<T>*) malloc(sizeof(Node<T>));
    if (newNode != nullptr) 
    {
        newNode->payload = payload;
        newNode->color = RED;
        newNode->ptrLeft = nullptr;
        newNode->ptrRight = nullptr;
        newNode->parent = nullptr;
    }
    return newNode;
}

template <typename T>
void rotateLeft(Node<T>*& root, Node<T>*& node) 
{
    Node<T>* rightChild = node->ptrRight;
    node->ptrRight = rightChild->ptrLeft;

    if (node->ptrRight != nullptr) 
    {
        node->ptrRight->parent = node;
    }

    rightChild->parent = node->parent;

    if (node->parent == nullptr) 
    {
        root = rightChild;
    } 
    else if (node == node->parent->ptrLeft) 
    {
        node->parent->ptrLeft = rightChild;
    } 
    else 
    {
        node->parent->ptrRight = rightChild;
    }

    rightChild->ptrLeft = node;
    node->parent = rightChild;
}

int main() 
{
    return 0;
}
