def load_input(filename:str):
    grid = []
    with open(filename, "r", encoding="utf-8") as f:
        raw_lines = f.readlines()
        for line in raw_lines:
            row = []
            for char in line:
                if char.isnumeric():
                    row.append(int(char))
                else:
                    row.append(char)
            grid.append(row)

    return grid

def build_number(grid, row, col):
    number = ''

    c = col
    while c >= 0 and isinstance(grid[row][c], int):
        number = str(grid[row][c]) + number
        c -= 1

    c = col + 1
    while c < len(grid[row]) and isinstance(grid[row][c], int):
        number += str(grid[row][c])
        c += 1

    return int(number) if number else 0

def is_valid(grid, row, col):
    rows = len(grid)
    cols = len(grid[0]) if rows > 0 else 0
    return 0 <= row < rows and 0 <= col < cols


def is_non_dot_symbol_around(grid, x, y):
    # Moore neigborhood thingie bingiee check
    for i in range(-1, 2):
        for j in range(-1, 2):
            nx, ny = x + i, y + j
            if is_valid(grid, nx, ny) and grid[nx][ny] != '.' and not (isinstance(grid[nx][ny], int)):
                return True
    return False


def finder(grid):
    global_sum = 0

    for row in range(len(grid)):
        added_nums = set()
        for col in range(len(grid[row])):
            if isinstance(grid[row][col], int):
                    if is_non_dot_symbol_around(grid, row, col):
                        num = build_number(grid, row, col)
                        if num not in added_nums:
                            print(f"Adding number {num} at ({row}, {col})")
                            global_sum += num
                            added_nums.add(num)

    return global_sum


def main():
    grid = load_input('input.txt')
    sum = finder(grid)
    print(f"Part 1: {sum}")

if __name__ == "__main__":
    main()

