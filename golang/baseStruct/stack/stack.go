// d. Стек. Операции: добавление и удаление элемента (push и pop),
// чтение.
package stack

import "fmt"

type Stack struct {
	values []int
}

func (s *Stack) Push(value int) {
	s.values = append(s.values, value)
}

func (s *Stack) Pop() (int, bool) {
	if len(s.values) == 0 {
		return 0, false
	}

	lastIndex := len(s.values) - 1
	value := s.values[lastIndex]

	s.values = s.values[:lastIndex]
	return value, true
}

func (s *Stack) isEmpty() bool {

	if len(s.values) == 0 {
		fmt.Println("stack isempty")
		return true
	} else {
		return false
	}
}

func (s *Stack) CheckAllElement() {
	fmt.Println(s.values)
}
