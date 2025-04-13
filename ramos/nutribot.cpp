#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include <cctype>
#include <cmath>
using namespace std;

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

int getValidatedInt(const string& prompt, const string& error, int min = 0, int max = 150) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < min || value > max) {
            cout << error << endl;
            clearInput();
        } else {
            clearInput();
            return value;
        }
    }
}

float getValidatedFloat(const string& prompt, const string& error, float min = 0.0f) {
    float value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < min) {
            cout << error << endl;
            clearInput();
        } else {
            clearInput();
            return value;
        }
    }
}

string toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

string getBMICategory(float bmi) {
    if (bmi < 18.5) return "Underweight";
    if (bmi < 25) return "Normal weight";
    if (bmi < 30) return "Overweight";
    return "Obese";
}

int main() {
    cout << "Hi! I'm NutriBot, your quick buddy for diet and wellness tips!" << endl;

    string name = getStringInput("What's your name? ");
    cout << "Nice to meet you, " << name << "!" << endl;

    int age = getValidatedInt("Enter your age: ", "Invalid input. Please enter a valid age.", 1);
    int gender;
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

    float height_cm = getValidatedFloat("Enter your height in cm: ", "Invalid input. Please enter a valid height.", 1.0f);
    float weight_kg = getValidatedFloat("Enter your weight in kg: ", "Invalid input. Please enter a valid weight.", 1.0f);

    float height_m = height_cm / 100;
    float bmi = weight_kg / (height_m * height_m);
    string bmiCategory = getBMICategory(bmi);

    cout << "\nYour BMI is " << bmi << ". You are classified as " << bmiCategory << "." << endl;

    string bodyShape;
    while (true) {
        cout << "\nSelect your body shape:\n";
        cout << "1. Ectomorph\n2. Endomorph\n3. Mesomorph\nChoice: ";
        int choice;
        cin >> choice;
        clearInput();
        if (choice == 1) bodyShape = "Ectomorph";
        else if (choice == 2) bodyShape = "Endomorph";
        else if (choice == 3) bodyShape = "Mesomorph";
        else {
            cout << "Invalid choice. Please enter the correct option.\n";
            continue;
        }
        break;
    }

    string restriction;
    cout << "\nDo you have any dietary preferences?\n";
    cout << "1. Gluten-Free\n2. Dairy-Free\n3. Vegetarian\n4. Vegan\n5. No restrictions\nChoice: ";
    int dietChoice;
    cin >> dietChoice;
    clearInput();
    switch (dietChoice) {
        case 1: restriction = "Gluten-Free"; break;
        case 2: restriction = "Dairy-Free"; break;
        case 3: restriction = "Vegetarian"; break;
        case 4: restriction = "Vegan"; break;
        case 5: restriction = "None"; break;
        default: restriction = "None"; break;
    }

    string activityLevel;
    while (true) {
        cout << "\nWhat is your activity level?\n";
        cout << "1. Sedentary\n2. Lightly Active\n3. Moderately Active\n4. Very Active\nChoice: ";
        int act;
        cin >> act;
        clearInput();
        if (act == 1) activityLevel = "Sedentary";
        else if (act == 2) activityLevel = "Lightly Active";
        else if (act == 3) activityLevel = "Moderately Active";
        else if (act == 4) activityLevel = "Very Active";
        else {
            cout << "Invalid choice. Please enter the correct option.\n";
            continue;
        }
        break;
    }

    string allergy;
    cout << "\nAny food allergies?\n";
    cout << "1. Nuts\n2. Dairy\n3. Gluten\n4. No allergies\n5. Other\nChoice: ";
    int allergyChoice;
    cin >> allergyChoice;
    clearInput();
    if (allergyChoice == 1) allergy = "Nuts";
    else if (allergyChoice == 2) allergy = "Dairy";
    else if (allergyChoice == 3) allergy = "Gluten";
    else if (allergyChoice == 4) allergy = "None";
    else {
        allergy = "Other";
        cout << "Please specify your food allergies: ";
        getline(cin, allergy);
    }

    string goal;
    cout << "\nWhat is your goal?\n";
    cout << "1. Lose Weight\n2. Gain Weight\n3. Maintain Weight\n4. Improve Fitness\n5. Build Muscle\nChoice: ";
    int goalChoice;
    cin >> goalChoice;
    clearInput();
    switch (goalChoice) {
        case 1: goal = "Lose Weight"; break;
        case 2: goal = "Gain Weight"; break;
        case 3: goal = "Maintain Weight"; break;
        case 4: goal = "Improve Fitness"; break;
        case 5: goal = "Build Muscle"; break;
        default: goal = "Maintain Weight"; break;
    }

    string condition;
    cout << "\nAny health conditions?\n";
    cout << "1. Diabetes\n2. High Blood Pressure\n3. Heart Disease\n4. None\n5. Other\nChoice: ";
    int condChoice;
    cin >> condChoice;
    clearInput();
    if (condChoice == 1) condition = "Diabetes";
    else if (condChoice == 2) condition = "High Blood Pressure";
    else if (condChoice == 3) condition = "Heart Disease";
    else if (condChoice == 4) condition = "None";
    else {
        condition = "Other";
        cout << "Please specify your health condition: ";
        getline(cin, condition);
    }

    // Display Summary
    cout << "\n===== SUMMARY OF YOUR INPUTS =====\n";
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Gender: " << (gender == 1 ? "Male" : "Female") << endl;
    cout << "Height: " << height_cm << " cm\n";
    cout << "Weight: " << weight_kg << " kg\n";
    cout << "BMI: " << bmi << " (" << bmiCategory << ")\n";
    cout << "Body Shape: " << bodyShape << endl;
    cout << "Dietary Preferences: " << restriction << endl;
    cout << "Activity Level: " << activityLevel << endl;
    cout << "Allergy: " << allergy << endl;
    cout << "Goal: " << goal << endl;
    cout << "Health Condition: " << condition << endl;

    // Display Recommendations
    cout << "\n===== YOUR PERSONALIZED DIET RECOMMENDATION =====\n";
    if (age >= 60) {
        cout << "\nSince you're 60 or older, we'll focus on gentle, nutrient-rich meals.\n";
        cout << "Include fiber (vegetables, fruits), calcium, and lean proteins.\n";
        cout << "Stay hydrated and eat smaller but more frequent meals for better digestion.\n";
    }
    
    if (bmiCategory == "Underweight") {
        cout << "- Eat calorie-rich, nutritious foods: avocados, nuts, healthy oils\n";
        cout << "- Protein: eggs, chicken, Greek yogurt\n";
        cout << "- Carbs: oats, sweet potatoes, whole grain bread\n";
        cout << "- Tip: Eat 3 meals + 2-3 snacks daily\n";
    } else if (bmiCategory == "Normal weight") {
        cout << "- Keep a balanced meal: veggies, lean proteins, grains, healthy fats\n";
        cout << "- Hydrate well (8 glasses/day)\n";
    } else if (bmiCategory == "Overweight") {
        cout << "- Focus on high-protein, high-fiber meals\n";
        cout << "- Avoid sugary snacks, processed food\n";
    } else {
        cout << "- Low-calorie, high-fiber, protein-rich foods\n";
        cout << "- Avoid sugary drinks, white carbs, salty snacks\n";
    }

    cout << "\nBased on Body Shape: " << bodyShape << endl;
    if (bodyShape == "Ectomorph") {
        cout << "- Eat more often with larger portions\n";
        cout << "- Focus on high-calorie foods like nuts, dairy, whole grains\n";
    } else if (bodyShape == "Endomorph") {
        cout << "- Go low-carb, high-protein and fiber\n";
        cout << "- Avoid processed, sugary, starchy foods\n";
    } else {
        cout << "- Balanced diet works best. Adjust portion based on activity\n";
    }

    cout << "\n===== DIETARY CONSIDERATIONS =====\n";

    if (restriction != "None") {
        cout << "\nDietary note: Following a " << restriction << " diet.\n";

        if (restriction == "Gluten-Free") {
            cout << "- Eat rice, corn, quinoa, potatoes, and gluten-free oats.\n";
            cout << "- Avoid wheat, barley, rye, and most traditional pasta and bread.\n";
        } 
        else if (restriction == "Dairy-Free") {
            cout << "- Use almond milk, soy milk, or oat milk as alternatives.\n";
            cout << "- Include calcium-rich foods like leafy greens and fortified plant milk.\n";
            cout << "- Avoid cheese, butter, milk, yogurt made from animal dairy.\n";
        } 
        else if (restriction == "Vegetarian") {
            cout << "- Include tofu, lentils, beans, eggs, and dairy like milk or yogurt.\n";
            cout << "- Ensure adequate protein and iron from legumes and eggs.\n";
        } 
        else if (restriction == "Vegan") {
            cout << "- Focus on plant-based foods: beans, lentils, tofu, vegetables, grains.\n";
            cout << "- Include B12 sources like fortified cereals, nutritional yeast, or supplements.\n";
            cout << "- Get protein from legumes, soy products, and whole grains.\n";
        }
        if (restriction == "Vegan" && allergy == "Nuts") {
            cout << "- Note: Since you're allergic to nuts, avoid nut-based products like almond milk and peanut butter.\n";
        }
        if (restriction == "Vegetarian" && allergy == "Dairy") {
            cout << "- Note: You're dairy allergic, so skip milk, cheese, and yogurt despite being vegetarian.\n";
        }
        if (restriction == "Gluten-Free" && allergy == "Gluten") {
            cout << "- Reminder: Strictly avoid wheat, barley, and rye due to your gluten allergy.\n";
        }
        if (restriction == "Dairy-Free" && allergy == "Dairy") {
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
        if (activityLevel == "Sedentary") {
            cout << "- Start with walking and gentle stretches\n";
        } else if (activityLevel == "Lightly Active") {
            cout << "- Add light cardio & bodyweight training\n";
        } else if (activityLevel == "Moderately Active") {
            cout << "- Jogging, swimming, resistance training\n";
        } else {
            cout << "- HIIT, strength circuits, endurance training\n";
        }

        if (age >= 60) {
            cout << "- Prioritize safe, gentle exercises like water aerobics\n";
        }

        if (condition == "Diabetes") {
            cout << "\n[Health Tip - Diabetes]\n";
            cout << "- Avoid processed sugar, focus on fiber-rich food, and monitor blood sugar.\n";
        } else if (condition == "High Blood Pressure") {
            cout << "\n[Health Tip - High Blood Pressure]\n";
            cout << "- Limit sodium, eat potassium-rich foods like bananas and spinach, exercise regularly.\n";
        } else if (condition == "Heart Disease") {
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
    if (goal == "Lose Weight") {
        cout << "- Eat nutrient-dense meals\n- Exercise 30-45 mins daily\n- Hydrate well\n";
    } else if (goal == "Gain Weight") {
        cout << "- Eat 3 full meals + 2-3 snacks\n- Strength train regularly\n";
    } else if (goal == "Maintain Weight") {
        cout << "- Balanced meals + 150 mins activity weekly\n";
    } else if (goal == "Improve Fitness") {
        cout << "- Combine cardio and strength 4-5x weekly\n";
    } else if (goal == "Build Muscle") {
        cout << "- High protein intake + 4-5x weight training/week\n";
    }

    cout << "\nThanks for chatting with NutriBot! Stay healthy, " << name << "!\n";
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
