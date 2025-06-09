# 🎓 Student Grades Sorting and Analysis System

A simple and interactive C program for managing, sorting, and analyzing student scores — complete with grading, academic warnings, and detailed statistics. 
(⚠️This program was made with Indonesia language, to avoid confusion please use translator).

---

## 📌 Project Overview

This project is a **console-based application** written in C language and has a purpose to able helps users (for a teachers, assistants, or students) to:

- Input student names and scores
- Automatically assign letter grades (A+ to E)
- Sort scores from highest to lowest
- Display detailed score statistics
- Provide academic warnings for failing students (Grade E)
- Use colored output for a friendly CLI experience (ANSI Escape Codes)

---

## 🛠 Features

- ✅ Score input with validation
- ✅ Letter grade calculation
- ✅ Bubble sort algorithm (descending order)
- ✅ Highlight students with failing grades
- ✅ Grade distribution summary
- ✅ Interactive CLI with color formatting
- ✅ Option to restart or exit the program

---

## ⚠️ Important!

Make sure the program is runs in a **terminal like Ubuntu**'s (*or other ANSI-compatible terminals*) because it uses *ANSI Escape Codes to display colored and formatted text output* 🟥🟩🟦🟨. Here's an example image of **WSL** in **🪟Windows** Terminal:

![Image](https://github.com/user-attachments/assets/c3140069-5c30-4b23-be3c-3e5306d07ab7)

---

## 🧠 Algorithms Used

#### 1. 🔁 Bubble Sort (Descending Order)

This function used to sort student scores in descending order.

```c
for (int i = 0; i < jumlah - 1; i++) {
    for (int j = 0; j < jumlah - i - 1; j++) {
        if (mahasiswa[j].nilai < mahasiswa[j + 1].nilai) {
            // Swap students
        }
    }
}
```

#### 2. 🏷️ Grade Mapping

This function has a purpose to maps numerical scores into standard letter grades (*A+, A, ..., E*).

```c
if (nilai >= 95.0) return "A+";
else if (nilai >= 90.0) return "A";
// ...
else return "E";
```

---

## Key Features of the Program

- Interactive and beginner-friendly interface
- Strong input validation to avoid incorrect entries
- Visually appealing output using colored text
- Displays detailed statistics:
- Highest and lowest score
- Average score
- Number of students per grade
- Academic warning alert for students who receive E

---

## ❌ Weaknesses of the Program

- Uses **Bubble Sort**, whic is inefficient for large datasets (O(n²) complexity)
- No file saving feature, meaning all data will be lost once the program is closed
- No search or data editing features
- Text-based only, no graphical interface/no GUI interface.

Based on the weaknesses mentioned above, I believe I can still improve this program by adding more useful features.

---

## 💡  Why I Created This Program

I developed this program because I wanted to create a simple tool that would help teachers, lecturers, or teaching assistants manage student grades more easily.

---

## Program Execution

![Image](https://github.com/user-attachments/assets/acd8b0b8-0104-4a5e-9ef1-612f61fcecca)

# 

The total number of students you can input must be at least 3 and at most 100. Also, this total should be an integer (INT).

As you can see, when I tried entering a student's name as a number, it was rejected ❌. Likewise, entering a student grade as text (varchar) is also not allowed. The names should be VARCHAR (text), and the grades should be INT (numbers).

# 🧑‍💻 Code Programs:

If you want to try out the programs or have any ideas to improve them, here’s the link to the code above in the same repository:

<a href="https://github.com/RockHead07/Student-Grade-Analyzer-lang_id-with-C-language/blob/main/Grade-Analyzer.c" 
   style="display: inline-block; background-color: #2d89ef; color: white; padding: 8px 16px; text-align: center; 
          border-radius: 5px; text-decoration: none; font-weight: bold;">
   View Grade-Analyzer.c on GitHub
</a>

#

P.S. I promise to add English versions of these programs in the future

