filename = "input1.txt"
# filename = "inputT.txt"
rapport = []

try:
    with open(filename, 'r') as file:
        for line in file:
            data = line.strip()
            data = list(map(int, data.split()))
            rapport.append(data)
except FileNotFoundError:
    print(f"File '{filename}' not found. Please check the file path.")

def is_safe(row):
    for i in range(len(row) - 1):
        increasing = all(i < j for i,j in zip(row, row[1:]))
        decreasing = all(i > j for i,j in zip(row, row[1:]))
        abs_diff = abs(row[i] - row[ i + 1])
        if not (increasing or decreasing):
            return False
        if not (1 <= abs_diff <= 3):
                return False
    return True

def part1():
    # print(rapport)
    tot_safe = 0
    for row in rapport:
        if is_safe(row):
            # print(f"row: {row}, Safe?: {is_safe(row)}")
            tot_safe += 1
    print("Part1: ", tot_safe)

def part2():
    # print(rapport)
    tot_safe = 0
    for row in rapport:
        if is_safe(row):
            tot_safe += 1
        else:
            # while True:
                for i in range(len(row)):
                    new_list = [x for j, x in enumerate(row) if j != i]
                    if is_safe(new_list):
                        tot_safe += 1
                        break
    print("Part2: ", tot_safe)


# part1()
part2()
