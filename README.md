# Curr.c - Modular C Data Structures Framework

🚀 A lightweight and modular Data Structures Framework in C, designed to provide reusable implementations of core data structures with **custom memory management** support.

## 🧠 Features

- ✅ Linked List
- ✅ Stack
- ✅ Queue
- ✅ Binary Search Tree
- ✅ Hash Map
- ✅ Custom Dynamic Memory Allocation (dmalloc, dcalloc, drealloc, dfree)

---

Curr.c/
├── include/ # Public headers
├── src/ # Data structure implementations
│ └── memory/ # Custom memory allocation modules
├── test/ # Unit test files
├── bin/ # Output binaries
├── Makefile # Build configuration
├── README.md # Project documentation
└── LICENSE # Open-source license (MIT)

## 🛠️ Build Instructions

### 1. Clone the Repository

```bash
git clone https://github.com/shihankv696/Curr.c.git
cd Curr.c

 Run Tests
bash
Copy code
./bin/test_data_structures.exe
yaml
Copy code



---

### 3. 📦 **Installation (Optional)**

If you support system-wide installation:

```markdown
## 📦 Install as a Library

```bash
sudo make install

## 💡 Quick Example

```c
#include "queue.h"

int main() {
    Queue *q = queue();
    enqueue(q, "Data 1");
    enqueue(q, "Data 2");

    printf("%s\n", (char *)dequeue(q));  // Output: Data 1
}



---

### 5. 🤝 **Contributing Guidelines**

Encourage contributions:

```markdown
## 🤝 Contributing

Want to improve this project?

- Fork the repo
- Create a new branch (`git checkout -b feature`)
- Make changes and commit
- Push to your fork and submit a Pull Request

Feel free to open Issues for bugs, ideas or questions!
