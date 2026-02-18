//https://stackoverflow.com/questions/67824110/fast-c-sign-function

// C++ program to find out execution time of  of functions 
#include <chrono> 
#include <iostream> 
#include <math.h>

using namespace std; 
using namespace std::chrono; 

template<typename Clock>

void printResult(const std::string name, std::chrono::time_point<Clock> start, std::chrono::time_point<Clock> stop, const int iterations)
{
    // Get duration. 
    std::chrono::duration my_duration = duration_cast<nanoseconds>(stop - start); 
    my_duration /= iterations;

    cout << "Time taken by "<< name <<" function: " << my_duration.count() << " ns avg. for " << iterations << " iterations." << endl << endl; 
}


template <typename T> int sgn(T val) 
{
    return (T(0) < val) - (val < T(0));
}


int main() {

    // ***************************************************************** //
    int numiters = 100000000;
    double vel = -0.6574;
    double result = 0;
    
    // Get starting timepoint 
    auto start_1 = high_resolution_clock::now(); 
    for(int x = 0; x < numiters; x++) 
    {

        result = (vel/fabs(vel)) * 12.1;

    }

    // Get ending timepoint 
    auto stop_1 = high_resolution_clock::now(); 
    cout << "Result is: " << result << endl;
    printResult("fabs", start_1, stop_1, numiters);

    // Get starting timepoint 
    result = 0;
    auto start_2 = high_resolution_clock::now(); 
    for(int x = 0; x < numiters; x++) 
    {

        result = sgn(vel) * 12.1;

    }

    // Get ending timepoint 
    auto stop_2 = high_resolution_clock::now(); 
    cout << "Result is: " << result << endl;
    printResult("sgn", start_2, stop_2, numiters);


    // Get starting timepoint 
    result = 0;
    auto start_10 = high_resolution_clock::now(); 
    for(int x = 0; x < numiters; x++) 
    {

        result = copysign(12.1, vel);

    }

    // Get ending timepoint 
    auto stop_10 = high_resolution_clock::now(); 
    cout << "Result is: " << result << endl;
    printResult("copysign", start_10, stop_10, numiters);

    cout << endl;


}


