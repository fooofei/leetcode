# leetcode


**数字序列找关系**
```
    001 两数之和 寻找 2 个数的和为某一值
    015 三数之和 先排序 然后确定 1 个数，其他 2 个数就转化为了两数之和问题
```
**单调栈**
```
单调递增栈可以找到左起第一个比当前数字小的元素。
单调递减栈可以找到左起第一个比当前数字大的元素。
```
```
    053  最大子序列和
        确保栈的 sum 总是 >=0 
        当前 num < 0 则保存快照 sum + num < 0 则清空栈，保存 num ，其他入栈
    084 最大矩形
    121 买卖股票最佳时间 非常适合单调栈的性质
    239 最大滑动窗口
    739 每日温度
    exam-0907 最少子弹数
```

**加1**
```
    002 十进制两个链表数字相加
    066 十进制数组加1
    067 两个二进制字符串相加
```


**sqrt**
```
    069 有二分查找有奇效
```

**典型深度 DFS**
```
    exam-0901 和为 N 的加法数量
    037 数独
    038 count and say
    051 nqueens
    070 爬楼梯 只能一步 1 个或者一步 2 个
```
