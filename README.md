# 📚 Learning Goals

This project is for learning:

  - Structs in C
  - Dynamic memory allocation
  - File I/O
  - String manipulation
  - Modular programming
----------------------------------------

# 📚 Student Grade Manager

A simple command-line program written in C to manage student grades.

## ✨ Features

- ✅ Add students with name, class, subject, and grade
- ✅ View all students
- ✅ Calculate average grade
- ✅ Save students to file
- ✅ Load students from file
- ✅ Dynamic memory allocation (unlimited students)

## 🛠️ Planned Features

- [ ] Edit existing student records
- [ ] Delete students
- [ ] Sort by grade or name
- [ ] Export to CSV

## 📋 Requirements

- GCC compiler
- Linux/Unix or Windows

## 🚀 How to Compile

```bash
gcc -Wall -Wextra -o student_manager main.c
```

🏃 How to Run
```bash
./student_manager
```
📝 Usage:
```text
==== STUDENT GRADE MANAGER ====
1. Add Student
2. View Students
3. Calculate Average
4. Save to File
5. Load from File
6. Exit
===============================

📁 File Format

Students are saved in students.txt:

Name|Class|Subject|Grade|GPA
