// ASU CSE310 Spring 2024 Assignment #1
// Name: Shravan Karande
// ASU ID: 1225888172
// Description: This file defines a LinkedList class managing car
//              information. It includes methods for adding, removing,
//              and updating cars, maintaining alphabetical order. The
//              Car structure holds model, make, vin, and price. The program
//              ensures unique vins and alphabetical ordering. The file also
//              features print functions and proper memory management.

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Car represents a Car information
struct Car
{
    string model, make;
    int vin; // vehicle identification number
    double price;
    struct Car *next;
};

// class LinkedList will contains a linked list of Cars
class LinkedList
{
private:
    struct Car *head;

public:
    LinkedList();
    ~LinkedList();
    bool findCar(int aVin);
    bool addCar(string model, string make, int vin, double price);
    bool removeByVin(int aVin);
    bool removeByModelAndMake(string model, string make);
    bool changeCarInfo(int aVin, string newModelAndMake);
    bool updateCarPrice(int aVin, double newPrice);
    void printCarListByMake(string make);
    void printCarList();
};

// Constructor to initialize an empty linked list
LinkedList::LinkedList()
{
    head = nullptr; // head pointer is initilized to null
}

// Destructor
// Before termination, the destructor is called to free the associated memory occupied by the existing linked list.
// It deletes all the nodes including the head and finally prints the number of nodes deleted by it.
// Return value: Prints the number of nodes deleted by it.
LinkedList::~LinkedList()
{
    int carCount = 0;       // helps keep track of the number of carObjects deleted
    Car *carNode = nullptr; // this pointer helps traverse through the list
    while (head != nullptr)
    {
        carNode = head->next;
        delete head;
        head = carNode;
        carCount++;
    }

    cout << "The number of deleted Car is: " << carCount << "\n";
}

// A function to identify if the parameterized Car is inside the LinkedList or not.
// Return true if it exists and false otherwise.
bool LinkedList::findCar(int aVin)
{
    Car *current = head; // using this pointer instead of head, as it's safer (temp)

    while (current != nullptr)
    {
        if (current->vin == aVin) // if we find the vin
        {
            return true;
        }
        else // else we keep traversing until we find it
        {
            current = current->next;
        }
    }

    return false;
}

// Creates a new Car and inserts it into the list at the right place.
// It also maintains an alphabetical ordering of Cars by their make and model, i.e.
// first by make, if two cars have same makes, then we will list them by model. Note: each Car
// has a unique vin, the vehicle identification number, but may have the same make and model.
// In case two Cars have same make and model, they should be inserted according to the
// increasing order of their vins.
// Return value: true if it is successfully inserted and false in case of failures.
bool LinkedList::addCar(string model, string make, int vin, double price)
{

    Car *carToAdd = new Car(); // a car node
    carToAdd->make = make;     // assigning the prameter properties to the car node
    carToAdd->model = model;
    carToAdd->vin = vin;
    carToAdd->price = price;

    Car *current = head;     // using this instead of the head pointer (temp)
    Car *previous = nullptr; // using this to keep track of the previous pointer (pointer before head)

    if (findCar(vin) == true) // if the Car already exist, return false
    {
        cout << "Duplicated Car. Not added." << endl;
        return false;
    }

    while (current != nullptr &&
           (current->make.compare(carToAdd->make) < 0 ||
            (current->make.compare(carToAdd->make) == 0 && current->model.compare(carToAdd->model) < 0) ||
            (current->make.compare(carToAdd->make) == 0 && current->model.compare(carToAdd->model) == 0 && current->vin < carToAdd->vin))) // all these factors mean that the made/model/vin are smaller and we can more forward in the list

    {

        previous = current; // this help move forward
        current = current->next;
    }
    // after the while loop is exited we have found the posistion and now we place the new car (carToAdd) in that spot

    if (previous == nullptr) // this shows that the linked list is not empty but the position found was the head
    {
        carToAdd->next = head;
        head = carToAdd;
        return true;
    }

    else if (current == nullptr) // this means we have reached the end of the linked list and the car should be added here (at tail)
    {
        previous->next = carToAdd;
        carToAdd->next = nullptr; //(current == nullptr)
        return true;
    }

    else
    { // this means we have to add it to the list between (after) previous and (before) current
        previous->next = carToAdd;
        carToAdd->next = current;
        return true;
    }
}

// Removes the specified Car from the list, releases the memory and updates pointers.
// Return true if it is successfully removed, false otherwise.
bool LinkedList::removeByVin(int aVin)
{
    Car *current = head;
    Car *previous = nullptr;
    bool success = false; 	    

    if (findCar(aVin) == false)
    {
        // Car with specified VIN not found

        return false;
    }

    while (current != nullptr && current->vin != aVin) // keep iternating until we find the linked car node
    {
        previous = current;
        current = current->next;
    }
    // have found the node after exiting the while loop

    if (previous == nullptr) // deletes head if required
    {
        head = head->next;
        delete current;
	success = true; 
        return true;
    }
    else if (current == nullptr) // deletes tail if required
    {
        delete previous;
        previous = nullptr;
	success = true; 
        return true;
    }
    else // delete a middle node if required
    {
        previous->next = current->next;
        delete current;
	success = true; 
        return true;
    }

  return success; 
}

// Removes the given Car from the list, releases the memory and updates pointers.
// Return true if it is successfully removed, false otherwise. Note: all Cars with
// the same model and make should be removed from the list.
bool LinkedList::removeByModelAndMake(string model, string make)
{
    Car *current = head;
    Car *previous = nullptr;
    bool carRemoved = false;

    // cout << "start" << endl;
    while (current != nullptr)
    {
        // cout << "inside while" << endl;

        if (current->model == model && current->make == make)
        {
            // cout << "the car exists" << endl;

            if (previous == nullptr) // deletes head
            {
                head = current->next;
                delete current;
		current = current->next;
                carRemoved = true;
            }

            else // deletes middle or tail
            { 
	       previous->next = current->next;
                delete current;
		current = previous;
                carRemoved = true;
                //return true;
            }
        }
	
	else {
        // keeps traversing
        previous = current;
        current = current->next;
	}
    }
    //return carRemoved;

    if (carRemoved == false) // if current == null error message
    {
       cout << "No such Car found." << endl;
	 cout << "\nCar: " <<  make << " " << model << " does NOT exist" << endl; // error message
        return false;
    }

    return carRemoved;
}
// Modifies the data of the given Car. Return true if it modifies successfully and
// false otherwise. Note: after changing a Car model and make, the linked list must still
// maintain the alphabetical order.
bool LinkedList::changeCarInfo(int aVin, string newModelAndMake)
{
    Car *current = head;
    Car *previous = nullptr;

    if (findCar(aVin) == true) // Check if Car with specified VIN exists
    {

        while (current != nullptr)
        {
            if (current->vin == aVin)
            {
                // Extract new model and make from the input string
                string modelNew = newModelAndMake.substr(0, newModelAndMake.find(' '));
                string makeNew = newModelAndMake.substr(newModelAndMake.find(' ') + 1);

                double oldPrice = current->price;

                removeByVin(current->vin); // Delete the old Car by Vin

                addCar(modelNew, makeNew, aVin, oldPrice); // Adds the updated Car using addCar

                cout << "Car VIN #: " << aVin << " model and make was changed" << endl;

                return true;
            }

            previous = current;
            current = current->next;
        }
    }
    
	cout << "Car is NOT inside the list, cannot change Car make and model." << endl; 
	cout << "\nCar VIN #: " << aVin << " does not exist" << endl; // error message
    return false;
}

bool LinkedList::updateCarPrice(int aVin, double newPrice)
{
    Car *current = head;

    while (current != nullptr)
    {
        if (current->vin == aVin)
        {
            // Car found, update its price and return true
            current->price = newPrice;
            cout << "Car with VIN #: " << aVin << " price was updated" << endl;
            return true;
        }

        current = current->next; // keep treversing
    }

    // Car with the specified VIN was not found
    return false;
}

// Prints all Cars in the list with the same make.
void LinkedList::printCarListByMake(string make)
{
    Car *current = head;
    bool carExist = false;

    if (current == nullptr) // checks to see if the list is empty
    {
        cout << "The list is empty\n";
        return;
    }

    while (current != nullptr)
    {
        if (current->make == make) // if we find the make we print it
        {

            cout << left << setw(12) << current->model
                 << left << setw(12) << current->make
                 << right << setw(8) << current->vin
                 << setw(10) << fixed << setprecision(2) << current->price << "\n";

            carExist = true;
        }

        current = current->next; // if we don't do this the current pointer will always be on the head and not move forwards resulting in a infinite loop (which i had delt with)
    }

    if (carExist == false) // if we don't find the make
    {
        cout << "No Cars with the specified make found." << endl;
    }
    return;
}

// Prints all Cars in the linked list starting from the head node.
void LinkedList::printCarList()
{
    Car *temp = head;

    if (temp == nullptr)
    {
        cout << "The list is empty\n";
        return;
    }

    while (temp != nullptr) // if linked list is not empty, prints the whole list
    {
        cout << left << setw(12) << temp->model
             << left << setw(12) << temp->make
             << right << setw(8) << temp->vin
             << setw(10) << fixed << setprecision(2) << temp->price << "\n";

        temp = temp->next; // goes to next node (traversing)
    }
}
