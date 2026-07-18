# 🌌 Star & Exoplanet Catalog

A command-line Star & Exoplanet Catalog written in C using a Binary Search Tree (BST). The project stores celestial objects sorted by their distance from Earth and demonstrates fundamental data structure concepts including insertion, searching, traversal, deletion, and file persistence.

## ✨ Features

- Add new celestial objects
- Search by exact distance
- Search objects within a distance range
- Display objects using Inorder Traversal (sorted by distance)
- Display objects using Level Order Traversal (Breadth-First Search)
- Delete an object by name + distance
- Load catalog data from a CSV file
- Save the current catalog to a CSV file
- Handle duplicate distances using the object name as a tie-breaker

## 🛠 Technologies

- C
- Binary Search Tree (BST)
- Queue (for Level Order Traversal)
- File I/O
- CSV Parsing (`sscanf` / `fprintf`)
- Makefile
- Python (data preprocessing with pandas)

## 📂 Project Structure

```
star-catalog/
├── data/
│   ├── raw/
│   └── processed/
├── src/
│   ├── helper.c
│   └── star-catalog.c
├── include/
│   └── helper.h
├── scripts/
│   └── clean_data.py
├── makefile
└── README.md
```

## 📊 Dataset

The catalog uses real exoplanet data from NASA's Exoplanet Archive. A preprocessing script (`clean_data.py`) cleans the dataset by:

- Selecting relevant columns
- Removing rows with missing distance values
- Converting distance from parsecs to light-years
- Renaming columns for clarity
- Sorting by distance
- Exporting the cleaned CSV used by the C application

## 🚀 Build

```bash
make
```

Run:

```bash
make run
```

## 📋 Menu

```
1. Add object
2. Search by exact distance
3. Display all (Inorder)
4. Display level order
5. Search by distance range
6. Delete object
7. Save to CSV
8. Load from CSV
9. Exit
```

## 🌳 BST Ordering

The Binary Search Tree is ordered by:

1. Distance from Earth (`distance_ly`)
2. Object name (used as a tie-breaker when distances are equal)

This allows multiple celestial objects to exist at the same distance while maintaining BST properties (e.g. Sirius A and Sirius B, or Proxima Centauri and Proxima Centauri b).

## 📖 Concepts Practiced

- Dynamic memory allocation
- Structures
- Recursive algorithms
- Binary Search Trees
- Queue implementation
- Breadth-First Search (BFS)
- File handling
- CSV parsing
- Data persistence
- Pointer manipulation (including double pointers)

## ⚠️ Known Limitations

- Distance comparisons use exact float equality (`==`), which can be unreliable for values read from files or computed at runtime
- No balancing (e.g. AVL/Red-Black), so a sorted or near-sorted input CSV can degrade the tree toward a linked list
- Search by name alone is not currently supported — searches and deletes require a distance

## 📌 Future Improvements

- AVL tree balancing
- Edit existing objects
- Tolerance-based floating-point comparison instead of exact equality
- Search by object name
- Export search results to a separate file
- Performance statistics (tree height, node count, etc.)
- Unit tests

## 📄 License

This project is intended for educational and learning purposes. No formal license has been applied.
