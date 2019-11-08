# leetcode

**001 两数之和**

    带索引的排序 然后 first last 双指针向中间靠拢
    也有人用 map 解决， map 存放 target - num[i] 当前数字的差

**003 最长没有重复字符的子串**

    我想复杂了，我使用到了 map + stack ，stack 可以使用一个 int 来表示距离就可以了
    应该是，一旦在 map 发现有重复字符就更新 lastRepeatPos，每循环都计算 i-lastRepeatPos 更新最大距离

**字符串：回文**
```
005 最长回文子串
    易想到 递归回溯 每深度有点像杨辉三角那种，要在设计时就剔除冗余情景，降低时间复杂度,
    不行的，每判断一个子串是否回文，都是子串全遍历，时间复杂度还是不满足要求，这个题目有优待，测试用例限制了s的长度
    难想到 马拉车算法
    难想到 hash 算法 hash 回退字符的时候不要使用除法要使用减法
125 是否是有效的回文串
214 在前面加字符，变成回文串
    递归
    马拉车
    哈希 这个哈希算法是最简洁的 比 005 的还简洁
409 最长回文串长度
    最简单 把能变成偶数的字符都个数都加上，最后加一次奇数的用来做中心轴就就行了
```

**011 容器最多盛水**

    双指针 理解为什么是移动较小高度的指针，因为移动了较大高度的必然导致面积比现在小，
    那就没计算的必要了

**014 最长公共前缀**

    我一上来就觉得应该以 str[0] 为 pattern，依次按照`列`遍历 [1,n) 后来发现我这是最简洁的写法
    有的办法还是先假设一个公共前缀，每次变换前缀去剩下字符串里匹配 `startsWith`，这种办法难看

**026 删除重复值**

**027 删除目标值**

    两道题一起看待，带有类库的语言 C++ Java 比较规矩，只要考虑如何使用容器 in-placed 删除多余元素即可
    对于 C 语言，可以使用的技巧是使用类似栈的技巧，原地用栈，不等于栈顶/目标值，则入栈，没有出栈这个操作

**028 strstr**

    KMP 过于复杂，写不出来，记住 sunday 算法。

**155 最小值栈**

    在 O(1) 时间下获得某个栈中的最小值，数据栈 +　辅助栈，技巧是在辅助栈中占坑
    栈是 8 4 9 3 辅助栈是 8 4 4 3 

**160 两个交叉链表在哪交叉**

    我想到的方法是分别遍历两个链表，存放到两个容器里，然后倒序找第一个指针值不同的结点
    更有技巧的办法是 a->b b->a ，遍历 a 链表的，遍历结束后，切换到 b 链表，
    同理 b a 的也是，当两个指针一样的时候，就是链表交叉点

**316 在保持位置情况下去除重复找子串**

    灵光点是要想到 栈 + for(currentChar < stack.top() && count[stack.top] > 0)
    当前字符比栈顶的更字典序靠前并且栈顶字符以后还出现，就出栈

**数字序列找关系**
```
xxx 最大公约数
    辗转相除法
xxx 最小公倍数
    a * b / 最大公约数
001 两数之和 
    寻找 2 个数的和为某一值
004 两个有序数组的中位数
    我直接合并两个数组，索引为 n/2 或者 (nums[n/2-1] + nums[n/2]) /2 求得
    二分法要在两个数组中周旋，还有虚拟位置的技巧，比较复杂
015 三数之和 
    先排序 然后确定 1 个数，其他 2 个数就转化为了两数之和问题
    不重复的所有解比起找到解就可以难度更大 
    需要考虑到 x+y+z 当找到解时 x 没变，如果 y 不变，那么 z 也不变，这样的下一个解是重复的
    z 不变， y 也不变，因此必须 y z 都要变，y z 要前进到不同值才停下
    另外的想法在动态语言中好处理，用一个 set 或者 dict 或者 map ，key 取 "{x}_{y}_{z}" 
    用来去除重复，这样思路直接，写代码迅速
016 最接近的三数之和
    警惕不要误入歧途，序列排序后，如果第一个数字 > target ，最接近的和不是 `array[0]+array[1]+array[2]`
    反例  -9 -8 1 2, target = -10 , 不是 -9-8+1=-16 -9+1+2=-6
    如果最后一个数字 < target，最接近的和不是 `array[-3]+array[-2]+array[-1]`
    存在1个优化条件是可以使用的，就是如果找到 sum==target 的时候，就可以 return 了，到此为止，
    除此之外是一直需要遍历下去，优化措施，还是跳跃过重复。

069 实现sqrt 不要小数位
    二分查找有奇效
122 买卖股票的最佳时机 II
124 二叉树中的最大（任意点之间）路径和
167 两数之和 II - 输入有序数组
169 求众数
    易想到 排序（难想到排序后 n/2 或者 n/2+1 就是要找的值）
    难想到 摩尔投票算法
    题目关联 加强版水王：有N个数，其中有一个数刚好出现一半次数，要求在线性时间内求出这个数。
    与摩尔投票算法相同， candidate 保存当前值 times 保存次数
    到最后所求一定在 candidate 和 a[n-1] 之间，是哪个不知道，如果选择某一个，再遍历一次，
    统计次数，如果是一半就是它，不是一半就是另一个数，
    或者直接在前面的循环中，计算一下 a[n-1] 的出现次数，不用遍历两次
172 阶乘后的零
    数乘数中 5 的个数
```

**单调栈**
```
单调递增栈可以找到左起第一个比当前数字小的元素。
单调递减栈可以找到左起第一个比当前数字大的元素。
```
```
企图在序列前(后)增加其他值，来减少判断，减少循环结束后的处理，
有些是成功的，有些是失败的

042 接雨水
    操作：入栈、清空栈、遍历栈抹平栈
    for(value in ) {
        // 右边是墙
        if (valueStack.size() > 0 && height[i] >= valueStack.back()) {
            // 左边墙同时有洼地就可以蓄水了
            if (valueStack.size() > 1) {
                int minHeight = min(height[i], valueStack.front());
                for (int j = valueStack.size() - 1; j >= 0; j--) {
                    if (valueStack[j] >= minHeight) {
                        break;
                    }
                    waiters += minHeight - valueStack[j];
                    // 把洼地填平
                    valueStack[j] = minHeight;
                }
            }
            // 看看是不是还有能力蓄水 左边墙是不是高于右边墙
            if (height[i] >= valueStack.front()) {
                valueStack.clear();
            }
        }
        valueStack.push_back(height[i]);
    }
053  最大子序列和
    用栈比较牵强，C 语言的写法没用到栈：入栈、清空栈
    栈放的是值
    确保栈的 sum 总是 >=0 
    start =0;
    sum = nums[0];
    for (int i = 1; i < numsSize; i++) {
        if (sum <= 0) {
            maxSum = MAX(maxSum, sum);
            sum = 0;
            start = i;
        } else if (nums[i] < 0) {
            maxSum = MAX(maxSum, sum);
        }
        sum += nums[i];
    }
    maxSum = MAX(maxSum, sum);

084 最大矩形
    操作：入栈、出栈
    栈放的是索引
    尾部放 -1 省去循环结束后的处理
    for(value in ) {
        for(value < 栈顶值) {
            出栈
            计算面积 面积 -1 有妙用
        }
        入栈
    }
    width = width1 + width2 
    width1 = 出栈的索引 - 出栈后栈顶的索引(没有就是 -1)
    width2 = 曾经出过栈的宽度 = 当前索引 - 出栈索引 - 1
    综述 ：width = 当前索引 - 出栈后栈顶索引 -1
    没有找到一个合适的角度去引入单调栈解决这个问题，
    区间内的最值可能是合适的引子。见子目录的 README

085 数组矩阵的最大连续矩形
    每一层包括上面，都可以构成竖立的矩形，然后套用 084 题目的成果
    每一层计算出最大，最后所有层中求最大

121 买卖股票最佳时间 非常适合单调栈的性质
    操作：出栈、入栈
    栈放的是索引
    入栈 -1 省去头的判断
    for(value in ) {
        for(value <= 栈顶) {
            出栈
        }
        入栈
        计算利润
    }

239 最大滑动窗口
    栈放的是索引
    for(i=0; i < 3; i++) {
        for(value >= 栈顶) {
            出栈
        }
        入栈
        栈底为所求最大值
    }
    for(value in ) {
        for(value >= 栈顶) {
            出栈
        }
        索引对比，出栈 1个
        入栈
        栈底为所求最大值
    }
    如果序列为 1 2 3 4 5 6
    栈变化为
        [2]   [0-2] // 栈有 1 个索引
        [3]   [1-3] // 极大值发生变化，现在是索引 3 最大，其他都出栈了
        [4]   [2-4] 
        [5]   [3-5] 
    如果序列为 6 5 4 3 2 1
    栈变化为 
        [0 1 2] [0-2] // 栈有 3 个索引
        [1 2 3] [1-3] // 更小的值入栈 超过索引范围的出栈
        [2 3 4] [2-4] 
        [3 4 5] [3-5] 
316 去除重复字母
    题目难在要保持旧的顺序
    凑合用了一下栈
    先遍历一遍主串，计算每个字符出现的次数
    然后第二次遍历主串，配合栈，栈中放最终的字符，
    对于每一个没放入栈的字符（用 size=0x100 的数组即可模拟 map）如果目标字符小于栈顶字符，
    且栈顶的字符以后还会出现，那么就出栈，把现在这个更小的目标字符入栈

496 下一个更大的元素
    先用单调栈把大数组求值
    然后把两个数组排序
    依次遍历有序的数组就快了
    如果用了 C++ 的 map，就不好翻译为 C 语言了

503 下一个更大的元素 2
    常规解法单调栈遍历一遍
    剔除整个数组的最大值，它必定是 -1
    单调栈中剩下的再遍历一遍数组，双 for loop，但是这次遍历不入栈 只出栈 

739 每日温度
    栈放的是索引
    for(value in ) {
        if(value >  栈顶) {
            出栈 求值
        }
        入栈
    }
    for(栈不空) {
        出栈 求值
    }
exam-0907 最少子弹数 单调栈很不划算
```

**加1**
```
002 十进制两个链表数字相加
066 十进制数组加1
067 两个二进制字符串相加
```

**典型深度 DFS**
```
exam-0901 和为 N 的加法数量
010 正则表达式
    秘诀是优先处理 `x*` 模式，`.` 和字符匹配放其后，回溯时使用
037 数独
038 count and say
051 nqueens
070 爬楼梯 
    只能一步 1 个或者一步 2 个
```


**他山之石：别人的字符串问题集合**

https://darktiantian.github.io/LeetCode%E7%AE%97%E6%B3%95%E9%A2%98%E6%95%B4%E7%90%86%EF%BC%88%E5%AD%97%E7%AC%A6%E4%B8%B2%E7%AF%87%EF%BC%89String/

**我欣赏的基础题目**
```
035 写一个二分查找
058 找最后一个出现的 WORD
278 第一个错误的版本
    二分查找情景题
```

**二叉树**
```
100 是否是同一个 TREE
101 轴对称二叉树 Symmetric
104 求最大深度
107 自底向上层次遍历
108 有序数组转为平衡二叉树
110 判断二叉树是否平衡
111 求最小深度
112 是否存在二叉树路径上的和为某值
113 找到所有二叉树路径上的和为某值
124 二叉树中的最大（任意点之间）路径和
257 二叉树的所有路径
988 从叶结点开始的字典序最小字符串
```

**编译原理**

    xxx DFA 设计判断字符串是否能被 3 整除
    xxx DFA 设计判断字符串是否能被 7 整除
