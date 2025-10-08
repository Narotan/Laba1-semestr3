/*
 * Реализация стека (LIFO - Last In First Out) на C++
 * Использует односвязный список для управления памятью
 */

#include "../include/Stack.hpp"
using namespace std;

unique_ptr<Stack> stack_create() {
    auto stack = make_unique<Stack>();
    stack->list = ll_create(); // Создаём односвязный список
    return stack;
}

void stack_push(Stack* stack, const string& value) {
    // LIFO - добавляем в голову списка (это быстро - O(1))
    ll_append_front(stack->list.get(), value);
}

optional<string> stack_pop(Stack* stack) {
    if (ll_empty(stack->list.get())) {
        return nullopt; 
    }
    // LIFO - берём элемент из головы списка (последний добавленный)
    Node* head = ll_begin(stack->list.get());
    string value = head->data;
    ll_delete_head(stack->list.get()); // Удаляем голову
    return value;
}

bool stack_is_empty(const Stack* stack) {
    return ll_empty(stack->list.get());
}

size_t stack_size(const Stack* stack) {
    return ll_size(stack->list.get());
}
