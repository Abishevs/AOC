import re


filename = "input1.txt"
# filename = "inputT.txt"
# filename = "inputT1.txt"
rapport = []

try:
    with open(filename, 'r') as file:
        for line in file:
            data = line.strip()
            rapport.append(data)
except FileNotFoundError:
    print(f"File '{filename}' not found. Please check the file path.")

def part1():
    pattern = r"mul\((\d{1,3}),(\d{1,3})\)"
    tot_sum = 0
    for line in rapport:
            matches = re.findall(pattern, line)
            for pair in matches:
                x, y = int(pair[0]), int(pair[1])
                product = x*y
                tot_sum += product

    print("Total sum part1", tot_sum)


def part2():

    pattern = r"(?P<instruction>mul\((\d{1,3}),(\d{1,3})\))|(?P<dont>don't\(\))|(?P<do>do\(\))"
    tot_sum = 0
    dont_toggle = False
    for line in rapport:
            matches = re.finditer(pattern, line)
            for match in matches:
                if match.group("dont"):
                    dont_toggle = True
                elif match.group("do"):
                    dont_toggle = False

                elif match.group("instruction") and not dont_toggle:
                        x, y = int(match.group(2)), int(match.group(3))
                        product = x*y
                        tot_sum += product

    print("Tottal sum part2", tot_sum)

part1()
part2()
