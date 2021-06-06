//
//  main.cpp
//  Project 2
//
//  Created by Claire Zhang on 4/10/21.
//

#include <iostream>
#include <string>
using namespace std;

int main()
{
    //Collect user age
    int age;
    cout << "Age of rider: ";
    cin >> age;
    cin.ignore(10000,'\n');
    if (age < 0)
    {
        cout << "---" << '\n' << "The age must not be negative" << endl;
        return 1;
    }
    // Collect user student status
    string student;
    cout << "Student? (y/n): ";
    getline(cin,student);
    if (student != "y" && student != "n")
    {
        cout << "---" << '\n' << "You must enter y or n" << endl;
        return 1;
    }
    //Collect destination
    string destination;
    cout << "Destination: ";
    getline(cin,destination);
    if (destination == "")
    {
        cout << "---" << '\n' << "You must enter a destination" << endl;
        return 1;
    }
    //Collect the number of zone boundaries crossed
    int boundary;
    cout << "Number of zone boundaries crossed: ";
    cin >> boundary;
    if (boundary < 0)
    {
        cout << "---" << '\n' << "The number of zone boundaries crossed must not be negative" << endl;
        return 1;
    }
    //Fare calculator including applicable discounts
    double fare;
    fare = 1.45+0.55*boundary;
    if (age >= 65)
    {
        fare = 0.55+0.35*boundary;
        if (boundary == 0)
            fare = 0.45;
        else if (student == "y" && boundary == 1)
            fare = 0.65;
    }
    else if (age < 18 || student == "y")
    {
        if (boundary == 0 || boundary == 1)
        fare = 0.65;
    }
    
        cout.setf(ios::fixed);
        cout.precision(2);
        cout << "---" << '\n' << "The fare to " << destination << " is $" << fare << endl;
    
}
