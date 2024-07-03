#include <iostream>
#include "red_black_tree.h"

using namespace std;
using namespace rbt;

int main() {
    // Teste inicial
    cout << "Teste inicial:" << endl;
    RedBlackTree<int> tree;
    tree.TNULL = createTNULL<int>();
    tree.root = tree.TNULL;

    int keys[] = {7, 3, 18, 10, 22, 8, 11, 26};
    int i;
    for (i = 0; i < sizeof(keys) / sizeof(keys[0]); i++) {
        insert(&tree, keys[i]);
    }

    cout << "Arvore Rubro-Negra (inorder traversal):" << endl;
    inorder(&tree);
    cout << "\n";

    if (isValidRedBlackTree(&tree)) {
        cout << "Arvore Rubro-Negra VALIDA depois das inserções iniciais." << endl;
    } else {
        cout << "Arvore Rubro-Negra INVALIDA depois das inserções iniciais." << endl;
    }

    visualizeRedBlackTree(tree.root);
    
    cout << "Altura da arvore(incluindo TNULL): " << height(tree.root) << endl;
    cout << "\n";

    // Testes após fazer mais inserções
    cout << "Testes depois de fazer mais inserções:" << endl;
    int more_keys[] = {5, 15, 30, 2, 1};
    for (i = 0; i < sizeof(more_keys) / sizeof(more_keys[0]); i++) {
        insert(&tree, more_keys[i]);
    }

    cout << "Arvore Rubro-Negra depois de mais inserções (inorder traversal):" << endl;
    inorder(&tree);
    cout << "\n\n";

    if (isValidRedBlackTree(&tree)) {
        cout << "Arvore Rubro-Negra VALIDA depois de mais inserções." << endl;
    } else {
        cout << "Arvore Rubro-Negra INVALIDA depois de mais inserções." << endl;
    }

    visualizeRedBlackTree(tree.root);

    cout << "Altura da arvore(incluindo TNULL): " << height(tree.root) << endl;
    cout << "\n";

    // Testes após deletar um nó da árvore
    cout << "Testes depois de deletar um node da arvore:" << endl;
    deleteNode(&tree, 18);

    cout << "Arvore Rubro-Negra depois de remover o node 18 (inorder traversal):" << endl;
    inorder(&tree);
    cout << "\n";

    if (isValidRedBlackTree(&tree)) {
        cout << "Arvore Rubro-Negra VALIDA depois da remoção de 18." << endl;
    } else {
        cout << "Arvore Rubro-Negra INVALIDA depois da remoção de 18." << endl;
    }

    visualizeRedBlackTree(tree.root);

    cout << "Altura da arvore(incluindo TNULL): " << height(tree.root) << endl;
    cout << "\n";

    // Testes após deletar outro nó da árvore
    cout << "Testes depois de deletar outro node da arvore: " << endl;
    deleteNode(&tree, 26);

    cout << "Arvore Rubro-Negra depois de remover o node 26 (inorder traversal):" << endl;
    inorder(&tree);
    cout << "\n";

    if (isValidRedBlackTree(&tree)) {
        cout << "Arvore Rubro-Negra VALIDA depois da remoção de 26." << endl;
    } else {
        cout << "Arvore Rubro-Negra INVALIDA depois da remoção de 26." << endl;
    }

    visualizeRedBlackTree(tree.root);

    cout << "Altura da arvore(incluindo TNULL): " << height(tree.root) << endl;
    cout << "\n";

    // Testes após inserir mais nós
    cout << "Testes depois de inserir mais nodes:" << endl;
    insert(&tree, 40);
    insert(&tree, 50);

    cout << "Arvore Rubro-Negra depois de inserir 40 e 50 (inorder traversal):" << endl;
    inorder(&tree);
    cout << "\n";

    if (isValidRedBlackTree(&tree)) {
        cout << "Arvore Rubro-Negra VALIDA depois das inserções de 40 e 50." << endl;
    } else {
        cout << "Arvore Rubro-Negra INVALIDA depois das inserções de 40 e 50." << endl;
    }

    visualizeRedBlackTree(tree.root);

    cout << "Altura da arvore(incluindo TNULL): " << height(tree.root) << endl;
    cout << "\n";

    // Testes após deletar outro nó
    cout << "Testes depois de deletar outro node:" << endl;
    deleteNode(&tree, 2);

    cout << "Arvore Rubro-Negra depois de remover o node 2 (inorder traversal):" << endl;
    inorder(&tree);
    cout << "\n";

    if (isValidRedBlackTree(&tree)) {
        cout << "Arvore Rubro-Negra VALIDA depois da remoção de 2." << endl;
    } else {
        cout << "Arvore Rubro-Negra INVALIDA depois da remoção de 2." << endl;
    }

    visualizeRedBlackTree(tree.root);

    cout << "Altura da arvore(incluindo TNULL): " << height(tree.root) << endl;
    cout << "\n";

    // Testes após deletar outro nó
    cout << "Testes depois de deletar outro node:" << endl;
    deleteNode(&tree, 30);

    cout << "Arvore Rubro-Negra depois de remover o node 30 (inorder traversal):" << endl;
    inorder(&tree);
    cout << "\n";

    if (isValidRedBlackTree(&tree)) {
        cout << "Arvore Rubro-Negra VALIDA depois da remoção de 30." << endl;
    } else {
        cout << "Arvore Rubro-Negra INVALIDA depois da remoção de 30." << endl;
    }

    visualizeRedBlackTree(tree.root);

    cout << "Altura da arvore(incluindo TNULL): " << height(tree.root) << endl;
    cout << "\n";

    // Testes após inserir mais nós
    cout << "Testes depois de inserir mais nodes:" << endl;
    insert(&tree, 30);
    insert(&tree, 2);

    cout << "Arvore Rubro-Negra depois de adicionar 30 e 2 (inorder traversal):" << endl;
    inorder(&tree);
    cout << "\n";

    if (isValidRedBlackTree(&tree)) {
        cout << "Arvore Rubro-Negra VALIDA depois da adição de 30 e 2." << endl;
    } else {
        cout << "Arvore Rubro-Negra INVALIDA depois da adição de 30 e 2." << endl;
    }

    visualizeRedBlackTree(tree.root);

    cout << "Altura da arvore(incluindo TNULL): " << height(tree.root) << endl;
    cout << "\n";

    // Testes após remover vários nós
    cout << "Testes depois de remover varios nodes:" << endl;
    deleteNode(&tree, 8);

    cout << "Arvore Rubro-Negra depois de remover o node 8 (inorder traversal):" << endl;
    inorder(&tree);
    cout << "\n";

    if (isValidRedBlackTree(&tree)) {
        cout << "Arvore Rubro-Negra VALIDA depois da remoção de 8." << endl;
    } else {
        cout << "Arvore Rubro-Negra INVALIDA depois da remoção de 8." << endl;
    }

    deleteNode(&tree, 22);
    deleteNode(&tree, 40);
    deleteNode(&tree, 30);
    deleteNode(&tree, 7);

    cout << "Arvore Rubro-Negra depois de remover o nodes  22,40,30, 7(inorder traversal):" << endl;
    inorder(&tree);
    cout << "\n";

    if (isValidRedBlackTree(&tree)) {
        cout << "Arvore Rubro-Negra VALIDA depois da remoção de 22,40,30 e 7." << endl;
    } else {
        cout << "Arvore Rubro-Negra INVALIDA depois da remoção de 22,40,30 e 7." << endl;
    }

    visualizeRedBlackTree(tree.root);

    cout << "Altura da arvore(incluindo TNULL): " << height(tree.root) << endl;
    cout << "\n";

    // Testes para os tempos da função de busca
    cout << "Testes para os tempos da funcao de busca" << endl;
    testFunctionSearch("searchTree", searchTree<int>);

    return 0;
}