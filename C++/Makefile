# Makefile для C++ версии проекта

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I.
TARGET = dbms
SRC_DIR = src
INCLUDE_DIR = include

# Исходные файлы
SOURCES = main.cpp \
          $(SRC_DIR)/Array.cpp \
          $(SRC_DIR)/LinkedList.cpp \
          $(SRC_DIR)/DoubleLinkedList.cpp \
          $(SRC_DIR)/Stack.cpp \
          $(SRC_DIR)/Queue.cpp \
          $(SRC_DIR)/AVLTree.cpp \
          $(SRC_DIR)/Database.cpp

# Объектные файлы
OBJECTS = $(SOURCES:.cpp=.o)

# Заголовочные файлы
HEADERS = $(INCLUDE_DIR)/Array.hpp \
          $(INCLUDE_DIR)/LinkedList.hpp \
          $(INCLUDE_DIR)/DoubleLinkedList.hpp \
          $(INCLUDE_DIR)/Stack.hpp \
          $(INCLUDE_DIR)/Queue.hpp \
          $(INCLUDE_DIR)/AVLTree.hpp \
          $(INCLUDE_DIR)/Database.hpp

# Основная цель
all: $(TARGET)

# Компиляция исполняемого файла
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Компиляция объектных файлов
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(OBJECTS) $(TARGET)

# Перекомпиляция
rebuild: clean all

.PHONY: all clean rebuild
