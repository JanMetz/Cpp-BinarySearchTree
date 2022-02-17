#include "Tree.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include "BST.h"

void Tree::tree_depth_calculator(BST* node, int& max_height) const{
    //searches through the tree to find the lowest sitting element.
    if (node != nullptr){

        if (node->Height > max_height)
            max_height = node->Height;

        if (node->L != nullptr)
            tree_depth_calculator(node->L, max_height);

        if (node->R != nullptr)
            tree_depth_calculator(node->R, max_height);
    }
}

void Tree::height_actualizer(BST* node, int height){
    //actualizes the tree height. Useful after balancing operations.

    node->Height = height;

    if (node->R != nullptr)
        height_actualizer(node->R, height + 1);

    if (node->L != nullptr)
        height_actualizer(node->L, height + 1);
}

Tree::Tree(){
    //initializes an exemplary tree with data from 'tab'

    int* tab;
    N = 10;

    tab = new int[N];
    for (int i = 0; i < N; i++)
        tab[i] = i;


    tree = new BST;
    tree->L = nullptr;
    tree->value = -1;
    tree->Up = nullptr;
    tree->Height = -1;

    tree->Height = 0;
    tree->R = VSL_tree_maker(tab, 0, N - 1, tree);

    delete[]tab;
}

BST* Tree::VSL_tree_maker(int* tab, int l, int r, BST* Up){
    //creates a VSL tree.
    //pointer .L points on the left child of the node, .R on the right one. Pointer .Up points on father of the node. .value stores key/value of the node
    //the tree is created using medians.

    int c = (l + r) / 2;
    BST* node;

    node = new BST;

    node->value = tab[c];
    node->Up = Up;
    node->Height = Up->Height + 1;


    if (l < c)
        node->L = VSL_tree_maker(tab, l, c - 1, node);
    else
        node->L = nullptr;


    if (c < r)
        node->R = VSL_tree_maker(tab, c + 1, r, node);
    else
        node->R = nullptr;


    return node;
}

void Tree::tree_element_adder(int key){
    //adds an element to the already existing tree.

    BST* new_node, *node = tree;

    new_node = new BST;

    new_node->value = key;
    new_node->L = nullptr;
    new_node->R = nullptr;

    while ((node->R != nullptr) || (node->L != nullptr)){
        if (key < node->value && node->L != nullptr)
            node = node->L;

        if (key > node->value && node->R != nullptr)
            node = node->R;

        if (key > node->value && node->R == nullptr)
            break;

        if (key < node->value && node->L == nullptr)
            break;
    }

    if (key < node->value)
        node->L = new_node;

    if (key > node->value)
        node->R = new_node;

    new_node->Height = node->Height + 1;
    new_node->Up = node;

    N++;
}

void Tree::random_tree_creator(int nodes){
    //creates a random tree

    srand(time(nullptr));
    int start, e, elem;

    start = rand() % 15 * nodes + 10 * nodes;
    e = rand() % (start/(2*nodes+1)) + 2;

    for (int i = 1; i <= nodes; i++){
        if (i % 2 == 0)
            elem = start + i * e;
        else
            elem = start - i * e;

        tree_element_adder(elem);
    }

}

void Tree::users_tree_generator(int nodes){
    if (tree->R != nullptr){
        deleter_r(tree->R, 'I');
        tree->R = nullptr;
    }
    N = nodes;

    int* tab = new int[nodes + 1];

    for (int i = 0; i < nodes; i++){
        std::cout << "Insert key: ";
        std::cin >> tab[i];
    }

    std::sort(tab, tab + nodes);
    tree->Height = 0;
    tree->R = VSL_tree_maker(tab, 0, nodes - 1, tree);

    delete[]tab;
}

int Tree::minimum_finder(BST* curr_node, std::string& path){
    //finds the smallest element in the tree, which is the most left one, and displays the path to this element
    while (curr_node->L != nullptr){
        path = path + std::to_string(curr_node->value) + " - ";
        curr_node = curr_node->L;
    }

    path = path + std::to_string(curr_node->value);
    return curr_node->value;
}

int Tree::maximum_finder(BST* curr_node, std::string& path){
    //finds the greatest element in the tree, which is the most right one, and displays the path to this element
    while (curr_node->R != nullptr){
        path = path + std::to_string(curr_node->value) + " - ";
        curr_node = curr_node->R;
    }

    path = path + std::to_string(curr_node->value);
    return curr_node->value;
}

BST* Tree::key_finder(int key) const{
    //searches through the tree to find given element. If it ends with failure the returned value is nullptr, if not, it returns the pointer to the sought element.
    //due to the design of the BST elements bigger than node are to its right, and element smaller are to its left.
    BST* node = tree->R;
    if (N != 0){
        while (true){
            if (key > node->value && node->R != nullptr)
                node = (*node).R;

            if (key < node->value && node->L != nullptr)
                node = (*node).L;

            if (key == node->value)
                return node;

            if (((node->R == nullptr) && (key > node->value)) || ((node->L == nullptr) && (key < node->value)))
                return nullptr;
        }
    }
    else
        return nullptr;

}

void Tree::deleter_r(BST* curr_node, char flag){
    //deletes the tree recursively in post-order manner, if the flag is set as 'V' (Visible) it also prints the key of the element before deleting it.
    N = 0;

    if (curr_node->L != nullptr)
        deleter_r(curr_node->L, flag);

    if (curr_node->R != nullptr)
        deleter_r(curr_node->R, flag);

    if (flag == 'V' && curr_node->Up != nullptr)
        std::cout << curr_node->value << "\t";

    delete curr_node;
}

void Tree::deleter_i(){
    //deletes the tree iteratively. In order to make it easier the tree before deleting is transformed into a grapevine.
    dsw_tree_to_vine();

    BST* node, *tmp;
    N = 0;
    node = tree->R;

    while (node->R != nullptr){
        tmp = node->R;

        delete node;

        node = tmp;
    }
}

void Tree::key_deleter(int key){
    //deletes given element from the tree.
    N -= 1;

    BST* for_deleting, *father, * replacement;

    for_deleting = key_finder(key);

    if (for_deleting != nullptr){
        father = (*for_deleting).Up;

        if (for_deleting->R != nullptr && for_deleting->L != nullptr){   //deleting a node with two children.
            replacement = for_deleting->R;

            bool iff = false;

            while ((*replacement).L != nullptr){
                iff = true;
                replacement = (*replacement).L; //after this operation replacement is going to be the closest (by key value) element to the removed node.
            }



            if (replacement->R != nullptr){
                if (iff)
                    (replacement->Up)->L = replacement->R;
                else
                    (replacement->Up)->R = replacement->R;

                (replacement->R)->Up = replacement->Up;
                height_actualizer(replacement->R, (replacement->R)->Height - 1);
            }
            else{
                if (iff)
                    (replacement->Up)->L = nullptr;
                else
                    (replacement->Up)->R = nullptr;
            }

            if ((*father).R == for_deleting)
                (*father).R = replacement;
            else
                (*father).L = replacement;


            (*replacement).Up = father;
            (*replacement).R = for_deleting->R;
            (*replacement).L = for_deleting->L;
            replacement->Height = for_deleting->Height;
            (for_deleting->R)->Up = replacement;
            (for_deleting->L)->Up = replacement;

        }
        else if (for_deleting->R == nullptr && for_deleting->L == nullptr){   //deleting a node without any children
            if ((*father).R == for_deleting)
                father->R = nullptr;
            else
                father->L = nullptr;
        }
        else{                                //deleting a node with one child
            if (for_deleting->R == nullptr)
                replacement = for_deleting->L;
            else
                replacement = for_deleting->R;

            if ((*father).R == for_deleting)
                (*father).R = replacement;
            else
                (*father).L = replacement;


            replacement->Up = father;
            replacement->Height = for_deleting->Height;
        }

        delete for_deleting;
    }
}

void Tree::dsw_tree_to_vine() const{
    //rotates the tree using DSW algorithm. Transforms the tree to a 'grapevine' structure, which has only right children. In a grapevine every child is smaller than its parent.
    BST * node = tree;

    while (true){
        if (node->L != nullptr){
            dsw_right_rotator(*node);
            node = tree;
        }
        else
        if (node->R != nullptr)
            node = node->R;
        else
            break;
    }
}

void Tree::dsw_right_rotator(BST &father){
    //rotates the tree right to obtain a grapevine structure.

    BST* son, * grandfather;

    grandfather = father.Up;
    son = father.L;

    father.L = (*son).R;
    (*son).R = &father;
    father.Up = son;

    (*grandfather).R = son;
    (*son).Up = grandfather;
}

void Tree::dsw_vine_to_tree(){
    //transforms the grapevine back into a tree.
    int e = round(log(N) / log(2))-1;

    BST* node;
    for (int i=0; i<e; i++){
        node = tree;
        while ((node->R != nullptr) && ((node->R)->R != nullptr)){
            node = (node->R)->R;
            dsw_left_rotator(node);
        }
    }
    height_actualizer(tree->R, 0);
}

void Tree::dsw_left_rotator(BST* node){
    //rotates the grapevine structure left to obtain a tree structure.

    BST *for_rotation, *father, *lchild=nullptr;

    for_rotation = node->Up;
    father = for_rotation->Up;

    if (node->L != nullptr){
        lchild = node->L;
        lchild->Up = for_rotation;
    }

    node->L = for_rotation;
    for_rotation->Up = node;

    father->R = node;
    node->Up = father;

    for_rotation->R = lchild;
}

void Tree::pre_order_printer(BST* curr_node) const{
    //prints the tree pre-order
    if (curr_node != nullptr){
        std::cout << curr_node->value << '\t';

        if (curr_node->L != nullptr)
            pre_order_printer(curr_node->L);


        if (curr_node->R != nullptr)
            pre_order_printer(curr_node->R);
    }
}

void Tree::in_order_printer(BST* curr_node) const{
    //prints the tree in-order
    if (curr_node != nullptr){
        if (curr_node->L != nullptr)
            in_order_printer(curr_node->L);

        std::cout << (*curr_node).value << '\t';

        if (curr_node->R != nullptr)
            in_order_printer(curr_node->R);
    }
}

void Tree::structure_printer() {
    //creates a visual representation of the tree using arrays.

    if (tree->R != nullptr){
        int K = 0, i, j, width;
        std::string** arr;

        tree_depth_calculator(tree->R, K);

        width = 1u << (K + 1);
        arr = new std::string * [K + 2];


        for (i = 0; i < K + 1; i++)
            arr[i] = new std::string[width];

        for (i = 0; i < K + 1; i++)
            for (j = 0; j < width; j++)
                arr[i][j] = (char)32;


        structure_filler(tree->R, 0, width - 1, arr);

        int x = 0;
        int tmp = tree->R->value;

        while (tmp > 0){
            x++;
            tmp /= 10;
        }

        for (i = 0; i < K + 1; i++){
            for (j = 0; j < width; j++){
                std::cout.width(x + 1);
                std::cout << arr[i][j];
            }

            std::cout << "\n\n";
        }

        for (i = 0; i < K + 1; i++)
            delete[]arr[i];

        delete[]arr;
    }
}

void Tree::structure_filler(BST* curr_node, int l, int r, std::string ** arr){
    //fills the arrays from structure_printer() with data about the tree.

    if (curr_node != nullptr){
        int c = (l + r) / 2;
        arr[ curr_node->Height ] [ c ]= std::to_string (curr_node->value);

        if (curr_node->L != nullptr)
            structure_filler(curr_node->L, l, c, arr);


        if (curr_node->R != nullptr)
            structure_filler(curr_node->R, c+1, r, arr);
    }

}
