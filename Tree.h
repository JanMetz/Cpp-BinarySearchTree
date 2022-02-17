#ifndef BINARY_SEARCH_TREE_TREE_H
#define BINARY_SEARCH_TREE_TREE_H

#include <string>
#include "BST.h"

class Tree{
public:
    int N = 0;
    BST *tree;

    Tree();
    void tree_element_adder(int key);
    BST* VSL_tree_maker(int* tab, int l, int r, BST* Up);

    static int minimum_finder(BST* curr_node, std::string& path);
    static int maximum_finder(BST* curr_node, std::string& path);

    void key_deleter(int key);
    void deleter_r(BST* curr_node, char flag);
    void deleter_i();

    [[nodiscard]] BST* key_finder(int key) const;

    void pre_order_printer(BST* curr_node) const;
    void in_order_printer(BST* curr_node) const;
    void structure_printer();

    void random_tree_creator(int nodes);
    void users_tree_generator(int nodes);

    void dsw_tree_to_vine() const;
    void dsw_vine_to_tree();

private:

    void height_actualizer(BST* node, int height);
    static void dsw_left_rotator(BST* node);
    static void dsw_right_rotator(BST &father);
    void tree_depth_calculator(BST* node, int &max_height) const;
    void structure_filler(BST* curr_node, int l, int r, std::string** arr);
};


#endif //BINARY_SEARCH_TREE_TREE_H
