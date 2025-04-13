#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <limits>

using namespace std;

// Function para ma display ung topic explanation with examples
void displayExplanation(const string& topic) {
    if (topic == "Addition") {
        cout << "\nAddition:\n";
        cout << "Addition is the process of combining two or more numbers to make a larger number.\n";
        cout << "Example: 7 + 5 = 12\n";
    }
    else if (topic == "Subtraction") {
        cout << "\nSubtraction:\n";
        cout << "Subtraction is the process of taking one number away from another.\n";
        cout << "Example: 15 - 8 = 7\n";
    }
    else if (topic == "Multiplication") {
        cout << "\nMultiplication:\n";
        cout << "Multiplication is repeated addition. For example, 3 * 2 is the same as 3 + 3.\n";
        cout << "Example: 4 * 3 = 12\n";
    }
    else if (topic == "Division") {
        cout << "\nDivision:\n";
        cout << "Division is the process of splitting a number into equal parts.\n";
        cout << "Example: 12 / 3 = 4\n";
    }
    else if (topic == "Fractions") {
        cout << "\nFractions:\n";
        cout << "Fractions represent a part of a whole. For example, 1/2 means one part of two equal parts.\n";
        cout << "Example: 1/2, 1/3, 1/4\n";
    }
    else if (topic == "Counting") {
        cout << "\nCounting:\n";
        cout << "Counting is the process of naming numbers in a sequence. Start from 1 and count up.\n";
        cout << "Example: 1, 2, 3, 4, 5, ...\n";
    }
    else if (topic == "Place Value") {
        cout << "\nPlace Value:\n";
        cout << "Place value tells you the value of a digit in a number based on its position.\n";
        cout << "Example: In 345, the 3 is in the hundreds place, so it represents 300.\n";
    }
    else if (topic == "Time") {
        cout << "\nTime:\n";
        cout << "Time is the process of measuring and understanding hours and minutes.\n";
        cout << "Example: 3:15 means 3 hours and 15 minutes.\n";
    }
    else if (topic == "Decimals") {
        cout << "\nDecimals:\n";
        cout << "Decimals represent fractions of a whole number.\n";
        cout << "Example: 0.5 is the same as 1/2.\n";
    }
    else if (topic == "Measurement") {
        cout << "\nMeasurement:\n";
        cout << "Measurement is the process of determining the size, length, or amount of something.\n";
        cout << "Example: A pencil is 10 cm long.\n";
    }
    else if (topic == "Geometry") {
        cout << "\nGeometry:\n";
        cout << "Geometry deals with shapes and their properties.\n";
        cout << "Example: A triangle has 3 sides and 3 angles.\n";
    }
    else if (topic == "Long Division") {
        cout << "\nLong Division:\n";
        cout << "Long division is a method for dividing larger numbers.\n";
        cout << "Example: 156 ÷ 12 = 13.\n";
    }
    else if (topic == "Word Problems") {
        cout << "\nWord Problems:\n";
        cout << "Word problems require you to apply math to real-life situations.\n";
        cout << "Example: If you have 3 apples and buy 2 more, how many apples do you have?\n";
    }
    else if (topic == "Ratios") {
        cout << "\nRatios:\n";
        cout << "A ratio is a way to compare two quantities.\n";
        cout << "Example: 3:2 means for every 3 of one thing, there are 2 of another.\n";
    }
    else if (topic == "Percentages") {
        cout << "\nPercentages:\n";
        cout << "A percentage is a way to express a number as a part of 100.\n";
        cout << "Example: 50% is the same as 50 out of 100.\n";
    }
    else if (topic == "Algebra") {
        cout << "\nAlgebra:\n";
        cout << "Algebra involves using letters to represent numbers in equations.\n";
        cout << "Example: x + 2 = 5. Solve for x, x = 3.\n";
    }
    else if (topic == "Data Analysis") {
        cout << "\nData Analysis:\n";
        cout << "Data analysis involves collecting and interpreting data.\n";
        cout << "Example: If you have 10 apples, 5 are red and 5 are green, what is the percentage of red apples?\n";
    }
}

// Function para ma generate ung question base sa grade at topic
int generateQuestion(int grade, const string& topic) {
    int a, b, answer = 0;
    
    if (topic == "Addition") {
        a = rand() % 20 + 1;
        b = rand() % 20 + 1;
        answer = a + b;
        cout << "What is " << a << " + " << b << "?\n";
    }
    else if (topic == "Subtraction") {
        a = rand() % 20 + 1;
        b = rand() % 20 + 1;
        answer = a - b;
        cout << "What is " << a << " - " << b << "?\n";
    }
    else if (topic == "Multiplication") {
        a = rand() % 10 + 1;
        b = rand() % 10 + 1;
        answer = a * b;
        cout << "What is " << a << " * " << b << "?\n";
    }
    else if (topic == "Division") {
        a = rand() % 12 + 1;
        b = rand() % 12 + 1;
        answer = a / b;
        cout << "What is " << a << " / " << b << "?\n";
    }
    else if (topic == "Fractions") {
        a = rand() % 10 + 1;
        b = rand() % 10 + 1;
        answer = a / b; // simple fractions
        cout << "What is " << a << "/" << b << "?\n";
    }
    else if (topic == "Time") {
        int hour = rand() % 12 + 1;  // Random hour from 1 to 12
        int minute = rand() % 60;    // Random minute from 0 to 59
        cout << "What time is " << hour << ":" << (minute < 10 ? "0" : "") << minute << "?\n";
        // For simplicity, we'll just return the time in minutes as the answer
        answer = hour * 60 + minute; 
    }
    else if (topic == "Geometry") {
        a = rand() % 10 + 1;  // Random side length
        cout << "What is the perimeter of a square with side length " << a << "?\n";
        answer = 4 * a; // Perimeter of a square is 4 times the side length
    }
    else if (topic == "Word Problems") {
        a = rand() % 10 + 1;  // Random number for apples
        b = rand() % 10 + 1;  // Random number for additional apples
        cout << "If you have " << a << " apples and buy " << b << " more, how many apples do you have in total?\n";
        answer = a + b;  // Word problem result
    }
    else if (topic == "Place Value") {
        a = rand() % 900 + 100;  // Random 3-digit number
        cout << "What is the value of the hundreds place in the number " << a << "?\n";
        answer = a / 100;  // Hundreds place value
    }
    else if (topic == "Measurement") {
        a = rand() % 100 + 1;  // Random measurement (length)
        cout << "If a pencil is " << a << " cm long, how many millimeters is that?\n";
        answer = a * 10;  // 1 cm = 10 mm
    }
    else if (topic == "Decimals") {
        float decimal = static_cast<float>(rand() % 1000) / 100;  // Random decimal
        cout << "What is " << decimal << " rounded to the nearest tenth?\n";
        answer = static_cast<int>(decimal * 10) / 10;  // Round to the nearest tenth
    }
    else if (topic == "Long Division") {
        a = rand() % 100 + 10;  // Random 2-digit dividend
        b = rand() % 10 + 1;  // Random divisor
        cout << "What is " << a << " ÷ " << b << "?\n";
        answer = a / b;  // Long division result
    }
    else if (topic == "Ratios") {
        a = rand() % 10 + 1;  // Random number
        b = rand() % 10 + 1;  // Random number
        cout << "What is the ratio of " << a << " to " << b << "?\n";
        answer = a * 100 / b;  // Simplified ratio as percentage
    }
    else if (topic == "Percentages") {
        a = rand() % 100 + 1;  // Random percentage
        cout << "What is " << a << "% of 200?\n";
        answer = (a * 200) / 100;  // Percentage calculation
    }
    else if (topic == "Algebra") {
        a = rand() % 10 + 1;  // Random number
        cout << "If x + " << a << " = 10, what is x?\n";
        answer = 10 - a;  // Simple algebra
    }
    else if (topic == "Data Analysis") {
        a = rand() % 20 + 1;  // Random count of apples
        b = rand() % 20 + 1;  // Random count of green apples
        cout << "You have " << a << " apples, " << b << " of which are red. What percentage of apples are red?\n";
        answer = (b * 100) / a;  // Percentage of red apples
    }

    return answer;
}


// Function para ma get ung valid input from the user
int getValidInput() {
    int input;
    while (true) {
        cin >> input;
        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a number: ";
        } else {
            return input;
        }
    }
}

// Function para ma track at provide feedback sa progress
void trackProgress(int correctAnswers) {
    if (correctAnswers >= 8) {
        cout << "Excellent work! You scored " << correctAnswers << "/10.\n";
    }
    else if (correctAnswers >= 5) {
        cout << "Good job! You scored " << correctAnswers << "/10.\n";
    }
    else {
        cout << "Keep practicing! You scored " << correctAnswers << "/10.\n";
    }
}

// Function para ma give hint kung kailangan
void giveHint(const string& topic) {
    if (topic == "Addition") {
        cout << "Hint: Try counting on from the larger number!\n";
    }
    else if (topic == "Subtraction") {
        cout << "Hint: Start with the larger number and count backwards.\n";
    }
    else if (topic == "Multiplication") {
        cout << "Hint: Think of multiplication as repeated addition.\n";
    }
    else if (topic == "Division") {
        cout << "Hint: Division is the opposite of multiplication.\n";
    }
    else if (topic == "Fractions") {
        cout << "Hint: A fraction is part of a whole. Try simplifying the fraction if you can.\n";
    }
    else if (topic == "Counting") {
        cout << "Hint: Start from the number and keep adding 1 for each next count.\n";
    }
    else if (topic == "Place Value") {
        cout << "Hint: The place value is based on the position of the digit in the number.\n";
    }
    else if (topic == "Time") {
        cout << "Hint: Convert minutes to hours if needed or break the time into smaller parts.\n";
    }
    else if (topic == "Decimals") {
        cout << "Hint: Decimals are another way of expressing fractions of a whole number.\n";
    }
    else if (topic == "Measurement") {
        cout << "Hint: Convert different units if necessary (e.g., cm to meters).\n";
    }
    else if (topic == "Geometry") {
        cout << "Hint: Review the properties of the shapes you are working with (sides, angles).\n";
    }
    else if (topic == "Long Division") {
        cout << "Hint: Break down the division into smaller steps if necessary (divide, multiply, subtract).\n";
    }
    else if (topic == "Word Problems") {
        cout << "Hint: Read the problem carefully and break it into smaller steps.\n";
    }
    else if (topic == "Ratios") {
        cout << "Hint: A ratio compares two quantities. Try to simplify the ratio if needed.\n";
    }
    else if (topic == "Percentages") {
        cout << "Hint: Percentages are out of 100. Convert fractions or decimals to percentages.\n";
    }
    else if (topic == "Algebra") {
        cout << "Hint: Solve for the unknown variable by isolating it on one side of the equation.\n";
    }
    else if (topic == "Data Analysis") {
        cout << "Hint: Look at the data carefully and calculate averages or percentages where needed.\n";
    }
}


// Function para ma display ung menu
void displayGradeMenu() {
    cout << "\nPlease select your grade (1-6): ";
}

// Function para ma display ung topic menu base sa grade 
void displayTopicMenu(int grade) {
    vector<string> topics;
    if (grade == 1) {
        topics = {"Addition", "Subtraction", "Multiplication", "Counting", "Fractions"};
    }
    else if (grade == 2) {
        topics = {"Addition", "Subtraction", "Multiplication", "Division", "Place Value"};
    }
    else if (grade == 3) {
        topics = {"Multiplication", "Division", "Fractions", "Time", "Decimals"};
    }
    else if (grade == 4) {
        topics = {"Multiplication", "Division", "Fractions", "Measurement", "Geometry"};
    }
    else if (grade == 5) {
        topics = {"Long Division", "Decimals", "Fractions", "Volume", "Word Problems"};
    }
    else if (grade == 6) {
        topics = {"Ratios", "Percentages", "Algebra", "Geometry", "Data Analysis"};
    }
    
    cout << "\nPlease select a topic:\n";
    for (int i = 0; i < topics.size(); i++) {
        cout << i + 1 << ". " << topics[i] << endl;
    }
    
    cout << "\nEnter your choice (1-" << topics.size() << "): ";
    int topicChoice = getValidInput();
    if (topicChoice < 1 || topicChoice > topics.size()) {
        cout << "Invalid choice. Exiting program.\n";
        exit(0);
    }
    
    string topic = topics[topicChoice - 1];
    displayExplanation(topic);
    
    int correctAnswers = 0;
    for (int i = 0; i < 10; i++) {
        int correctAnswer = generateQuestion(grade, topic);
        int studentAnswer;
        cout << "Your answer: ";
        studentAnswer = getValidInput();

        if (studentAnswer == correctAnswer) {
            cout << "Correct!\n";
            correctAnswers++;
        }
        else {
            cout << "Incorrect. The correct answer was " << correctAnswer << ".\n";
            giveHint(topic);
        }
    }
    
    trackProgress(correctAnswers);
}

int main() {
    srand(time(0)); 
    cout << "Welcome to the Math Quiz!\n";
    cout << "This quiz is designed to help you practice various math topics.\n";
    
    int grade;
    displayGradeMenu();
    grade = getValidInput(); 

    if (grade < 1 || grade > 6) {
        cout << "Invalid grade. Exiting program.\n";
        return 0;
    }

    displayTopicMenu(grade);
    
    return 0;
}
