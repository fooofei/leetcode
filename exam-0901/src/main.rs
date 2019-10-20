// 题目说明
// 1 =1

// 1+1
// 2
// = 2

// 1+1+1
// 2+1
// 3
//  =3

// 1+1+1+1
// 2+1+1
// 3+1 / 2+2
// 4
// = 5

// 1+1+1+1+1
// 2+1+1+1
// 3+1+1 / 2+2+1
// 4+1 / 3+2
// 5
// = 7

// 1+1+1+1+1+1
// 2+1+1+1+1
// 3+1+1+1 2+2+1+1
// 4+1+1 3+2+1 (3+2+1) 2+2+2
// 5+1 4+2  (5+1) 3+3
// 6
// =11

// 1+1+1+1+1+1+1
// 2+1+1+1+1+1
// 3+1+1+1+1 2+2+1+1+1
// 4+1+1+1 3+2+1+1 2+2+2+1
// 5+1+1 4+2+1 3+3+1  3+2+2
// 6+1 5+2 4+3
// 7
// = 15

// 1+1+1+1+1+1+1+1
// 2+1+1+1+1+1+1+1
// 3+1+1+1+1+1 2+2+1+1+1+1
// 4+1+1+1+1 3+2+1+1+1 2+2+2+1+1
// 5+1+1+1 4+2+1+1 3+3+1+1 3+2+2+1 2+2+2+2
// 6+1+1 5+2+1 4+3+1 (5+1+2) 4+2+2 3+3+2
// 7+1 6+2 5+3 4+4
// 8
// = 22

//  10 = 42 20 = 627

// 解题思路
// 先定递归函数的参数
// f(x,y) 
// :x 和为x  
// :y 表示用几个数字表示和x 
// :return 返回可能的组成结果数量
//
// f(x,y) =
// 举例归纳 f(8,3)
// 既然是 3 个数字组成，每个数字最小为 1，因此先垫上 1
// 1 1 1 为基准，还剩 8-3=5，在 <3 的坑上随便放，即 f(5,1) + f(5,2)
// 2 2 2 为基准，还剩 8-6=2, 在 <3 的坑上随便放，即 f(2,1) + f(2,2) 
// 3 3 3 不成立，结束
// 归纳到一般情况
//
//    sum =0
//    for(m in 1..=x/y) { 
//        for(n in 1..=y-1) { 
//            sum += f(x-y*m, n);
//        }
//    }
//    return sum;
//
// 并且两个特例 f(x, 1)=1 f(x,x)=1

fn layer_count(cache: &mut Vec<Vec<i32>>, num: i32, layer: i32) -> i32 {
    if layer <= 1 {
        return 1;
    }
    if layer == num {
        return 1;
    }

    let i: usize = num as usize;
    let j: usize = layer as usize;
    if cache[i][j] > 0 {
        return cache[i][j];
    }

    let mut r = 0;
    let inc = num / layer;
    for i in 1..=inc {
        let inner_number = num - i * layer;
        for inner_layer in 1..=layer - 1 {
            let _v1 = layer_count(cache, inner_number, inner_layer);
            r += _v1;
        }
    }

    cache[i][j] = r;

    return r;
}
fn sum(cache: &mut Vec<Vec<i32>>, num: i32) -> i32 {
    let mut r = 0;

    for layer in 1..=num {
        let mut _v1 = layer_count(cache, num, layer);
        r += _v1;
    }
    return r;
}

#[test]
fn test1() {
    let mut cache = vec![vec![0; 300]; 300];

    assert_eq!(sum(&mut cache, 1), 1);
    assert_eq!(sum(&mut cache, 2), 2);
    assert_eq!(sum(&mut cache, 3), 3);
    assert_eq!(sum(&mut cache, 4), 5);
    assert_eq!(sum(&mut cache, 5), 7);
    assert_eq!(sum(&mut cache, 6), 11);
    assert_eq!(sum(&mut cache, 7), 15);
    assert_eq!(sum(&mut cache, 8), 22);
    assert_eq!(sum(&mut cache, 10), 42);
    assert_eq!(sum(&mut cache, 20), 627);
}

#[test]
fn test2(){
    let mut cache = vec![vec![0; 300]; 300];
    for i in 1..121 {
        println!("sum({}) = {}", i, sum(&mut cache, i));
    }
}

pub fn main() {
    println!("main exit");

    let mut cache = vec![vec![0; 300]; 300];
    let mut v = layer_count(&mut cache, 8, 3);
    println!("v= {}", v)
}
