# 🗄️ Data Structures Database

**Универсальная база данных для изучения и демонстрации структур данных** - реализация на C++ и Go с командным интерфейсом.

## 📖 Использование

### Основные команды

#### Массивы (Array)
```bash
# Добавить элементы
./dbms --query "MPUSH myarr hello world"

# Вставить по индексу
./dbms --query "MINSERT myarr 1 middle"

# Получить все элементы
./dbms --query "MGET myarr"
# Вывод: [hello middle world]

# Удалить по индексу
./dbms --query "MDELINDEX myarr 1"
```

#### Списки (Linked List)
```bash
# Добавить в конец
./dbms --query "FPUSH list A B C"

# Добавить в начало
./dbms --query "FADDHEAD list Z"

# Вставить после элемента
./dbms --query "FADDAFTER list A X"

# Получить список
./dbms --query "FGET list"
# Вывод: [Z A X B C]
```

#### Стек (Stack - LIFO)
```bash
# Добавить элементы
./dbms --query "SPUSH stack 1 2 3"

# Извлечь элементы (LIFO)
./dbms --query "SPOP stack"  # → 3
./dbms --query "SPOP stack"  # → 2
./dbms --query "SPOP stack"  # → 1
```

#### Очередь (Queue - FIFO)
```bash
# Добавить элементы
./dbms --query "QPUSH queue A B C"

# Извлечь элементы (FIFO)
./dbms --query "QPOP queue"  # → A
./dbms --query "QPOP queue"  # → B
./dbms --query "QPOP queue"  # → C
```

#### AVL-дерево
```bash
# Вставить ключи
./dbms --query "TINSERT tree 50 25 75 10 30"

# Проверить существование
./dbms --query "TGET tree 25"  # → TRUE

# Удалить ключ
./dbms --query "TDEL tree 50"
```


## 📁 Структура проекта

```
.
├── C++/                    # C++ реализация
│   ├── include/           # Заголовочные файлы
│   ├── src/              # Исходный код
│   ├── main.cpp          # Точка входа
│   ├── Makefile          # Скрипт сборки
│   └── commands.txt      # Документация команд
├── golang/               # Go реализация
│   ├── cmd/             # Точка входа
│   ├── baseStruct/      # Структуры данных
│   ├── go.mod           # Модули Go
│   └── commands.txt     # Документация команд
└── README.md            # Этот файл
```
