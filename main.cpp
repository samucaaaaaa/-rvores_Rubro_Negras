#include <iostream>
#include "red_black_tree.h"

using namespace std;
using namespace rbt;

int main() {
    // Teste inicial
    cout << "-------------------------------------------------------------------\n" << endl;
    cout << "TESTE INICIAL:\n" << endl;
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
        cout << "Arvore Rubro-Negra VALIDA depois das insercoes iniciais." << endl;
    } else {
        cout << "Arvore Rubro-Negra INVALIDA depois das insercoes iniciais." << endl;
    }

    visualizeRedBlackTree(tree.root);
    
    cout << "Altura da arvore(incluindo TNULL): " << height(tree.root) << endl;
    cout << "\n";

    cout << "-------------------------------------------------------------------\n" << endl;

    // Testes após fazer mais inserções
    cout << "TESTES DEPOIS DE FAZER MAIS INSERCOES:\n" << endl;
    int more_keys[] = {5, 15, 30, 2, 1};
    for (i = 0; i < sizeof(more_keys) / sizeof(more_keys[0]); i++) {
        insert(&tree, more_keys[i]);
    }

    cout << "Arvore Rubro-Negra depois de mais insercoes (inorder traversal):" << endl;
    inorder(&tree);
    cout << "\n\n";

    if (isValidRedBlackTree(&tree)) {
        cout << "Arvore Rubro-Negra VALIDA depois de mais insercoes." << endl;
    } else {
        cout << "Arvore Rubro-Negra INVALIDA depois de mais insercoes." << endl;
    }

    visualizeRedBlackTree(tree.root);

    cout << "Altura da arvore(incluindo TNULL): " << height(tree.root) << endl;
    cout << "\n";

    cout << "-------------------------------------------------------------------\n" << endl;

    // Testes após deletar um nó da árvore
    cout << "TESTES DEPOIS DE DELETAR UM NODE DA ARVORE:\n" << endl;
    deleteNode(&tree, 18);

    cout << "Arvore Rubro-Negra depois de remover o node 18 (inorder traversal):" << endl;
    inorder(&tree);
    cout << "\n";

    if (isValidRedBlackTree(&tree)) {
        cout << "Arvore Rubro-Negra VALIDA depois da remocao de 18." << endl;
    } else {
        cout << "Arvore Rubro-Negra INVALIDA depois da remocao de 18." << endl;
    }

    visualizeRedBlackTree(tree.root);

    cout << "Altura da arvore(incluindo TNULL): " << height(tree.root) << endl;
    cout << "\n";

    cout << "-------------------------------------------------------------------\n" << endl;

    // Testes após deletar outro nó da árvore
    cout << "TESTES DEPOIS DE DELETAR OUTRO NODE DA ARVORE:\n" << endl;
    deleteNode(&tree, 26);

    cout << "Arvore Rubro-Negra depois de remover o node 26 (inorder traversal):" << endl;
    inorder(&tree);
    cout << "\n";

    if (isValidRedBlackTree(&tree)) {
        cout << "Arvore Rubro-Negra VALIDA depois da remocao de 26." << endl;
    } else {
        cout << "Arvore Rubro-Negra INVALIDA depois da remocao de 26." << endl;
    }

    visualizeRedBlackTree(tree.root);

    cout << "Altura da arvore(incluindo TNULL): " << height(tree.root) << endl;
    cout << "\n";

    cout << "-------------------------------------------------------------------\n" << endl;

    // Testes após inserir mais nós
    cout << "TESTES DEPOIS DE INSERIR MAIS NODES:\n" << endl;
    insert(&tree, 40);
    insert(&tree, 50);

    cout << "Arvore Rubro-Negra depois de inserir 40 e 50 (inorder traversal):" << endl;
    inorder(&tree);
    cout << "\n";

    if (isValidRedBlackTree(&tree)) {
        cout << "Arvore Rubro-Negra VALIDA depois das insercoes de 40 e 50." << endl;
    } else {
        cout << "Arvore Rubro-Negra INVALIDA depois das insercoes de 40 e 50." << endl;
    }

    visualizeRedBlackTree(tree.root);

    cout << "Altura da arvore(incluindo TNULL): " << height(tree.root) << endl;
    cout << "\n";

    cout << "-------------------------------------------------------------------\n" << endl;

    // Deletando alguns nós
    deleteNode(&tree, 2);
    deleteNode(&tree, 30);

    // Testes após inserir mais nós
    cout << "TESTES DEPOIS DE DELETAR O 2 E O 30 E OS INSERIR NOVAMENTE:\n" << endl;
    insert(&tree, 30);
    insert(&tree, 2);

    cout << "Arvore Rubro-Negra depois de adicionar 30 e 2 (inorder traversal):" << endl;
    inorder(&tree);
    cout << "\n";

    if (isValidRedBlackTree(&tree)) {
        cout << "Arvore Rubro-Negra VALIDA depois da adicao de 30 e 2." << endl;
    } else {
        cout << "Arvore Rubro-Negra INVALIDA depois da adicao de 30 e 2." << endl;
    }

    visualizeRedBlackTree(tree.root);

    cout << "Altura da arvore(incluindo TNULL): " << height(tree.root) << endl;
    cout << "\n";

    cout << "-------------------------------------------------------------------\n" << endl;

    // Testes após remover vários nós
    cout << "TESTES DEPOIS DE REMOVER VARIOS NODES:\n" << endl;
    deleteNode(&tree, 8);

    cout << "Arvore Rubro-Negra depois de remover o node 8 (inorder traversal):" << endl;
    inorder(&tree);
    cout << "\n";

    if (isValidRedBlackTree(&tree)) {
        cout << "Arvore Rubro-Negra VALIDA depois da remocao de 8." << endl;
    } else {
        cout << "Arvore Rubro-Negra INVALIDA depois da remocao de 8." << endl;
    }

    deleteNode(&tree, 22);
    deleteNode(&tree, 40);
    deleteNode(&tree, 30);
    deleteNode(&tree, 7);

    cout << "Arvore Rubro-Negra depois de remover o nodes  22,40,30, 7(inorder traversal):" << endl;
    inorder(&tree);
    cout << "\n";

    if (isValidRedBlackTree(&tree)) {
        cout << "Arvore Rubro-Negra VALIDA depois da remocao de 22,40,30 e 7." << endl;
    } else {
        cout << "Arvore Rubro-Negra INVALIDA depois da remocao de 22,40,30 e 7." << endl;
    }

    visualizeRedBlackTree(tree.root);

    cout << "Altura da arvore(incluindo TNULL): " << height(tree.root) << endl;
    cout << "\n";

    cout << "-------------------------------------------------------------------\n" << endl;

    // Testes para os tempos da função de busca
    testFunctionSearch("searchTree", searchTree<int>);

    cout << "\n-------------------------------------------------------------------\n" << endl;

    // Testar a função minimum
    testFunctionMaxMin<int>("minimum", minimum);

    cout << "\n-------------------------------------------------------------------\n" << endl;

    // Testar a função maximum
    testFunctionMaxMin<int>("maximum", maximum);

    cout << "\n-------------------------------------------------------------------\n" << endl;

    return 0;
}