// e. Очередь. Операции: добавление и удаление элемента (push и
// pop), чтение.

package queue

import doubleLinkedlist "BaseStruct/baseStruct/doubleLinkedList"

type Queue struct {
	list *doubleLinkedlist.DoublyLinkedList
}

func NewQueue() *Queue {
	return &Queue{list: &doubleLinkedlist.DoublyLinkedList{}}
}

func (q *Queue) Enqueue(data int) {
	q.list.AppendAtBack(data)
}

func (q *Queue) Dequeue() (int, bool) {
	if q.list.Head == nil {
		return 0, false
	}
	data := q.list.Head.Data
	q.list.DeleteHead()
	return data, true
}

func (q *Queue) Peek() (int, bool) {
	if q.list.Head == nil {
		return 0, false
	}
	return q.list.Head.Data, true
}

func (q *Queue) IsEmpty() bool {
	return q.list.Head == nil
}

func (q *Queue) ToSlice() []int {
	return q.list.ToSlice()
}
