using namespace std;
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
#include "include/Database.hpp"

// Преобразование строки в верхний регистр
string toUpper(string str) {
    transform(str.begin(), str.end(), str.begin(), 
                   [](unsigned char c) { return toupper(c); });
    return str;
}

// Вывод содержимого массива
void printArray(const Array* arr) {
    cout << "[";
    for (size_t i = 0; i < array_size(arr); i++) {
        cout << array_get(arr, i);
        if (i < array_size(arr) - 1) cout << " ";
    }
    cout << "]";
}

// Вывод содержимого односвязного списка
void printList(const LinkedList* list) {
    cout << "[";
    bool first = true;
    Node* curr = ll_begin(list);
    while (curr) {
        if (!first) cout << " ";
        cout << curr->data;
        first = false;
        curr = curr->next.get();
    }
    cout << "]";
}

// Вывод содержимого двусвязного списка
void printDList(const DoubleLinkedList* dlist) {
    cout << "[";
    bool first = true;
    DNode* curr = dll_begin(dlist);
    while (curr) {
        if (!first) cout << " ";
        cout << curr->data;
        first = false;
        curr = curr->next.get();
    }
    cout << "]";
}

int main(int argc, char* argv[]) {
    string filepath = "file.data";
    string query;
    
    // Парсинг аргументов
    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "--file" && i + 1 < argc) {
            filepath = argv[++i];
        } else if (string(argv[i]) == "--query" && i + 1 < argc) {
            query = argv[++i];
        }
    }
    
    if (query.empty()) {
        cout << "ERROR: no query provided\n";
        cout << "Usage: " << argv[0] << " --file <filepath> --query <query>\n";
        return 1;
    }
    
    auto db = db_create();
    db_load(db.get(), filepath);
    
    // Парсинг команды: разбиваем на глагол, имя структуры и аргументы
    istringstream iss(query);
    string verb, name, arg1, arg2;
    iss >> verb >> name >> arg1 >> arg2;
    verb = toUpper(verb); // Приводим команду к верхнему регистру
    
    bool changed = false; // Флаг изменения данных (для сохранения)
    
    // Массивы (M) - определяем по первой букве команды
    if (verb[0] == 'M') {
        Array* arr = db_get_array(db.get(), name); // Получаем или создаём массив
        
        if (verb == "MPUSH") {
            array_append(arr, arg1); // Добавляем элемент в конец
            changed = true;
            cout << "-> " << arg1 << "\n";
        }
        else if (verb == "MINSERT") {
            // Вставка элемента по индексу: MINSERT name index value
            int idx = stoi(arg1);
            array_insert(arr, idx, arg2);
            changed = true;
            cout << "-> " << arg2 << "\n";
        }
        else if (verb == "MSET") {
            // Изменение элемента по индексу: MSET name index value
            int idx = stoi(arg1);
            array_set(arr, idx, arg2);
            changed = true;
            cout << "-> " << arg2 << "\n";
        }
        else if (verb == "MDEL") {
            // Удаление по значению
            if (array_remove_by_value(arr, arg1)) {
                changed = true;
                cout << "-> " << arg1 << "\n";
            } else {
                cout << "-> NOTFOUND\n";
            }
        }
        else if (verb == "MDELINDEX") {
            // Удаление по индексу: MDELINDEX name index
            if (arg1.empty()) {
                cout << "-> ERROR: index not provided\n";
            } else {
                int idx = stoi(arg1);
                if (idx >= 0 && (size_t)idx < array_size(arr)) {
                    array_remove(arr, idx);
                    changed = true;
                    cout << "-> OK\n";
                } else {
                    cout << "-> OUTOFRANGE\n";
                }
            }
        }
        else if (verb == "MGET") {
            if (!arg1.empty()) {
                int idx = stoi(arg1);
                string val = array_get(arr, idx);
                if (!val.empty()) {
                    cout << "-> " << val << "\n";
                } else {
                    cout << "-> NULL\n";
                }
            } else {
                cout << "-> ";
                printArray(arr);
                cout << "\n";
            }
        }
        else if (verb == "MSIZE") {
            cout << "-> " << array_size(arr) << "\n";
        }
    }
    
    // Односвязный список (F)
    else if (verb[0] == 'F') {
        LinkedList* list = db_get_list(db.get(), name);
        
        if (verb == "FPUSH") {
            ll_append_back(list, arg1);
            changed = true;
            cout << "-> " << arg1 << "\n";
        }
        else if (verb == "FADDHEAD") {
            ll_append_front(list, arg1);
            changed = true;
            cout << "-> " << arg1 << "\n";
        }
        else if (verb == "FADDAFTER") {
            ll_append_after(list, arg1, arg2);
            changed = true;
            cout << "-> " << arg2 << "\n";
        }
        else if (verb == "FADDBEFORE") {
            ll_append_before(list, arg1, arg2);
            changed = true;
            cout << "-> " << arg2 << "\n";
        }
        else if (verb == "FDEL") {
            ll_delete_by_value(list, arg1);
            changed = true;
            cout << "-> " << arg1 << "\n";
        }
        else if (verb == "FDELHEAD") {
            ll_delete_head(list);
            changed = true;
            cout << "-> OK\n";
        }
        else if (verb == "FDELTAIL") {
            ll_delete_tail(list);
            changed = true;
            cout << "-> OK\n";
        }
        else if (verb == "FGET") {
            if (!arg1.empty()) {
                int idx = stoi(arg1);
                string val = ll_get_by_index(list, idx);
                if (!val.empty()) {
                    cout << "-> " << val << "\n";
                } else {
                    cout << "-> NULL\n";
                }
            } else {
                cout << "-> ";
                printList(list);
                cout << "\n";
            }
        }
        else if (verb == "FEXISTS") {
            cout << "-> " << (ll_find(list, arg1) ? "TRUE" : "FALSE") << "\n";
        }
    }
    
    // Двусвязный список (L)
    else if (verb[0] == 'L') {
        DoubleLinkedList* dlist = db_get_dlist(db.get(), name);
        
        if (verb == "LPUSH") {
            dll_append_back(dlist, arg1);
            changed = true;
            cout << "-> " << arg1 << "\n";
        }
        else if (verb == "LUNSHIFT") {
            dll_append_front(dlist, arg1);
            changed = true;
            cout << "-> " << arg1 << "\n";
        }
        else if (verb == "LAFTER") {
            dll_append_after(dlist, arg1, arg2);
            changed = true;
            cout << "-> " << arg2 << "\n";
        }
        else if (verb == "LBEFORE") {
            dll_append_before(dlist, arg1, arg2);
            changed = true;
            cout << "-> " << arg2 << "\n";
        }
        else if (verb == "LDEL") {
            dll_delete_by_value(dlist, arg1);
            changed = true;
            cout << "-> " << arg1 << "\n";
        }
        else if (verb == "LDELHEAD") {
            dll_delete_head(dlist);
            changed = true;
            cout << "-> OK\n";
        }
        else if (verb == "LDELTAIL") {
            dll_delete_tail(dlist);
            changed = true;
            cout << "-> OK\n";
        }
        else if (verb == "LGET") {
            cout << "-> ";
            printDList(dlist);
            cout << "\n";
        }
        else if (verb == "LEXISTS") {
            cout << "-> " << (dll_find(dlist, arg1) ? "TRUE" : "FALSE") << "\n";
        }
    }
    
    // Стек (S)
    else if (verb[0] == 'S') {
        Stack* stack = db_get_stack(db.get(), name);
        
        if (verb == "SPUSH") {
            stack_push(stack, arg1);
            changed = true;
            cout << "-> " << arg1 << "\n";
        }
        else if (verb == "SPOP") {
            auto val = stack_pop(stack);
            if (val.has_value()) {
                changed = true;
                cout << "-> " << val.value() << "\n";
            } else {
                cout << "-> NULL\n";
            }
        }
        else if (verb == "SSIZE") {
            cout << "-> " << stack_size(stack) << "\n";
        }
    }
    
    // Очередь (Q)
    else if (verb[0] == 'Q') {
        Queue* queue = db_get_queue(db.get(), name);
        
        if (verb == "QPUSH") {
            queue_enqueue(queue, arg1);
            changed = true;
            cout << "-> " << arg1 << "\n";
        }
        else if (verb == "QPOP") {
            auto val = queue_dequeue(queue);
            if (val.has_value()) {
                changed = true;
                cout << "-> " << val.value() << "\n";
            } else {
                cout << "-> NULL\n";
            }
        }
    }
    
    // Дерево (T)
    else if (verb[0] == 'T') {
        AVLTree* tree = db_get_tree(db.get(), name);
        
        if (verb == "TINSERT") {
            int key = stoi(arg1);
            if (!avl_search(tree, key)) {
                avl_insert(tree, key);
                changed = true;
                cout << "-> " << key << "\n";
            } else {
                cout << "-> ALREADY\n";
            }
        }
        else if (verb == "TDEL") {
            int key = stoi(arg1);
            if (avl_search(tree, key)) {
                avl_delete(tree, key);
                changed = true;
                cout << "-> " << key << "\n";
            } else {
                cout << "-> NOTFOUND\n";
            }
        }
        else if (verb == "TGET") {
            int key = stoi(arg1);
            cout << "-> " << (avl_search(tree, key) ? "TRUE" : "FALSE") << "\n";
        }
    }
    
    if (changed) {
        db_save(db.get(), filepath);
    }
    
    return 0;
}
