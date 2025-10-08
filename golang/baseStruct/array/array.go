package array

type Array struct {
	values []int
}

func NewArray() *Array {
	return &Array{values: []int{}}
}

func (a *Array) Append(value int) {
	a.values = append(a.values, value)
}

func (a *Array) Insert(index int, value int) {
	if index < 0 || index > len(a.values) {
		return
	}
	a.values = append(a.values[:index], append([]int{value}, a.values[index:]...)...)
}

func (a *Array) Get(index int) (int, bool) {
	if index < 0 || index >= len(a.values) {
		return 0, false
	}
	return a.values[index], true
}

func (a *Array) Remove(index int) {
	if index < 0 || index >= len(a.values) {
		return
	}
	a.values = append(a.values[:index], a.values[index+1:]...)
}

func (a *Array) Set(index int, value int) {
	if index < 0 || index >= len(a.values) {
		return
	}
	a.values[index] = value
}

func (a *Array) Length() int {
	return len(a.values)
}

func (a *Array) Read() []int {
	out := make([]int, len(a.values))
	copy(out, a.values)
	return out
}
