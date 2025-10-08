// b. Односвязный список. Операции: добавление и удаление элемента
// (4 способа (до после голова хвост)), чтение (разное, несколько
// способов), удаление элемента по значению, поиск элемента по
// значению.

package linkedlist

import "fmt"

type Node struct {
	Next *Node
	Data int
}

type LinkedList struct {
	Head *Node
}

func (list *LinkedList) AppendAtBack(Data int) {
	newNode := &Node{Data: Data}

	if list.Head == nil {
		list.Head = newNode
		return
	}

	current := list.Head
	for current.Next != nil {
		current = current.Next
	}

	current.Next = newNode
}

func (list *LinkedList) AppendAtStart(Data int) {
	newNode := &Node{Data: Data, Next: list.Head}
	list.Head = newNode

}

func (list *LinkedList) AppendAfterValue(value, Data int) {
	if list.Head == nil {
		fmt.Println("список пуст")
		return
	}

	current := list.Head
	for current != nil && current.Data != value {
		current = current.Next
	}

	if current == nil {
		fmt.Printf("элемент %d не найден\n", value)
		return
	}

	newNode := &Node{Data: Data, Next: current.Next}
	current.Next = newNode
}

func (list *LinkedList) AppendBeforeValue(value, Data int) {
	if list.Head == nil {
		fmt.Println("список пуст")
		return
	}

	if list.Head.Data == value {
		list.AppendAtStart(Data)
		return
	}

	prev := list.Head
	current := list.Head.Next

	for current != nil && current.Data != value {
		prev = current
		current = current.Next
	}

	if current == nil {
		fmt.Printf("элемент %d не найден\n", value)
		return
	}

	newNode := &Node{Data: Data, Next: current}
	prev.Next = newNode
}

func (list *LinkedList) DeleteTail() {
	if list.Head == nil {
		fmt.Println("нечего удалять")
		return
	}

	if list.Head.Next == nil {
		list.Head = nil
		return
	}

	current := list.Head
	for current.Next.Next != nil {
		current = current.Next
	}

	current.Next = nil
}

func (list *LinkedList) DeleteHead() {
	if list.Head == nil {
		fmt.Println("нечего удалять")
		return
	}
	list.Head = list.Head.Next
}

func (list *LinkedList) DeleteAfterValue(Data int) {
	if list.Head == nil {
		fmt.Println("нечего удалять")
		return
	}

	current := list.Head
	for current.Data != Data {
		if current.Next == nil {
			return
		}
		current = current.Next
	}

	if current.Next == nil {
		fmt.Println("нечего удалять")
		return
	}
	current.Next = current.Next.Next
}

func (list *LinkedList) DeleteBeforeValue(Data int) {
	if list.Head == nil || list.Head.Next == nil {
		return
	}

	var previous *Node
	current := list.Head

	for current.Next != nil {
		if current.Next.Data == Data {
			if previous == nil {
				list.Head = current.Next
			} else {
				previous.Next = current.Next
			}
			return
		}
		previous = current
		current = current.Next
	}
}

func (list *LinkedList) DeleteForValue(Data int) {
	if list.Head == nil {
		return
	}

	if list.Head.Data == Data {
		list.Head = list.Head.Next
		return
	}

	current := list.Head
	for current.Next != nil {
		if current.Next.Data == Data {
			current.Next = current.Next.Next
			return
		}
		current = current.Next
	}
}

func (list *LinkedList) FindElementForValue(Data int) *Node {
	current := list.Head

	for current != nil {
		if current.Data == Data {
			return current
		}
		current = current.Next
	}

	return nil
}

func (list *LinkedList) ReadLinkedListCycle() {
	current := list.Head
	for current != nil {
		fmt.Println(current.Data)
		current = current.Next
	}
}

func (list *LinkedList) ReadLinkedListForSlice() []int {
	collector := []int{}
	current := list.Head
	for current != nil {
		collector = append(collector, current.Data)
		current = current.Next
	}
	return collector
}
