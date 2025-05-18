# Smart-Library-Management-System
A simple and smart Library Management System built using C++. It lets students register, borrow and return books, view their history, and even get book recommendations based on genre. All features are built using core data structures like stacks, queues, graphs, and hash maps. Perfect project to learn how DSA can be used in real-world applications.

A C++ console-based **Library Management System** built entirely using **Data Structures and Algorithms (DSA)**. It supports book inventory, student registration, borrowing/returning books, and even a **graph-based recommendation system**.

---

## ✨ Features

🔹 **Book Management**
- Add, display, and search books by title.
- Track book quantity, genre, author, and rating.

🔹 **Student Management**
- Register students with name and ID.
- Track borrowed books per student.

🔹 **Borrow & Return System**
- Borrow books (only if in stock).
- Return books and update inventory.
- Maintain a **stack-based borrow history**.

🔹 **Graph-Based Recommendations**
- Recommend similar books by genre using **BFS traversal** on an undirected graph.

---

## 🔧 Technologies Used

- Language: **C++**
- Concepts:  
  - `unordered_map` (Hash Maps)  
  - `stack` (Borrow history)  
  - `queue` (BFS recommendation)  
  - `vector` (Student and book lists)  
  - `set` (Visited set in graph traversal)

---

## 🧠 How It Works

1. 📚 **Book Addition**:
   - When a book is added, it is linked to others with the same genre to form a **graph**.

2. 👩‍🎓 **Student Registration**:
   - Each student is tracked by ID and has a personal list of borrowed books.

3. 🔁 **Borrow/Return Books**:
   - Borrowing decreases quantity.
   - Returns increase it.
   - All borrows are stored in a `stack` to maintain history (LIFO).

4. 🤝 **Recommendations**:
   - Given a book ID, the system searches its neighbors in the graph and suggests similar genre books using **Breadth-First Search**.

---

## 🧪 Sample Operations

```bash
1. Add Book
2. Show All Books
3. Search Book by Title
4. Register Student
5. Borrow Book
6. Return Book
7. View Borrow History
8. Recommend Books
```

---

## 📁 File Structure

```
📦 LibraryManagementDSA/
 ┣ 📄 main.cpp        -> Main C++ file with all logic
 ┗ 📄 README.md       -> This file
```

---

## 📌 How to Run

```bash
g++ main.cpp -o library
./library
```

---

## ✅ Future Enhancements

- Save/load data from file (persistence).
- GUI using C++ libraries like Qt or switch to web interface.
- Add login system for students.
- Set borrowing limits and due dates.



