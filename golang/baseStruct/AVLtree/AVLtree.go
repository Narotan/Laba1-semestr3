package avltree

import "fmt"

type Node struct {
	Key    int
	Height uint8
	Left   *Node
	Right  *Node
}

func NewNode(key int) *Node {
	return &Node{
		Key:    key,
		Height: 1,
	}
}

// HeightVal возвращает высоту узла (0, если узел nil)
func (n *Node) HeightVal() uint8 {
	if n == nil {
		return 0
	}
	return n.Height
}

// BalanceFactor возвращает баланс-фактор узла
func (n *Node) BalanceFactor() int {
	if n == nil {
		return 0
	}
	return int(n.Left.HeightVal()) - int(n.Right.HeightVal())
}

// FixHeight пересчитывает высоту узла
func (n *Node) FixHeight() {
	if n == nil {
		return
	}
	hl := n.Left.HeightVal()
	hr := n.Right.HeightVal()
	if hl > hr {
		n.Height = hl + 1
	} else {
		n.Height = hr + 1
	}
}

// RotateRight выполняет правый поворот
func (p *Node) RotateRight() *Node {
	if p == nil || p.Left == nil {
		return p
	}

	q := p.Left
	p.Left = q.Right
	q.Right = p

	p.FixHeight()
	q.FixHeight()

	return q
}

// RotateLeft выполняет левый поворот
func (q *Node) RotateLeft() *Node {
	if q == nil || q.Right == nil {
		return q
	}

	p := q.Right
	q.Right = p.Left
	p.Left = q

	q.FixHeight()
	p.FixHeight()

	return p
}

// Balance балансирует узел
func (p *Node) Balance() *Node {
	if p == nil {
		return nil
	}

	p.FixHeight()

	// Правый дисбаланс
	if p.BalanceFactor() == 2 {
		if p.Right != nil && p.Right.BalanceFactor() < 0 {
			p.Right = p.Right.RotateRight()
		}
		return p.RotateLeft()
	}

	// Левый дисбаланс
	if p.BalanceFactor() == -2 {
		if p.Left != nil && p.Left.BalanceFactor() > 0 {
			p.Left = p.Left.RotateLeft()
		}
		return p.RotateRight()
	}

	return p
}

// Insert добавляет ключ в дерево
func (p *Node) Insert(key int) *Node {
	if p == nil {
		return NewNode(key)
	}

	if key < p.Key {
		p.Left = p.Left.Insert(key)
	} else if key > p.Key {
		p.Right = p.Right.Insert(key)
	} else {
		return p
	}

	return p.Balance()
}

// Search ищет ключ в дереве
func (n *Node) Search(key int) bool {
	if n == nil {
		return false
	}

	if key == n.Key {
		return true
	} else if key < n.Key {
		return n.Left.Search(key)
	} else {
		return n.Right.Search(key)
	}
}

// findMin ищет узел с минимальным ключом
func (n *Node) findMin() *Node {
	if n.Left == nil {
		return n
	}
	return n.Left.findMin()
}

// removeMin удаляет узел с минимальным ключом
func (n *Node) removeMin() *Node {
	if n.Left == nil {
		return n.Right
	}
	n.Left = n.Left.removeMin()
	n.FixHeight()
	return n.Balance()
}

// Delete удаляет ключ из дерева
func (n *Node) Delete(key int) *Node {
	if n == nil {
		return nil
	}

	if key < n.Key {
		n.Left = n.Left.Delete(key)
	} else if key > n.Key {
		n.Right = n.Right.Delete(key)
	} else {
		left := n.Left
		right := n.Right
		if right == nil {
			return left
		}
		min := right.findMin()
		n.Key = min.Key
		n.Right = n.Right.removeMin()
	}

	n.FixHeight()
	return n.Balance()
}

// InOrder печатает дерево в порядке возрастания
func (n *Node) InOrder() {
	if n == nil {
		return
	}
	n.Left.InOrder()
	fmt.Print(n.Key, " ")
	n.Right.InOrder()
}
