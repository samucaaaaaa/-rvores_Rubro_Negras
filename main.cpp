#include <iostream>
#include <cstdlib>

using namespace std;

typedef enum { RED, BLACK } Color; // Enumeração para definir as cores dos nós

template <typename T>
struct Node {
    T data;// Dados do nó
    Color color;      // Cor do nó (RED ou BLACK)
    Node *left, *right, *parent; // Ponteiros para o filho esquerdo, direito e pai
};

template <typename T>
Node<T>* createNode(T data) {
    Node<T>* newNode = (Node<T>*)malloc(sizeof(Node<T>)); 
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
    Node<T>* y = x->right; // Define y como o filho direito de x
    if (!y) return root; // Retorna a raiz se y for null (checagem de segurança)
    x->right = y->left; // Move o filho esquerdo de y para ser o filho direito de x
    if (y->left != nullptr) y->left->parent = x; // Atualiza o pai do filho esquerdo de y
    y->parent = x->parent; // Liga o pai de x a y
    if (x->parent == nullptr) root = y; // Atualiza a raiz se x for a raiz original
    else if (x == x->parent->left) x->parent->left = y; // Atualiza o filho esquerdo do pai de x
    else x->parent->right = y; // Atualiza o filho direito do pai de x
    y->left = x; // Coloca x à esquerda de y
    x->parent = y; // Define y como pai de x
    return root; // Retorna a raiz atualizada
}

template <typename T>
Node<T>* rotateRight(Node<T>* root, Node<T>* x) {
    Node<T>* y = x->left; // Define y como o filho esquerdo de x
    if (!y) return root; // Retorna a raiz se y for null (checagem de segurança)
    x->left = y->right; // Move o filho direito de y para ser o filho esquerdo de x
    if (y->right != nullptr) y->right->parent = x; // Atualiza o pai do filho direito de y
    y->parent = x->parent; // Liga o pai de x a y
    if (x->parent == nullptr) root = y; // Atualiza a raiz se x for a raiz original
    else if (x == x->parent->right) x->parent->right = y; // Atualiza o filho direito do pai de x
    else x->parent->left = y; // Atualiza o filho esquerdo do pai de x
    y->right = x; // Coloca x à direita de y
    x->parent = y; // Define y como pai de x
    return root; // Retorna a raiz atualizada
}

template <typename T>
Node<T>* insertFixUp(Node<T>* root, Node<T>* z) {
    while (z->parent != nullptr && z->parent->color == RED) { // Enquanto o pai de z for RED
        if (z->parent == z->parent->parent->left) { // Se o pai de z for o filho esquerdo
            Node<T>* y = z->parent->parent->right; 
            if (y != nullptr && y->color == RED) { 
                z->parent->color = BLACK; // Recolore o pai de z
                y->color = BLACK; // Recolore o tio de z
                z->parent->parent->color = RED; // Recolore o avô de z
                z = z->parent->parent; // Move z para cima da árvore
            } else {
                if (z == z->parent->right) { // Caso 2: z é filho direito
                    z = z->parent; // Move z para o pai
                    root = rotateLeft(root, z); // Rotaciona para a esquerda
                }
                z->parent->color = BLACK; // Caso 3: z é filho esquerdo
                z->parent->parent->color = RED; // Recolore o avô de z
                root = rotateRight(root, z->parent->parent); // Rotaciona para a direita
            }
        } else { // Casos simétricos
            Node<T>* y = z->parent->parent->left; // y é o tio de z
            if (y != nullptr && y->color == RED) { // Caso 1: tio é RED
                z->parent->color = BLACK; // Recolore o pai de z
                y->color = BLACK; // Recolore o tio de z
                z->parent->parent->color = RED; // Recolore o avô de z
                z = z->parent->parent; // Move z para cima da árvore
            } else {
                if (z == z->parent->left) { // Caso 2: z é filho esquerdo
                    z = z->parent; // Move z para o pai
                    root = rotateRight(root, z); // Rotaciona para a direita
                }
                z->parent->color = BLACK; // Caso 3: z é filho direito
                z->parent->parent->color = RED; // Recolore o avô de z
                root = rotateLeft(root, z->parent->parent); // Rotaciona para a esquerda
            }
        }
    }
    root->color = BLACK; // Garante que a raiz seja BLACK
    return root; // Retorna a raiz atualizada
}

template <typename T>
Node<T>* insert(Node<T>* root, Node<T>* z) {
    Node<T>* y = nullptr;
    Node<T>* x = root;
    while (x != nullptr) { // Encontra a posição para inserir o novo nó
        y = x;
        if (z->data < x->data) x = x->left;
        else x = x->right;
    }
    z->parent = y; // Define o pai do novo nó
    if (y == nullptr) root = z; // Se a árvore estava vazia, o novo nó é a raiz
    else if (z->data < y->data) y->left = z; // Insere à esquerda
    else y->right = z; // Insere à direita
    return insertFixUp(root, z); // Ajusta a árvore
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
    if (node == nullptr) return 0; // Se o nó for null, a altura é 0
    int leftHeight = height(node->left); // Calcula a altura do filho esquerdo
    int rightHeight = height(node->right); // Calcula a altura do filho direito
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight); // Retorna a altura maior entre os filhos + 1
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
    if (u->parent == nullptr) root = v; // Se u for a raiz, v se torna a nova raiz
    else if (u == u->parent->left) u->parent->left = v; // Se u for o filho esquerdo, substitui pelo v
    else u->parent->right = v; // Se u for o filho direito, substitui pelo v
    if (v != nullptr) v->parent = u->parent; // Atualiza o pai de v
    return root; // Retorna a raiz atualizada
}

template <typename T>
Node<T>* deleteFixUp(Node<T>* root, Node<T>* x) {
    while (x != root && (x == nullptr || x->color == BLACK)) { // Enquanto x não for a raiz e for BLACK
        if (x != nullptr && x->parent != nullptr && x == x->parent->left) { // Se x for filho esquerdo
            Node<T>* w = x->parent->right; // w é o irmão de x
            if (w->color == RED) { // Caso 1: w é RED
                w->color = BLACK;
                x->parent->color = RED;
                root = rotateLeft(root, x->parent); // Rotaciona para a esquerda
                w = x->parent->right;
            }
            if ((w->left == nullptr || w->left->color == BLACK) && (w->right == nullptr || w->right->color == BLACK)) { // Caso 2: w tem filhos BLACK
                w->color = RED;
                x = x->parent; // Move x para o pai
            } else {
                if (w->right == nullptr || w->right->color == BLACK) { // Caso 3: w tem filho esquerdo RED
                    if (w->left != nullptr) w->left->color = BLACK;
                    w->color = RED;
                    root = rotateRight(root, w); // Rotaciona para a direita
                    w = x->parent->right;
                }
                w->color = x->parent->color; // Caso 4: w tem filho direito RED
                x->parent->color = BLACK;
                if (w->right != nullptr) w->right->color = BLACK;
                root = rotateLeft(root, x->parent); // Rotaciona para a esquerda
                x = root;
            }
        } else { // Casos simétricos
            Node<T>* w = x->parent->left; // w é o irmão de x
            if (w->color == RED) { // Caso 1: w é RED
                w->color = BLACK;
                x->parent->color = RED;
                root = rotateRight(root, x->parent); // Rotaciona para a direita
                w = x->parent->left;
            }
            if ((w->left == nullptr || w->left->color == BLACK) && (w->right == nullptr || w->right->color == BLACK)) { // Caso 2: w tem filhos BLACK
                w->color = RED;
                x = x->parent; // Move x para o pai
            } else {
                if (w->left == nullptr || w->left->color == BLACK) { // Caso 3: w tem filho direito RED
                    if (w->right != nullptr) w->right->color = BLACK;
                    w->color = RED;
                    root = rotateLeft(root, w); // Rotaciona para a esquerda
                    w = x->parent->left;
                }
                w->color = x->parent->color; // Caso 4: w tem filho esquerdo RED
                x->parent->color = BLACK;
                if (w->left != nullptr) w->left->color = BLACK;
                root = rotateRight(root, x->parent); // Rotaciona para a direita
                x = root;
            }
        }
    }
    if (x != nullptr) x->color = BLACK; // Garante que x seja BLACK
    return root; // Retorna a raiz atualizada
}

template <typename T>
Node<T>* deleteNode(Node<T>* root, Node<T>* z) {
    Node<T>* y = z;
    Node<T>* x;
    Color yOriginalColor = y->color; // Guarda a cor original de y
    if (z->left == nullptr) { // Se z não tem filho esquerdo
        x = z->right; // x é o filho direito de z
        root = transplant(root, z, z->right); // Transplanta z pelo seu filho direito
    } else if (z->right == nullptr) { // Se z não tem filho direito
        x = z->left; // x é o filho esquerdo de z
        root = transplant(root, z, z->left); // Transplanta z pelo seu filho esquerdo
    } else { // Se z tem ambos os filhos
        y = minimum(z->right); // y é o menor nó da subárvore direita
        yOriginalColor = y->color; // Guarda a cor original de y
        x = y->right; // x é o filho direito de y
        if (y->parent == z) {
            if (x != nullptr) x->parent = y; // Atualiza o pai de x
        } else {
            root = transplant(root, y, y->right); // Transplanta y pelo seu filho direito
            y->right = z->right; // Define o filho direito de y como o filho direito de z
            if (y->right != nullptr) y->right->parent = y; // Atualiza o pai do filho direito de y
        }
        root = transplant(root, z, y); // Transplanta z por y
        y->left = z->left; // Define o filho esquerdo de y como o filho esquerdo de z
        if (y->left != nullptr) y->left->parent = y; // Atualiza o pai do filho esquerdo de y
        y->color = z->color; // Mantém a cor de z em y
    }
    free(z); // Libera a memória do nó z
    if (yOriginalColor == BLACK) root = deleteFixUp(root, x); // Ajusta a árvore se necessário
    return root; // Retorna a raiz atualizada
}

template <typename T>
Node<T>* search(Node<T>* root, T key) {
    if (root == nullptr || root->data == key) return root; // Retorna o nó se encontrado ou null
    if (key < root->data) return search(root->left, key); // Busca na subárvore esquerda
    return search(root->right, key); // Busca na subárvore direita
}

template <typename T>
void freeTree(Node<T>* root) {
    if (root == nullptr) return; // Se a raiz for null, retorna
    freeTree(root->left); // Libera a subárvore esquerda
    freeTree(root->right); // Libera a subárvore direita
    free(root); // Libera o nó atual
}

template <typename T>
bool isRedBlackTree(Node<T>* node, int blackCount, int& pathBlackCount) {
    if (node == nullptr) {
        if (pathBlackCount == -1) pathBlackCount = blackCount; // Define a contagem de nós pretos no caminho
        return blackCount == pathBlackCount; // Verifica se a contagem é consistente
    }
    if (node->color == BLACK) blackCount++; // Incrementa a contagem de nós pretos
    if (node->color == RED && node->parent->color == RED) return false; // Verifica a regra do nó vermelho
    return isRedBlackTree(node->left, blackCount, pathBlackCount) && isRedBlackTree(node->right, blackCount, pathBlackCount); // Verifica recursivamente para as subárvores
}

template <typename T>
bool validateRedBlackTree(Node<T>* root) {
    if (root == nullptr) return true; // Uma árvore vazia é válida
    if (root->color != BLACK) return false; // A raiz deve ser preta
    int pathBlackCount = -1;
    return isRedBlackTree(root, 0, pathBlackCount); // Verifica se a árvore é uma árvore rubro-negra
}
int main() {
    Node<int>* root = nullptr;

    root = insert(root, createNode(10));
    root = insert(root, createNode(20));
    root = insert(root, createNode(30));
    root = insert(root, createNode(15));
    root = insert(root, createNode(25));

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
    root = insert(root, createNode(5));
    root = insert(root, createNode(35));
    root = insert(root, createNode(40));
    root = insert(root, createNode(1));

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
    root = insert(root, createNode(27));

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
