
// result: min bullet count

// 约束：
//  每人至少 1 个子弹
//  相邻两人 上一轮成绩好的人要比成绩差的人，给的子弹多
//  隐含概念：给发多少子弹不看成绩，只看左右相邻

// 概念:一轮成绩
//  一轮成绩是多个人的成绩，每个人的成绩只有 1 个

// [1,0,5]  = 5   2+1+2 = 5
// [1,2,2]  = 4   1+2+1 = 4
// [ 1, 0, 5, 7, 8, 7, 6, 4, 3, 3, 1] = 26
//   2+ 1+ 2+ 3+ 5+  4+ 3+ 2+ 1+ 2+ 1 = 26


fn min_bullet(grades : &Vec<i32>) -> i32 {

    let mut mins = Vec::with_capacity(grades.capacity());
    // 先每个人最少发 1
    grades.iter().for_each(|_|{mins.push(1)});

    // 正方向，走在前面的比走在后面的多，就是 走在后面的子弹数+1
    for i in 1..grades.len() {
        if grades[i] > grades[i-1]{
            mins[i] = mins[i-1]+1;
        }
    }
    // 反方向，走在前面的比走在后面的多，就是 走在后面的子弹数+1
    for i in (1..grades.len()).rev() {
        if grades[i-1] > grades[i] {
            mins[i-1] = mins[i]+1;
        }
    }
    return mins.iter().sum::<i32>();

}

#[test]
fn test1(){
    assert_eq!(min_bullet(&vec![1,0,5]), 5);
    assert_eq!(min_bullet(&vec![1,2,2]), 4);
    assert_eq!(min_bullet(&vec![ 1, 0, 5, 7, 8, 7, 6, 4, 3, 3, 1] ), 26);
}

fn main() {

    println!("{:?}", min_bullet(&vec![1,0,5]));

    println!("Hello, world!");
}
