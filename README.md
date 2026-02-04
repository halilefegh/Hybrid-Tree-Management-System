# Artifact Management System (AVL & Red-Black Tree Implementation)

A high-performance C++ management system designed to handle complex data relations between historical artifacts and researchers using strictly balanced tree structures. This project focuses on efficient data retrieval, memory management, and advanced algorithmic complexity.

## 🧠 Technical Architecture

This system is built upon two primary custom-implemented data structures to ensure $O(\log n)$ operational complexity:

- **AVL Tree (Artifact Storage):** Manages artifact records (ID, rarity, value) with strict height balancing. Implements specialized rotations (LL, RR, LR, RL) to maintain performance during frequent insertions and removals.
- **Red-Black Tree (Researcher Management):** Handles researcher data using a balanced BST with color-coding properties (Red/Black) to ensure efficient hiring/firing operations and load balancing.

## 🚀 Key Features

- **Dynamic Resource Allocation:** Match artifacts with researchers based on capacity and rarity levels.
- **Complexity Focus:** All search, insert, and delete operations are guaranteed $O(\log n)$.
- **Memory Safety:** Implemented with custom destructors and the **Rule of Three** to prevent memory leaks in a pointer-heavy environment.
- **Command-Line Interface:** Supports complex commands like `MATCH_RARITY`, `EXPORT_STATS`, and `RECURSIVE_RETURN_ALL`.

## 🛠 Tech Stack & Tools

- **Language:** C++ (Standard 11/14)
- **Data Structures:** AVL Tree, Red-Black Tree, Dynamic Arrays.
- **Memory Management:** Valgrind-tested pointer logic.

## 📁 Project Structure

- `AVLTree.cpp/h`: Core AVL logic and balancing rotations.
- `RedBlackTree.cpp/h`: Red-Black Tree implementation with fix-up algorithms.
- `ArtifactManager.cpp/h`: The controller class that parses commands and manages tree interactions.
- `Researcher.cpp/h`: Handles dynamic memory for artifact assignments per researcher.

## 📊 Performance Analysis
- **Insertion:** $O(\log n)$
- **Deletion:** $O(\log n)$
- **Search:** $O(\log n)$
- **Space Complexity:** $O(n)$ where $n$ is the number of artifacts/researchers.

---
Developed by **Halil Efe Güzelimdağ**