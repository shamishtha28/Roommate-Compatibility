#include <cmath>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Stores the lifestyle preferences of a student
class Preferences {
private:
    int sleepSchedule;
    int studyHabit;
    int cleanliness;
    int noiseTolerance;
    int visitorFrequency;

public:
    Preferences(int sleep, int study, int clean,
                int noise, int visitors) {
        sleepSchedule = sleep;
        studyHabit = study;
        cleanliness = clean;
        noiseTolerance = noise;
        visitorFrequency = visitors;
    }

    int getSleep() const {
        return sleepSchedule;
    }

    int getStudy() const {
        return studyHabit;
    }

    int getCleanliness() const {
        return cleanliness;
    }

    int getNoise() const {
        return noiseTolerance;
    }

    int getVisitors() const {
        return visitorFrequency;
    }
};

// Stores student information

class Student {
private:
    int studentID;
    string name;
    Preferences preferences;

public:
    // Constructor
    Student(int id, string studentName, Preferences p)
        : studentID(id), name(studentName), preferences(p) {
    }

    // Getter for name
    string getName() const {
        return name;
    }

    // Getter for preferences
    Preferences getPreferences() const {
        return preferences;
    }
    static int getValidInput(string message, int min, int max) {
    int value;

    while (true) {
        cout << message;
        cin >> value;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Please enter a number.\n";
        }
        else if (value < min || value > max) {
            cout << "Invalid choice! Enter a value between "
                 << min << " and " << max << ".\n";
        }
        else {
            return value;
        }
    }
}
    // Function to take student input
    static Student inputStudent(int id) {
        string name;
        int sleep, study, clean, noise, visitors;

        cout << "\nEnter student name: ";
        getline(cin >> ws, name);

        sleep = getValidInput(
    "Sleep schedule (1-Early, 2-Normal, 3-Late): ", 1, 3);

        study = getValidInput(
    "Study habit (1-Silence, 2-Music): ", 1, 2);

        clean = getValidInput(
    "Cleanliness (1-Relaxed, 2-Moderate, 3-Very clean): ", 1, 3);

        noise = getValidInput(
    "Noise tolerance (1-Low, 2-Medium, 3-High): ", 1, 3);

        visitors = getValidInput(
    "Visitors (1-Rarely, 2-Sometimes, 3-Often): ", 1, 3);

        Preferences p(sleep, study, clean, noise, visitors);

        return Student(id, name, p);
    }
};


// Calculates compatibility between two students
class CompatibilityEngine {
public:

    static double compare(int a, int b, double weight) {
        int difference = abs(a - b);

        if (difference == 0)
            return weight;
        else if (difference == 1)
            return weight * 0.5;
        else
            return 0;
    }

    static double calculateScore(Student s1, Student s2) {
        Preferences p1 = s1.getPreferences();
        Preferences p2 = s2.getPreferences();

        double score = 0;

        score += compare(p1.getSleep(), p2.getSleep(), 30);
        score += compare(p1.getStudy(), p2.getStudy(), 25);
        score += compare(p1.getCleanliness(), p2.getCleanliness(), 20);
        score += compare(p1.getNoise(), p2.getNoise(), 15);
        score += compare(p1.getVisitors(), p2.getVisitors(), 10);

        return score;
    }
    static void displayCategoryScores(Student s1, Student s2) {
    Preferences p1 = s1.getPreferences();
    Preferences p2 = s2.getPreferences();

    cout << "\n===== CATEGORY-WISE COMPATIBILITY =====" << endl;

    cout << "Sleep Schedule: "
         << compare(p1.getSleep(), p2.getSleep(), 100) << "%" << endl;

    cout << "Study Habit: "
         << compare(p1.getStudy(), p2.getStudy(), 100) << "%" << endl;

    cout << "Cleanliness: "
         << compare(p1.getCleanliness(), p2.getCleanliness(), 100) << "%" << endl;

    cout << "Noise Tolerance: "
         << compare(p1.getNoise(), p2.getNoise(), 100) << "%" << endl;

    cout << "Visitor Frequency: "
         << compare(p1.getVisitors(), p2.getVisitors(), 100) << "%" << endl;
}
};

class ConflictDetector {
public:

    static void detectConflicts(Student s1, Student s2) {

        Preferences p1 = s1.getPreferences();
        Preferences p2 = s2.getPreferences();

        cout << "\n===== CONFLICT REPORT =====" << endl;

        bool conflictFound = false;

        if (p1.getSleep() != p2.getSleep()) {
    cout << "\nConflict: Different sleep schedules";
    cout << "\nSuggestion: Establish quiet hours at night "
         << "and respect each other's sleep routines.";
    conflictFound = true;
}

        if (p1.getStudy() != p2.getStudy()) {
    cout << "\nConflict: Different study preferences";
    cout << "\nSuggestion: Set designated silent study hours "
         << "and use headphones when listening to music.";
    conflictFound = true;
}

        if (p1.getCleanliness() != p2.getCleanliness()) {
    cout << "\nConflict: Different cleanliness preferences";
    cout << "\nSuggestion: Divide cleaning responsibilities "
         << "and create a weekly cleaning schedule.";
    conflictFound = true;
}

        if (p1.getNoise() != p2.getNoise()) {
    cout << "\nConflict: Different noise tolerance";
    cout << "\nSuggestion: Set acceptable noise levels "
         << "and use headphones when needed.";
    conflictFound = true;
}

        if (p1.getVisitors() != p2.getVisitors()) {
    cout << "\nConflict: Different visitor preferences";
    cout << "\nSuggestion: Discuss visitor limits, timings "
         << "and give each other advance notice.";
    conflictFound = true;
}

        if (!conflictFound) {
            cout << "\nNo major preference differences found!";
        }

        cout << endl;
    }
};
class FileManager {
public:
    static void saveStudent(Student s) {
        ofstream file("roomsync_data.txt", ios::app);

        if (!file) {
            cout << "Error: Could not open file!" << endl;
            return;
        }

        Preferences p = s.getPreferences();

        file << "Student Name: " << s.getName() << endl;
        file << "Sleep Schedule: " << p.getSleep() << endl;
        file << "Study Habit: " << p.getStudy() << endl;
        file << "Cleanliness: " << p.getCleanliness() << endl;
        file << "Noise Tolerance: " << p.getNoise() << endl;
        file << "Visitor Frequency: " << p.getVisitors() << endl;
        file << "-----------------------------" << endl;

        file.close();

        cout << s.getName() << "'s data saved successfully!" << endl;
    }
    static void viewSavedStudents() {
    ifstream file("roomsync_data.txt");

    if (!file) {
        cout << "\nNo saved student records found!" << endl;
        return;
    }

    string line;
    bool hasRecords = false;

    cout << "\n===== SAVED STUDENT RECORDS =====" << endl;

    while (getline(file, line)) {
        cout << line << endl;
        hasRecords = true;
    }

    if (!hasRecords) {
        cout << "No student records available." << endl;
    }

    file.close();
}
};
    int main() {

    cout << "===== ROOMSYNC =====" << endl;

    Student s1 = Student::inputStudent(101);
    Student s2 = Student::inputStudent(102);
    cout << "\n===== SAVING STUDENT DATA =====" << endl;

FileManager::saveStudent(s1);
FileManager::saveStudent(s2);
FileManager::viewSavedStudents();
    double score =
        CompatibilityEngine::calculateScore(s1, s2);

    cout << "\n===== MATCHING RESULTS =====" << endl;

    cout << "Student 1: " << s1.getName() << endl;
    cout << "Student 2: " << s2.getName() << endl;

    cout << "Compatibility Score: "
         << score << "%" << endl;
    CompatibilityEngine::displayCategoryScores(s1, s2);
    ConflictDetector::detectConflicts(s1, s2);

    return 0;
}




