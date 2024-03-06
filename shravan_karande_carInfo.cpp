// ASU CSE310 Spring 2024 Assignment #1
// Name: Shravan Karande
// ASU ID: 1225888172
// Description: This program displays a menu of choices to a user
//              and performs the chosen task. It will keep asking a user to
//              enter the next choice until the choice of 'Q' (Quit) is entered.

#include <iostream>
#include <string>
#include "LinkedList.h"

using namespace std;

void printMenu();

int main()
{
   // local variables, can be accessed anywhere from the main method
   char input1 = 'Z';
   string inputInfo;
   string model, make, oldModelAndMake, newModelAndMake;
   int vin;
   double price;
   string line;
   bool success = false;

   // instantiate a Linked List object
   LinkedList *list1 = new LinkedList();

   printMenu();

   do // ask for user input
   {
      cout << "\nWhat action would you like to perform?\n";
      cin.get(input1);
      input1 = toupper(input1); // change it to upper case
      cin.ignore(20, '\n');     // flush the buffer

      // matches one of the following cases
      switch (input1)
      {
      case 'A': // Add the Car
         cout << "Please enter the Car information:\n";
         cout << "Enter Car Model:\n";
         getline(cin, model);
         cout << "Enter Car Make:\n";
         getline(cin, make);
         cout << "Enter Car Vin:\n";
         cin >> vin;

         cout << "Enter Car Price:\n";
         cin >> price;
         cin.ignore(20, '\n'); // flush the buffer

         success = list1->addCar(model, make, vin, price);

         if (success == true)
            cout << "Car \"" << model << " " << make << "\" is added\n";
         else
            cout << "Car \"" << model << " " << make << "\" is NOT added\n";
         break;

      case 'C': // Change Car model and make
         cout << "Please enter the Car vin which you want to change the model and make:\n";
         cin >> vin;
         cout << "\nPlease enter the new model and make: \n";
         cin.ignore(20, '\n'); // flush the buffer 
	 getline(cin, newModelAndMake);

         list1->changeCarInfo(vin, newModelAndMake);

         break;

      case 'D': // Display all Cars

         list1->printCarList();

         break;

      case 'E': // Display Cars by make
         cout << "\nPlease enter Car make which you want to display:\n";

         cin >> make;
         cin.ignore(20, '\n');
         list1->printCarListByMake(make);

         break;

      case 'F': // Find a Car
         cout << "\nPlease enter the car VIN you want to search:\n";
         cin >> vin;
         cin.ignore(20, '\n'); // flush the buffer

         if (list1->findCar(vin) == true)
         {
            cout << "Car with VIN #: " << vin << " was found" << endl;
         }
         else
         {
            cout << "Car with VIN #: " << vin << " was NOT found" << endl;
         }

         break;

      case 'P': // Update a Car price
         cout << "\nPlease enter the Car VIN you want to update the price:\n";
         cin >> vin;
         cin.ignore(20, '\n');   
	 if(list1->findCar(vin) == true) 
	 {
	 cout << "\nPlease enter the new price:\n";
         cin >> price;
	 cin.ignore(20, '\n'); 
         list1->updateCarPrice(vin, price);
	 }
	 
	else {
	cout<<"Car with VIN #: " << vin << " does NOT exist";   
	 } 

         break;

      case 'R': // Remove a Car from the list by VIN
         cout << "\nPlease enter the Car VIN to remove:\n";
         cin >> vin;
         cin.ignore(20, '\n'); // flush the buffer

         if (list1->removeByVin(vin) == true)
         {
            cout << "\nCar with VIN #: " << vin << " was removed" << endl;
         }
         else
         {
            cout << "\nCar with VIN #: " << vin << " does NOT exist" << endl;
         }

         break;

      case 'S': // Remove a Car from the list by model and make
         cout << "Please enter Car model you want to remove:\n";
         getline(cin, model);
         cout << "Please enter Car make you want to remove:\n";
         getline(cin, make);

         if(list1->removeByModelAndMake(model, make)==true) {
         
	cout << "\nCar: " << make << " " << model << " was removed"  << endl;
	
	}
 
	// {

         //    cout << "request granted" << endl;
         // }ddd
         // else
         // {
         //    cout << "..I." << endl;
         // }

         break;

      case 'Q': // Quit
         delete list1;
         break;

      case '?': // Display Menu
         printMenu();
         break;

      default:
         cout << "Unknown action\n";
         break;
      }

   } while (input1 != 'Q');
   return 0;
}

/** The method printMenu displays the menu to a user**/
void printMenu()
{
   cout << "Choice\t\tAction\n";
   cout << "------\t\t------\n";
   cout << "A\t\tAdd A Car\n";
   cout << "C\t\tChange A Car Model and Make\n";
   cout << "D\t\tDisplay All Cars\n";
   cout << "E\t\tDisplay Cars by Make\n";
   cout << "F\t\tFind A Car\n";
   cout << "P\t\tUpdate Car price\n";
   cout << "R\t\tRemove Car by VIN\n";
   cout << "S\t\tRemove Car by Model and Make\n";
   cout << "Q\t\tQuit\n";
   cout << "?\t\tDisplay Help\n\n";
}
