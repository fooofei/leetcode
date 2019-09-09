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
// f(x,y) 表示为 和为 x 的，组成数值个数为 y 的结果有多少可能
// f(x,y) =
//
//    sum =0
//    for(m in 1..=x/y) { // 填 y 个坑，每个坑先填入多少值(从 1 到 x/y)
//        for(n in 1..=y-1) { // 剩下的值总和还给提供多少坑(从 1 到 y-1)
//            // 和为 x-y*m 填入 n 个坑，有多少可能
//            sum += f(x-y*m, n);
//        }
//    }
//    return sum;
//

fn layer_count(cache: &mut Vec<Vec<i32>>, num: i32, layer: i32) -> i32 {
    if layer <= 1 {
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
    for i in 1..121 {
        println!("sum({}) = {}", i, sum(&mut cache, i));
    }
}
