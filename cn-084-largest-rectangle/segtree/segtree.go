package segtree

type node struct {
	startIndex int
	endIndex   int // [start, end) not include end
	valueIndex int // 如果这里放索引，好处是不需要知道目标集合是什么数值类型，
	// 就跟 sort.Stable() 学习了，但是坏处 是 SegmentTree 无法应用于 积 这样的运算
	parent *node
	left   *node
	right  *node
}

type SegmentTree struct {
	root *node
}

type Interface interface {
	// 对索引 left right 做运算， 返回索引
	// 因为都是使用的索引，因此只能返回其中 1 个
	Oper(left int, right int) int
	Len() int
}

func makeNode(start int, end int, values Interface, parent *node) *node {

	n := &node{
		startIndex: start,
		endIndex:   end,
		valueIndex: -1,
		parent:     parent,
		left:       nil,
		right:      nil,
	}

	if start == end-1 {
		n.valueIndex = start
		return n
	}

	mid := (start + end) / 2
	n.left = makeNode(start, mid, values, n)
	n.right = makeNode(mid, end, values, n)
	n.valueIndex = values.Oper(n.left.valueIndex, n.right.valueIndex)
	return n
}

func New(values Interface) *SegmentTree {

	if values.Len() <= 0 {
		return nil
	}
	st := &SegmentTree{
		root: nil,
	}

	st.root = makeNode(0, values.Len(), values, nil)
	return st
}

func searchNode(n *node, start int, end int, values Interface) int {
	if n.startIndex == start && n.endIndex == end {
		return n.valueIndex
	}
	// 加速
	if start == end-1 {
		return start
	}

	mid := (n.startIndex + n.endIndex) / 2
	if end <= mid {
		// 错误用法 searchNode(n.left, start, mid, values)
		return searchNode(n.left, start, end, values)
	}
	// start > mid
	if start >= mid {
		return searchNode(n.right, start, end, values)
	}
	leftIndex := searchNode(n.left, start, mid, values)
	rightIndex := searchNode(n.right, mid, end, values)
	return values.Oper(leftIndex, rightIndex)
}

// Search a value in [start, end]
func (st *SegmentTree) Search(start int, end int, values Interface) int {
	return searchNode(st.root, start, end, values)
}
