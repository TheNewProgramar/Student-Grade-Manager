# 📚 Learning Goals

This project demonstrates:

  - Structs in C
  - Dynamic memory allocation (malloc, realloc, free)
  - File I/O (fopen, fprintf, fgets)
  - String parsing (strtok, strcpy, strcspn)
  - Authentication systems
  - Random number generation
  - Menu-driven programming
----------------------------------------
# 📚 Student Grade Manager

A command-line student management system written in C with admin authentication and student login.

## ✨ Features

### 🔐 Authentication
- ✅ Admin login with username and password
- ✅ Student login using unique student ID

### 👨‍🎓 Student Management
- ✅ Add students with name, class, subject, and grade
- ✅ Auto-generate unique 5-digit student ID
- ✅ View all students
- ✅ Calculate average grade

### 💾 Data Persistence
- ✅ Save students to file
- ✅ Load students from file
- ✅ Data survives between sessions

### 🔢 GPA Calculation
- ✅ Automatic GPA calculation (Grade / 25)
- ✅ 100 = 4.0 GPA scale

## 🛠️ Planned Features

- [ ] Edit student records
- [ ] Delete students
- [ ] Sort by grade or name
- [ ] Change admin password
- [ ] Export to CSV

## 📋 Default Admin Credentials
```text
Username: admin
Password: admin123
```

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
# welcome menu:
```text
===== WELCOME =====
1. Admin Login
2. Student Login
3. Exit
====================
```
📁 File Format

Students are saved in students.txt:

Name|Class|Subject|Grade|GPA
