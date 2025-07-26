# Bank Management System using SQLite

A command-line based **Bank Management System** written in C using **SQLite** as the backend database. This project demonstrates how to manage bank accounts using CRUD operations integrated with `sqlite3` in C.

---

## 🚀 Features

* Create new account
* View account details
* Deposit money
* Withdraw money
* Update account holder's name
* Delete account
* View all accounts

---

## 🛠️ Tech Stack

* **Language:** C
* **Database:** SQLite
* **Compiler:** GCC (MinGW or Linux GCC)
* **IDE:** VS Code / CodeBlocks / Any C IDE

---

## 📁 Project Structure

```bash
bank-management-system-sqlite/
├── bank_management.c          # Main source code file
├── sqlite3.c                  # SQLite amalgamation file
├── sqlite3.h                  # SQLite header file
├── bankapp.exe                # Compiled executable (Windows)
└── README.md                  # Project documentation
```

---

## ⚙️ How to Compile and Run

### 🧱 Prerequisites:

* `gcc` compiler installed
* `sqlite3.c` and `sqlite3.h` files present in the project directory

### 🔨 Compile:

```bash
gcc bank_management.c sqlite3.c -o bankapp.exe
```

### ▶️ Run:

```bash
./bankapp.exe   # On Windows
./bankapp       # On Linux/Mac after changing output name
```

---

## 📌 Notes

* All database operations are handled through `sqlite3` API.
* Ensure the SQLite database file is created properly on first run.
* Modular design kept in a single `.c` file for simplicity. You can split into multiple files as a learning upgrade.

---

## 📚 Learning Outcomes

* How to integrate SQLite with C
* Perform parameterized queries using `sqlite3_prepare_v2`, `sqlite3_bind_*`, and `sqlite3_step`
* Practice replacing file I/O logic with relational database logic

---

## 🧑‍💻 Author

**Harshit Yadav**
BCA Cybersecurity Student | Manav Rachna, Faridabad
📫 [official.harshit@outlook.com](mailto:official.harshit@outlook.com)

GitHub: [@Harshit4847](https://github.com/Harshit4847)

---

## 📃 License

This project is open-source and free to use for educational purposes.

---

## ✅ TODO (Future Enhancements)

* Add password-protected admin login
* Implement transaction history logs
* Separate logic into multiple files (Modularize code)
* GUI version using C++/Java
* Dockerize the SQLite setup

---
