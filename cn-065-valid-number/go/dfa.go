package leetcode

// 参考学习
// 【编译原理】把正规式转化为DFA
// https://blog.csdn.net/C2681595858/article/details/85262797

// 不使用 DFA ，朴素校验
// https://github.com/begeekmyfriend/leetcode/blob/master/065_valid_number/valid_number.c

// Valid Number - By DFA  讲的还欠缺点
// https://powersnail.com/2016/valid-number/

// valid number 判断字符串是否为有效数字 我觉得讲的还是不够
// https://www.cnblogs.com/higerzhang/p/4086191.html

// 奇葩 他写出了一个非标准的 NFA 然后直接就得到矩阵了
// https://sosohu.github.io/leetcode/2015/05/01/LeetCode-Valid_Number.html

// 高手 用 flex 完成
// https://blog.finaltheory.me/research/Flex-Tricks.html

// 他自己的积累 让他有了轻功
// https://zhuanlan.zhihu.com/p/25879478

// 总结的好，从这里知道符合题意的正则表达式怎么写
// https://leetcode-cn.com/problems/valid-number/solution/yong-zheng-ze-biao-da-shi-jie-jue-you-xiao-shu-zi-/

// 065 https://leetcode-cn.com/problems/valid-number/

// 解题步骤
// 1 看懂题目，找到怎么写符合题意的正则表达式
// 2 根据正规式做组成单元，把正则表达式画出 NFA, 也叫 Thompson 构造法
// 3 把 NFA 转为 DFA， 画出 DFA 图之前，应该有矩阵，有了矩阵就能直接使用表驱动法解题，不需要把 DFA 图画出来
//   不需要精简 DFA，都是表驱动法，性能一致

func toMove(c byte) int {
	switch c {
	case ' ':
		return 0
	case '+', '-':
		return 1
	case '0', '1', '2', '3', '4', '5', '6', '7', '8', '9':
		return 2
	case '.':
		return 3
	case 'e', 'E':
		return 4
	default:
		return 5
	}
}

// 从 NFA 得到的 DFA 表中 转为表驱动法解决 // 未经过化简
func makeMatrix() [][]int {
	m := [][]int{
		{1, 2, 3, 4, -1, -1},     // 0
		{1, 2, 3, 4, -1, -1},     // 1
		{-1, -1, 3, 4, -1, -1},   // 2
		{5, -1, 6, 7, 8, -1},     // 3
		{-1, -1, 9, -1, -1, -1},  // 4
		{5, -1, -1, -1, -1, -1},  // 5
		{5, -1, 6, 7, 8, -1},     // 6
		{5, -1, 9, -1, 8, -1},    // 7
		{-1, 10, 11, -1, -1, -1}, // 8
		{5, -1, 9, -1, 8, -1},    // 9
		{-1, -1, 11, -1, -1, -1}, // 10
		{5, -1, 12, -1, -1, -1},  // 11
		{5, -1, 12, -1, -1, -1},  // 12
	}
	return m
}

func isNumber(s string) bool {
	state := 0
	bs := []byte(s)
	matrix := makeMatrix()

	for _, c := range bs {
		move := toMove(c)
		state = matrix[state][move]
		if state < 0 {
			return false
		}
	}

	// 根据矩阵表，得到的结束状态为
	switch state {
	case 3, 5, 6, 7, 9, 11, 12:
		return true
	default:
		return false
	}
}
