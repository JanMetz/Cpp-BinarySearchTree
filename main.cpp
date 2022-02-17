#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <ctime>
#include <cmath>
#include "Tree.h"
#include "BST.h"

void menu_options_printer();
void option_switcher(int opt, Tree obj);
void test_conductor();

int main(){
    Tree obj;
    int opt = 0;

    std::cout << "Initializing...\n";
    menu_options_printer();

    while (true){
        std::cout <<"\nChoose option: ";
        std::cin >> opt;

        if (opt == 0)
            break;

        if (opt == 15)
            menu_options_printer();

        option_switcher(opt, obj);
        std::cout << "\n\nFor menu press 15.\n\n";
    }

    std::cout << "Good bye!";

    return 0;
}

void menu_options_printer(){
    //prints the menu options
    std::cout << "\nPlease choose from the following options: \n"
        << "To print your tree in-order press 1\n"
        << "To print your tree pre-order press 2\n"
        << "To print the structure of the tree press 3\n"
        << "To print your tree from chosen node press 4\n"
        << "To print greatest element press 5\n"
        << "To print smallest element press 6\n"
        << "To delete an element press 7\n"
        << "To balance your tree press 8\n"
        << "To delete your tree press 9\n"
        << "To delete your tree and print every deleted element press 10\n"
        << "To perform a series of tests press 11\n"
        << "To add a new element to the tree press 12\n"
        << "To generate a random tree press 13\n"
        << "To generate your own tree (up to 25 elements) press 14\n"
        << "To exit press 0\n";

}

void option_switcher(int opt, Tree obj){
    //initializes chosen function.

    int X = 0;
    std::string max_path, min_path;

    switch (opt)
    {
    case 1:
        std::cout << "In order:\n";
        obj.in_order_printer(obj.tree->R);
        break;

    case 2:
        std::cout << "Pre order: \n";
            obj.pre_order_printer(obj.tree->R);
        break;

    case 3:
        std::cout << "Structure: \n";
        obj.structure_printer();
        break;

    case 4:
        std::cout << "Insert key of the node you would like the printing to begin from: ";
        std::cin >> X;
        if (obj.tree->R != nullptr)
            obj.pre_order_printer(obj.key_finder(X));
        else
            std::cout << "The tree does not exist!\n";
        break;

    case 5:
        std::cout << "Greatest element: " << Tree::maximum_finder(obj.tree->R, max_path) << "\tIt's path: " << max_path;
        break;

    case 6:
        std::cout << "Smallest element: " << Tree::minimum_finder(obj.tree->R, min_path) << "\tIt's path: " << min_path;
        break;

    case 7:
        std::cout << "Insert which element you would like to delete: ";
        std::cin >> X;
        std::cout << "Deleting...\n";
        if (obj.tree->R != nullptr && obj.key_finder(X) != nullptr){
            obj.key_deleter(X);
            std::cout << "Key deletion successful.";
        }
        else
            std::cout << "The chosen element does not exist!\n";
        break;

    case 8:
        std::cout << "Balancing...\n";
        if (obj.tree->R != nullptr){
            obj.dsw_tree_to_vine();
            obj.dsw_vine_to_tree();
            std::cout << "\nTree balancing successful.";
        }
        else
            std::cout << "The tree does not exist!\n";

        break;

    case 9:
        if (obj.tree->R != nullptr){
            std::cout << "Deleting the tree...";
            if (obj.N < 5000)
                obj.deleter_r(obj.tree->R, 'I');
            else
                obj.deleter_i();
            obj.tree->R = nullptr;
            std::cout << "\nTree deletion successful.";
        }
        else
            std::cout << "The tree has already been deleted!\n";

        break;

    case 10:
        if (obj.tree->R != nullptr){
            std::cout << "Deleting the tree...\n";
            if (obj.N < 5000){
                obj.deleter_r(obj.tree->R, 'V');
                obj.tree->R = nullptr;
            }
            else
                std::cout << "Program error! Cannot display the tree elements if the size of the tree exceeds 5000.\n";

            std::cout << "\nTree deletion successful.";
        }
        else
            std::cout << "The tree has already been deleted!\n";

        break;

    case 11:
        std::cout << "Launching tests...\n";
        test_conductor();
        std::cout << "\nTest launch successful.";
        break;

    case 12:
        while (true){
            std::cout << "Insert key of the element you would like to add to the tree: ";
            std::cin >> X;
            if (obj.key_finder(X) != nullptr)
                std::cout << "This element is already in a tree! Please try again.\n";
            else{
                obj.tree_element_adder(X);
                break;
            }
        }
        std::cout << "\nElement adding successful.";
        break;

    case 13:
        std::cout << "Insert number of elements you wish the tree to have: ";
        std::cin >> X;
        if (X > 0){
            if (obj.tree->R != nullptr){
                obj.deleter_r(obj.tree->R, 'I');
                obj.tree->R = nullptr;
            }
            obj.random_tree_creator(X);

            std::cout << "\nTree creation successful.";
        }
        else
            std::cout << "Cannot create tree with less than 1 element!\n";
        break;

    case 14:
        std::cout << "Insert number of elements you wish the tree to have: ";
        std::cin >> X;
        if (X < 26 && X > 0){
            obj.users_tree_generator(X);
            std::cout << "\nTree creation successful.";
        }
        else
            std::cout << "Cannot create trees smaller than 1 nor bigger than 25 elements!\n";

        break;

    case 15: break;

    default:
        std::cout << "Wrong number inserted! Please, try again.";

    }

}

void test_conductor(){
    //performs 13 tests, each for different number of elements in a tree (ranging from 20 000 to 200 000). Each test contains checking the execution times of different operations, such as:
    //tree creation, finding minimum, balancing a tree and printing it in-order. All this data is then saved in a res.txt file.
    clock_t st, nd;
    std::fstream res;
    std::string path;
    int i, j, **tab;
    double ex_time;

    tab = new int* [14];

    BST* VSL = new BST;

    (*VSL).L = nullptr;
    (*VSL).value = -1;
    (*VSL).Up = nullptr;
    VSL->Height = -1;

    BST* BT = new BST;

    (*BT).L = nullptr;
    (*BT).R = nullptr;
    (*BT).value = -1;
    (*BT).Up = nullptr;
    BT->Height = -1;

    Tree obj, obj2;

    res.open("results.txt", std::ios::out);
    srand(time(nullptr));

    res << "Operation\tNo.\tEx_t\n\n";

    for (j = 0; j < 13; j++){
        obj.N = 2000 + 15000 * j;

        tab[j] = new int[obj.N+2];

        st = clock();
        for (i = obj.N; i >0; i--)
            obj.tree_element_adder(i);

        nd = clock();
        ex_time = double(nd - st) / CLOCKS_PER_SEC;

        res << "Creating BST:\t" << obj.N << '\t' << ex_time << '\n';


        st = clock();
        for (i = 1; i <= obj.N; i++)
            tab[j][i] = i;

        VSL->Height = 0;
        VSL->R = obj2.VSL_tree_maker(tab[j], 1, obj.N, VSL);

        nd = clock();
        ex_time = double(nd - st) / CLOCKS_PER_SEC;

        res << "Creating VSL:\t" << obj2.N << '\t' << ex_time << '\n';


        st = clock();
        Tree::minimum_finder(BT, path);
        nd = clock();
        ex_time = double(nd - st) / CLOCKS_PER_SEC;

        res << "Minimum BST:\t" << obj.N << '\t' << ex_time << '\n';

        st = clock();
        Tree::minimum_finder(VSL, path);
        nd = clock();
        ex_time = double(nd - st) / CLOCKS_PER_SEC;

        res << "Minimum VSL:\t" << obj2.N << '\t' << ex_time << '\n';

        st = clock();
        obj.in_order_printer(BT->R);
        nd = clock();
        ex_time = double(nd - st) / CLOCKS_PER_SEC;

        res << "Traversing BST:\t" << obj.N << '\t' << ex_time << '\n';

        st = clock();
        obj2.in_order_printer(VSL->R);
        nd = clock();
        ex_time = double(nd - st) / CLOCKS_PER_SEC;

        res << "Traversing VSL:\t" << obj2.N << '\t' << ex_time << '\n';

        st = clock();
        obj.dsw_tree_to_vine();
        obj.dsw_vine_to_tree();
        nd = clock();
        ex_time = double(nd - st) / CLOCKS_PER_SEC;

        res << "Balancing BST:\t" << obj.N << '\t' << ex_time << "\n\n";


        delete[]tab[j];

        obj2.deleter_i();
        VSL->R = nullptr;

        obj.deleter_i();
        BT->R = nullptr;
    }

    delete[]tab;
    res.close();

}



