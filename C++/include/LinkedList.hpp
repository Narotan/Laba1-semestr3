#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <string>
#include <memory>

using namespace std;

// Узел односвязного списка
struct Node {
    string data;
    unique_ptr<Node> next; // unique_ptr автоматически удаляет узел при уничтожении
};

// Односвязный список - каждый узел хранит ссылку только на следующий
struct LinkedList {
    unique_ptr<Node> head; // Указатель на первый элемент
};

unique_ptr<LinkedList> ll_create();
void ll_append_back(LinkedList* list, const string& data);
void ll_append_front(LinkedList* list, const string& data);
void ll_append_after(LinkedList* list, const string& target, const string& data);
void ll_append_before(LinkedList* list, const string& target, const string& data);
void ll_delete_head(LinkedList* list);
void ll_delete_tail(LinkedList* list);
void ll_delete_by_value(LinkedList* list, const string& value);
bool ll_find(const LinkedList* list, const string& value);
string ll_get_by_index(const LinkedList* list, size_t index);
bool ll_empty(const LinkedList* list);
size_t ll_size(const LinkedList* list);
Node* ll_begin(const LinkedList* list);

#endif // LINKED_LIST_HPP
