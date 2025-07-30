/*
 * Full Name: Hannah Vosteen
 * Filename: project1_hev0011_Hannah_Vosteen.cpp
 * How to compile: g++ -o project1 project1_hev0011_Hannah_Vosteen.cpp
 * How to run: ./project1
 * I went to tutoring to help use ubuntu but only to make sure my code ran in the AU server correctly before I turn it in
 * for collumns like setw(n) i looked up on google how to correctly get each collumn where I want it to print out
 */

#include <iostream>
#include <iomanip>
#include <limits>
int main() {
    using namespace std;
    double loanAmount, interestRateYr, monthlyPayment;
    double monthlyInterestRate, balance, interest, principal; 
 

    
    // this is where the user just sets the amount
    cout << "Loan Amount: ";
    cin >> loanAmount;
    cout << "Interest Rate(% per year): ";
    cin >> interestRateYr;
    cout << "Monthly Payments: ";
    cin >> monthlyPayment;

    //special cases
    if (loanAmount <= 0 || monthlyPayment <= 0 || interestRateYr < 0) {
        cout << "loan and monthly payment must be positive" << endl;
        cout << "interest rate must be above 0 " << endl;
        return 1;
    }

       
        //this is just the math for each value and initializing values
        monthlyInterestRate = interestRateYr / 12.0 / 100.0;
        balance = loanAmount;
        // must do a special case to make sure the payment can be met
        if (monthlyPayment <= loanAmount * monthlyInterestRate) {
            cout << "monthly payment will not meet monthly interest" << endl;
            return 1;
        }
        double totalInterest = 0.0;
        int month = 0;
        

        //tried copy and pasting from the pdf to get exact number of stars but i could not get it exactly space correctly like the slide
        cout << "********************************************************" << endl;
        cout << " Amortization Table " << endl;
        cout << "********************************************************" << endl;

        //this is the collumn setup
        cout << left << setw(10) << "Month" << setw(10) << "Balance" << setw(10) << "Payment" << setw(10) << "Rate" << setw(10) << "Interest" << setw(10) << "Principal" << endl;
        cout << "********************************************************" << endl;

        // now i get the starting space of the collumns that we will have
        cout << left << setw(10) << month << "$" << setw(10) << balance  << setw(10) << "N/A" << setw(10) << "N/A" << setw(10) << "N/A" << setw(10) << "N/A" << endl;

        // for loop until loan is paid for each value
        for (;  balance > 0.005;) {
            month++;
            interest = balance * monthlyInterestRate;
            principal = monthlyPayment - interest;
            if (principal > balance) {
                principal = balance;
                monthlyPayment = interest + principal;
            }
            balance -= principal;
            totalInterest += interest;
            
            //this is going to print the month given the users input number
            cout << left << setw(10) << month << "$" << setw(10) << (balance < 0 ? 0.00 : balance) << "$" << setw(10) << monthlyPayment << setw(10) << (monthlyInterestRate * 100) << "$" << setw(10) << interest << "$" << setw(10) << principal << endl;
        }
        //this is just pritning the end with the values
        cout << "********************************************************" << endl;
        cout << "It takes " << month << " months to pay off the loan" << endl;
        cout << "Total interest paid is: $" << totalInterest << endl;

    

    return 0;
}