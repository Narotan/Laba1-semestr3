/*
 * Реализация односвязного списка на C++
 * Использует unique_ptr для автоматического управления памятью
 */

#include "../include/LinkedList.hpp"

using namespace std;

unique_ptr<LinkedList> ll_create() {
    auto list = make_unique<LinkedList>();
    list->head = nullptr;
    return list;
}

void ll_append_back(LinkedList* list, const string& data) {
    // Создаём новый узел с данными
    auto newNode = make_unique<Node>();
    newNode->data = data;
    newNode->next = nullptr;
    
    // Если список пустой, новый узел становится головой
    if (!list->head) {
        list->head = move(newNode);
        return;
    }
    
    // Идём до последнего узла (у которого next == nullptr)
    Node* current = list->head.get();
    while (current->next) {
        current = current->next.get();
    }
    // Присоединяем новый узел в конец
    current->next = move(newNode);
}

void ll_append_front(LinkedList* list, const string& data) {
    auto newNode = make_unique<Node>();
    newNode->data = data;
    newNode->next = move(list->head);
    list->head = move(newNode);
}

void ll_append_after(LinkedList* list, const string& target, const string& data) {
    Node* current = list->head.get();
    while (current && current->data != target) {
        current = current->next.get();
    }
    
    if (!current) return;
    
    auto newNode = make_unique<Node>();
    newNode->data = data;
    newNode->next = move(current->next);
    current->next = move(newNode);
}

void ll_append_before(LinkedList* list, const string& target, const string& data) {
    if (!list->head) return;
    
    if (list->head->data == target) {
        ll_append_front(list, data);
        return;
    }
    
    Node* prev = list->head.get();
    Node* current = list->head->next.get();
    
    while (current && current->data != target) {
        prev = current;
        current = current->next.get();
    }
    
    if (!current) return;
    
    auto newNode = make_unique<Node>();
    newNode->data = data;
    newNode->next = move(prev->next);
    prev->next = move(newNode);
}

void ll_delete_head(LinkedList* list) {
    if (!list->head) return;
    list->head = move(list->head->next);
}

void ll_delete_tail(LinkedList* list) {
    if (!list->head) return;
    
    if (!list->head->next) {
        list->head.reset();
        return;
    }
    
    Node* current = list->head.get();
    while (current->next && current->next->next) {
        current = current->next.get();
    }
    
    current->next.reset();
}

void ll_delete_by_value(LinkedList* list, const string& value) {
    if (!list->head) return;
    
    // Если удаляемый элемент в голове списка
    if (list->head->data == value) {
        ll_delete_head(list);
        return;
    }
    
    // Ищем нужный узел, сохраняя предыдущий
    Node* prev = list->head.get();
    Node* current = list->head->next.get();
    
    while (current && current->data != value) {
        prev = current;
        current = current->next.get();
    }
    
    if (!current) return; // Элемент не найден
    
    // Перенаправляем указатель предыдущего узла, минуя удаляемый
    // unique_ptr автоматически удалит current
    prev->next = move(current->next);
}

bool ll_find(const LinkedList* list, const string& value) {
    Node* current = list->head.get();
    while (current) {
        if (current->data == value) {
            return true;
        }
        current = current->next.get();
    }
    return false;
}

string ll_get_by_index(const LinkedList* list, size_t index) {
    Node* current = list->head.get();
    size_t i = 0;
    while (current && i < index) {
        current = current->next.get();
        i++;
    }
    return current ? current->data : "";
}

bool ll_empty(const LinkedList* list) {
    return list->head == nullptr;
}

// Возвращает количество элементов в списке
size_t ll_size(const LinkedList* list) {
    size_t count = 0;
    Node* current = list->head.get();
    // Проходим по всему списку и считаем узлы
    while (current != nullptr) {
        count++;
        current = current->next.get();
    }
    return count;
}

Node* ll_begin(const LinkedList* list) {
    return list->head.get();
}
