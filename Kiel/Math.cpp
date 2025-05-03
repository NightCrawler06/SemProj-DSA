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

void printLine() {
    cout << "\n--------------------------------------------------\n";
}

void explainTopic(string topic) {
    printLine();
    cout << "Reviewing Topic: " << topic << "\n\n";

    if (topic == "Addition") {
        cout << "Addition is the process of combining two or more numbers to make a larger number.\n";
        cout << "Example: 7 + 5 = 12\n";
    } else if (topic == "Subtraction") {
        cout << "Subtraction is the process of taking one number away from another.\n";
        cout << "Example: 15 - 8 = 7\n";
    } else if (topic == "Multiplication") {
        cout << "Multiplication is repeated addition. For example, 3 * 2 is the same as 3 + 3.\n";
        cout << "Example: 4 * 3 = 12\n";
    } else if (topic == "Division") {
        cout << "Division is the process of splitting a number into equal parts.\n";
        cout << "Example: 12 / 3 = 4\n";
    } else if (topic == "Fractions") {
        cout << "Fractions represent a part of a whole. For example, 1/2 means one part of two equal parts.\n";
        cout << "Example: 1/2, 1/3, 1/4\n";
    } else if (topic == "Counting") {
        cout << "Counting is the process of naming numbers in a sequence. Start from 1 and count up.\n";
        cout << "Example: 1, 2, 3, 4, 5, ...\n";
    } else if (topic == "Place Value") {
        cout << "Place value tells you the value of a digit in a number based on its position.\n";
        cout << "Example: In 345, the 3 is in the hundreds place, so it represents 300.\n";
    } else if (topic == "Time") {
        cout << "Time is the process of measuring and understanding hours and minutes.\n";
        cout << "Example: 3:15 means 3 hours and 15 minutes.\n";
    } else if (topic == "Decimals") {
        cout << "Decimals represent fractions of a whole number.\n";
        cout << "Example: 0.5 is the same as 1/2.\n";
    } else if (topic == "Measurement") {
        cout << "Measurement is the process of determining the size, length, or amount of something.\n";
        cout << "Example: A pencil is 10 cm long.\n";
    } else if (topic == "Geometry") {
        cout << "Geometry deals with shapes and their properties.\n";
        cout << "Example: A triangle has 3 sides and 3 angles.\n";
    } else if (topic == "Long Division") {
        cout << "Long division is a method for dividing larger numbers.\n";
        cout << "Example: 156 ÷ 12 = 13\n";
    } else if (topic == "Word Problems") {
        cout << "Word problems require you to apply math to real-life situations.\n";
        cout << "Example: If you have 3 apples and buy 2 more, how many apples do you have?\n";
    } else if (topic == "Ratios") {
        cout << "A ratio is a way to compare two quantities.\n";
        cout << "Example: 3:2 means for every 3 of one thing, there are 2 of another.\n";
    } else if (topic == "Percentages") {
        cout << "A percentage is a way to express a number as a part of 100.\n";
        cout << "Example: 50% is the same as 50 out of 100.\n";
    } else if (topic == "Algebra") {
        cout << "Algebra involves using letters to represent numbers in equations.\n";
        cout << "Example: x + 2 = 5. Solve for x, x = 3.\n";
    } else if (topic == "Data Analysis") {
        cout << "Data analysis involves collecting and interpreting data.\n";
        cout << "Example: If you have 10 apples, 5 are red and 5 are green, what is the percentage of red apples?\n";
    } else {
        cout << "Sorry, we don't have an explanation for this topic yet.\n";
    }
    printLine();
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
        cout << "\nQuestion " << i << ":\n" << question << "\nYour answer: ";
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
            cout << "Still not right. The correct answer was: " << correctAnswer << "\n";
            wrongQuestions.push(question);
            correctAnswers.push(to_string(correctAnswer));
            userWrongAnswers.push(userAnswer);
        }
    }

    printLine();
    cout << "\nQuiz Complete, " << name << "!\nYour score: " << score << "/10\n";

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
    printLine();
}

int main() {
    srand(time(0));
    int grade, choice;
    string name;

    cout << "\nWelcome to your personal Math Tutor Bot!\n";
    cout << "I'm here to help you review math topics and practice with quizzes.\n";
    cout << "Before we begin, what's your name? ";
    cin >> name;

    cout << "\nHi " << name << "! What grade are you in? (1-6): ";
    cin >> grade;

    if (grade < 1 || grade > 6) {
        cout << "That doesn't seem like a valid grade. Please restart and enter 1 to 6.\n";
        return 0;
    }

    while (true) {
        printLine();
        cout << "\nTopics for Grade " << grade << ":\n";
        for (int i = 0; i < 5; i++) {
            cout << i + 1 << ". " << gradeTopics[grade - 1][i] << "\n";
        }

        printLine();
        cout << "\nWhat would you like to do, " << name << "?\n";
        cout << "1. Review a topic\n";
        cout << "2. Take a quiz\n";
        cout << "3. Exit\n";
        cout << "Enter your choice (1-3): ";
        int action;
        cin >> action;

        if (action == 3) {
            cout << "\nThanks for learning with me today, " << name << "!\nKeep practicing and see you next time!\n";
            break;
        }

        if (action != 1 && action != 2) {
            cout << "Invalid option. Please choose 1, 2, or 3.\n";
            continue;
        }

        cout << "\nEnter a topic number (1-5): ";
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
