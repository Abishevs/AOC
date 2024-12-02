from collections import Counter

left = []
right = []

filename = "input1.txt"
# filename = "inputT.txt"

try:
    with open(filename, 'r') as file:
        for line in file:
            data = line.strip()
            if not data:
                continue
            try:
                l, r = map(int, data.split())  
                left.append(l)
                right.append(r)
            except ValueError:
                print(f"Invalid line: '{line.strip()}'. Skipping.")
except FileNotFoundError:
    print(f"File '{filename}' not found. Please check the file path.")

# print("Left:", left)
# print("Right:", right)

def part1():
    left.sort()
    right.sort()

    tot_distance = 0

    for i in range(len(left)):
            x,y = left[i], right[i]
            print(x, y)
            tot_distance += abs(x-y)



    print(f"Total: {tot_distance}")
# print("Left:", left)
# print("Right:", right)

def part2():
    similarity_score = 0
    y_occernecies = Counter(right)
    # print(y_occernecies)
    for i in range(len(left)):
        x = left[i]
        similarity_score += x * y_occernecies[x]

    print(similarity_score)

part1()
part2()
