use dsa::List;

fn main() {
    let mut l: List<u32> = List::new();
    for n in 1..10 {
        l.push(n);
    }
    println!("list:\n{}", l);
}
