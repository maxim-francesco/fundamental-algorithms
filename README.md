# Fundamental Algorithms – Assignment Collection with Performance Analysis

This repository contains all algorithm assignments for the **Fundamental Algorithms** course taken at the Technical University of Cluj-Napoca, Computer Science department. Each assignment explores a classical algorithm or data structure and includes **both implementation and performance analysis**.

To benchmark and compare the algorithms, a custom **Profiler** library is used. It measures operation counts and execution time, allowing empirical evaluation of algorithmic complexity and optimizations.

---

## 📘 Assignments Overview

| No. | Title | Description |
|-----|-------|-------------|
| 1 | **Direct Sorting Methods** | Comparison of Bubble Sort, Insertion Sort, and Selection Sort on sorted, reverse, and random data |
| 2 | **Heap Build Approaches** | Bottom-up vs Top-down heap construction – complexity and speed comparison |
| 3 | **Advanced Sorting** | Heapsort, Quicksort, and QuickSelect – hybrid techniques and performance on various inputs |
| 4 | **Merge K Ordered Lists** | Efficiently merging k sorted lists using heap-based strategies |
| 5 | **Hash Tables** | Open addressing with quadratic probing – implementation and search analysis |
| 6 | **Multi-way Trees** | Transformations between different tree representations (parent arrays, edge lists, etc.) |
| 7 | **Dynamic Order Statistics** | Select the i-th smallest element dynamically in augmented BSTs |
| 8 | **Hybrid Quicksort & Tree Traversal** | Recursive vs iterative traversal in binary trees + hybrid Quicksort with insertion sort threshold |
| 9 | **Disjoint Sets (DSU)** | Union-Find with and without optimizations (path compression, union by rank) |
| 10 | **Breadth-First Search (BFS)** | Graph traversal and shortest path on unweighted graphs |
| 11 | **Depth-First Search (DFS)** | Iterative and recursive DFS, connected components, and traversal applications |

---

## ⚙️ Profiler Library

The `Profiler` is a custom-made C++ utility used throughout all assignments to measure:

- **Execution time**
- **Number of key operations** (comparisons, assignments, swaps, etc.)
- **Scalability on varying input sizes**

You can find the Profiler in the `/Profiler` folder. It can be reused across all experiments to generate comparable results.

---

## 🛠️ Technologies

- Language: **C / C++**
- IDEs: Visual Studio / CLion / Code::Blocks
- Performance tools: Custom Profiler (based on `QueryPerformanceCounter` or similar timing APIs)
- Topics: Sorting, trees, hashing, graph traversal, DSU, etc.

---

## 🚀 How to Run

1. Clone the repository:
```bash
git clone https://github.com/maxim-francesco/fundamental-algorithms.git
```

2. Compile and run a specific assignment:
```bash
g++ assignment-01/main.cpp -o assignment1
./assignment1
```

2. Output will include performance metrics printed to the console (or optionally saved as files).
