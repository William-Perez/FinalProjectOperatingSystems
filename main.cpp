#include <iostream>
#include <cmath>
#include "disk.h"

using namespace std;



int main()
{
    int option;
    Disk userDisk;
	userDisk.setData();
	do{
        cout << "Welcome to the menu!\n";
        cout << "1. Enter New Disk\n";
        cout << "2. Change Head Position\n";
        cout << "3. Change Requests\n";
        cout << "4. Change Head Direction\n";
        cout << "5. Print Out Tables For Algorithms\n";
        cout << "10.End Program\n";
        cout << "Enter: ";
        cin >> option;
        cout << endl;
        switch(option)
        {
        case 1:
            {
                userDisk.setData();
                break;
            }
        case 2:
            {
                userDisk.setHeadStart();
                break;
            }
        case 3:
            {
                cout << "Remeber that you can add " << userDisk.getAmountOfRequests() << "requests.\n";
                cout << "In a disk that has " << userDisk.getNumberOfTracks() << " total tracks.\n" << endl;
                userDisk.addRequests(userDisk.getAmountOfRequests(), userDisk.getNumberOfTracks());
                break;
            }
        case 4:
            {
                userDisk.setDirection();
                break;
            }
        case 5:
            {

            }
        case 10:
            {
                std::cout << std::endl;
                std::cout << "Quitting...\n" << std::endl;
                break;
            }
        default:
            {
                std::cout << std::endl;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore();
                    std::cout << "Option not valid. Please try again.\n";
                } else {
                    std::cout << "Option not valid. Please try again.\n";
                }
                std::cout << std::endl;
            }
        }
	}while(option != 10);

	return 0;
}
