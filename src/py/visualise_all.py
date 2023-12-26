import matplotlib.pyplot as plt
from generate import nums, generate_length_list


sequential = []
recursive = []
alt = []

with open(f"file/out/measures.txt", "r") as f:
    lines = f.readlines()
    lines = [int(i) for i in lines]
    n = lines[0]
    n_files = n * len(nums)
    
    sequential = lines[1:1 + n_files]
    recursive = lines[1 + n_files:1 + 2*n_files]
    alt = lines[1 + 2*n_files:]


array_lengths = generate_length_list(n, nums)

plt.plot(array_lengths, sequential, label="Sequential", marker=".")
plt.plot(array_lengths, recursive, label="Parallel Recursive", marker=".")
plt.plot(array_lengths, alt, label="Parallel Alternative", marker=".")
plt.xlabel("Array length")
plt.ylabel("Time, nanoseconds")
plt.title("Prefix sum computation time")
# plt.xscale("log")
# plt.yscale("log")
plt.legend()
plt.show()
