# leetcode

有轻功就是有技巧的意思，轻功就是理解某个算法的任督二脉。

### 单个例题

#### 011 容器最多盛水

    双指针 理解为什么是移动较小高度的指针，因为移动了较大高度的必然导致面积比现在小，
    那就没计算的必要了

#### 014 最长公共前缀

    我一上来就觉得应该以 str[0] 为 pattern，依次按照`列`遍历 [1,n) 后来发现我这是最简洁的写法
    有的办法还是先假设一个公共前缀，每次变换前缀去剩下字符串里匹配 `startsWith`，这种办法难看

#### 026 删除重复值

#### 027 删除目标值

    两道题一起看待，带有类库的语言 C++ Java 比较规矩，只要考虑如何使用容器 in-placed 删除多余元素即可
    对于 C 语言，可以使用的技巧是使用类似栈的技巧，原地用栈，不等于栈顶/目标值，则入栈，没有出栈这个操作

#### 155 最小值栈

    在 O(1) 时间下获得某个栈中的最小值，数据栈 +　辅助栈，技巧是在辅助栈中占坑
    栈是 8 4 9 3 辅助栈是 8 4 4 3 

#### 160 两个交叉链表在哪交叉

#### 235 求二叉树上两个结点的最近公共祖先(不要求二叉搜索树)

    我想到的方法是分别遍历两个链表，存放到两个容器里，然后倒序找第一个指针值不同的结点
    更有技巧的办法是 a->b b->a ，遍历 a 链表的，遍历结束后，切换到 b 链表，
    同理 b a 的也是，当两个指针一样的时候，就是链表交叉点
    
### 题目聚合

#### 字符串

    字符串题目太多，只列举其中不会做的题目
    003 最长没有重复字符的子串**
        滑动窗口/队列 队列中一旦有重复字符，就按照队列方向移出
        双指针
    316 去除重复字母
        在保持位置情况下去除重复找子串
        灵光点是要想到 栈 + for(currentChar < stack.top() && count[stack.top] > 0)
        当前字符比栈顶的更字典序靠前并且栈顶字符以后还出现，就出栈
        相比 387 题目更容易解决，直接遍历一次求次数，然后再遍历一次就可以了
    387 找到第一个第一次出现的字母
    xxx 套路：倒着复制
        反向遍历
    xxx 套路：循环不变式
        正向遍历
        改变了原数组的顺序
        

#### 回文

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
    234 回文单链表
        1 先倍速递进，找到分割点
        2 分割点开始头插法反转链表
        3 判断两个单链表是否一致
    409 最长回文串长度
        最简单 把能变成偶数的字符都个数都加上，最后加一次奇数的用来做中心轴就就行了


#### 数字序列找关系

    xxx 最大公约数
        辗转相除法
    xxx 最小公倍数
        a * b / 最大公约数
    001 两数之和 
        寻找 2 个数的和为某一值
        带索引的排序 然后 first last 双指针向中间靠拢
        也有人用 map 解决，C 语言不合适用 map， map 存放 target - num[i] 当前数字的差
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
    069 实现 sqrt 不要小数位
        轻功 二分查找有奇效
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
    189 旋转数组/平移数组
        把数组像链式一样旋转 证明有环，n%k == 0 会产生环状
        破解办法是索引 +1 再来一次
    191 汉明重量 (位移定理)
        一个 0/1 构成的字符串或者一个整数中，1 的个数
        土办法是自己循环每次移动 1 位，判断末尾是不是 1
        轻功是利用 n & (n-1) 意思是去掉最后出现的 1
    204 质数/素数
        判断是不是质数时的定理 不在6的倍数两侧的一定不是质数, 质数一定落在 6x-1/6x+1 上
        在求个数时的算法 Sieve of Eratosthenes [埃拉托斯特尼筛法]
        (https://zh.wikipedia.org/wiki/%E5%9F%83%E6%8B%89%E6%89%98%E6%96%AF%E7%89%B9%E5%B0%BC%E7%AD%9B%E6%B3%95)
    xxx 合数
        质数的反义词
    205 同构字符串
        翻译一下就是同一个索引的字符在各自的字符串中第一次出现时的索引要相同
    231 判断是不是 2 的次幂 (位移定理)
        同样应用定理 n & (n-1) 只有 1 个 1 才是符合题意
    242 字母异位词
        情景太难理解了
        两个单词包含相同的字母，但是次序不同
        countMap 和 uniqChars 遍历一次求出来 countMap 对应次数一样
        有人归类为双指针求解
    258 各位相加
        38 = 3+8 (11) = 1+1 = 2
        轻功是只要 n%9 计算就行了
        假设四位十进制数字表示为 num = 1000*a + 100*b + 10*c + d
        num2 所求 = a+b+c+d
        num-num2 = 999*a + 99*b + 9*c
                 =9 * (111*a + 11*b + c)
        这个值必定是 9 的倍数
        因此 num % 9 剩下的就是所求
    263 丑数 ugly number   
        丑数就是只包含质因数 2, 3, 5 的正整数
        不需要使用递归，三个 for 循环，for num%5==0; for num%3==0; for num%2==0; 
        最后判断 num==1 是符合要求
    268 缺失数字
        这个题目的情景很怪，感觉是勉强拼凑的题目 
        轻功是 异或
        我直接想到了已知和，然后做减法就可以了
    292 NIM 游戏
        一次只能减少 1-3 个，自己先摸，找是否自己最后赢
        轻功是 n%4 != 0 就赢，纯数学
    415 字符串表示的十进制非负数字加和

#### 单调栈

    单调递增栈可以找到左起第一个比当前数字小的元素。
    单调递减栈可以找到左起第一个比当前数字大的元素。

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

#### 添加删除/对数据结构的 CRUD

    002 十进制两个链表数字相加
    066 十进制数组加1
    067 两个二进制字符串相加


#### 典型深度 DFS
    
    exam-0901 和为 N 的加法数量
    037 数独
        DFS + 标记选择/重置选择
    038 count and say
    051 nqueens
        DFS + 标记选择/重置选择
    070 爬楼梯 
        只能一步 1 个或者一步 2 个
    212 单词搜索 2
        同时归类到 trie 求解
        DFS + 标记选择/重置选择


#### 他山之石：别人的集合

[LeetCode算法题整理（字符串篇）String](https://darktiantian.github.io/LeetCode%E7%AE%97%E6%B3%95%E9%A2%98%E6%95%B4%E7%90%86%EF%BC%88%E5%AD%97%E7%AC%A6%E4%B8%B2%E7%AF%87%EF%BC%89String/)

[LeetCode刷题文章目录](https://codechina.org/leetcode-catalog-index/)

#### 我欣赏的基础题目

    035 写一个二分查找/常考基础
    058 找最后一个出现的 WORD/单字符搜索异常分支考虑周全
    203 单链表移除与指定值相等元素
        轻功 用 Linux Torvalds 教学的二级指针 https://coolshell.cn/articles/8990.html
    278 第一个错误的版本
        二分查找情景题/应用题
    290 单词规律 wordPattern
        给定一种规律 pattern 和一个字符串 str ，判断 str 是否遵循相同的规律。
        轻功是 把字符串转化为 uint64 的表示，进制数字选 233 就够用了

#### 二叉树

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
        对比学习 053 最大子序列和
    226 invert 二叉树 （homebrew 作者面试的题目）
    235 求二叉树上两个结点的最近公共祖先
    257 二叉树的所有路径
    988 从叶结点开始的字典序最小字符串


#### NFA/DFA
    
    010 正则表达式匹配
        多解法
        从 Russ Cox 学到的 NFA 解决方法，
        并且是避免回溯的多状态同时匹配
    028 strstr
        KMP 过于复杂，写不出来，记住 sunday 算法。
        后来学到了基于 DFA 理解 KMP，轻功是遇到不匹配字符 p[j] 时，
            应该要想到仿照朴素匹配，把 p[1,j-1] 作输入，从 0 状态开始
            得到 x 状态, DFA[p[j]][x] 就是不匹配时要转移的下一个状态
    XXX AC 自动机
    065 有效十进制数字
        判断字符串是不是有效十进制数字 
        基础知识是要理解并记忆有效十进制数字的构成
        之后写出其正则表达式，
        然后在纸上画出 NFA 图，
        NFA 得到 DFA 状态矩阵，
        表驱动法解答题目
    xxx DFA 设计判断字符串是否能被 3 整除
        [nark 整理的正则表达式](http://nark.cc/test/s2.html)
    xxx DFA 设计判断字符串是否能被 7 整除

#### 动态规划
    
    010 正则表达式匹配
        多解法
        动态规划的代码是用 C++ 实现的
        row len = p len
        col len = s len
        遇到非 * 时　T[i+1][j+1] = T[i][j] && (p[i] == '.' || p[i] == s[j]);
        遇到 * 时　T[i+1][j+1] = T[i-1][j+1] || 
        T[i+1][j] && (p[i - 1] == '.' || p[i - 1] == s[j])
        求解是否匹配
        动态规划状态表示子问题是否匹配
        两个字符串的字符表示矩阵
    044 通配符匹配
        动态规划在遇到 * 时，如何理解 T[i+1][j+1] = T[i+1][j] || T[i][j+1]
        从公式理解 T[i+1][j+1] = T[i+1][j] || T[i][j] || T[i-1][j] ... || T[0][j]
        当把 i+1 替换为 i 时，含义从匹配完主串的 i+1 和模式串的 j+1 到匹配完主串的 i 和模式串的 j+1 
        因为p[j+1] = *，所以含义是一样的，T[i][j+1] = T[i][j] || T[i-1][j] ... || T[0][j]
        因此换算为 T[i+1][j+1] = T[i+1][j] || T[i][j+1]
        从文字理解 T[i+1][j+1] = *匹配 0 个字符 || *匹配 1 个字符 || *匹配 2 个字符 ...
        T[i][j+1] = *匹配 0 个字符 || *匹配 1 个字符 || *匹配 2 个字符 ...
        从 T[i][j+1] 到 T[i+1][j+1] 理解为 pattern 字符数没变，string 多来 1 个字符，
        因此 T[i+1][j+1] = *匹配 0 个字符 || 在 T[i][j+1] 的基础上匹配 1 个字符
        T[i+1][j+1] = *匹配 0 个字符 || （T[i][j+1] &&　继续匹配 1 个字符)
        T[i+1][j+1] = *匹配 0 个字符 || T[i][j+1]
        求解是否匹配
        动态规划状态表示也是是否匹配
        两个字符串的字符表示矩阵
    053 最大子序列和
        用栈比较牵强，C 语言的写法没用到栈：入栈、清空栈
        
        T[i] = maxInts(T[i+1]+nums[i], nums[i])
        然后再 maxInts(T...)        
        求解子序列和
        动态规划状态表示挨着当前数的子序列和，不挨着表示与前面的子序列切断联系
        一维数组
        最后需要把动态规划结果做二次处理
        
        Kadane 算法 图画的好看
        http://bedirtapkan.com/Kadane%27s-Algorithm-2/
        简要的说，Kadane 算法是动态规划空间复杂度的降维
    072 字符串编辑距离 
        if s[i] == p[j] {
            T[i+1][j+1] = T[i][j]
        } else {
            T[i+1][j+1] = minInts(T[i][j], T[i+1][j], T[i][j+1]) + 1
        }
        求解编辑距离
        动态规划状态表示子问题编辑距离
        两个字符串表示成矩阵
    198 打家劫舍
        money[i] = maxInts(money[i-2]+nums[i], money[i-1])
        求解抢劫的最大和
        动态规划状态表示子问题抢劫最大和
        一维数组
    279 完全平方数 
        看了教程才知道是贪心算法有关
        直觉的以为减去小于当前数字的最大平方数的值，递归就可以了，
        结果考虑的还不够 12=4+4+4 48+16+16+16
        要 for 循环全判断一次，遇到 for 循环还怀疑人生，以为有什么轻功，其实没轻功了
        max := int(math.Sqrt(float64(i)))
        min := i + 2
        for ; max > 0; max -= 1 {
            j := i - max*max
            if j < 1 {
                min = minInts(min, 1)
            } else {
                min = minInts(min, T[i-max*max]+1)
            }
        }
        T[i] = min
        求解和为n的个数
        动态规划状态表示子问题和为m的个数(附带选择最值)
        一维数组
    292 NIM 游戏
        正确解法是找到数学规律 用动态规划无法解决 n 过大，内存不够的问题
        T[i] = !T[i-1] || !T[i-2] || !T[i-3]
        对比石子游戏学习 877 1140
    300 最长上升子序列/最长递增子序列
        轻功 patience game 扑克算法
        朴素的办法是双 for 循环 O(n^2) 时间复杂度，几乎看不到动态规划
        这个题目的动态规划感太弱了
    
    877 石子游戏
        vi := piles[i] + T[i+1][j].Second
        vj := piles[j] + T[i][j-1].Second
        if vi > vj {
            T[i][j].First = vi
            T[i][j].Second = T[i+1][j].First
        } else {
            T[i][j].First = vj
            T[i][j].Second = T[i][j-1].First
        }
        求解自己先拿最多拿到石子数目(最后判断大小就成了 bool )
        动态规划状态表示子问题 [i,j] 之间最多拿石子数目(没有先后的判断)
            在子问题的基础上向两边增加石子，先后拿石子的顺序发生颠倒
        i,j 组成的区间二维矩阵 只用到了部分格子 倒推的动态规划
    1140 石子游戏 II
        更难想到
        max := T[i][j]
        for x := 1; x <= 2*j && i+x <= len(piles); x++ {
            v1 := maxInts(x, j)
            max = maxInts(max, sums[i]-T[i+x][v1])
        }
        T[i][j] = max
        求解自己先拿最多拿到石子数目
        动态规划状态表示子问题 [i,end) 之间最多拿石子数目(没有先后的判断)
            在子问题的基础上向左边增加石子，通过所有石子和 - 下一个人拿的石子 
            (附带选择最值)    
        i,M 组成的区间二维矩阵 倒推的动态规划
    1278 分割回文串 III
        minCost := T[i-1][j-1]
        for k := 1; k < j; k++ {
            v1 := T[i-1][k-1] + costT[k][j]
            minCost = minInts(minCost, v1)
        }
        T[i][j] = minCost
        求解 N 长度的串变成 K 个子回文串 的最小修改数
        动态规划状态表示子问题区间 [0,i] 变成 K 个回文串的最小修改数
        也就是求解 T[K][N-1]
        可以有递推公式 T[k][i] = T[k-1][i-1] + 0 (s[i,i]的最小修改数是0)
        还可以有  T[k-1][i-2] + cost(s[i-1,i]) ... 一直下去，
        这里附带选择最值
        i,K 组成的二维矩阵

#### 动态规划 - 股票买卖

更喜欢外国人 [Tushar Roy](https://www.youtube.com/user/tusharroy2525/videos) 讲的，更有逻辑，缺点是只处理了 k 次交易的情景

中国人的教程 [团灭 LeetCode 股票买卖问题](https://labuladong.gitbook.io/algo/dong-tai-gui-hua-xi-lie/tuan-mie-gu-piao-wen-ti) 逻辑上差点，感觉是背诵出来的

    121 只允许买卖 1 次
        构造差价数组 然后就是一个`最大子序列和`的问题了
        也可以直接入手动态规划

        T[天][持有股票/不持有]
        i 和 j 不要作区分，只是为了数组边界不越界 好处理，没改变其含义
        T[j][0] = max(T[j-1][0], T[j-1][1] + prices[i])
        T[j][1] = max(T[j-1][1], -prices[i])
    122 不限次数买卖
        T[天][持有股票/不持有]
        i 和 j 不要作区分，只是为了数组边界不越界 好处理，没改变其含义
        T[j][0] = max(T[j-1][0], T[j-1][1] + prices[i])
        T[j][1] = max(T[j-1][1], T[j-1][0] - prices[i])
    123 只允许买卖 2 次
        188 题目 k=2 的特例
    188 允许买卖 K 次
        T[j][k] = max(T[j-1][k], T[0][k-1] + prices[j] - prices[0],
                                 T[1][k-1] + prices[j] - prices[1],
                                 T[2][k-1] + prices[j] - prices[2],
                                 ...
                                 T[j-1][k-1] + prices[j] - prices[j-1])
                = max(T[j-1][k], prices[j] + maxDiff)
                maxDiff 每次循环都变，这样就把上面的公式降低维度，降低时间复杂度
        T[j][k][0] = max(T[j-1][k][0], T[j-1][k][1] + prices[i])
        T[j][k][1] = max(T[j-1][k][1], T[j-1][k-1][0] - prices[i])
        T[j][0][0] = 0
        T[j][0][1] = MIN
    309 不限次数买卖 两次买卖之间有 1 天的冻结期间 cooldown
        T[天][持有股票/不持有]
        i 和 j 不要作区分，只是为了数组边界不越界 好处理，没改变其含义
        T[j][0] = max(T[j-1][0], T[j-1][1] + prices[i])
        T[j][1] = max(T[j-1][1], T[j-2][0] - prices[i])
    714 不限次数买卖 每笔交易有手续费
        T[天][持有股票/不持有]
        i 和 j 不要作区分，只是为了数组边界不越界 好处理，没改变其含义
        T[j][0] = max(T[j-1][0], T[j-1][1] + prices[i])
        T[j][1] = max(T[j-1][1], T[j-1][0] - prices[i] - fee)

#### 前缀树/字典树/Trie

    139 单词拆分
        word break
    208 实现 Trie
        search()
        startsWith()
    211 添加与搜索单词
        在字典内进行全文搜索
        带 . 匹配任意字符的搜索
    212 单词搜索 2
        题意需要反复理解：是从任意点开始向上下左右方向步进
        不需要 AC 自动机


#### 很难看懂题目

    007 整数反转
        原来题目只要 int 整数类型，其他整数类型不让使用
    016 最接近的三数之和
        是否需要排序
    020 有效的括号
        是否有嵌套 以及优先级关系
    065 有效数字 
        具备基础知识 有效数字的正则表达式如何构造
    071 简化路径
        模糊 ../ 才是向上一层目录 ...abc 不可以向上
    076 最小覆盖子串
        S 和 T ，要求 T 中所有字母都出现在窗口中，
        这里开始出现歧义，如果 T 中存在重复字母，那么窗口也要出现等量的重复字母，会让人以为字母要去重复
        双指针
    108 将有序数组转换为二叉搜索树
        我理解只要生成的二叉树 左右子树满足高度差绝对值不超过 1 就可以了
        但是测试预期不是这样子
        从测试预期猜测必须采用递归的求解
    124 二叉树中的最大路径和
        从任意点出发到任意点结束 不能有三叉
    205 同构字符串
        两个字符串满足互换性 互相为同构
    292 NIM 游戏
        模糊的地方是只要可能性中有赢的就是赢了
    1140 石子游戏 II
