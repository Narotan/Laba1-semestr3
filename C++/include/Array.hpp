#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <string>
#include <memory>
#include <cstring>

using namespace std;

// Динамический массив строк с ручным управлением памятью через new/delete
struct Array {
    char** data;       // Массив указателей на C-строки
    size_t size;       // Текущее количество элементов
    size_t capacity;   // Выделенная ёмкость (сколько можно хранить без расширения)
};

unique_ptr<Array> array_create();
void array_destroy(Array* arr);  // Освобождает всю выделенную память
void array_append(Array* arr, const string& value);
void array_insert(Array* arr, size_t index, const string& value);
string array_get(const Array* arr, size_t index);
void array_remove(Array* arr, size_t index);
void array_set(Array* arr, size_t index, const string& value);
bool array_remove_by_value(Array* arr, const string& value);
size_t array_size(const Array* arr);
bool array_empty(const Array* arr);

#endif // ARRAY_HPP
