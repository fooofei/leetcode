
// https://zhuanlan.zhihu.com/p/74893652

fn convert(s: String, n: i32) -> String {
    // 得到按照字符串字符的顺序得到其所在行号
    let it = (0..n).into_iter().chain((1..=n - 2).rev().into_iter());
    // 搞一个二维数组
    let mut vr: Vec<Vec<char>> = vec![vec![]; n as usize];
    // 按照行号顺序 把字符填入对应行的数组
    s.chars()
        .zip(it.cycle())
        .for_each(|(c, i)| vr[i as usize].push(c));
    // 把二维数组平坦化 得到一维数组
    vr.into_iter().flatten().collect()
}

#[test]
fn test1() {
    let v1 = convert(String::from("PAYPALISHIRING"), 3);
    assert_eq!(v1, String::from("PAHNAPLSIIGYIR"))
}

fn main() {
    println!("Hello, world!");
}
