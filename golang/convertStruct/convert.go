package convertstruct

import (
	doubleLinkedlist "BaseStruct/baseStruct/doubleLinkedList"
	linkedlist "BaseStruct/baseStruct/linkedList"
)

// Конвертация среза в LinkedList
func LinkedListFromSlice(slice []int) *linkedlist.LinkedList {
	ll := &linkedlist.LinkedList{}
	for _, v := range slice {
		ll.AppendAtBack(v)
	}
	return ll
}

// Конвертация LinkedList обратно в срез
func SliceFromLinkedList(ll *linkedlist.LinkedList) []int {
	return ll.ReadLinkedListForSlice()
}

// Конвертация среза в двусвязный список
func DllFromSlice(slice []int) *doubleLinkedlist.DoublyLinkedList {
	dll := &doubleLinkedlist.DoublyLinkedList{}
	for _, v := range slice {
		dll.AppendAtBack(v)
	}
	return dll
}

// Конвертация DLL обратно в срез
func SliceFromDLL(dll *doubleLinkedlist.DoublyLinkedList) []int {
	return dll.ToSlice()
}
