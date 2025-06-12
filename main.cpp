#include <iostream>

const int SUBJECTS = 3;  // Number of subjects
const int QUARTERS = 4;  // Number of quarters

struct Student {
    std::string name;
    int **grades;

    Student () {
        grades = new int* [SUBJECTS];
        for (int i = 0; i < SUBJECTS; i++) {
            grades[i] = new int[QUARTERS];
            for (int j = 0; j < QUARTERS; j++) {
                grades[i][j] = 0;
            }
        }
    }

    ~Student () {
        for (int i = 0; i < SUBJECTS; i++) {
            delete[] grades[i];
        }
        delete[] grades;
    }
};

// Function declarations
void addStudent(Student*& students, int& count, int& capacity);
void addGrade(Student*& students, int& count);
void printStudents(Student* students, int count);
void clearStudents(Student*& students, int count);

int main () {
    const int initialCapacity = 2;
    int studentCount = 0;
    int capacity = initialCapacity;
    Student* students = new Student[capacity];

    int choice;
    do {
        std::cout << "\nMenu:\n"
                  << "1. Add student\n"
                  << "2. Add grade\n"
                  << "3. Show students list\n"
                  << "4. Exit\n"
                  << "Select action: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addStudent(students, studentCount, capacity);
                break;
            case 2:
                addGrade(students, studentCount);
                break;
            case 3:
                printStudents(students, studentCount);
                break;
            case 4:
                std::cout << "Exiting the program...\n";
                break;
            default:
                std::cout << "Incorrect selection. Try again.\n";
        }
    } while (choice != 4);

    clearStudents(students, studentCount); // Free allocated memory
    return 0;
}

// Adds a new student to the list
void addStudent(Student*& students, int& count, int& capacity ) {
    if (count >= capacity) {
        capacity *= 2;
        Student* temp = new Student[capacity];
        for (int i = 0; i < count; i++) {
            temp[i] = students[i];
        }
        delete[] students;
        students = temp;
    }

    std::cout << "Enter student name: ";
    std::cin >> std::ws;
    getline(std::cin, students[count].name);

    count++;
    std::cout << "Student added.\n";
}

// Adds a grade to selected student
void addGrade(Student*& students, int& count) {
    if (count == 0) {
        std::cout << "There are no students to add a grade to.\n";
        return;
    }

    std::cout << "Select student (number):\n";
    for (int i = 0; i < count; i++)
        std::cout << i + 1 << ". " << students[i].name << std::endl;

    int studentIndex;
    std::cin >> studentIndex;
    if (studentIndex < 1 || studentIndex > count) {
        std::cout << "Invalid student number.\n";
        return;
    }

    Student& s = students[studentIndex - 1];
    int subject, quarter, grade;
    std::cout << "Enter the subject number (1-" << SUBJECTS << "):";
    std::cin >> subject;
    std::cout << "Enter the grade (1-" << QUARTERS << "):";
    std::cin >> quarter;
    std::cout << "Enter rating (0-5):";
    std::cin >> grade;

    if (subject < 1 || subject > SUBJECTS || quarter < 1 || quarter > QUARTERS || grade < 0 || grade > 5) {
        std::cout << "Incorrect data.\n";
        return;
    }

    s.grades [subject - 1] [quarter - 1] = grade;
    std::cout << "Rating added.\n";
}

// Prints all students and their grades
void printStudents(Student* students, int count) {
    if (count == 0) {
        std::cout << "There are no students.\n";
        return;
    }
    for (int i = 0; i < count; i++) {
        std::cout << "Student: " << students[i].name << std::endl;
        std::cout << "Grades: \n";
        for (int sub = 0; sub < SUBJECTS; sub++) {
            std::cout << "Subject: " << sub + 1 << ": ";
            for (int q = 0; q < QUARTERS; q++)
                std::cout << students[i].grades[sub][q] << " ";
            std::cout << std::endl;
        }
    }
}

// Frees all dynamically allocated memory
void clearStudents(Student*& students, int count) {
    delete[] students;
    students = nullptr;
}