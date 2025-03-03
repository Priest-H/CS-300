//============================================================================
// Name        : Project2.cpp
// Author      : Harmony Priest
// Version     : 1.0
// Copyright   : Copyright � 2023 SNHU COCE
// Description : Project 2 CS 300
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// course struct
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// node struct
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(Course c) : course(c), left(nullptr), right(nullptr) {}
};

//binary search tree
class CourseBST {
private:
    Node* root;
    // inserting into Binary Search tree
    Node* insert(Node* node, Course course) {
        if (node == nullptr) return new Node(course);
        if (course.courseNumber < node->course.courseNumber)
            node->left = insert(node->left, course);
        else
            node->right = insert(node->right, course);
        return node;
    }
    // in-order traversal
    void inOrder(Node* node) const {
        if (node == nullptr) return;
        inOrder(node->left);
        cout << node->course.courseNumber << ", " << node->course.courseTitle << endl;
        inOrder(node->right);
    }
    //Find a course 
    Node* search(Node* node, const string& courseNumber) const {
        if (node == nullptr || node->course.courseNumber == courseNumber)
            return node;
        if (courseNumber < node->course.courseNumber)
            return search(node->left, courseNumber);
        return search(node->right, courseNumber);
    }

public:
    CourseBST() : root(nullptr) {}

    void insert(Course course) {
        root = insert(root, course);
    }

    void printCourseList() const {
        if (root == nullptr) {
            cout << "No courses available. Load data first." << endl;
        }
        else {
            cout << "Here is a sample schedule:" << endl;
            inOrder(root);
        }
    }
    void printCourseInfo(const string& courseNumber) const {
        Node* node = search(root, courseNumber);
        if (node) {
            cout << node->course.courseNumber << ", " << node->course.courseTitle << endl;
            if (!node->course.prerequisites.empty()) {
                cout << "Prerequisites: ";
                for (size_t i = 0; i < node->course.prerequisites.size(); ++i) {
                    cout << node->course.prerequisites[i];
                    if (i < node->course.prerequisites.size() - 1) cout << ", ";
                }
                cout << endl;
            }
            else {
                cout << "Prerequesites : none" << endl;
            }
        }
        else {
            cout << "not found" << endl;
        }
    }
};
// load the courses from csv file split with commas
void loadCourses(CourseBST& bst) {
    string filename = "CS 300 ABCU_Advising_Program_Input.csv";
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream coursesstring(line);
        string courseNumber, courseTitle, prereq;
        vector<string> prerequisites;

        getline(coursesstring,courseNumber, ',');
        getline(coursesstring,courseTitle, ',');

        while (getline(coursesstring, prereq, ',')) {
            prerequisites.push_back(prereq);
        }

        Course course = { courseNumber, courseTitle, prerequisites };
        bst.insert(course);
    }
    file.close();
}

// main menu
int main() {
    CourseBST bst;
    int choice;
    cout << "Welcome to the course planner." << endl;
    do {
        cout << "\n1. Load Data Structure.\n"
            << "2. Print Course List.\n"
            << "3. Print Course.\n"
            << "9. Exit\n"
            << "What would you like to do? ";
        cin >> choice;
        switch (choice) {
        case 1:
            loadCourses(bst);
            break;
        case 2:
            bst.printCourseList();
            break;
        case 3: {
            string courseNumber;
            cout << "What course do you want to know about? ";
            cin >> courseNumber;
            bst.printCourseInfo(courseNumber);
            break;
        }
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;
        default:
            cout << choice << " is not a valid option." << endl;
        }
    } while (choice != 9);
    return 0;
}
