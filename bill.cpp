//
//  main.cpp
//  Project_2
//
//  Created by Nakul Khambhati on 4/6/22.
//

#include <iostream>
#include <string>
using namespace std;

int main() {
    
    const double FIRST_TIER_RATE = 5.41;
    const double SECOND_TIER_HIGH_RATE = 9.79;
    const double SECOND_TIER_LOW_RATE = 7.77;
    const int HIGH_TIER_CUTOFF = 23;
    const int LOW_TIER_CUTOFF = 15;                // creating constants to improve readability
    
    int nInitialMeter;
    int nFinalMeter;
    string sCustomerName;
    int nMonthNum;                                 // declaring variables
    
    cout<< "Initial meter reading: ";
    cin >> nInitialMeter;
    if(nInitialMeter<0){
        cout << "---" << endl;
        cout << "The initial meter reading must not be negative." << endl;
        return 1;
    }
    
    cout<< "Final meter reading: ";
    cin >> nFinalMeter;
    cin.ignore(1000, '\n');
    if(nInitialMeter>nFinalMeter){
        cout << "---" << endl;
        cout << "The final meter reading must be at least as large as the initial reading." << endl;
        return 1;
    }
    
    cout<< "Customer name: ";
    getline(cin, sCustomerName);
    if(sCustomerName == ""){
        cout << "---" << endl;
        cout << "You must enter a customer name." << endl;
        return 1;
    }
    
    cout<< "Month number (1=Jan, 2=Feb, etc.): ";
    cin >> nMonthNum;
    if(nMonthNum<1 || nMonthNum>12){
        cout << "---" << endl;
        cout << "The month number must be in the range 1 through 12." << endl;
        return 1;
    }                                                  // collecting input and displaying errors
    
    int usage = nFinalMeter - nInitialMeter;
    double amt;                                 // declaring variables for intermediate calcs
    
    if (nMonthNum >= 4 && nMonthNum <= 10){
        if (usage <= HIGH_TIER_CUTOFF){
            amt = usage * FIRST_TIER_RATE;
        } else amt = HIGH_TIER_CUTOFF * FIRST_TIER_RATE + (usage - HIGH_TIER_CUTOFF) * SECOND_TIER_HIGH_RATE;
    } else if (usage <= LOW_TIER_CUTOFF){
        amt = usage * FIRST_TIER_RATE;
    } else amt = LOW_TIER_CUTOFF * FIRST_TIER_RATE + (usage - LOW_TIER_CUTOFF) * SECOND_TIER_LOW_RATE;  // creating if statements to compute bill in different situations

    cout.setf(ios::fixed);
    cout.precision(2);         // setting 2 decimal point precision (because output is money)
    
    cout << "---" << endl;
    cout << "The bill for " << sCustomerName << " is $" << amt << endl; //final output for                                                                          valid inputs
    
    return 0;
}
