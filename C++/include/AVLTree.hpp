#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <memory>
#include <cstdint>

using namespace std;

// Узел AVL-дерева
struct TreeNode {
    int key;                    // Ключ для поиска
    uint8_t height;             // Высота поддерева (для балансировки)
    unique_ptr<TreeNode> left;  // Левое поддерево (ключи меньше)
    unique_ptr<TreeNode> right; // Правое поддерево (ключи больше)
};

// AVL-дерево - самобалансирующееся бинарное дерево поиска
// Гарантирует, что разница высот левого и правого поддеревьев не превышает 1
struct AVLTree {
    unique_ptr<TreeNode> root;
};

unique_ptr<AVLTree> avl_create();
void avl_insert(AVLTree* tree, int key);
void avl_delete(AVLTree* tree, int key);
bool avl_search(const AVLTree* tree, int key);

#endif // AVL_TREE_HPP
