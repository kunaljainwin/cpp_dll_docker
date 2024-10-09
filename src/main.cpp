/*
data: A global vector of integer pointers used to store the data.

extern "C" block: This defines functions with C linkage, which can be used externally by a DLL or shared library. The API_FUNC macro ensures these functions are visible outside the module.

InitializeDLL: Initializes the data vector by resizing it to the given size and populating it with multiples of 2. It also deletes any previously allocated memory to prevent memory leaks.

incrementAll: Increments the values pointed to by each element in the data vector by a given value.
*/

#include <iostream>
#include <vector>
using namespace std;

 
// Declaration of C-style functions for external linkage
extern "C"
{
    // Attribute to make the function visible externally
    #define API_FUNC __attribute__((visibility("default")))

    // Global vector of integer pointers to store data
    vector<int*> data; 

    // Function to initialize the DLL and allocate memory for the given size
    API_FUNC bool InitializeDLL(int Size);

    // Placeholder for a function to get a number by its index (not defined here)
    API_FUNC void IncrementAll(int Index);
}


/* DLL Definitions [S] */

// Function to initialize the DLL, allocate memory, and populate the 'data' vector
API_FUNC bool InitializeDLL(int Size)
{
    // Free the memory from previous data entries to avoid memory leaks
    int n=data.size();
    for(int i = 0; i < n; i++)
    {
        delete data[i];
    }

    // Resize the vector to hold 'Size' elements
    data.resize(Size);
    cout << "DLL initialized" << endl;
    
    // Print and initialize the data with multiples of 2
    cout << "Data : [";
    for(auto i = 0; i < Size; i++)
    {
        // Dynamically allocate memory for an integer and store multiples of 2
        int* ptrNum = new int(i * 2);
        data[i] = ptrNum;

        // Print the value (except for the last element to avoid trailing comma)
        cout << *ptrNum;
        if (i == Size - 1)
            break;
            
         cout<< ", ";
    }
    cout << ']' << endl;
    
    return true; // Return false (success status)
}

// Function to increment all stored numbers by a given value 'x'
API_FUNC void IncrementAll(int x)
{
    for (auto& ptrNum : data)
    {
        *ptrNum += x; // Increment the value at each pointer by 'x'
    }
    cout << "Incremented each by " << x << endl;
}
/* DLL Definitions [E] */


/* internal tests */
// int main()
// {
//     // Test the InitializeDLL function with a size of 5
//     InitializeDLL(5);
//     cout<<"DLL main called "<<endl;
//     return 0;
// }
