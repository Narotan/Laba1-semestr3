/*
 * Реализация двусвязного списка на C++
 * Использует unique_ptr для автоматического управления памятью
 */

#include "../include/DoubleLinkedList.hpp"
using namespace std;

unique_ptr<DoubleLinkedList> dll_create() {
    auto list = make_unique<DoubleLinkedList>();
    list->head = nullptr;
    list->tail = nullptr;
    return list;
}

void dll_append_back(DoubleLinkedList* list, const string& data) {
    // Создаём новый узел
    auto newNode = make_unique<DNode>();
    newNode->data = data;
    newNode->next = nullptr;
    newNode->prev = list->tail; // Связываем с текущим хвостом
    
    if (!list->tail) {
        // Список пустой - новый узел становится и головой, и хвостом
        list->tail = newNode.get();
        list->head = move(newNode);
    } else {
        // Присоединяем к концу и обновляем указатель tail
        list->tail->next = move(newNode);
        list->tail = list->tail->next.get();
    }
}

void dll_append_front(DoubleLinkedList* list, const string& data) {
    auto newNode = make_unique<DNode>();
    newNode->data = data;
    newNode->next = move(list->head);
    newNode->prev = nullptr;
    
    if (!newNode->next) {
        list->head = move(newNode);
        list->tail = list->head.get();
    } else {
        newNode->next->prev = newNode.get();
        list->head = move(newNode);
    }
}

void dll_append_after(DoubleLinkedList* list, const string& target, const string& data) {
    DNode* current = list->head.get();
    while (current && current->data != target) {
        current = current->next.get();
    }
    
    if (!current) return;
    
    auto newNode = make_unique<DNode>();
    newNode->data = data;
    newNode->next = move(current->next);
    newNode->prev = current;
    
    if (newNode->next) {
        newNode->next->prev = newNode.get();
    } else {
        list->tail = newNode.get();
    }
    
    current->next = move(newNode);
}

void dll_append_before(DoubleLinkedList* list, const string& target, const string& data) {
    DNode* current = list->head.get();
    while (current && current->data != target) {
        current = current->next.get();
    }
    
    if (!current) return;
    
    if (!current->prev) {
        dll_append_front(list, data);
        return;
    }
    
    auto newNode = make_unique<DNode>();
    newNode->data = data;
    newNode->next = move(current->prev->next);
    newNode->prev = current->prev;
    
    current->prev->next = move(newNode);
    current->prev = current->prev->next.get();
}

void dll_delete_head(DoubleLinkedList* list) {
    if (!list->head) return;
    
    list->head = move(list->head->next);
    
    if (list->head) {
        list->head->prev = nullptr;
    } else {
        list->tail = nullptr;
    }
}

void dll_delete_tail(DoubleLinkedList* list) {
    if (!list->tail) return;
    
    if (list->tail->prev) {
        list->tail = list->tail->prev;
        list->tail->next.reset();
    } else {
        list->head.reset();
        list->tail = nullptr;
    }
}

void dll_delete_by_value(DoubleLinkedList* list, const string& value) {
    // Ищем узел с нужным значением
    DNode* current = list->head.get();
    while (current && current->data != value) {
        current = current->next.get();
    }
    
    if (!current) return; // Не нашли
    
    if (current->prev) {
        // Перенаправляем указатель предыдущего узла
        current->prev->next = move(current->next);
        if (current->next) {
            // Обновляем prev у следующего узла
            current->next->prev = current->prev;
        } else {
            // Удаляемый узел был хвостом
            list->tail = current->prev;
        }
    } else {
        // Удаляемый узел в голове списка
        dll_delete_head(list);
    }
}

bool dll_find(const DoubleLinkedList* list, const string& value) {
    DNode* current = list->head.get();
    while (current) {
        if (current->data == value) {
            return true;
        }
        current = current->next.get();
    }
    return false;
}

bool dll_empty(const DoubleLinkedList* list) {
    return list->head == nullptr;
}

DNode* dll_begin(const DoubleLinkedList* list) {
    return list->head.get();
}
