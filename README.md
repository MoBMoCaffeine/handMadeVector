"# handMadeVector" 
# Vec<T> – Custom C++ Vector Implementation

This project provides a **template-based dynamic array class** (`Vec<T>`) implemented in C++.  
It mimics some of the functionality of `std::vector`, with additional features like built-in merge sort and custom merging.

---

## ✨ Features

- Dynamic resizing (automatic capacity growth).
- Copy constructor, copy assignment, move constructor, and move assignment.
- Element access (`operator[]`, `front()`, `back()`).
- Modifiers:
  - `push_back()`
  - `pop_back()`
  - `insert()`
  - `resize()`
  - `clear()`
- Iterators: `begin()`, `end()`.
- Sorting using **merge sort** (`sort()`).
- Merge two vectors with automatic sorting (`merge()`).
- Utility functions: `size()`, `empty()`, `swap()`.

---

## 📂 File Structure

- `handmadeVector.cpp` → Contains the `Vec<T>` class implementation.
- `README.md` → Project documentation.

---

## 🔧 Requirements

- C++11 or later
- A compiler such as `g++`, `clang`, or MSVC

---

## 🚀 How to Compile and Run

```bash
g++ handmadeVector.cpp -o vectorApp
./vectorApp
```

## example 
```
#include <iostream>
#include "handmadeVector.cpp"

int main() {
    Vec<int> v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(5);

    std::cout << "Size: " << v.size() << std::endl;   // Size: 3
    std::cout << "Front: " << v.front() << std::endl; // Front: 10
    std::cout << "Back: " << v.back() << std::endl;   // Back: 5

    v.sort(); // sort using merge sort
    for (auto &x : v) std::cout << x << " "; // 5 10 20

    return 0;
}
```