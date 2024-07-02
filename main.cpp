#include "red_black_tree.h"

using namespace std;
using namespace rbt;

int main() {
    Node<int>* root = nullptr;

    root = insert(root, rbt::createNode(10));
    root = insert(root, rbt::createNode(20));
    root = insert(root, rbt::createNode(30));
    root = insert(root, rbt::createNode(15));
    root = insert(root, rbt::createNode(25));

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
    root = insert(root, rbt::createNode(5));
    root = insert(root, rbt::createNode(35));
    root = insert(root, rbt::createNode(40));
    root = insert(root, rbt::createNode(1));

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
    root = insert(root, rbt::createNode(27));

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
