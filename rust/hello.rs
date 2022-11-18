fn main() {
    println!("Hello, world!");
    let a = 1223;
    let b = 2334;
    
    //~ a = 2342;  //without "mut"able keyword can not reassign
    println!("a is {} and b is {}", a , b);
    
    let mut x = 12;
    let mut y = 21;
    println!("x is {x} and y is {y}");
    println!("x is {} and y is {}", x , y);
    
    x = 234;
    y = 321;
    println!("x is {x} and y is {y}");
    let s = "rajesh" ;
    println!("len is {}", s.len());
    
    //~ let mut str_not_mutable = "pandian" ;   
    //~ println!("len is {}", str_not_mutable.len());
    
}
