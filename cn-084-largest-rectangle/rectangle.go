package leetcode

import (
	"encoding/json"
	"fmt"
)

type indexVal struct {
	value int
	index int
}

func (w *indexVal) String() string {
	out, _ := json.Marshal(w)
	return string(out)
}

func (w *indexVal) GoString() string {
	return fmt.Sprintf("withIndex %p %v", w, w.String())
}
