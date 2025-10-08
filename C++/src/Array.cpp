#include "../include/Array.hpp"
#include <cstring>

using namespace std;

// Создаёт новый динамический массив с начальной ёмкостью
unique_ptr<Array> array_create() {
    auto arr = make_unique<Array>();
    arr->capacity = 4;  
    arr->size = 0;
    arr->data = new char*[arr->capacity];
    return arr;
}

void array_destroy(Array* arr) {
    // Сначала освобождаем каждую строку
    for (size_t i = 0; i < arr->size; i++) {
        delete[] arr->data[i];
    }
    delete[] arr->data;
}

static void array_resize(Array* arr) {
    arr->capacity *= 2;  
    
    // Выделяем новый массив указателей большего размера
    char** new_data = new char*[arr->capacity];
    
    for (size_t i = 0; i < arr->size; i++) {
        new_data[i] = arr->data[i];
    }
    
    delete[] arr->data;
    
    arr->data = new_data;
}

void array_append(Array* arr, const string& value) {
    // Если массив заполнен — расширяем его
    if (arr->size >= arr->capacity) {
        array_resize(arr);
    }
    // Выделяем память для новой строки и копируем данные
    arr->data[arr->size] = new char[value.length() + 1];
    strcpy(arr->data[arr->size], value.c_str());
    arr->size++;  
}

// Вставляет элемент по индексу
void array_insert(Array* arr, size_t index, const string& value) {
    if (index > arr->size) return;
    
    if (arr->size >= arr->capacity) {
        array_resize(arr);
    }
    
    for (size_t i = arr->size; i > index; i--) {
        arr->data[i] = arr->data[i - 1];
    }
    
    arr->data[index] = new char[value.length() + 1];
    strcpy(arr->data[index], value.c_str());
    arr->size++;
}

// Возвращает элемент по индексу
string array_get(const Array* arr, size_t index) {
    if (index >= arr->size) 
        return ""; // если индекс за пределами — возвращаем пустую строку
    return string(arr->data[index]); // Преобразуем char* в string
}

// Удаляет элемент по индексу
void array_remove(Array* arr, size_t index) {
    if (index >= arr->size) return;
    
    // Освобождаем память удаляемой строки
    delete[] arr->data[index];
    
    // Сдвигаем все указатели справа от index на одну позицию влево
    for (size_t i = index; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }
    
    arr->size--; 
}

// Заменяет элемент по индексу новым значением
void array_set(Array* arr, size_t index, const string& value) {
    if (index >= arr->size) return;
    
    delete[] arr->data[index];
    
    arr->data[index] = new char[value.length() + 1];
    strcpy(arr->data[index], value.c_str());
}

bool array_remove_by_value(Array* arr, const string& value) {
    for (size_t i = 0; i < arr->size; i++) {
        if (strcmp(arr->data[i], value.c_str()) == 0) {
            array_remove(arr, i);  // Удаляем найденный элемент
            return true;
        }
    }
    return false; // элемент не найден
}

// Возвращает количество элементов
size_t array_size(const Array* arr) {
    return arr->size;
}

// Проверяет, пуст ли массив
bool array_empty(const Array* arr) {
    return arr->size == 0;
}
