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
    cout << "\nLet's go over: " << topic << "\n";
    if (topic == "Addition") {
        cout << "Addition means putting numbers together.\n";
        cout << "Examples: 5 + 3 = 8, 10 + 7 = 17, 2 + 6 = 8\n";
    } else if (topic == "Subtraction") {
        cout << "Subtraction means taking one number away from another.\n";
        cout << "Examples: 9 - 4 = 5, 15 - 6 = 9, 12 - 3 = 9\n";
    } else if (topic == "Multiplication") {
        cout << "Multiplication is repeated addition.\n";
        cout << "Examples: 4 * 3 = 12, 2 * 5 = 10, 6 * 2 = 12\n";
    } else if (topic == "Division") {
        cout << "Division is splitting into equal parts.\n";
        cout << "Examples: 8 / 2 = 4, 12 / 3 = 4, 20 / 5 = 4\n";
    } else {
        cout << "This topic is interesting, but we don't have examples for it yet.\n";
    }
}

string giveHint(string topic) {
    if (topic == "Addition") return "Hint: Try using your fingers or a number line.";
    if (topic == "Subtraction") return "Hint: Think about what's left after taking away.";
    if (topic == "Multiplication") return "Hint: Try repeated addition.";
    if (topic == "Division") return "Hint: Think of equal sharing.";
    return "Hint: Think it through step by step.";
}

int generateQuestion(string topic, string &question) {
    int a = rand() % 10 + 1;
    int b = rand() % 10 + 1;
    int answer = 0;

    if (topic == "Addition") {
        answer = a + b;
        question = "What is " + to_string(a) + " + " + to_string(b) + "?";
    } else if (topic == "Subtraction") {
        if (a < b) swap(a, b);
        answer = a - b;
        question = "What is " + to_string(a) + " - " + to_string(b) + "?";
    } else if (topic == "Multiplication") {
        answer = a * b;
        question = "What is " + to_string(a) + " * " + to_string(b) + "?";
    } else if (topic == "Division") {
        int result = (rand() % 10) + 1;
        b = (rand() % 9) + 1;
        a = result * b;
        answer = result;
        question = "What is " + to_string(a) + " / " + to_string(b) + "?";
    }
    return answer;
}

void runQuiz(string selectedTopic, string name) {
    int score = 0;
    string question, userAnswer;
    int correctAnswer;
    queue<string> wrongQuestions, correctAnswers, userWrongAnswers;

    for (int i = 1; i <= 10; i++) {
        correctAnswer = generateQuestion(selectedTopic, question);
        cout << "\n" << i << ". " << question << "\nYour answer: ";
        cin >> userAnswer;

        if (userAnswer == to_string(correctAnswer)) {
            cout << "Correct!\n";
            score++;
            continue;
        }

        cout << "Not quite.\n" << giveHint(selectedTopic) << "\nTry again: ";
        cin >> userAnswer;

        if (userAnswer == to_string(correctAnswer)) {
            cout << "Good job, you got it on the second try!\n";
            score++;
        } else {
            cout << "That's still not right. The correct answer was: " << correctAnswer << "\n";
            wrongQuestions.push(question);
            correctAnswers.push(to_string(correctAnswer));
            userWrongAnswers.push(userAnswer);
        }
    }

    cout << "\nQuiz Complete, " << name << ".\n";
    cout << "Your score: " << score << "/10\n";

    if (!wrongQuestions.empty()) {
        cout << "\nHere are the questions you missed:\n";
        while (!wrongQuestions.empty()) {
            cout << wrongQuestions.front() << "\n";
            cout << "Your answer: " << userWrongAnswers.front()
                 << " | Correct answer: " << correctAnswers.front() << "\n\n";
            wrongQuestions.pop();
            correctAnswers.pop();
            userWrongAnswers.pop();
        }
    }
}

int main() {
    srand(time(0));
    int grade, choice;
    string name;

    // Introduction
    cout << "Welcome to your personal Math Tutor Bot.\n";
    cout << "I'm here to help you review math topics and practice with quizzes.\n";
    cout << "Before we begin, what's your name? ";
    cin >> name;

    cout << "\nGreat to meet you, " << name << ". What grade are you in? (1-6): ";
    cin >> grade;

    if (grade < 1 || grade > 6) {
        cout << "That doesn't seem like a valid grade. Please restart and enter 1 to 6.\n";
        return 0;
    }

    while (true) {
        cout << "\nHere are the topics available for grade " << grade << ":\n";
        for (int i = 0; i < 5; i++) {
            cout << i + 1 << ". " << gradeTopics[grade - 1][i] << "\n";
        }

        cout << "\n" << name << ", what would you like to do?\n";
        cout << "1. Review a topic\n";
        cout << "2. Take a quiz\n";
        cout << "3. Exit\n";
        cout << "Enter your choice (1-3): ";

        int action;
        cin >> action;

        if (action == 3) {
            cout << "\nThanks for learning with me today, " << name << ". Keep practicing and see you next time!\n";
            break;
        }

        if (action != 1 && action != 2) {
            cout << "Invalid option. Please choose 1, 2, or 3.\n";
            continue;
        }

        cout << "Choose a topic number (1-5): ";
        cin >> choice;
        if (choice < 1 || choice > 5) {
            cout << "That topic number is not available. Please choose from 1 to 5.\n";
            continue;
        }

        string selectedTopic = gradeTopics[grade - 1][choice - 1];

        if (action == 1) {
            explainTopic(selectedTopic);
        } else if (action == 2) {
            string confirm;
            cout << "Are you ready to take a quiz on " << selectedTopic << "? (yes/no): ";
            cin >> confirm;
            if (confirm == "yes") {
                runQuiz(selectedTopic, name);
            } else {
                cout << "No problem! You can come back to the quiz anytime.\n";
            }
        }
    }

    return 0;
}
