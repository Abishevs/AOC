use std::io::{self, BufRead};

fn map_str_to_digit(str_num: &str) -> u32 {
    match str_num {
        "one" => 1,
        "two" => 2,
        "three" => 3,
        "four" => 4,
        "five" => 5,
        "six" => 6,
        "seven" => 7,
        "eight" => 8,
        "nine" => 9,
        // will map str num to int
        _ => str_num.parse::<u32>().unwrap(),
    }
}

struct Number(u32, usize);

fn finder(line: &str) -> u32 {
    let number_words = ["one", "two", "three", "four", "five", "six", "seven", "eight", "nine"];
    let digits = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"];

    let mut first_num = Number(0, 0);
    let mut last_num = Number(0,0);



    let res = 10 * first_num.0 + last_num.0; 
    println!("LIne res: {}", res);
    res
}

fn main() {
    let stdin = io::stdin();
    let mut sum = 0;

    for line in stdin.lock().lines() {
        let line = line.expect("Failed to read line");
        sum += finder(&line);
    }

    println!("Result: {}", sum);
}
