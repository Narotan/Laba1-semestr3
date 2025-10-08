#ifndef DOUBLE_LINKED_LIST_HPP
#define DOUBLE_LINKED_LIST_HPP

#include <string>
#include <memory>

using namespace std;

// Узел двусвязного списка - хранит ссылки на предыдущий и следующий узлы
struct DNode {
    string data;
    unique_ptr<DNode> next; // Владеющий указатель на следующий
    DNode* prev;            // Невладеющий указатель на предыдущий (чтобы избежать циклических ссылок)
};

// Двусвязный список - позволяет обходить список в обе стороны
struct DoubleLinkedList {
    unique_ptr<DNode> head; // Начало списка
    DNode* tail;            // Конец списка (для быстрой вставки в конец)
};

unique_ptr<DoubleLinkedList> dll_create();
void dll_append_back(DoubleLinkedList* list, const string& data);
void dll_append_front(DoubleLinkedList* list, const string& data);
void dll_append_after(DoubleLinkedList* list, const string& target, const string& data);
void dll_append_before(DoubleLinkedList* list, const string& target, const string& data);
void dll_delete_head(DoubleLinkedList* list);
void dll_delete_tail(DoubleLinkedList* list);
void dll_delete_by_value(DoubleLinkedList* list, const string& value);
bool dll_find(const DoubleLinkedList* list, const string& value);
bool dll_empty(const DoubleLinkedList* list);
DNode* dll_begin(const DoubleLinkedList* list);

#endif // DOUBLE_LINKED_LIST_HPP
