// main.go
package main

import (
	convertstruct "BaseStruct/convertStruct"
	"encoding/json"
	"flag"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type DBFile struct {
	Arrays  map[string][]int `json:"arrays"`
	Lists   map[string][]int `json:"lists"`
	DlLists map[string][]int `json:"dllists"`
	Stacks  map[string][]int `json:"stacks"`
	Queues  map[string][]int `json:"queues"`
	Trees   map[string][]int `json:"trees"`
}

func NewEmptyDB() *DBFile {
	return &DBFile{
		Arrays:  map[string][]int{},
		Lists:   map[string][]int{},
		DlLists: map[string][]int{},
		Stacks:  map[string][]int{},
		Queues:  map[string][]int{},
		Trees:   map[string][]int{},
	}
}

func loadDB(path string) (*DBFile, error) {
	data, err := os.ReadFile(path)
	if err != nil {
		if os.IsNotExist(err) {
			return NewEmptyDB(), nil
		}
		return nil, err
	}
	var db DBFile
	if err := json.Unmarshal(data, &db); err != nil {
		return nil, err
	}
	if db.Arrays == nil {
		db.Arrays = map[string][]int{}
	}
	if db.Lists == nil {
		db.Lists = map[string][]int{}
	}
	if db.DlLists == nil {
		db.DlLists = map[string][]int{}
	}
	if db.Stacks == nil {
		db.Stacks = map[string][]int{}
	}
	if db.Queues == nil {
		db.Queues = map[string][]int{}
	}
	if db.Trees == nil {
		db.Trees = map[string][]int{}
	}
	return &db, nil
}

func saveDB(path string, db *DBFile) error {
	b, err := json.MarshalIndent(db, "", "  ")
	if err != nil {
		return err
	}
	return os.WriteFile(path, b, 0644)
}

func parseInt(s string) (int, error) {
	return strconv.Atoi(s)
}

func sliceToString(s []int) string {
	if s == nil {
		return "[]"
	}
	parts := make([]string, 0, len(s))
	for _, v := range s {
		parts = append(parts, strconv.Itoa(v))
	}
	return "[" + strings.Join(parts, " ") + "]"
}

func removeFirstByValue(s []int, val int) ([]int, bool) {
	for i := 0; i < len(s); i++ {
		if s[i] == val {
			return append(s[:i], s[i+1:]...), true
		}
	}
	return s, false
}

func contains(s []int, val int) bool {
	for _, v := range s {
		if v == val {
			return true
		}
	}
	return false
}

func treeInsert(s []int, v int) ([]int, bool) {
	if contains(s, v) {
		return s, false
	}
	return append(s, v), true
}

func treeDelete(s []int, v int) ([]int, bool) {
	return removeFirstByValue(s, v)
}

func main() {
	filePath := flag.String("file", "file.data", "path to data file")
	query := flag.String("query", "", "query string, e.g. 'SPUSH mystack 10'")
	flag.Parse()

	if *query == "" {
		fmt.Println("no query provided")
		return
	}

	db, err := loadDB(*filePath)
	if err != nil {
		fmt.Println("Error loading file:", err)
		return
	}

	// parse query
	// split by spaces but preserve quoted tokens (simple approach)
	parts := strings.Fields(*query)
	if len(parts) < 1 {
		fmt.Println("invalid query")
		return
	}

	verb := parts[0]
	name := ""
	args := []string{}
	if len(parts) >= 2 {
		name = parts[1]
	}
	if len(parts) > 2 {
		args = parts[2:]
	}

	verb = strings.ToUpper(verb)

	// dispatch based on verb prefix (letter)
	var changed bool
	var output string

	switch {
	// M - массив
	case strings.HasPrefix(verb, "M"):
		switch verb {
		case "MPUSH":
			if name == "" || len(args) < 1 {
				fmt.Println("ERROR: MPUSH requires name and value")
				return
			}
			v, err := parseInt(args[0])
			if err != nil {
				fmt.Println("ERROR: value must be integer")
				return
			}
			db.Arrays[name] = append(db.Arrays[name], v)
			changed = true
			output = strconv.Itoa(v)
		case "MDEL":
			if name == "" || len(args) < 1 {
				fmt.Println("ERROR: MDEL requires name and value")
				return
			}
			v, err := parseInt(args[0])
			if err != nil {
				fmt.Println("ERROR: value must be integer")
				return
			}
			newSlice, ok := removeFirstByValue(db.Arrays[name], v)
			if ok {
				db.Arrays[name] = newSlice
				changed = true
				output = strconv.Itoa(v)
			} else {
				output = "NOTFOUND"
			}
		case "MGET":
			if name == "" {
				fmt.Println("ERROR: MGET requires name")
				return
			}
			if len(args) >= 1 {
				// treat arg as index
				idx, err := parseInt(args[0])
				if err != nil {
					fmt.Println("ERROR: index must be integer")
					return
				}
				if idx < 0 || idx >= len(db.Arrays[name]) {
					output = "NULL"
				} else {
					output = strconv.Itoa(db.Arrays[name][idx])
				}
			} else {
				output = sliceToString(db.Arrays[name])
			}
		default:
			fmt.Println("Unknown M command:", verb)
			return
		}

	// F - односвязный список
	case strings.HasPrefix(verb, "F"):
		if name == "" {
			fmt.Println("ERROR: F command requires container name")
			return
		}

		ll := convertstruct.LinkedListFromSlice(db.Lists[name])

		switch verb {
		case "FPUSH":
			v, err := parseInt(args[0])
			if err != nil {
				fmt.Println("ERROR: value must be integer")
				return
			}
			ll.AppendAtBack(v)
			db.Lists[name] = convertstruct.SliceFromLinkedList(ll)
			changed = true
			output = strconv.Itoa(v)

		case "FADDHEAD":
			v, _ := parseInt(args[0])
			ll.AppendAtStart(v)
			db.Lists[name] = convertstruct.SliceFromLinkedList(ll)
			changed = true
			output = strconv.Itoa(v)

		case "FADDAFTER":
			target, _ := parseInt(args[0])
			v, _ := parseInt(args[1])
			ll.AppendAfterValue(target, v)
			db.Lists[name] = convertstruct.SliceFromLinkedList(ll)
			changed = true
			output = strconv.Itoa(v)

		case "FADDBEFORE":
			target, _ := parseInt(args[0])
			v, _ := parseInt(args[1])
			ll.AppendBeforeValue(target, v)
			db.Lists[name] = convertstruct.SliceFromLinkedList(ll)
			changed = true
			output = strconv.Itoa(v)

		case "FDEL":
			v, _ := parseInt(args[0])
			ll.DeleteForValue(v)
			db.Lists[name] = convertstruct.SliceFromLinkedList(ll)
			changed = true
			output = strconv.Itoa(v)

		case "FDELHEAD":
			ll.DeleteHead()
			db.Lists[name] = convertstruct.SliceFromLinkedList(ll)
			changed = true
			output = "OK"

		case "FDELTAIL":
			ll.DeleteTail()
			db.Lists[name] = convertstruct.SliceFromLinkedList(ll)
			changed = true
			output = "OK"

		case "FGET":
			if len(args) >= 1 {
				idx, _ := parseInt(args[0])
				slice := convertstruct.SliceFromLinkedList(ll)
				if idx < 0 || idx >= len(slice) {
					output = "NULL"
				} else {
					output = strconv.Itoa(slice[idx])
				}
			} else {
				output = sliceToString(convertstruct.SliceFromLinkedList(ll))
			}

		case "FEXISTS":
			v, _ := parseInt(args[0])
			node := ll.FindElementForValue(v)
			if node != nil {
				output = "TRUE"
			} else {
				output = "FALSE"
			}

		default:
			fmt.Println("Unknown F command:", verb)
			return
		}

		// L - двусвязный список (dllists)
	case strings.HasPrefix(verb, "L"):
		if name == "" {
			fmt.Println("ERROR: L command requires container name")
			return
		}

		// Получаем DLL из среза, если контейнера нет — создаём новый
		listl := convertstruct.DllFromSlice(db.DlLists[name])

		switch verb {
		case "LPUSH": // добавить в конец
			if len(args) < 1 {
				fmt.Println("ERROR: LPUSH requires value")
				return
			}
			v, _ := parseInt(args[0])
			listl.AppendAtBack(v)
			changed = true
			output = strconv.Itoa(v)

		case "LUNSHIFT": // добавить в начало
			if len(args) < 1 {
				fmt.Println("ERROR: LUNSHIFT requires value")
				return
			}
			v, _ := parseInt(args[0])
			listl.AppendAtStart(v)
			changed = true
			output = strconv.Itoa(v)

		case "LAFTER": // добавить после значения
			if len(args) < 2 {
				fmt.Println("ERROR: LAFTER requires target value and new value")
				return
			}
			target, _ := parseInt(args[0])
			v, _ := parseInt(args[1])
			listl.AppendAfterValue(target, v)
			changed = true
			output = strconv.Itoa(v)

		case "LBEFORE": // добавить перед значением
			if len(args) < 2 {
				fmt.Println("ERROR: LBEFORE requires target value and new value")
				return
			}
			target, _ := parseInt(args[0])
			v, _ := parseInt(args[1])
			listl.AppendBeforeValue(target, v)
			changed = true
			output = strconv.Itoa(v)

		case "LDEL": // удалить по значению
			if len(args) < 1 {
				fmt.Println("ERROR: LDEL requires value")
				return
			}
			v, _ := parseInt(args[0])
			listl.DeleteForValue(v)
			changed = true
			output = strconv.Itoa(v)

		case "LDELHEAD": // удалить голову
			listl.DeleteHead()
			changed = true
			output = "OK"

		case "LDELTAIL": // удалить хвост
			listl.DeleteTail()
			changed = true
			output = "OK"

		case "LGET": // вывести весь список
			output = sliceToString(convertstruct.SliceFromDLL(listl))

		case "LEXISTS": // проверить наличие элемента
			if len(args) < 1 {
				fmt.Println("ERROR: LEXISTS requires value")
				return
			}
			v, _ := parseInt(args[0])
			node := listl.FindElementForValue(v)
			if node != nil {
				output = "TRUE"
			} else {
				output = "FALSE"
			}

		default:
			fmt.Println("Unknown L command:", verb)
			return
		}

		// Сохраняем обратно в базу
		db.DlLists[name] = convertstruct.SliceFromDLL(listl)

	// Q - очередь
	case strings.HasPrefix(verb, "Q"):
		switch verb {
		case "QPUSH":
			if name == "" || len(args) < 1 {
				fmt.Println("ERROR: QPUSH requires name and value")
				return
			}
			v, err := parseInt(args[0])
			if err != nil {
				fmt.Println("ERROR: value must be integer")
				return
			}
			db.Queues[name] = append(db.Queues[name], v)
			changed = true
			output = strconv.Itoa(v)
		case "QPOP":
			if name == "" {
				fmt.Println("ERROR: QPOP requires name")
				return
			}
			if len(db.Queues[name]) == 0 {
				output = "NULL"
			} else {
				val := db.Queues[name][0]
				db.Queues[name] = db.Queues[name][1:]
				changed = true
				output = strconv.Itoa(val)
			}
		default:
			fmt.Println("Unknown Q command:", verb)
			return
		}

	// S - стек
	case strings.HasPrefix(verb, "S"):
		switch verb {
		case "SPUSH":
			if name == "" || len(args) < 1 {
				fmt.Println("ERROR: SPUSH requires name and value")
				return
			}
			v, err := parseInt(args[0])
			if err != nil {
				fmt.Println("ERROR: value must be integer")
				return
			}
			db.Stacks[name] = append(db.Stacks[name], v)
			changed = true
			output = strconv.Itoa(v)
		case "SPOP":
			if name == "" {
				fmt.Println("ERROR: SPOP requires name")
				return
			}
			if len(db.Stacks[name]) == 0 {
				output = "NULL"
			} else {
				last := len(db.Stacks[name]) - 1
				val := db.Stacks[name][last]
				db.Stacks[name] = db.Stacks[name][:last]
				changed = true
				output = strconv.Itoa(val)
			}
		default:
			fmt.Println("Unknown S command:", verb)
			return
		}

	// T - дерево (set-like)
	case strings.HasPrefix(verb, "T"):
		switch verb {
		case "TINSERT":
			if name == "" || len(args) < 1 {
				fmt.Println("ERROR: TINSERT requires name and value")
				return
			}
			v, err := parseInt(args[0])
			if err != nil {
				fmt.Println("ERROR: value must be integer")
				return
			}
			newSlice, added := treeInsert(db.Trees[name], v)
			if added {
				db.Trees[name] = newSlice
				changed = true
			}
			if added {
				output = strconv.Itoa(v)
			} else {
				output = "ALREADY"
			}
		case "TDEL":
			if name == "" || len(args) < 1 {
				fmt.Println("ERROR: TDEL requires name and value")
				return
			}
			v, err := parseInt(args[0])
			if err != nil {
				fmt.Println("ERROR: value must be integer")
				return
			}
			newSlice, ok := treeDelete(db.Trees[name], v)
			if ok {
				db.Trees[name] = newSlice
				changed = true
				output = strconv.Itoa(v)
			} else {
				output = "NOTFOUND"
			}
		case "TGET":
			// TGET name value -> TRUE/FALSE (membership)
			if name == "" || len(args) < 1 {
				fmt.Println("ERROR: TGET requires name and value")
				return
			}
			v, err := parseInt(args[0])
			if err != nil {
				fmt.Println("ERROR: value must be integer")
				return
			}
			if contains(db.Trees[name], v) {
				output = "TRUE"
			} else {
				output = "FALSE"
			}
		default:
			fmt.Println("Unknown T command:", verb)
			return
		}

	default:
		fmt.Println("Unknown command prefix:", verb)
		return
	}

	fmt.Println("->", output)

	if changed {
		if err := saveDB(*filePath, db); err != nil {
			fmt.Println("Error saving file:", err)
		}
	}
}
