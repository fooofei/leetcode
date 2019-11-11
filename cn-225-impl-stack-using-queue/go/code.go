package leetcode

// 225 https://leetcode-cn.com/problems/implement-stack-using-queues/

type MyStack struct {
	container []int
}

func Constructor() MyStack {
	return MyStack{container: make([]int, 0)}
}
func (this *MyStack) Push(x int) {
	this.container = append(this.container, x)
}

func (this *MyStack) Pop() int {
	if len(this.container) < 1 {
		return 0
	}
	tailOff := len(this.container) - 1
	ret := this.container[tailOff]
	this.container = this.container[:tailOff]
	return ret
}

func (this *MyStack) Top() int {
	if len(this.container) < 1 {
		return 0
	}
	return this.container[len(this.container)-1]
}
func (this *MyStack) Empty() bool {
	return len(this.container) < 1
}

/**
 * Your MyStack object will be instantiated and called as such:
 * obj := Constructor();
 * obj.Push(x);
 * param_2 := obj.Pop();
 * param_3 := obj.Top();
 * param_4 := obj.Empty();
 */
