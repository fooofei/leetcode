package leetcode

// 232 https://leetcode-cn.com/problems/implement-queue-using-stacks/

type MyQueue struct {
	container []int
}

/** Initialize your data structure here. */
func Constructor() MyQueue {
	return MyQueue{container: make([]int, 0)}
}

/** Push element x to the back of queue. */
func (this *MyQueue) Push(x int) {
	this.container = append(this.container, x)
}

/** Removes the element from in front of queue and returns that element. */
func (this *MyQueue) Pop() int {
	if len(this.container) < 1 {
		return 0
	}
	ret := this.container[0]
	this.container = this.container[1:]
	return ret
}

/** Get the front element. */
func (this *MyQueue) Peek() int {
	if len(this.container) < 1 {
		return 0
	}
	return this.container[0]
}

/** Returns whether the queue is empty. */
func (this *MyQueue) Empty() bool {
	return len(this.container) < 1
}

/**
 * Your MyQueue object will be instantiated and called as such:
 * obj := Constructor();
 * obj.Push(x);
 * param_2 := obj.Pop();
 * param_3 := obj.Peek();
 * param_4 := obj.Empty();
 */
