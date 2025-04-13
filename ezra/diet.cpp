#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cctype>
using namespace std;

string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

bool isAlphabetic(const string& str) {
    for (char c : str)
        if (!isalpha(c) && !isspace(c)) return false;
    return !str.empty();
    
}

int getValidatedAge(string prompt) {
    string input;
    int age;
    while (true) {
        cout << prompt;
        getline(cin, input);
        if (input.empty()) {
            cout << "No input detected. Please enter a valid age.\n";
            continue;
        }
        try {
            age = stoi(input);
        } catch (...) {
            cout << "Invalid input. Please enter a valid age.\n";
            continue;
        }
        if (age < 0) cout << "Invalid input. Please enter a valid age.\n";
        else if (age > 120) cout << "Age seems too high. Please enter a realistic age.\n";
        else return age;
    }
}

double getValidatedDouble(string prompt, string label) {
    string input;
    double value;
    while (true) {
        cout << prompt;
        getline(cin, input);
        if (input.empty()) {
            cout << "Invalid Input. Please enter valid " << label << ".\n";
            continue;
        }
        try {
            value = stod(input);
        } catch (...) {
            cout << "Invalid Input. Please enter valid " << label << ".\n";
            continue;
        }
        if (value <= 0) cout << "Invalid Input. Please enter valid " << label << ".\n";
        else return value;
    }
}

string getValidatedOption(string prompt, const string options[], int size) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        for (int i = 0; i < size; ++i) {
            if (toLower(input) == toLower(options[i])) return options[i];
        }
        cout << "Invalid input. Please choose from the given options.\n";
    }
}
int main() {
    string name, lifestyle, bodyShape, foodRestriction, healthCondition, goal, wantsExercise;
    int age;
    double heightCm, weightKg;
    cout << "\n============================\n";
    cout << "Hi there! My name is Dietry! Welcome to the Diet Recommender Bot!\n";
    cout << "Get Your Perfect Diet Plan Today!\n";
    cout << "============================\n";

    // Step 1: Name
    cout << "============================\n";
    cout << "Let's get started. First, what's your name? ";
    cout << "============================\n";
    getline(cin, name);
    while (!isAlphabetic(name)) {
        cout << "Invalid input. Please enter a valid name (letters only): ";
        getline(cin, name);
    }

    // Step 2: Age
    cout << "============================\n";
    age = getValidatedAge("Nice to meet you, " + name + "! How old are you? ");
    cout << "============================\n";
    
    // Step 3: Height and Weight
    cout << "============================\n";
    heightCm = getValidatedDouble("Thanks! Now, could you tell me your height in centimeters? ", "Height in cm");
    weightKg = getValidatedDouble("Great! What's your weight in kilograms? ", "Weight in kg");
    cout << "============================\n";

    
    // Step 4: Compute BMI
    double heightM = heightCm / 100.0;
    double bmi = weightKg / (heightM * heightM);
    string bmiCategory;
    if (bmi < 18.5) bmiCategory = "Underweight";
    else if (bmi < 25) bmiCategory = "Normal weight";
    else if (bmi < 30) bmiCategory = "Overweight";
    else bmiCategory = "Obese";
    cout << "============================\n";
    cout << fixed << setprecision(1);
    cout << "\nYour BMI is " << bmi << ", which means you're classified as " << bmiCategory << ".\n";
    cout << "============================\n";
    
    // Step 5: Lifestyle
    const string lifestyleOptions[] = {
        "Sedentary", "Lightly Active", "Moderately Active", "Very Active"
    };
    lifestyle = getValidatedOption(
        "\nNow, let's talk about your lifestyle. How would you describe your typical activity level?\n"
        "Options:\n Sedentary(little or no exercise)\n Lightly Active(light exercise or sports 1-3 days/week),\n Moderately Active(moderate exercise or sports 3-5 days/week),\n Very Active(hard exercise or sports 6-7 days a week) \nYour choice: ",
        lifestyleOptions, 4
    );
    cout << "============================\n";

    // Step 6: Body Shape
    const string bodyOptions[] = {
        "Ectomorph", "Endomorph", "Mesomorph"
    };
    bodyShape = getValidatedOption(
        "\nGot it! Lastly, which body shape best describes you?\n"
        "Options:\n Ectomorph(naturally slim, struggles to gain weight),\n Endomorph(rounder, tends to gain weight easily),\n Mesomorph(athletic, can gain or lose weight relatively easily) \nYour choice: ",
        bodyOptions, 3
    );
    cout << "============================\n";

    // Step 7: Food Restrictions
    const string foodOptions[] = {
        "Vegetarian", "Vegan", "Gluten-free", "Dairy-free", "Nut allergy", "No restrictions"
    };
    foodRestriction = getValidatedOption(
        "\nDo you have any specific food restrictions or preferences?\n"
        "Options: \nVegetarian, \nVegan, \nGluten-free, \nDairy-free, \nNut allergy, \nNo restrictions\nYour choice: ",
        foodOptions, 6
    );
    cout << "============================\n";

    // Step 8: Health Conditions
    const string healthOptions[] = {
        "Diabetes", "High Blood Pressure", "Heart Disease", "No health conditions"
    };
    healthCondition = getValidatedOption(
        "\nBefore we move forward, are there any health conditions you'd like me to consider?\n"
        "Options: \nDiabetes, \nHigh Blood Pressure, \nHeart Disease, \nNo health conditions \nYour choice: ",
        healthOptions, 4
    );
    cout << "============================\n";

    if (toLower(healthCondition) != "no health conditions") {
        cout << "Thank you for sharing! Having conditions like " << healthCondition
             << " can impact how your body responds to food and exercise, so I'll make sure to account for that.\n";
    } else {
        cout << "Great! Since there are no health conditions to consider, I'll tailor the recommendations to your general needs.\n";
    }

    // Step 9: Goals
    const string goalOptions[] = {
        "Lose Weight", "Gain Weight", "Maintain a Healthy Weight", "Improve Fitness", "Build Muscle"
    };
    goal = getValidatedOption(
        "\nNow that we've covered your health details, let's talk about your goals!\n"
        "Options: \nLose Weight, \nGain Weight, \nMaintain a Healthy Weight, \nImprove Fitness, \nBuild Muscle\nYour choice: ",
        goalOptions, 5
    );
    cout << "============================\n";
    // Step 10: Ask about Exercise Plan
    const string yesNo[] = {"yes", "no"};
    wantsExercise = getValidatedOption(
        "\nWould you like to create a detailed exercise plan along with this diet? (yes/no): ", yesNo, 2
    );
    cout << "============================\n";

    // Step 11: Diet Recommendations Based on BMI
    cout << "\n--- Diet Recommendations ---\n";

    if (bmiCategory == "Underweight") {
        cout << "Since you're underweight, your body might need extra calories to gain and maintain a healthy weight. \nA nutrient-dense diet with healthy fats and protein will help you build muscle mass, which is key for a healthy weight gain.\n";
        cout << "============================\n";
        cout << "Recommended foods:\n";
        cout << "============================\n";
        cout << "- Lean meats (chicken, turkey): Rich in protein, these foods will help build muscle.\n";
        cout << "- Nuts and seeds: Full of healthy fats and calories to help you gain weight.\n";
        cout << "- Avocados: High in healthy fats and calories, perfect for boosting your caloric intake.\n";
        cout << "- Whole grains (brown rice, quinoa): They provide energy and help keep your body strong.\n";
        cout << "Lean proteins like chicken help repair muscle tissue, while healthy fats like those in avocados and nuts increase your calorie intake without promoting fat gain.\n Whole grains give you long-lasting energy, keeping your metabolism healthy.\n";
    } else if (bmiCategory == "Normal weight") {
        cout << "You're at a healthy weight! It's important to maintain balance by eating a variety of foods that will give you the right amount of energy, vitamins, and minerals.\n";
        cout << "============================\n";
        cout << "Recommended foods:\n";
        cout << "============================\n";
        cout << "- Lean proteins (fish, chicken, tofu): Essential for muscle maintenance and growth.";
        cout << "- Vegetables (broccoli, spinach, kale): Full of vitamins, minerals, and fiber that promote overall health.";
        cout << "- Fruits (berries, apples, bananas): Provide essential nutrients and antioxidants to keep your immune system strong.";
        cout << "- Whole grains (oats, brown rice, quinoa): Offer steady energy release and keep you feeling full.";
        cout << "A balanced diet is key to maintaining a healthy weight. Lean proteins and fiber-rich vegetables provide essential nutrients, while whole grains help manage your energy levels throughout the day.\n";
    } else if (bmiCategory == "Overweight") {
        cout << "To manage your weight, focusing on a nutrient-dense, lower-calorie diet is essential. A higher-protein, lower-carb diet can help with fat loss and muscle building.\n";
        cout << "============================\n";
        cout << "Recommended foods:\n";
        cout << "============================\n";
        cout << "- Lean meats (chicken breast, fish): High in protein and low in fat, helping build lean muscle.\n";
        cout << "- Leafy greens (spinach, kale, lettuce): Low-calorie and rich in fiber, helping you feel full without extra calories.";
        cout << "- Legumes (beans, lentils): Great sources of protein and fiber, they will keep you feeling full and satisfied.";
        cout << "- Avoid sugary foods and drinks: Sugary foods can lead to weight gain and fat accumulation, especially around the belly.";
        cout << "Protein helps build lean muscle, while fiber from vegetables and legumes aids digestion and satiety. \nLimiting sugar intake helps manage calorie consumption and avoids excess fat storage.";
    } else {
        cout << "For weight management, a low-calorie, high-protein diet combined with regular physical activity is crucial. \nAvoid processed foods, refined sugars, and unhealthy fats.\n";
        cout << "============================\n";
        cout << "Recommended foods:\n";
        cout << "============================\n";
        cout << "- Lean proteins (turkey, chicken breast): They will help you maintain muscle mass while losing fat.\n";
        cout << "- Non-starchy vegetables (cucumbers, broccoli): Very low in calories but high in fiber, they're perfect for filling up.\n";
        cout << "- Healthy fats (olive oil, avocado): While low in carbs, they are high in essential nutrients.\n";
        cout << "- Avoid high-carb foods like bread, pasta, and sugary snacks.\n";
        cout << "Protein and fiber help promote muscle retention and keep you full for longer, while healthy fats support metabolism.\n Cutting out high-carb and sugary foods will reduce fat storage.\n";
    }

    // Body Shape
    cout << "\n--- Body Shape Nutrition Tips ---\n";
    if (bodyShape == "Ectomorph") {
        cout << "As an ectomorph, your metabolism is fast, and you might find it harder to gain weight. Focus on nutrient-dense, calorie-rich foods to support muscle growth.\n";
        cout << "============================\n";
        cout << "Recommended foods:\n";
        cout << "============================\n";
        cout << "- Full-fat dairy (cheese, yogurt): Calorie-dense and great for building mass.\n";
        cout << "- Oils (olive, coconut): Adding oils to meals will increase your calorie intake without feeling too full.\n";
        cout << "- Whole grains (oats, quinoa, rice): Slow-digesting carbs that provide long-lasting energy.\n";
        cout << "Ectomorphs often have a high metabolism, meaning they burn calories quickly. High-calorie, nutrient-dense foods like full-fat dairy and oils will provide the \n";
        cout << "necessary calories for weight gain and muscle development.\n";
    } else if (bodyShape == "Endomorph") {
        cout << "As an endomorph, your body tends to store more fat, especially around the waist. Focusing on lean proteins and reducing your carb intake will help control fat gain.\n";
        cout << "============================\n";
        cout << "Recommended foods:\n";
        cout << "============================\n";
        cout << "- Lean proteins (chicken, turkey): Protein will support muscle maintenance while aiding fat loss.\n";
        cout << "- Leafy vegetables (spinach, lettuce): High in fiber, they help manage hunger without adding calories.\n";
        cout << "- Healthy fats (avocados, nuts): Help regulate hormone levels and prevent fat storage.\n";
        cout << "Protein supports muscle mass, and high-fiber, low-carb vegetables help control hunger while promoting fat loss.\n Healthy fats are essential for balancing hormones, which can affect fat storage.\n";
    } else if (bodyShape == "Mesomorph") {
        cout << "Mesomorphs generally have a well-balanced body type and can gain or lose weight relatively easily\n. You can maintain your physique with a balanced diet.\n";
        cout << "============================\n";
        cout << "Recommended foods:\n";
        cout << "============================\n";
        cout << "- Proteins (chicken, fish, tofu): Support muscle building and fat loss.\n";
        cout << "- Whole grains (brown rice, quinoa): Help maintain energy and prevent fat gain.\n";
        cout << "- Fruits and vegetables: Rich in vitamins, minerals, and fiber, they're crucial for your overall health.\n";
        cout << "As a mesomorph, you can afford a balance of macronutrients. \nProtein helps build and maintain muscle, while whole grains and vegetables ensure steady energy levels without excessive fat accumulation.";
    }

    // Food Restriction Tips
    cout << "\n--- Food Restriction Adjustments ---\n";
    if (foodRestriction == "Vegetarian") {
        cout << "- Because you are Vegetarian, focus on plant-based proteins, such as tofu, lentils, and beans.\n Replace dairy with alternatives like soy or almond milk.\n";
    } else if (foodRestriction == "Vegan") {
        cout << "- Because you are Vegan, ensure you're getting complete proteins from foods like quinoa, tempeh, and lentils,\n and be mindful of B12 and iron intake.\n";
    } else if (foodRestriction == "Gluten-free") {
        cout << "- Because you are Gluten- Free, choose naturally gluten-free grains like quinoa, rice, and potatoes.\n";
    } else if (foodRestriction == "Dairy-free") {
        cout << "- Because you are Dairy- free, use non-dairy alternatives for your calcium and protein needs,\n such as almond milk, coconut yogurt, and leafy greens.\n";
    } else if (foodRestriction == "Nut allergy") {
        cout << "- Because you are Nut allergy, substitute with seeds like chia, sunflower, and pumpkin seeds.\n";
    } else {
        cout << "- No restrictions. You're free to explore a balanced diet!\n";
    }

    // Health Condition Tips
    cout << "\n--- Health Considerations ---\n";
    if (healthCondition == "Diabetes") {
        cout << "Since you have diabetes, it's important to monitor your carbohydrate intake and focus on foods that help maintain stable blood sugar levels. \n";
        cout << "So, I recommend a balanced diet rich in fiber, lean proteins, healthy fats, and complex carbohydrates. \nRegular meals and snacks can also help stabilize blood sugar throughout the day.\n";
    } else if (healthCondition == "High Blood Pressure") {
        cout << "With high blood pressure, it's crucial to follow a heart-healthy diet. \n This means eating more fruits, vegetables, whole grains, and lean proteins while limiting sodium, processed foods, and saturated fats. \n The DASH diet (Dietary Approaches to Stop Hypertension) is a great option. \n";
    } else if (healthCondition == "Heart Disease") {
        cout << "For heart disease, a diet low in saturated fats, trans fats, and cholesterol is key. \n Focus on eating foods that are heart-healthy, such as leafy greens, berries, nuts, seeds, and fatty fish rich in omega-3s. \n Reducing sodium intake and choosing whole grains will also benefit your cardiovascular health. \n";
    } else {
        cout << "Since there are no health conditions to consider, I'll tailor the recommendations to your general needs. \n A balanced diet with a mix of lean proteins, whole grains, healthy fats, and plenty of fruits and vegetables will give you the nutrients your body needs.\n";
    }
    // Step 10: Final Summary with Detailed Explanations
    cout << "\n\n--- Final Summary of Your Profile & Recommendations ---\n";
    cout << "============================\n";
    cout << "Name: " << name << "\n";
    cout << "Age: " << age << "\n";
    cout << "Height: " << heightCm << " cm\n";
    cout << "Weight: " << weightKg << " kg\n";
    cout << "BMI: " << bmi << " (Category: " << bmiCategory << ")\n";
    cout << "============================\n";
    // Lifestyle
    cout << "Lifestyle: " << lifestyle << "\n";
    cout << "============================\n";
    if (lifestyle == "Sedentary") {
        cout << "Since you're not very active, start with low-impact activities like walking or stretching. \nThese exercises will help increase circulation and promote joint flexibility.\n\n";
        cout << "Light activity like walking helps activate muscles and promotes cardiovascular health without overstraining the body.\n\n";
    } else if (lifestyle == "Lightly Active") {
        cout << "Consider adding some light cardio (e.g., walking or cycling) and strength exercises like bodyweight squats or push-ups.\n\n";
        cout << "Cardio will improve heart health, while strength exercises will build muscle, improving metabolism.\n\n";
    } else if (lifestyle == "Moderately Active") {
        cout << "Since you're already moderately active, you can increase the intensity by doing running, swimming, or resistance training with weights.\n\n";
        cout << "Cardio improves endurance, and strength training with weights will help you build muscle, which in turn burns more calories.\n\n";
    } else if (lifestyle == "Very Active") {
        cout << "Since you're very active, I recommend incorporating high-intensity interval training (HIIT) and intense strength training sessions.\n These will challenge your body and help you build both strength and endurance.\n\n";
        cout << "HIIT maximizes calorie burn and improves both strength and cardiovascular health.\n Intense strength training builds muscle, which accelerates fat loss and improves body composition.\n\n";
    }

    // Body Shape
    cout << "============================\n";
    cout << "Body Shape: " << bodyShape << "\n";
    cout << "============================\n";
    if (bodyShape == "Ectomorph") {
        cout << "You're naturally slim with a fast metabolism, which can make gaining weight harder. Focus on high-calorie meals, full-fat dairy, and strength training to build muscle.\n";
    } else if (bodyShape == "Endomorph") {
        cout << "You may store fat more easily. Stick to lean protein, fiber-rich veggies, and healthy fats to support your metabolism and avoid fat gain.\n";
    } else if (bodyShape == "Mesomorph") {
        cout << "You're naturally athletic. A balanced diet with enough protein, carbs, and fats will help you maintain or shape your body.\n";
    }

    // Food 
    cout << "============================\n";
    cout << "Food Restrictions: " << foodRestriction << "\n";
    cout << "============================\n";
    if (foodRestriction == "No restrictions") {
        cout << "Great! You can enjoy a wide variety of foods with no limitations - perfect for flexible meal planning.\n";
    } else if (foodRestriction == "Vegetarian") {
        cout << "As a vegetarian, focus on plant-based proteins like tofu, lentils, and beans.\n";
    } else if (foodRestriction == "Vegan") {
        cout << "As a vegan, make sure to get complete proteins from foods like quinoa and tempeh, and monitor B12 and iron intake.\n";
    } else if (foodRestriction == "Gluten-free") {
        cout << "You're gluten-free. Choose grains like rice, quinoa, and gluten-free oats.\n";
    } else if (foodRestriction == "Dairy-free") {
        cout << "You're dairy-free. Use alternatives like almond milk and coconut yogurt, and get calcium from leafy greens.\n";
    } else if (foodRestriction == "Nut allergy") {
        cout << "You're avoiding nuts. Seeds like chia, sunflower, and pumpkin are great substitutes for healthy fats and protein.\n";
    }

    // Health Condition
    cout << "============================\n";
    cout << "Health Condition: " << healthCondition << "\n";
    cout << "============================\n";
    if (healthCondition == "No health conditions") {
        cout << "You have no medical concerns, so your plan can be based entirely on your goals and preferences.\n";
    } else if (healthCondition == "Diabetes") {
        cout << "Because you have health condition which is diabetes, for exercise, low to moderate-intensity activities like walking, swimming, or cycling are ideal, as they can improve insulin sensitivity.\n";
    } else if (healthCondition == "High Blood Pressure") {
        cout << "Because you have health condition which is High Blood Pressure exercise like walking, biking, or yoga can help reduce stress and improve circulation. Regular physical activity can significantly support lowering blood pressure.\n";
    } else if (healthCondition == "Heart Disease") {
        cout << "Because you have health condition which is Heart Disease exercise like walking, strength training, or swimming can help improve heart function and circulation, but make sure to check with your doctor before starting any new routines.\n";
    }

    // Goal
    cout << "============================\n";
    cout << "Goal: " << goal << "\n";
    cout << "============================\n";
    if (goal == "Gain Weight") {
        cout << "To help you gain weight in a healthy way, it's important to focus on both nutrition and lifestyle.\n Here are some extra tips beyond diet and exercise:\n";
        cout << "- Calorie Tracking: Monitor your calorie intake to ensure you're consistently in a calorie surplus, which is crucial for weight gain. \n";
        cout << "- Meal Timing: Try eating smaller meals more frequently throughout the day.\n Eating every 3-4 hours can help you consistently provide your body with the energy and nutrients it needs to build muscle and gain weight. \n";
        cout << "- Focus on Strength Training: In addition to eating more calories, aim to incorporate strength training to ensure that the weight you gain is muscle, not fat. \n";
        cout << "- Recovery: Prioritize recovery and rest. Muscle growth happens during recovery, not during the workout itself, so give your muscles time to rebuild. \n";
        cout << "- High-Quality Snacks: Incorporate healthy, calorie-dense snacks into your daily routine, such as smoothies with protein, nut butters, or energy bars. \n";
    } else if (goal == "Lose Weight") {
        cout << "To help you lose weight effectively, consistency is key!\n Here are a few recommendations aside from diet and exercise:\n";
        cout << "- Hydration: Drink plenty of water throughout the day. Hydration plays a crucial role in weight loss by promoting digestion and controlling appetite. \n";
        cout << "- Sleep: Aim for 7-9 hours of sleep per night. Lack of sleep can hinder weight loss and negatively affect metabolism. \n";
        cout << "- Mindful Eating: Practice mindful eating by focusing on your food, eating slowly, and stopping when you're full. This can prevent overeating. \n"; 
        cout << "- Track Progress: Keep a journal of your meals and workouts to stay accountable. Tracking helps in identifying habits that can be improved. \n";
        cout << "- Stress Management: High stress can lead to emotional eating. Try to incorporate relaxation techniques like deep breathing, meditation, or yoga into your routine. \n";   
    } else if (goal == "Maintain a Healthy Weight") {
        cout << "To maintain a healthy weight, it's important to focus on balance and consistency.\n Here are some helpful tips aside from diet and exercise:\n";
        cout << "- Consistency is Key: Keep a regular eating schedule and balanced diet to avoid fluctuating weight. \n";
        cout << "- Moderation: Don't deprive yourself of your favorite foods, but practice moderation. \n The goal is to enjoy everything in moderation without overeating. \n";
        cout << "- Self-Monitoring: Use a fitness or health app to track your weight, meals, and exercise. This helps keep you accountable and on track. \n";
        cout << "- Mental Well-Being: Maintaining a healthy weight isn't just about physical health—mental health plays a major role. \n Engage in stress-relieving activities like yoga, reading, or listening to music. \n";
        cout << "- Periodic Check-ins: Reassess your weight and health every few months to make sure you're staying on track. \n Sometimes habits need to be adjusted along the way. \n";
    } else if (goal == "Improve Fitness") {
        cout << "Improving fitness is a great goal!\n Here are a few non-exercise-related tips to enhance your fitness journey:\n";
        cout << "- Set Realistic Milestones: Break your fitness journey down into smaller, achievable goals, like running a mile, lifting a specific weight, or mastering a yoga pose. \n";
        cout << "- Nutrition Timing: Pay attention to the timing of your meals and snacks around your workouts. \n Fueling properly before and after workouts can help with recovery and performance. \n";
        cout << "- Rest and Recovery: Fitness improvement isn't only about pushing hard. \n It's just as important to rest and recover between workouts to allow your body to rebuild and strengthen. \n";
        cout << "- Mental Focus: Stay mentally engaged in your workouts. \n Whether it's visualization techniques or mindfulness practices, focusing your mind can help improve performance and results. \n";
        cout << "- Track Progress: Keep a fitness journal or use a fitness app to track progress. \nThis helps to stay motivated and ensures you're progressing steadily. \n";
    } else if (goal == "Build Muscle") {
        cout << "Building muscle requires more than just lifting weights and eating protein.\n Here are some additional tips to help you build muscle more effectively:\n";
        cout << "- Recovery: Allow your muscles to recover properly. After intense training, muscles need rest to grow. Make sure you are getting enough sleep and recovery time. \n";
        cout << "- Protein Intake: Ensure you're getting sufficient protein throughout the day to repair muscle fibers. Try to spread protein intake across multiple meals. \n";
        cout << "- Progressive Overload: Gradually increase the weight, reps, or sets in your workouts to continue stimulating muscle growth. Don't stay at the same level of intensity for too long. \n";
        cout << "- Supplements: Consider supplements like creatine or branched-chain amino acids (BCAAs) to support muscle growth, but make sure to consult with a healthcare provider before using any. \n";
        cout << "- Consistency: Building muscle takes time and patience. Stay consistent with your workouts and nutrition, and you'll see results over time. \n";
    }
    cout << "============================\n";

    if (toLower(wantsExercise) == "yes") {
        cout << "\nExercise Plan Included:\n";
        cout << "============================\n";
        if (age >= 60) {
            cout << "Because you are Senior Citizen and aged is 60 or older, it's important to be cautious and focus on low-impact, \n gentle exercises that promote mobility, flexibility, and overall well-being,\n while avoiding any activities that could put too much strain on the joints or heart.\n";
            cout << "Recommended exercises:\n";
            cout << "- For Basic Exercises: Simple, low-intensity activities like walking, light stretching, yoga, and bodyweight exercises (e.g., seated exercises, gentle squats, or leg raises).\n These exercises help maintain joint mobility, improve circulation, and build strength, without causing excessive strain on the body.\n";
            cout << "- For Safety: Always ensure that exercises are performed with proper form and under supervision if necessary. It's advisable to consult with a healthcare provider before starting any new exercise routine.";
        } else if (lifestyle == "Lightly Active") {
            cout << "Since you're lightly active, add structured light cardio and strength training to support weight gain.\n";
        } else if (lifestyle == "Sedentary") {
            cout << "Start with daily walks or basic stretching. Gradually build up to strength exercises like bodyweight squats.\n";
        } else if (lifestyle == "Moderately Active") {
            cout << "You're already moving well. Add resistance training 3-5 times a week to enhance muscle development.\n";
        } else if (lifestyle == "Very Active") {
            cout << "You're active. Challenge yourself with HIIT or progressive strength training for improved results.\n";
        }
        cout << "============================\n";
        if (healthCondition == "Diabetes") {
            cout << "Because you have health condition which is diabetes, for exercise, low to moderate-intensity activities like walking, swimming, or cycling are ideal, as they can improve insulin sensitivity.\n";
        } else if (healthCondition == "High Blood Pressure") {
            cout << "Because you have health condition which is High Blood Pressure exercise like walking, biking, or yoga can help reduce stress and improve circulation. Regular physical activity can significantly support lowering blood pressure.\n";
        } else if (healthCondition == "Heart Disease") {
            cout << "Because you have health condition which is Heart Disease exercise like walking, strength training, or swimming can help improve heart function and circulation, but make sure to check with your doctor before starting any new routines.\n";
        }
        cout << "============================\n";
    } else {
        cout << "\nExercise Plan: Not Included.\n";
        cout << "No problem! Focus on the diet for now and stay active as you can!\n";
    }

    cout << "\nThank you for using the Diet and Exercise Recommender!\n";
    cout << "Stay healthy, and God bless on your journey!\n";
    

    return 0;
}
