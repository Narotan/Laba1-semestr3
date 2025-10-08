#ifndef DATABASE_HPP
#define DATABASE_HPP

#include "Array.hpp"
#include "LinkedList.hpp"
#include "DoubleLinkedList.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include "AVLTree.hpp"
#include <string>
#include <memory>
#include <unordered_map>

using namespace std;

// База данных - хранит все структуры данных в hash-таблицах (unordered_map)
// Ключ - имя структуры (string), значение - умный указатель на структуру
struct Database {
    unordered_map<string, unique_ptr<Array>> arrays;
    unordered_map<string, unique_ptr<LinkedList>> lists;
    unordered_map<string, unique_ptr<DoubleLinkedList>> dlists;
    unordered_map<string, unique_ptr<Stack>> stacks;
    unordered_map<string, unique_ptr<Queue>> queues;
    unordered_map<string, unique_ptr<AVLTree>> trees;
};

unique_ptr<Database> db_create();
Array* db_get_array(Database* db, const string& name);
LinkedList* db_get_list(Database* db, const string& name);
DoubleLinkedList* db_get_dlist(Database* db, const string& name);
Stack* db_get_stack(Database* db, const string& name);
Queue* db_get_queue(Database* db, const string& name);
AVLTree* db_get_tree(Database* db, const string& name);
bool db_load(Database* db, const string& filepath);
bool db_save(const Database* db, const string& filepath);

#endif // DATABASE_HPP
