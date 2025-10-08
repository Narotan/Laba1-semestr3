#ifndef STACK_HPP
#define STACK_HPP

#include "LinkedList.hpp"
#include <string>
#include <optional>
#include <memory>

using namespace std;

// Стек - LIFO (Last In First Out - последним вошёл, первым вышел)
// Реализован через односвязный список (добавление и удаление из головы за O(1))
struct Stack {
    unique_ptr<LinkedList> list; // Используем односвязный список
};

unique_ptr<Stack> stack_create();
void stack_push(Stack* stack, const string& value);
optional<string> stack_pop(Stack* stack);
bool stack_is_empty(const Stack* stack);
size_t stack_size(const Stack* stack);

#endif // STACK_HPP
