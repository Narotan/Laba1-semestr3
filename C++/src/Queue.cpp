#include "../include/Queue.hpp"
using namespace std;

unique_ptr<Queue> queue_create() {
    auto queue = make_unique<Queue>();
    queue->list = dll_create();
    return queue;
}

void queue_enqueue(Queue* queue, const string& data) {
    dll_append_back(queue->list.get(), data);
}

optional<string> queue_dequeue(Queue* queue) {
    // Проверяем, не пуста ли очередь
    if (dll_empty(queue->list.get())) {
        return nullopt; // Возвращаем пустое значение
    }
    
    // Берём элемент из головы списка (FIFO - первый вошёл, первый вышел)
    DNode* node = dll_begin(queue->list.get());
    string result = node->data;
    dll_delete_head(queue->list.get()); // Удаляем из головы
    return result;
}

bool queue_is_empty(const Queue* queue) {
    return dll_empty(queue->list.get());
}
