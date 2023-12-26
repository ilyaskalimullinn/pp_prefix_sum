from ast import List
from random import randint
import sys


def generate_length_list(n: int, nums: List = [5, 10]):
    lst = []
    power_of_ten = 1
    for i in range(n):
        lst += [num * power_of_ten for num in nums]
        power_of_ten *= 10
    return lst


nums = [5, 10]
MIN = 1
MAX = 1000

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Must have exactly one argument: max number of zeros")
        exit(1)
        
    n = int(sys.argv[1])
    lengths = generate_length_list(n, nums)

    print(f"Generating {len(lengths)} data files (for nums {lengths})...")
    for i in range(len(lengths)):
        print(f"{i + 1}...")    
        with open(f"file/in/input{i + 1}.txt", "w") as f:
            f.write(f"{lengths[i]}\n")
            for length in range(lengths[i]):
                f.write(f"{randint(MIN, MAX)} ")
            f.write("\n")

    print("Finished generating!")
