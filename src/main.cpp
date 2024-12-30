#include <iostream>
#include <limits>
#include "WiFi4Simulator.h"
#include "WiFi5Simulator.h"
#include "WiFi6Simulator.h"


using namespace std;


void displayMenu()
{
    cout << "-------------------------------\n";
    cout << "   WiFi Communication Simulator\n";
    cout << "--------------------------------\n";
    cout << "Select a Communication Type:\n";
    cout << "1. WiFi 4 (CSMA/CA)\n";
    cout << "2. WiFi 5 (MU-MIMO)\n";
    cout << "3. WiFi 6 (OFDMA)\n";
    cout << "4. Exit\n";
    cout << "--------------------------------\n";
    cout << "Your Choice: ";
}

// Validated integer input
int getValidatedInput(const string &prompt, int min = 0, int max = numeric_limits<int>::max())
{
    int value;
    while (true)
    {
        cout << prompt;
        cin >> value;

        if (cin.fail() || value < min || value > max)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
        }
        else
        {
            break;
        }
    }
    return value;
}

int main()
{
    int choice = -1;

    while (choice != 4)  
    {
        displayMenu();
        choice = getValidatedInput("", 1, 4); 

        if (choice == 4) 
        {
            cout << "[Exit] Thank you for using the WiFi Simulator. Goodbye!\n";
            break;
        }

        int numUsers = getValidatedInput("Enter the number of users: ", 1);
        int bandwidth = 20;

        switch (choice)
        {
        case 1:
            cout << "[Begin] Initializing WiFi 4 Simulation...\n\n";
            try
            {
                WiFi4Simulator wifi4Simulator(numUsers, bandwidth);
                wifi4Simulator.executeSimulation();
            }
            catch (const exception &e)
            {
                cerr << "[Error] WiFi 4 Simulation failed: " << e.what() << "\n";
            }
            break;

        case 2:
            cout << "[Begin] Initializing WiFi 5 Simulation...\n";
            try
            {
                WiFi5Simulator wifi5Simulator(numUsers, bandwidth);
                wifi5Simulator.executeSimulation();
            }
            catch (const exception &e)
            {
                cerr << "[Error] WiFi 5 Simulation failed: " << e.what() << "\n";
            }
            break;

        case 3:
            cout << "[Begin] Initializing WiFi 6 Simulation...\n";
            try
            {
                WiFi6Simulator wifi6Simulator(numUsers, bandwidth);
                wifi6Simulator.executeSimulation();
            }
            catch (const exception &e)
            {
                cerr << "[Error] WiFi 6 Simulation failed: " << e.what() << "\n";
            }
            break;

        default:
            cerr << "[Critical Error] Unexpected input.\n";
        }

        cout << "-------------------------------\n\n";
    }

    return 0;
}
