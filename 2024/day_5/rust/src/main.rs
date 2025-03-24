use std::{fs, io, path::PathBuf, u32};

#[derive(Debug)]
struct PageOrdering {
    left: u32,
    right: u32,
}


impl PageOrdering {
    fn from_str(value: &str) -> Result<PageOrdering, Box<dyn std::error::Error>> {
        let mut pairs = value.trim().split("|");

        let left = pairs
            .next()
            .ok_or("Missing left part")?
            .trim()
            .parse::<u32>()?;

        let right = pairs
            .next()
            .ok_or("Missing left part")?
            .trim()
            .parse::<u32>()?;


        Ok(PageOrdering {
            left,
            right
        })
        
    }

    fn filter_by_existance<'a>(page: &'a [PageOrdering], update: &'a Update) -> Vec<&'a PageOrdering> {
        page
            .iter()
            .filter(|page| { 
                update.elem.contains(&page.left) &&
                   update.elem.contains(&page.right)
            })
        .collect()

    }
}

#[derive(Debug)]
struct Update {
    elem: Vec<u32>,
}

impl Update {
    fn from_str(value: &str) -> Result<Self, Box<dyn std::error::Error>> {
        let elem: Vec<u32> = value
            .split(",")
            .map(|ch| ch.trim().parse::<u32>())
            .collect::<Result<Vec<u32>, _>>()?;

        Ok(Self { elem })
    }
    
}

fn main() {
    // Identify page numbers in update and filter only those rules?
    // PageOrderings
    // Update
    // Loop by each update and filter by which is correct
    let path = PathBuf::from("../input.txt");

    let contents = fs::read_to_string(path)
        .expect("Unable to read file");

    // Split by blank line
    let mut parts = contents.split("\n\n");
        
    let pages = parse_pages(parts.next().unwrap_or(""));
    let updates = parse_updates(parts.next().unwrap_or(""));

    let first_update = updates
        .iter()
        .next()
        .ok_or("SHit where is my Update line")
        .unwrap();

    
    let filered = PageOrdering::filter_by_existance(&pages, &first_update);
    assert_eq!(&filered.len(), &pages.len());
    dbg!(filered);
    dbg!(first_update);

    // dbg!(pages);
    // dbg!(updates);

}

fn parse_pages(input: &str) -> Vec<PageOrdering> {
    input
        .lines()
        .filter_map(|line| {
            PageOrdering::from_str(line)
                .map_err(|err| eprintln!("OrderingsParsing Err: {}", err))
                .ok()

        })
        .collect()
}

fn parse_updates(input: &str) -> Vec<Update> {
    input
        .lines()
        .filter_map(|line| {
            Update::from_str(line)
                .map_err(|err| eprintln!("UpdatesParsing Err: {}", err))
                .ok()

        })
    .collect()
}
