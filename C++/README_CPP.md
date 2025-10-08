# Базовые структуры данных на C++

Проект переписан с C на C++ с использованием современных возможностей C++17.

## Основные улучшения по сравнению с C версией:

### 1. **Автоматическое управление памятью**
- Использование `std::unique_ptr` для автоматического освобождения памяти
- Использование `std::vector` и `std::string` вместо ручного управления массивами
- Отсутствие утечек памяти благодаря RAII (Resource Acquisition Is Initialization)

### 2. **Объектно-ориентированный подход**
- Все структуры данных реализованы как классы
- Инкапсуляция данных (приватные поля)
- Конструкторы и деструкторы для инициализации и очистки

### 3. **Современные возможности C++**
- `std::optional` для безопасного возврата значений (вместо NULL)
- `std::unordered_map` для хранения контейнеров в базе данных
- Итераторы для обхода списков
- Lambda-функции
- `std::move` для эффективного перемещения ресурсов

### 4. **Безопасность типов**
- Использование `std::string` вместо `char*`
- Использование `size_t` для индексов
- Проверка границ массивов

## Структуры данных

### Array (Массив)
- Реализован через `std::vector<std::string>`
- Автоматическое изменение размера
- Методы: `append`, `insert`, `get`, `remove`, `set`, `removeByValue`

### LinkedList (Односвязный список)
- Использует `std::unique_ptr` для узлов
- Методы: `appendBack`, `appendFront`, `appendAfter`, `appendBefore`, 
  `deleteHead`, `deleteTail`, `deleteByValue`, `find`, `getByIndex`
- Поддержка итераторов

### DoubleLinkedList (Двусвязный список)
- Узлы с указателями на предыдущий и следующий элементы
- Быстрая вставка/удаление с обоих концов
- Поддержка итераторов

### Stack (Стек - LIFO)
- Реализован через `std::vector<std::string>`
- Методы: `push`, `pop` (возвращает `std::optional<std::string>`)

### Queue (Очередь - FIFO)
- Основана на двусвязном списке
- Методы: `enqueue`, `dequeue` (возвращает `std::optional<std::string>`)

### AVLTree (АВЛ-дерево)
- Самобалансирующееся бинарное дерево поиска
- Автоматическая балансировка после вставки/удаления
- Методы: `insert`, `remove`, `search`

## Компиляция

```bash
make
```

Это создаст исполняемый файл `dbms_cpp`.

Для очистки:
```bash
make clean
```

Для перекомпиляции:
```bash
make rebuild
```

## Использование

Формат команды:
```bash
./dbms_cpp --file <файл> --query "<КОМАНДА> <имя> [аргументы]"
```

### Примеры команд

**Массив:**
```bash
./dbms_cpp --query "MPUSH myarray hello"    # Добавить элемент
./dbms_cpp --query "MGET myarray"           # Получить все элементы
./dbms_cpp --query "MGET myarray 0"         # Получить элемент по индексу
./dbms_cpp --query "MDEL myarray hello"     # Удалить элемент
```

**Односвязный список:**
```bash
./dbms_cpp --query "FPUSH mylist world"            # Добавить в конец
./dbms_cpp --query "FADDHEAD mylist first"         # Добавить в начало
./dbms_cpp --query "FADDAFTER mylist world test"   # Добавить после элемента
./dbms_cpp --query "FGET mylist"                   # Получить все элементы
./dbms_cpp --query "FEXISTS mylist world"          # Проверить наличие
```

**Стек:**
```bash
./dbms_cpp --query "SPUSH mystack item1"    # Положить в стек
./dbms_cpp --query "SPOP mystack"           # Извлечь из стека
```

**Очередь:**
```bash
./dbms_cpp --query "QPUSH myqueue item1"    # Добавить в очередь
./dbms_cpp --query "QPOP myqueue"           # Извлечь из очереди
```

**Дерево:**
```bash
./dbms_cpp --query "TINSERT mytree 42"      # Вставить число
./dbms_cpp --query "TGET mytree 42"         # Проверить наличие
./dbms_cpp --query "TDEL mytree 42"         # Удалить число
```

## Архитектура

```
C++/
├── include/              # Заголовочные файлы (.hpp)
│   ├── Array.hpp
│   ├── LinkedList.hpp
│   ├── DoubleLinkedList.hpp
│   ├── Stack.hpp
│   ├── Queue.hpp
│   ├── AVLTree.hpp
│   └── Database.hpp
├── src/                  # Реализация (.cpp)
│   ├── Array.cpp
│   ├── LinkedList.cpp
│   ├── DoubleLinkedList.cpp
│   ├── Stack.cpp
│   ├── Queue.cpp
│   ├── AVLTree.cpp
│   └── Database.cpp
├── main.cpp             # Точка входа
├── Makefile            # Сборка проекта
└── file.data           # Файл данных
```

## Требования

- Компилятор с поддержкой C++17 (g++ 7+ или clang++ 5+)
- make

## Преимущества C++ версии

1. **Меньше кода**: автоматическое управление памятью сокращает количество кода
2. **Безопаснее**: меньше ошибок с памятью и утечек
3. **Удобнее**: использование STL (Standard Template Library)
4. **Современнее**: использование современных практик программирования
5. **Эффективнее**: умные указатели и move-семантика уменьшают копирование
