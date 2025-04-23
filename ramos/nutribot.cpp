#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cmath>
using namespace std;

struct User {
    string name;
    int age;
    string gender;
    float height_cm;
    float weight_kg;
    float bmi;
    string bmiCategory;
    string bodyShape;
    string restriction;
    string activityLevel;
    string allergy;
    string goal;
    string condition;
};



void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string getStringInput(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    if (input.empty()) {
        cout << "No input detected. Exiting the program..." << endl;
        exit(0);
    }
    return input;
}
int stringToInt(string s) {
    int value = 0;
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] < '0' || s[i] > '9') return -1;
        value = value * 10 + (s[i] - '0');
    }
    return value;
}

int getValidatedInt(const string& prompt, const string& error, int min = 0, int max = 150) {
    string input;
    int value = -1;
    while (true) {
        cout << prompt;
        getline(cin, input);
        value = stringToInt(input);
        if (value < min || value > max) {
            cout << error << endl;
        } else {
            return value;
        }
    }
}


double stringToDouble(string s) {
    double result = 0, divisor = 1;
    bool decimal = false;
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '.') {
            if (decimal) return -1;
            decimal = true;
            continue;
        }
        if (s[i] < '0' || s[i] > '9') return -1;
        if (!decimal) {
            result = result * 10 + (s[i] - '0');
        } else {
            divisor *= 10;
            result += (s[i] - '0') / divisor;
        }
    }
    return result;
}

double getValidatedFloat(const string& prompt, const string& error, double min = 0.0) {
    string input;
    double value = -1;
    while (true) {
        cout << prompt;
        getline(cin, input);
        value = stringToDouble(input);
        if (value < min) {
            cout << error << endl;
        } else {
            return value;
        }
    }
}


string toLower(string s) {
    string result = "";
    for (int i = 0; i < s.length(); ++i) {
        char c = s[i];
        if (c >= 'A' && c <= 'Z') c += 32;
        result += c;
    }
    return result;
}


string getBMICategory(float bmi) {
    if (bmi < 18.5) return "Underweight";
    if (bmi < 25) return "Normal weight";
    if (bmi < 30) return "Overweight";
    return "Obese";
}

int main() {
    User user;
    int gender;
    cout << "Hi! I'm NutriBot, your quick buddy for diet and wellness tips!" << endl;

    user.name = getStringInput("What's your name? ");
    cout << "Nice to meet you, " << user.name << "!" << endl;

    user.age = getValidatedInt("Enter your age: ", "Invalid input. Please enter a valid age.", 1);
    while (true) {
        cout << "1. Male\n2. Female\nChoose your gender (1 or 2): ";
        cin >> gender;
        if (cin.fail() || (gender != 1 && gender != 2)) {
            cout << "Invalid choice. Please enter 1 (male) or 2 (female)." << endl;
            clearInput();
        } else {
            clearInput();
            break;
        }
    }

    if (gender == 1) user.gender = "Male";
    else user.gender = "Female";

    user.height_cm = getValidatedFloat("Enter your height in cm: ", "Invalid input. Please enter a valid height.", 1.0f);
    user.weight_kg = getValidatedFloat("Enter your weight in kg: ", "Invalid input. Please enter a valid weight.", 1.0f);

    float height_m = user.height_cm / 100;
    user.bmi = user.weight_kg / (height_m * height_m);
    user.bmiCategory = getBMICategory(user.bmi);

    cout << "\nYour BMI is " << user.bmi << ". You are classified as " << user.bmiCategory << "." << endl;

    while (true) {
        cout << "\nSelect your body shape:\n";
        cout << "1. Ectomorph\n2. Endomorph\n3. Mesomorph\nChoice: ";
        int choice;
        cin >> choice;
        clearInput();
        if (choice == 1) user.bodyShape = "Ectomorph";
        else if (choice == 2) user.bodyShape = "Endomorph";
        else if (choice == 3) user.bodyShape = "Mesomorph";
        else {
            cout << "Invalid choice. Please enter the correct option.\n";
            continue;
        }
        break;
    }

    cout << "\nDo you have any dietary preferences?\n";
    cout << "1. Gluten-Free\n2. Dairy-Free\n3. Vegetarian\n4. Vegan\n5. No restrictions\nChoice: ";
    int dietChoice;
    cin >> dietChoice;
    clearInput();
    switch (dietChoice) {
        case 1: user.restriction = "Gluten-Free"; break;
        case 2: user.restriction = "Dairy-Free"; break;
        case 3: user.restriction = "Vegetarian"; break;
        case 4: user.restriction = "Vegan"; break;
        case 5: user.restriction = "None"; break;
        default: user.restriction = "None"; break;
    }

    while (true) {
        cout << "\nWhat is your activity level?\n";
        cout << "1. Sedentary\n2. Lightly Active\n3. Moderately Active\n4. Very Active\nChoice: ";
        int act;
        cin >> act;
        clearInput();
        if (act == 1) user.activityLevel = "Sedentary";
        else if (act == 2) user.activityLevel = "Lightly Active";
        else if (act == 3) user.activityLevel = "Moderately Active";
        else if (act == 4) user.activityLevel = "Very Active";
        else {
            cout << "Invalid choice. Please enter the correct option.\n";
            continue;
        }
        break;
    }

    cout << "\nAny food allergies?\n";
    cout << "1. Nuts\n2. Dairy\n3. Gluten\n4. No allergies\n5. Other\nChoice: ";
    int allergyChoice;
    cin >> allergyChoice;
    clearInput();
    if (allergyChoice == 1) user.allergy = "Nuts";
    else if (allergyChoice == 2) user.allergy = "Dairy";
    else if (allergyChoice == 3) user.allergy = "Gluten";
    else if (allergyChoice == 4) user.allergy = "None";
    else {
        user.allergy = "Other";
        cout << "Please specify your food allergies: ";
        getline(cin, user.allergy);
    }

    cout << "\nWhat is your goal?\n";
    cout << "1. Lose Weight\n2. Gain Weight\n3. Maintain Weight\n4. Improve Fitness\n5. Build Muscle\nChoice: ";
    int goalChoice;
    cin >> goalChoice;
    clearInput();
    switch (goalChoice) {
        case 1: user.goal = "Lose Weight"; break;
        case 2: user.goal = "Gain Weight"; break;
        case 3: user.goal = "Maintain Weight"; break;
        case 4: user.goal = "Improve Fitness"; break;
        case 5: user.goal = "Build Muscle"; break;
        default: user.goal = "Maintain Weight"; break;
    }

    cout << "\nAny health conditions?\n";
    cout << "1. Diabetes\n2. High Blood Pressure\n3. Heart Disease\n4. None\n5. Other\nChoice: ";
    int condChoice;
    cin >> condChoice;
    clearInput();
    if (condChoice == 1) user.condition = "Diabetes";
    else if (condChoice == 2) user.condition = "High Blood Pressure";
    else if (condChoice == 3) user.condition = "Heart Disease";
    else if (condChoice == 4) user.condition = "None";
    else {
        user.condition = "Other";
        cout << "Please specify your health condition: ";
        getline(cin, user.condition);
    }

    // Display Summary
    cout << "\n===== SUMMARY OF YOUR INPUTS =====\n";
    cout << "Name: " << user.name << endl;
    cout << "Age: " << user.age << endl;
    cout << "Gender: " << user.gender << endl;
    cout << "Height: " << user.height_cm << " cm\n";
    cout << "Weight: " << user.weight_kg << " kg\n";
    cout << "BMI: " << user.bmi << " (" << user.bmiCategory << ")\n";
    cout << "Body Shape: " << user.bodyShape << endl;
    cout << "Dietary Preferences: " << user.restriction << endl;
    cout << "Activity Level: " << user.activityLevel << endl;
    cout << "Allergy: " << user.allergy << endl;
    cout << "Goal: " << user.goal << endl;
    cout << "Health Condition: " << user.condition << endl;

    // Display Recommendations
    cout << "\n===== YOUR PERSONALIZED DIET RECOMMENDATION =====\n";
    if (user.age >= 60) {
        cout << "\nSince you're 60 or older, we'll focus on gentle, nutrient-rich meals.\n";
        cout << "Include fiber (vegetables, fruits), calcium, and lean proteins.\n";
        cout << "Stay hydrated and eat smaller but more frequent meals for better digestion.\n";
    }
    
    if (user.bmiCategory == "Underweight") {
        cout << "- Eat calorie-rich, nutritious foods: avocados, nuts, healthy oils\n";
        cout << "- Protein: eggs, chicken, Greek yogurt\n";
        cout << "- Carbs: oats, sweet potatoes, whole grain bread\n";
        cout << "- Tip: Eat 3 meals + 2-3 snacks daily\n";
    } else if (user.bmiCategory == "Normal weight") {
        cout << "- Keep a balanced meal: veggies, lean proteins, grains, healthy fats\n";
        cout << "- Hydrate well (8 glasses/day)\n";
    } else if (user.bmiCategory == "Overweight") {
        cout << "- Focus on high-protein, high-fiber meals\n";
        cout << "- Avoid sugary snacks, processed food\n";
    } else {
        cout << "- Low-calorie, high-fiber, protein-rich foods\n";
        cout << "- Avoid sugary drinks, white carbs, salty snacks\n";
    }

    cout << "\nBased on Body Shape: " << user.bodyShape << endl;
    if (user.bodyShape == "Ectomorph") {
        cout << "- Eat more often with larger portions\n";
        cout << "- Focus on high-calorie foods like nuts, dairy, whole grains\n";
    } else if (user.bodyShape == "Endomorph") {
        cout << "- Go low-carb, high-protein and fiber\n";
        cout << "- Avoid processed, sugary, starchy foods\n";
    } else {
        cout << "- Balanced diet works best. Adjust portion based on activity\n";
    }

    cout << "\n===== DIETARY CONSIDERATIONS =====\n";

    if (user.restriction != "None") {
        cout << "\nDietary note: Following a " << user.restriction << " diet.\n";

        if (user.restriction == "Gluten-Free") {
            cout << "- Eat rice, corn, quinoa, potatoes, and gluten-free oats.\n";
            cout << "- Avoid wheat, barley, rye, and most traditional pasta and bread.\n";
        } 
        else if (user.restriction == "Dairy-Free") {
            cout << "- Use almond milk, soy milk, or oat milk as alternatives.\n";
            cout << "- Include calcium-rich foods like leafy greens and fortified plant milk.\n";
            cout << "- Avoid cheese, butter, milk, yogurt made from animal dairy.\n";
        } 
        else if (user.restriction == "Vegetarian") {
            cout << "- Include tofu, lentils, beans, eggs, and dairy like milk or yogurt.\n";
            cout << "- Ensure adequate protein and iron from legumes and eggs.\n";
        } 
        else if (user.restriction == "Vegan") {
            cout << "- Focus on plant-based foods: beans, lentils, tofu, vegetables, grains.\n";
            cout << "- Include B12 sources like fortified cereals, nutritional yeast, or supplements.\n";
            cout << "- Get protein from legumes, soy products, and whole grains.\n";
        }
        if (user.restriction == "Vegan" && user.allergy == "Nuts") {
            cout << "- Note: Since you're allergic to nuts, avoid nut-based products like almond milk and peanut butter.\n";
        }
        if (user.restriction == "Vegetarian" && user.allergy == "Dairy") {
            cout << "- Note: You're dairy allergic, so skip milk, cheese, and yogurt despite being vegetarian.\n";
        }
        if (user.restriction == "Gluten-Free" && user.allergy == "Gluten") {
            cout << "- Reminder: Strictly avoid wheat, barley, and rye due to your gluten allergy.\n";
        }
        if (user.restriction == "Dairy-Free" && user.allergy == "Dairy") {
            cout << "- Reinforcing dairy avoidance due to allergy and dietary preference.\n";
        }
        
    } else {
        cout << "\nYou have no dietary restrictions. You're free to enjoy a balanced and varied diet!\n";
    }


    // Exercise Plan
    cout << "\nWould you like a personalized exercise plan? (yes/no): ";
    string exChoice;
    getline(cin, exChoice);
    while (exChoice != "yes" && exChoice != "no") {
        cout << "Please enter yes or no: ";
        getline(cin, exChoice);
    }
    
    if (toLower(exChoice) == "yes") {
        cout << "\nGreat! Here's a basic exercise plan based on your inputs:\n";


        cout << "\n===== EXERCISE PLAN =====\n";
        if (user.activityLevel == "Sedentary") {
            cout << "- Start with walking and gentle stretches\n";
        } else if (user.activityLevel == "Lightly Active") {
            cout << "- Add light cardio & bodyweight training\n";
        } else if (user.activityLevel == "Moderately Active") {
            cout << "- Jogging, swimming, resistance training\n";
        } else {
            cout << "- HIIT, strength circuits, endurance training\n";
        }

        if (user.age >= 60) {
            cout << "- Prioritize safe, gentle exercises like water aerobics\n";
        }

        if (user.condition == "Diabetes") {
            cout << "\n[Health Tip - Diabetes]\n";
            cout << "- Avoid processed sugar, focus on fiber-rich food, and monitor blood sugar.\n";
        } else if (user.condition == "High Blood Pressure") {
            cout << "\n[Health Tip - High Blood Pressure]\n";
            cout << "- Limit sodium, eat potassium-rich foods like bananas and spinach, exercise regularly.\n";
        } else if (user.condition == "Heart Disease") {
            cout << "\n[Health Tip - Heart Disease]\n";
            cout << "- Eat heart-healthy fats like olive oil, avoid red meat and alcohol, and do moderate exercise.\n";
        } else {
            cout << "\nNo special health-related dietary tips.\n";
        }
        
    } else {
        cout << "No problem! Stick to your healthy eating plan and stay active. You've got this!\n";
    }

    // Goal Recommendations
    cout << "\n===== DAILY RECOMMENDATIONS BASED ON YOUR GOAL =====\n";
    if (user.goal == "Lose Weight") {
        cout << "- Eat nutrient-dense meals\n- Exercise 30-45 mins daily\n- Hydrate well\n";
    } else if (user.goal == "Gain Weight") {
        cout << "- Eat 3 full meals + 2-3 snacks\n- Strength train regularly\n";
    } else if (user.goal == "Maintain Weight") {
        cout << "- Balanced meals + 150 mins activity weekly\n";
    } else if (user.goal == "Improve Fitness") {
        cout << "- Combine cardio and strength 4-5x weekly\n";
    } else if (user.goal == "Build Muscle") {
        cout << "- High protein intake + 4-5x weight training/week\n";
    }

    cout << "\nThanks for chatting with NutriBot! Stay healthy, " << user.name << "!\n";
    cout << "\nWe'd love your feedback! \n";
    cout << "Do you have any comments or suggestions about your experience? \n";
    string feedback;
    getline(cin, feedback);
    if (!feedback.empty()) {
        cout << "Thanks for your feedback! We'll use it to improve NutriBot. \n";
    }

    cout << "\nWould you like more personalized tips in the future? (yes/no): ";
    string followUp;
    getline(cin, followUp);
    if (toLower(followUp) == "yes") {
        cout << "Great! We'll be ready with more helpful advice next time. \n";
    } else {
        cout << "No worries! Come back anytime you need a healthy boost. \n";
    }


    return 0;
}
