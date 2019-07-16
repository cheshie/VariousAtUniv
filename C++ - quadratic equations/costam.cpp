#include <iostream>
#include <vector>
using namespace std;

int main()
{
    std::vector <float> real;
    std::vector <float> imaginary;
    
    
    std::vector < std::pair <float, float> > complex;
    
    real.push_back(1);

    imaginary.push_back(2);
    
    // Entering values in vector of pairs
    for (int i=0; i<1; i++)
        complex.push_back( make_pair(real[i],imaginary[i]) );
    
    // Printing the vector
    for (int i=0; i<1; i++)
    {
        // "first" and "second" are used to access
        // 1st and 2nd element of pair respectively
        cout << complex[i].first << " "
             << complex[i].second << endl;
    }
    
    return 0;
}
