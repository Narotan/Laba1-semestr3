#include "../include/AVLTree.hpp"
using namespace std;

// Вспомогательные функции
static uint8_t max_height(uint8_t a, uint8_t b) {
    return a > b ? a : b;
}

static uint8_t node_height(const TreeNode* node) {
    return node ? node->height : 0;
}

static int balance_factor(const TreeNode* node) {
    return node ? static_cast<int>(node_height(node->left.get())) - 
                  static_cast<int>(node_height(node->right.get())) : 0;
}

static void fix_height(TreeNode* node) {
    if (!node) return;
    node->height = max_height(node_height(node->left.get()), node_height(node->right.get())) + 1;
}


static unique_ptr<TreeNode> rotate_right(unique_ptr<TreeNode> p) {
    if (!p || !p->left) return p;
    
    auto q = move(p->left);        // Сохраняем левого потомка
    p->left = move(q->right);      // B переходит к p
    fix_height(p.get());           // Пересчитываем высоты
    fix_height(q.get());
    q->right = move(p);            // p становится правым потомком q
    
    return q; // Возвращаем новый корень
}

static unique_ptr<TreeNode> rotate_left(unique_ptr<TreeNode> q) {
    if (!q || !q->right) return q;
    
    auto p = move(q->right);
    q->right = move(p->left);
    fix_height(q.get());
    fix_height(p.get());
    p->left = move(q);
    
    return p;
}

// Балансировка узла после вставки/удаления
static unique_ptr<TreeNode> balance(unique_ptr<TreeNode> p) {
    if (!p) return nullptr;
    
    fix_height(p.get());
    int bf = balance_factor(p.get());
    
    // Левый перевес (левое поддерево выше на 2)
    if (bf == 2) {
        // Если у левого потомка правый перевес, делаем двойной поворот
        if (balance_factor(p->left.get()) < 0) {
            p->left = rotate_left(move(p->left));
        }
        return rotate_right(move(p));
    }
    
    // Правый перевес (правое поддерево выше на 2)
    if (bf == -2) {
        // Если у правого потомка левый перевес, делаем двойной поворот
        if (balance_factor(p->right.get()) > 0) {
            p->right = rotate_right(move(p->right));
        }
        return rotate_left(move(p));
    }
    
    return p; // Дерево уже сбалансировано
}

static unique_ptr<TreeNode> insert_node(unique_ptr<TreeNode> node, int key) {
    if (!node) {
        auto newNode = make_unique<TreeNode>();
        newNode->key = key;
        newNode->height = 1;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }
    
    if (key < node->key) {
        node->left = insert_node(move(node->left), key);
    } else if (key > node->key) {
        node->right = insert_node(move(node->right), key);
    } else {
        return node;
    }
    
    return balance(move(node));
}

static TreeNode* find_min(TreeNode* node) {
    return node->left ? find_min(node->left.get()) : node;
}

static unique_ptr<TreeNode> remove_min(unique_ptr<TreeNode> node) {
    if (!node->left) return move(node->right);
    node->left = remove_min(move(node->left));
    return balance(move(node));
}

static unique_ptr<TreeNode> delete_node(unique_ptr<TreeNode> node, int key) {
    if (!node) return nullptr;
    
    if (key < node->key) {
        node->left = delete_node(move(node->left), key);
    } else if (key > node->key) {
        node->right = delete_node(move(node->right), key);
    } else {
        auto left = move(node->left);
        auto right = move(node->right);
        
        if (!right) return left;
        
        TreeNode* minNode = find_min(right.get());
        auto newNode = make_unique<TreeNode>();
        newNode->key = minNode->key;
        newNode->height = 1;
        newNode->right = remove_min(move(right));
        newNode->left = move(left);
        return balance(move(newNode));
    }
    
    return balance(move(node));
}

static bool search_node(const TreeNode* node, int key) {
    if (!node) return false;
    if (key == node->key) return true;
    if (key < node->key) return search_node(node->left.get(), key);
    return search_node(node->right.get(), key);
}

unique_ptr<AVLTree> avl_create() {
    auto tree = make_unique<AVLTree>();
    tree->root = nullptr;
    return tree;
}

void avl_insert(AVLTree* tree, int key) {
    tree->root = insert_node(move(tree->root), key);
}

void avl_delete(AVLTree* tree, int key) {
    tree->root = delete_node(move(tree->root), key);
}

bool avl_search(const AVLTree* tree, int key) {
    return search_node(tree->root.get(), key);
}
