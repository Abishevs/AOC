BLUE = 14
GREEN = 13
RED = 12

def is_valid(subsets:list):
        for subset in subsets:
            subset = subset.split(',')
            for sub in subset:
                num, name = sub.split()
                num = int(num)
                if name == 'green' and num > GREEN:
                    return False 
                if name == 'red' and num > RED:
                    return False
                if name == 'blue' and num > BLUE:
                    return False
        return True

def power_thingie(subsets:list):
    cur_greens = []
    cur_reds = []
    cur_blues = []
    for subset in subsets:
        subset = subset.split(',')
        for sub in subset:
            num, name = sub.split()
            num = int(num)
            if name == 'green':
                cur_greens.append(num)
            if name == 'red':
                cur_reds.append(num)
            if name == 'blue':
                cur_blues.append(num)
    return max(cur_blues) * max(cur_reds) * max(cur_greens)


def main():
    with open("input.txt", "r", encoding="utf-8") as f:

        raw_lines = f.readlines()
        possible_games = []
        power_sums = []
        for line in raw_lines:
            line = line[:-1]

            id_index = line.find(":")
            id = int(line[:id_index].removeprefix('Game '))

            line = line[id_index + 1:].strip()
            subsets = line.split(';')
            
            if is_valid(subsets):
                possible_games.append(id)

            power_sums.append(power_thingie(subsets))

        print(f'Part 1: {sum(possible_games)}')
        print(f'Part 2: {sum(power_sums)}')

if __name__ == "__main__":
    main()

