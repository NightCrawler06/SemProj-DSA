#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>
#include <cmath>

using namespace std;

struct Meal {
    string name;
    int calories;
    int protein;
    int carbs;
    int fats;
};

struct Exercise {
    string name;
    int duration;
};

void printHeader() {
    cout << "Welcome to the Diet & Exercise Chatbot!" << endl;
    cout << "Please answer the following questions to get your personalized plan." << endl;
}

int getValidInput(string prompt, int min, int max) {
    int input;
    while (true) {
        cout << prompt;
        cin >> input;
        if (cin.fail() || input < min || input > max) {
            cin.clear();
            cin.ignore();
            cout << "Invalid input. Please enter a number between " << min << " and " << max << "." << endl;
        } else break;
    }
    return input;
}

string getValidStringInput(string prompt) {
    string input;
    cout << prompt;
    cin.ignore();
    getline(cin, input);
    return input;
}


float computeBMI(int weight, int heightCm) {
    float heightM = heightCm / 100.0;
    return weight / (heightM * heightM);
}

string getBMICategory(float bmi) {
    if (bmi < 18.5) return "Underweight";
    else if (bmi < 25) return "Normal";
    else if (bmi < 30) return "Overweight";
    else return "Obese";
}

vector<Meal> getMealsByBMI(string category) {
    if (category == "Underweight") {
        return {
            {"Rice Bowl w/ Chicken", 700, 55, 65, 25},
            {"Protein Pancakes", 650, 45, 70, 20},
            {"Steak and Potatoes", 700, 50, 60, 30}
        };
    } else if (category == "Normal") {
        return {
            {"Chicken with Rice", 500, 40, 45, 15},
            {"Salmon with Quinoa", 600, 50, 40, 30},
            {"Tofu Stir Fry", 400, 20, 35, 18}
        };
    } else {
        return {
            {"Veggie Soup", 250, 8, 20, 6},
            {"Grilled Fish & Greens", 400, 35, 15, 10},
            {"Avocado Toast", 350, 12, 30, 16}
        };
    }
}

void recommendMeals(string activityLevel, string gender, int weeks, string allergy, string bmiCategory, bool showMacros) {
    vector<Meal> selectedMeals = getMealsByBMI(bmiCategory);

    cout << "\nBased on your BMI category (" << bmiCategory << "), here is your recommended meal plan:" << endl;

    for (int w = 1; w <= weeks; ++w) {
        cout << "\nWeek " << w << ":" << endl;
        for (int d = 1; d <= 7; ++d) {
            int bi = (d + w * 2) % selectedMeals.size();
            int li = (d + w * 3 + 1) % selectedMeals.size();
            int di = (d + w * 5 + 2) % selectedMeals.size();

            Meal b = selectedMeals[bi], l = selectedMeals[li], diM = selectedMeals[di];

            if (
                (!allergy.empty() && (
                    b.name.find(allergy) != string::npos ||
                    l.name.find(allergy) != string::npos ||
                    diM.name.find(allergy) != string::npos))) {
                cout << "Day " << d << ": Skipped due to allergy match.\n";
                continue;
            }

            cout << "Day " << d << ":\n";
            cout << "  Breakfast: " << b.name << " (" << b.calories << " kcal, " << b.protein << "g protein, "
                 << b.carbs << "g carbs, " << b.fats << "g fats)" << endl;
            cout << "  Lunch: " << l.name << " (" << l.calories << " kcal, " << l.protein << "g protein, "
                 << l.carbs << "g carbs, " << l.fats << "g fats)" << endl;
            cout << "  Dinner: " << diM.name << " (" << diM.calories << " kcal, " << diM.protein << "g protein, "
                 << diM.carbs << "g carbs, " << diM.fats << "g fats)" << endl;

            if (showMacros) {
                int tCal = b.calories + l.calories + diM.calories;
                int tPro = b.protein + l.protein + diM.protein;
                int tCarbs = b.carbs + l.carbs + diM.carbs;
                int tFat = b.fats + l.fats + diM.fats;
                cout << "  Total: " << tCal << " kcal, " << tPro << "g protein, "
                     << tCarbs << "g carbs, " << tFat << "g fats\n";
            }
        }
    }
}

void recommendExercises(string gender, int weeks) {
    vector<Exercise> maleExercises = {
        {"Push-Ups", 15}, {"Squats", 20}, {"Pull-Ups", 10}, {"Deadlifts", 25}, {"Bench Press", 20}, {"Lunges", 15}, {"Planks", 10}
    };
    vector<Exercise> femaleExercises = {
        {"Squats", 20}, {"Lunges", 15}, {"Push-Ups", 10}, {"Planks", 20}, {"Leg Raises", 15}, {"Glute Bridges", 12}, {"Mountain Climbers", 15}
    };

    vector<Exercise> selected = (gender == "male") ? maleExercises : femaleExercises;

    cout << "\nHere is your exercise plan:" << endl;
    for (int w = 1; w <= weeks; ++w) {
        cout << "\nWeek " << w << ":" << endl;
        for (int d = 1; d <= 7; ++d) {
            Exercise ex = selected[(d + w) % selected.size()];
            cout << "Day " << d << " - Exercise: " << ex.name << " for " << ex.duration << " minutes." << endl;
        }
    }
}

void recommendHydration(int activityLevel) {
    double waterIntake = (activityLevel == 1) ? 2.0 : (activityLevel == 2) ? 2.5 : 3.0;

    cout << "You should drink at least " << waterIntake << "L of water per day because your activity level is ";
    if (activityLevel == 1) cout << "light." << endl;
    else if (activityLevel == 2) cout << "average." << endl;
    else cout << "very active." << endl;
}

int main() {
    while (true) {
        printHeader();

        string name = getValidStringInput("What's your name? ");
        int age = getValidInput("How old are you? ", 1, 120);
        int height = getValidInput("What's your height (in cm)? ", 50, 250);
        int weight = getValidInput("What's your weight (in kg)? ", 10, 300);

        string activityLevels[] = {"light", "average", "very active"};
        int act = getValidInput("Choose your activity level (1 = light, 2 = average, 3 = very active): ", 1, 3);
        string activityLevel = activityLevels[act - 1];

        string gender = getValidStringInput("Please specify your gender (male/female): ");
        int weeks = getValidInput("For how many weeks would you like your diet and exercise plan? (1-4): ", 1, 4);

        float bmi = computeBMI(weight, height);
        string bmiCategory = getBMICategory(bmi);
        cout << "\nYour BMI is " << fixed << setprecision(1) << bmi << " - Category: " << bmiCategory << "\n";

        string hasAllergy = getValidStringInput("Do you have any food allergies? (yes/no): ");
        string allergy = "";
        if (hasAllergy == "yes") {
            allergy = getValidStringInput("Please specify your food allergy: ");
        }

        string macroChoice = getValidStringInput("Would you like to see daily macros (yes/no)? ");
        bool showMacros = (macroChoice == "yes");

        recommendMeals(activityLevel, gender, weeks, allergy, bmiCategory, showMacros);
        recommendExercises(gender, weeks);

        string hydrationChoice = getValidStringInput("\nWould you like a hydration recommendation based on your activity level? (yes/no): ");
        if (hydrationChoice == "yes") {
            recommendHydration(act);
        } else {
            cout << "\nRemember: Progress is progress, no matter how small!\n";
        }

        string exitChoice = getValidStringInput("\nWould you like to create a plan for another user? (yes/no): ");
        if (exitChoice != "yes") {
            cout << "Thank you for using the Diet & Exercise Chatbot. Goodbye!" << endl;
            break;
        }
    }

    return 0;
}
