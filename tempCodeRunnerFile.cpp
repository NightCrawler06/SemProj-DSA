cout << "\nBreakdown: \n";
    // Payment schedule breakdown
    double remainingBalance = new_customer.loanAmount;
    double totalInterest = 0;
    double monthlyPayment = calculate_monthly_payment(new_customer.loanAmount, new_customer.interestRate, new_customer.months);

    cout << "\n  Month   Payment Amount    Interest    Principal    Remaining Balance";
    cout << "\n  -----   -------------    --------    ---------    ----------------";

    for (int i = 1; i <= new_customer.months; i++) {
        // Calculate interest for this month
        double monthlyInterest = (remainingBalance * new_customer.interestRate / 100) / 12;
        double principal = monthlyPayment - monthlyInterest;
        
        totalInterest += monthlyInterest;
        remainingBalance -= principal;
        
        // Handle potential negative remainingBalance in final payment due to rounding
        if (i == new_customer.months && remainingBalance < 0) {
            remainingBalance = 0;
        }
        
        // Print formatted row
        cout << "\n  " << setw(5) << i << "   ";
        cout << "PHP " << setw(10) << fixed << setprecision(2) << monthlyPayment << "    ";
        cout << "PHP " << setw(6) << fixed << setprecision(2) << monthlyInterest << "    ";
        cout << "PHP " << setw(7) << fixed << setprecision(2) << principal << "    ";
        cout << "PHP " << setw(14) << fixed << setprecision(2) << remainingBalance;
        
        // If we have many months, just show first 6 and last 6
        if (new_customer.months > 12 && i == 6) {
            cout << "\n  ...      ...             ...         ...         ...";
            // Jump to last 6 months
            int jumpTo = new_customer.months - 6;
            
            // Recalculate remaining balance for the last 6 months
            remainingBalance = new_customer.loanAmount;
            for (int j = 1; j < jumpTo; j++) {
                double monthInt = (remainingBalance * new_customer.interestRate / 100) / 12;
                double princ = monthlyPayment - monthInt;
                remainingBalance -= princ;
            }
            
            i = jumpTo - 1; // -1 because the loop will increment i
        }
    }

    // Show total amounts
    cout << "\n----------------------------------------";
    cout << "\nTotal Payment: PHP " << fixed << setprecision(2) << (monthlyPayment * new_customer.months);
    cout << "\nTotal Interest: PHP " << fixed << setprecision(2) << totalInterest;
    cout << "\nTotal Principal: PHP " << fixed << setprecision(2) << new_customer.loanAmount;

    