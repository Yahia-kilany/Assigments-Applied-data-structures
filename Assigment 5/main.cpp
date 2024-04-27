#include<iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
// Declaration of functions
struct Exchange_data {
    string date;
    double value;
    double rate_of_change;
    // Default constructor
    Exchange_data ();
    // Parameterized constructor
    Exchange_data (string str , double val);
    // Overloading < operator
    bool operator < (const Exchange_data& data);
    // Overloading > operator
    bool operator > (const Exchange_data& data);
};

// Function to read data from file
void read_data (vector<Exchange_data>& data , string file);
// Function to calculate rate of change
void CalculateChange (vector<Exchange_data>& data);
// Function to build max heap
void MaxHeapify (vector<Exchange_data>& arr , int n , int i);
// Function to build max heap
void Build_Max_Heap (vector<Exchange_data>& arr);
// Function to build min heap
void MinHeapify (vector<Exchange_data>& arr , int n , int i);
// Function to build min heap
void Build_Min_Heap (vector<Exchange_data>& arr);
// Function to swap two elements
void swap (Exchange_data& d1 , Exchange_data& d2);
// Function to print top N max and min rates
void Top_rates (vector<Exchange_data>& arr , int N , bool MaxHeap);
// Function to find max subarray
void findMaxRate (const std::vector<Exchange_data>& arr);

// Driver Code
int main ()
{
    vector<Exchange_data> data;
    string filename;
    int N;
    cout << "Enter File Name: " << endl;
    cin >> filename;

    cout << endl;
    read_data (data , filename);

    cout << endl;

    CalculateChange (data);

    findMaxRate (data);
    cout << "Enter the value of N:";
    cin >> N;

    Build_Max_Heap (data);
    cout << endl << "The top " << N << " max rates: " << endl;
    Top_rates (data , N , true);

    Build_Min_Heap (data);
    cout << endl << "The top " << N << " min rates: " << endl;
    Top_rates (data , N , false);
    return 0;
}

// Structure constructors
Exchange_data::Exchange_data () {
    date = "";
    value = 0;
    rate_of_change = 0;
}

Exchange_data::Exchange_data (string str , double val) {
    date = str;
    value = val;
    rate_of_change = 0;
}

// Operator overloading
bool Exchange_data::operator < (const Exchange_data& data) {
    return this->rate_of_change < data.rate_of_change;
}

bool Exchange_data::operator > (const Exchange_data& data) {
    return this->rate_of_change > data.rate_of_change;
}

// Function to read data from file
void read_data (vector<Exchange_data>& data , string file) {
    ifstream infile (file);

    if (!infile)
    {
        cerr << "Unable to open file" << endl;
        exit (1);
    }

    //skip the first 17 lines which contain metadata
    for (int i = 1;i < 17;i++) {
        string dummy;
        getline (infile , dummy);
    }
    while (!infile.eof ()) {
        string str;
        double val;
        infile.ignore ();//skips the newline character "/n" at the start of each line in the .csv file
        getline (infile , str , ',');
        infile >> val;
        Exchange_data exchange (str , val);
        data.push_back (exchange);
    }
    data.pop_back ();// Remove the last element of the vector, which is empty and added by mistake
}

//Calculates the overall average
//Calculates and assgins the rates of change to their respective elements
void CalculateChange (vector<Exchange_data>& data) {
    double m = 0;
    for (int i = 0;i < data.size ();i++) {
        m += data[i].value;
    }
    m /= data.size ();
    cout << "Average: " << m << endl;
    for (int i = 0;i < data.size ();i++) {
        double c;
        c = data[i].value - m;
        data[i].rate_of_change = c;
    }
}

void MaxHeapify (vector<Exchange_data>& arr , int n , int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap (arr[i] , arr[largest]);
        MaxHeapify (arr , n , largest);
    }
}

//Create a maxiumum heap from the data given
void Build_Max_Heap (vector<Exchange_data>& arr) {
    int n = arr.size ();
    int startIdx = (n / 2) - 1;

    for (int i = startIdx; i >= 0; i--) {
        MaxHeapify (arr , n , i);
    }
}

void MinHeapify (vector<Exchange_data>& arr , int n , int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] < arr[smallest])
        smallest = left;

    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    if (smallest != i) {
        swap (arr[i] , arr[smallest]);
        MinHeapify (arr , n , smallest);
    }
}

//Create a maxiumum heap from the data given
void Build_Min_Heap (vector<Exchange_data>& arr) {
    int n = arr.size ();
    int startIdx = (n / 2) - 1;

    for (int i = startIdx; i >= 0; i--) {
        MinHeapify (arr , n , i);
    }
}

//Swaps two Exchange_data elements with each other 
void swap (Exchange_data& d1 , Exchange_data& d2) {
    Exchange_data temp = d1;
    d1 = d2;
    d2 = temp;
}

// Function to find top N max or min rates
void Top_rates (vector<Exchange_data>& arr , int N , bool MaxHeap) {
    vector<Exchange_data> topElements;
    for (int i = 0; i < N && i < arr.size (); i++) {
        topElements.push_back (arr[0]);
        swap (arr[0] , arr[arr.size () - i - 1]);

        //if the array given is a maximum heap call MaxHeapify()
        //if it is a minimum heap call MinHeapify()
        if (MaxHeap) {
            MaxHeapify (arr , arr.size () - i - 1 , 0);
        }

        else {
            MinHeapify (arr , arr.size () - i - 1 , 0);
        }
    }
    for (int i = 0;i < topElements.size ();i++) {
        cout << topElements[i].date << "    " << topElements[i].rate_of_change << endl;
    }
    return;
}


// Function to find the maximum sum subarray of rate of change
void findMaxRate (const std::vector<Exchange_data>& arr) {


    double maxSum = arr[0].rate_of_change;
    double currentSum = arr[0].rate_of_change;
    int start = 0;
    int maxStart = 0;
    int end = 0;

    for (int i = 1; i < arr.size (); i++) {
        if (currentSum + arr[i].rate_of_change < arr[i].rate_of_change) {
            currentSum = arr[i].rate_of_change;
            start = i;
        }
        else {
            currentSum += arr[i].rate_of_change;
        }

        if (currentSum > maxSum) {
            maxSum = currentSum;
            maxStart = start;
            end = i;
        }
    }
    cout << "The date range with the maximum sum of rate of change is from "
        << arr[maxStart].date << " to " << arr[end].date << "." << endl;
}