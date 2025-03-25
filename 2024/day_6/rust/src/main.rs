use std::fs;
use std::io::{self, Write};
use std::thread;
use std::time::Duration;


#[derive(Debug, Clone, Copy)]
struct Point {
    x: usize,
    y: usize,
}

impl Point {
    fn new(x: usize, y: usize) -> Self {
        Self {x,y}
    }
}

#[derive(Debug)]
enum Direction {
    UP,
    DOWN,
    RIGHT,
    LEFT
}

impl Direction {
    fn turn_90_deg(&self) -> Self {
        match self {
            Self::UP => Self::RIGHT,
            Self::RIGHT => Self::DOWN,
            Self::DOWN => Self::LEFT,
            Self::LEFT => Self::UP,
        }
    }

    fn to_char(&self) -> char {
        match self {
            Self::UP => '^',
            Self::RIGHT => '>',
            Self::LEFT => '<',
            Self::DOWN => 'V',
        }
    }
}

#[derive(Debug)]
struct Arrow {
    direction: Direction,
    pos: Option<Point>,
}

impl Arrow {
    fn new(direction: Direction, x: usize, y: usize) -> Self {
        Self { direction, pos: Some(Point::new(x, y)) }
    }

    fn next_position(&mut self, map: &Vec<Vec<char>>) -> Option<Point>{
        let pos = self.pos.as_mut().expect("WTF it should be valid here"); // panick if its not there
                                     
        let x = pos.x as i32;
        let y = pos.y as i32;
        let (new_x, new_y) = match self.direction {
            Direction::UP => (x, y.wrapping_sub(1)),
            Direction::RIGHT => (x + 1, y),
            Direction::DOWN => (x, y + 1),
            Direction::LEFT => (x.wrapping_sub(1), y),
        };


        if new_y >= 0 && new_y < map.len() as i32
    && new_x >= 0 && new_x < map[0].len() as i32 {
            Some(Point::new(new_x as usize, new_y as usize))
        } else {
            None
        }

    }

}

fn main() {
    let input = fs::read_to_string("../test.txt")
        .expect("Ah shiiiit");

    let mut map: Vec<Vec<char>> = input
        .lines()
        .map(|line| line.chars().collect())
        .collect();

    let mut arrow = find_pos(&map).expect("Where is my arrow");
    dbg!(&arrow);

    while arrow.pos.is_some() {
        let pos = arrow.pos.expect("Wtf pos should be valid rn");
        if let Some(next_pos) = arrow.next_position(&map) {
            map[pos.y][pos.x] = 'X';
            match map[next_pos.y][next_pos.x] {
                '#' => arrow.direction = arrow.direction.turn_90_deg(),
                _ => {
                    arrow.pos = Some(next_pos); // Move forward
                    map[next_pos.y][next_pos.x] = arrow.direction.to_char();
                }
            }
        } else {
            map[pos.y][pos.x] = 'X'; // Draw last pos
            arrow.pos = None; // Out of bounds 
        }
        // animate_output(&map);
    }

    let sum = map.iter().flatten().filter(|&&ch| ch == 'X').count();
    animate_output(&map);
    println!("Res: {}", sum);


}

fn animate_output(map: &Vec<Vec<char>>) {
    clear_screen();
    print_map(map);
    io::stdout().flush().unwrap();
    thread::sleep(Duration::from_millis(1000));
}

fn print_map(map: &Vec<Vec<char>>) {
    for row in map {
        let line: String = row.iter().collect();
        println!("{}", line);
    }
}

fn clear_screen() {
    print!("\x1B[2J\x1B[H");
    io::stdout().flush().unwrap();
}

fn find_pos(map: &Vec<Vec<char>>) -> Option<Arrow> {
    for x in 0..map.len() {
        for y in 0..map[0].len() {
            let pos = map[x][y];
            match pos {
                '^' => return Some(Arrow::new(Direction::UP, y, x)),
                '>' => return Some(Arrow::new(Direction::RIGHT, y, x)),
                '<' => return Some(Arrow::new(Direction::LEFT, y, x)),
                'V' => return Some(Arrow::new(Direction::DOWN, y, x)),
                _ =>  (),
                
            }
        }
    }

    None

}
