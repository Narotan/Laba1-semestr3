/*
 * Модуль управления базой данных структур на C++
 * Использует unordered_map для хранения контейнеров
 */

#include "../include/Database.hpp"
using namespace std;
#include <fstream>
#include <sstream>

unique_ptr<Database> db_create() {
    return make_unique<Database>();
}

Array* db_get_array(Database* db, const string& name) {
    // Ищем массив по имени в хеш-таблице
    auto it = db->arrays.find(name);
    if (it != db->arrays.end()) {
        return it->second.get(); // Нашли - возвращаем указатель
    }
    
    // Не нашли - создаём новый массив
    auto newArray = array_create();
    Array* ptr = newArray.get(); // Сохраняем сырой указатель
    db->arrays[name] = move(newArray); // Передаём владение в map
    return ptr;
}

LinkedList* db_get_list(Database* db, const string& name) {
    auto it = db->lists.find(name);
    if (it != db->lists.end()) {
        return it->second.get();
    }
    
    auto newList = ll_create();
    LinkedList* ptr = newList.get();
    db->lists[name] = move(newList);
    return ptr;
}

DoubleLinkedList* db_get_dlist(Database* db, const string& name) {
    auto it = db->dlists.find(name);
    if (it != db->dlists.end()) {
        return it->second.get();
    }
    
    auto newDList = dll_create();
    DoubleLinkedList* ptr = newDList.get();
    db->dlists[name] = move(newDList);
    return ptr;
}

Stack* db_get_stack(Database* db, const string& name) {
    auto it = db->stacks.find(name);
    if (it != db->stacks.end()) {
        return it->second.get();
    }
    
    auto newStack = stack_create();
    Stack* ptr = newStack.get();
    db->stacks[name] = move(newStack);
    return ptr;
}

Queue* db_get_queue(Database* db, const string& name) {
    auto it = db->queues.find(name);
    if (it != db->queues.end()) {
        return it->second.get();
    }
    
    auto newQueue = queue_create();
    Queue* ptr = newQueue.get();
    db->queues[name] = move(newQueue);
    return ptr;
}

AVLTree* db_get_tree(Database* db, const string& name) {
    auto it = db->trees.find(name);
    if (it != db->trees.end()) {
        return it->second.get();
    }
    
    auto newTree = avl_create();
    AVLTree* ptr = newTree.get();
    db->trees[name] = move(newTree);
    return ptr;
}

bool db_save(const Database* db, const string& filepath) {
    ofstream file(filepath);
    if (!file.is_open()) return false;
    
    // Сохраняем массивы
    file << "ARRAYS " << db->arrays.size() << "\n";
    for (const auto& [name, arr] : db->arrays) {
        file << name << " " << array_size(arr.get()) << "\n";
        for (size_t i = 0; i < array_size(arr.get()); i++) {
            file << array_get(arr.get(), i) << "\n";
        }
    }
    
    // Сохраняем односвязные списки
    file << "LISTS " << db->lists.size() << "\n";
    for (const auto& [name, list] : db->lists) {
        file << name << " ";
        // Сначала подсчитываем количество элементов
        int count = 0;
        Node* curr = ll_begin(list.get());
        while (curr) {
            count++;
            curr = curr->next.get();
        }
        file << count << "\n";
        // Затем сохраняем все элементы
        curr = ll_begin(list.get());
        while (curr) {
            file << curr->data << "\n";
            curr = curr->next.get();
        }
    }
    
    // Сохраняем двусвязные списки
    file << "DLISTS " << db->dlists.size() << "\n";
    for (const auto& [name, dlist] : db->dlists) {
        file << name << " ";
        int count = 0;
        DNode* curr = dll_begin(dlist.get());
        while (curr) {
            count++;
            curr = curr->next.get();
        }
        file << count << "\n";
        curr = dll_begin(dlist.get());
        while (curr) {
            file << curr->data << "\n";
            curr = curr->next.get();
        }
    }
    
    // Сохраняем стеки
    file << "STACKS " << db->stacks.size() << "\n";
    for (const auto& [name, stack] : db->stacks) {
        file << name << " " << stack_size(stack.get()) << "\n";
        // Стек теперь на односвязном списке - обходим его
        Node* curr = ll_begin(stack->list.get());
        while (curr) {
            file << curr->data << "\n";
            curr = curr->next.get();
        }
    }
    
    // Сохраняем очереди
    file << "QUEUES " << db->queues.size() << "\n";
    for (const auto& [name, queue] : db->queues) {
        file << name << " ";
        int count = 0;
        DNode* curr = dll_begin(queue->list.get());
        while (curr) {
            count++;
            curr = curr->next.get();
        }
        file << count << "\n";
        curr = dll_begin(queue->list.get());
        while (curr) {
            file << curr->data << "\n";
            curr = curr->next.get();
        }
    }
    
    // Сохраняем деревья
    file << "TREES " << db->trees.size() << "\n";
    for (const auto& [name, tree] : db->trees) {
        file << name << "\n";
    }
    
    file.close();
    return true;
}

bool db_load(Database* db, const string& filepath) {
    ifstream file(filepath);
    if (!file.is_open()) return false;
    
    string type;
    int count;
    
    // Загружаем массивы
    file >> type >> count;
    if (type == "ARRAYS") {
        for (int i = 0; i < count; i++) {
            string name;
            size_t size;
            file >> name >> size;
            file.ignore(); // пропускаем \n
            
            Array* arr = db_get_array(db, name);
            for (size_t j = 0; j < size; j++) {
                string value;
                getline(file, value);
                array_append(arr, value);
            }
        }
    }
    
    // Загружаем односвязные списки
    file >> type >> count;
    if (type == "LISTS") {
        for (int i = 0; i < count; i++) {
            string name;
            int size;
            file >> name >> size;
            file.ignore();
            
            LinkedList* list = db_get_list(db, name);
            for (int j = 0; j < size; j++) {
                string value;
                getline(file, value);
                ll_append_back(list, value);
            }
        }
    }
    
    // Загружаем двусвязные списки
    file >> type >> count;
    if (type == "DLISTS") {
        for (int i = 0; i < count; i++) {
            string name;
            int size;
            file >> name >> size;
            file.ignore();
            
            DoubleLinkedList* dlist = db_get_dlist(db, name);
            for (int j = 0; j < size; j++) {
                string value;
                getline(file, value);
                dll_append_back(dlist, value);
            }
        }
    }
    
    // Загружаем стеки
    file >> type >> count;
    if (type == "STACKS") {
        for (int i = 0; i < count; i++) {
            string name;
            size_t size;
            file >> name >> size;
            file.ignore();
            
            Stack* stack = db_get_stack(db, name);
            // Загружаем элементы в обратном порядке или добавляем в конец списка
            // Т.к. сохранили от головы к хвосту, добавляем в конец, чтобы восстановить порядок
            for (size_t j = 0; j < size; j++) {
                string value;
                getline(file, value);
                ll_append_back(stack->list.get(), value); // Добавляем в конец, не через stack_push
            }
        }
    }
    
    // Загружаем очереди
    file >> type >> count;
    if (type == "QUEUES") {
        for (int i = 0; i < count; i++) {
            string name;
            int size;
            file >> name >> size;
            file.ignore();
            
            Queue* queue = db_get_queue(db, name);
            for (int j = 0; j < size; j++) {
                string value;
                getline(file, value);
                queue_enqueue(queue, value);
            }
        }
    }
    
    // Загружаем деревья
    file >> type >> count;
    if (type == "TREES") {
        for (int i = 0; i < count; i++) {
            string name;
            file >> name;
            db_get_tree(db, name);
        }
    }
    
    file.close();
    return true;
}
