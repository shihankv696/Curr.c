# Curr.c - Lightweight Modular Data Structures in C


**Curr.c** is a lightweight, modular data structure framework written in C.  
It offers reusable implementations of essential data structures along with custom memory management using `dmalloc`, `dcalloc`, `drealloc`, and `dfree`.

> Ideal for:  
> 🧠 Learning C fundamentals  
> 💡 Teaching data structures  
> 🏗️ Embedding efficient structures in C projects

---

## 🚀 Features

- ✅ Custom memory allocation layer (for learning or debugging memory)
- ✅ Modular C structure (separated `src/`, `include/`, `test/`, etc.)
- ✅ Reusable & clean APIs
- ✅ Fully tested with sample test programs
- ✅ Cross-platform support

Supported Structures:
- [x] Linked List  
- [x] Stack  
- [x] Queue  
- [x] Hash Map  
- [x] Binary Search Tree (BST)  

---

## 📦 Installation

### ⚙️ 1. Install using `install.sh` (Linux/macOS)

```bash
git clone https://github.com/shihankv696/Curr.c.git
cd Curr.c
chmod +x install.sh
./install.sh


🪟 2. Install using install.bat (Windows)

git clone https://github.com/shihankv696/Curr.c.git
cd Curr.c
install.bat


🔧 3. Build Manually with Makefile

make all
./bin/test_data_structures.exe


🗂 Directory Structure

Curr.c/
│
├── bin/                  # Compiled binaries
├── include/              # Header files
├── lib/                  # Shared libraries (DLL/.so/.a)
├── src/                  # Source code (memory + program)
├── test/                 # Unit tests
├── currc_package/        # NuGet-like distributable
├── install.sh            # Linux/macOS installer
├── install.bat           # Windows installer
├── Makefile              # Build script
├── LICENSE
└── README.md

🧑‍💻 Contributing
Contributions are welcome!
Please fork this repository, make your changes, and submit a pull request.

You can also:

Report bugs or issues

Suggest new data structures

Improve tests and memory management

📬 Contact
Maintained by shihankv696
Feel free to open an issue for bugs or feature requests.

🙋 Get in Touch
Have suggestions, improvements, or just want to say hi?
Connect with me on LinkedIn: https://www.linkedin.com/in/shihan-kv-945ab0288/
Let’s collaborate on something awesome! 🚀

