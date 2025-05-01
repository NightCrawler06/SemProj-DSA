#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>    
#include <queue>    

using namespace std;

string gradeTopics[6][5] = {
    {"Addition", "Subtraction", "Multiplication", "Counting", "Fractions"},    
    {"Addition", "Subtraction", "Multiplication", "Division", "Place Value"},   
    {"Multiplication", "Division", "Fractions", "Time", "Decimals"},             
    {"Multiplication", "Division", "Fractions", "Measurement", "Geometry"},      
    {"Long Division", "Decimals", "Fractions", "Volume", "Word Problems"},       
    {"Ratios", "Percentages", "Algebra", "Geometry", "Data Analysis"}           
};


void explainTopic(string topic) {
    cout << "\n--- " << topic << " ---\n";
    if (topic == "Addition") {
        cout << "Meaning: Adding numbers together.\n";
        cout << "Purpose: Find the total.\n";
        cout << "Steps: Line up numbers -> Add from right to left -> Carry over if needed.\n";
        cout << "Example: 47 + 26 = 73\n";
    }
    else if (topic == "Subtraction") {
        cout << "Meaning: Finding the difference.\n";
        cout << "Purpose: Find what is left.\n";
        cout << "Steps: Line up numbers -> Subtract from right to left -> Borrow if needed.\n";
        cout << "Example: 52 - 19 = 33\n";
    }
    else if (topic == "Multiplication") {
        cout << "Meaning: Repeated addition.\n";
        cout << "Purpose: Quick total for equal groups.\n";
        cout << "Steps: Multiply numbers directly.\n";
        cout << "Example: 4 x 3 = 12\n";
    }
    else if (topic == "Division") {
        cout << "Meaning: Splitting into equal parts.\n";
        cout << "Purpose: To share or group.\n";
        cout << "Steps: Divide numbers.\n";
        cout << "Example: 12 / 3 = 4\n";
    }
    else if (topic == "Counting") {
        cout << "Meaning: Listing numbers in order.\n";
        cout << "Purpose: Know quantity.\n";
        cout << "Steps: Start from 1 or 0, count up.\n";
        cout << "Example: 1, 2, 3, 4, 5...\n";
    }
    else if (topic == "Fractions") {
        cout << "Meaning: Part of a whole.\n";
        cout << "Purpose: Show portions.\n";
        cout << "Steps: Top number shows parts you have; bottom shows total parts.\n";
        cout << "Example: 1/2 means one part out of two.\n";
    }
}


void generateQuiz(string topic, queue<string>& questions, stack<string>& answers) {
    srand(time(0));
    for (int i = 0; i < 3; i++) {
        int a = rand() % 10 + 1;
        int b = rand() % 10 + 1;

        if (topic == "Addition") {
            questions.push("What is " + to_string(a) + " + " + to_string(b) + "?");
            answers.push(to_string(a + b));
        }
        else if (topic == "Subtraction") {
            if (a < b) swap(a, b);
            questions.push("What is " + to_string(a) + " - " + to_string(b) + "?");
            answers.push(to_string(a - b));
        }
        else if (topic == "Multiplication") {
            questions.push("What is " + to_string(a) + " * " + to_string(b) + "?");
            answers.push(to_string(a * b));
        }
        else if (topic == "Division") {
            int result = (rand() % 10) + 1;
            a = result * b;
            questions.push("What is " + to_string(a) + " / " + to_string(b) + "?");
            answers.push(to_string(result));
        }
    }
}

int main() {
    int grade, choice;
    char takeQuiz;

    cout << "Welcome to Beginner Math Tutor!\n";
    cout << "Enter your grade (1-6): ";
    cin >> grade;

    if (grade < 1 || grade > 6) {
        cout << "Invalid grade.\n";
        return 0;
    }

    cout << "\nAvailable Topics:\n";
    for (int i = 0; i < 5; i++) {
        cout << i + 1 << ". " << gradeTopics[grade - 1][i] << endl;
    }

    cout << "Choose a topic number: ";
    cin >> choice;

    if (choice < 1 || choice > 5) {
        cout << "Invalid topic choice.\n";
        return 0;
    }

    string selectedTopic = gradeTopics[grade - 1][choice - 1];

    explainTopic(selectedTopic);

    cout << "\nDo you want a short quiz? (y/n): ";
    cin >> takeQuiz;

    if (takeQuiz == 'y' || takeQuiz == 'Y') {
        queue<string> questions;
        stack<string> answers;

        generateQuiz(selectedTopic, questions, answers);

        while (!questions.empty()) {
            cout << questions.front() << endl;
            cout << "Your answer: ";
            string userAnswer;
            cin >> userAnswer;

            if (userAnswer == answers.top()) {
                cout << "Correct!\n";
            } else {
                cout << "Wrong. Correct answer: " << answers.top() << endl;
            }

            questions.pop();
            answers.pop();
        }
    }

    cout << "\nThank you for using Beginner Math Tutor!\n";
    return 0;
}
