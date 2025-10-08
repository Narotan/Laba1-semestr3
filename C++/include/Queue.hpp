#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "DoubleLinkedList.hpp"
#include <memory>
#include <optional>

using namespace std;

// Очередь - FIFO (First In First Out - первым вошёл, первым вышел)
// Реализована через двусвязный список для эффективного добавления в конец и удаления из начала
struct Queue {
    unique_ptr<DoubleLinkedList> list;
};

unique_ptr<Queue> queue_create();
void queue_enqueue(Queue* queue, const string& data);
optional<string> queue_dequeue(Queue* queue);
bool queue_is_empty(const Queue* queue);

#endif // QUEUE_HPP
