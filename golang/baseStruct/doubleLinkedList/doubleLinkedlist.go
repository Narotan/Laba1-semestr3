// c. Двусвязный список. Операции: добавление и удаление элемента
// (4 способа (до после голова хвост)), чтение (разное, несколько
// способов), удаление элемента по значению, поиск элемента по
// значению.

package doubleLinkedlist

import "fmt"

type Node struct {
	Next *Node
	Prev *Node
	Data int
}

type DoublyLinkedList struct {
	Head *Node
	Tail *Node
}

func (list *DoublyLinkedList) AppendAtBack(Data int) {
	newNode := &Node{Data: Data}

	if list.Tail == nil {
		list.Head = newNode
		list.Tail = newNode
		return
	}

	list.Tail.Next = newNode
	newNode.Prev = list.Tail
	list.Tail = newNode
}

func (list *DoublyLinkedList) AppendAtStart(Data int) {
	newNode := &Node{Data: Data}

	if list.Head == nil {
		list.Head = newNode
		list.Tail = newNode
		return
	}

	newNode.Next = list.Head
	list.Head.Prev = newNode
	list.Head = newNode
}

func (list *DoublyLinkedList) AppendAfterValue(value, Data int) {
	current := list.Head
	for current != nil && current.Data != value {
		current = current.Next
	}

	if current == nil {
		fmt.Printf("элемент %d не найден\n", value)
		return
	}

	newNode := &Node{Data: Data}
	newNode.Next = current.Next
	newNode.Prev = current
	if current.Next != nil {
		current.Next.Prev = newNode
	} else {
		list.Tail = newNode
	}
	current.Next = newNode
}

func (list *DoublyLinkedList) AppendBeforeValue(value, Data int) {
	current := list.Head
	for current != nil && current.Data != value {
		current = current.Next
	}

	if current == nil {
		fmt.Printf("элемент %d не найден\n", value)
		return
	}

	newNode := &Node{Data: Data}
	newNode.Next = current
	newNode.Prev = current.Prev

	if current.Prev != nil {
		current.Prev.Next = newNode
	} else {
		list.Head = newNode
	}

	current.Prev = newNode
}

func (list *DoublyLinkedList) DeleteHead() {
	if list.Head == nil {
		return
	}
	list.Head = list.Head.Next
	if list.Head != nil {
		list.Head.Prev = nil
	} else {
		list.Tail = nil
	}
}

func (list *DoublyLinkedList) DeleteTail() {
	if list.Tail == nil {
		return
	}
	list.Tail = list.Tail.Prev
	if list.Tail != nil {
		list.Tail.Next = nil
	} else {
		list.Head = nil
	}
}

func (list *DoublyLinkedList) DeleteForValue(Data int) {
	current := list.Head
	for current != nil && current.Data != Data {
		current = current.Next
	}

	if current == nil {
		return
	}

	if current.Prev != nil {
		current.Prev.Next = current.Next
	} else {
		list.Head = current.Next
	}

	if current.Next != nil {
		current.Next.Prev = current.Prev
	} else {
		list.Tail = current.Prev
	}
}

func (list *DoublyLinkedList) FindElementForValue(Data int) *Node {
	current := list.Head
	for current != nil {
		if current.Data == Data {
			return current
		}
		current = current.Next
	}
	return nil
}

func (list *DoublyLinkedList) ReadForward() {
	current := list.Head
	for current != nil {
		fmt.Println(current.Data)
		current = current.Next
	}
}

func (list *DoublyLinkedList) ReadBackward() {
	current := list.Tail
	for current != nil {
		fmt.Println(current.Data)
		current = current.Prev
	}
}

func (list *DoublyLinkedList) ToSlice() []int {
	collector := []int{}
	current := list.Head
	for current != nil {
		collector = append(collector, current.Data)
		current = current.Next
	}
	return collector
}
