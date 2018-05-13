#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;

int main()
{
    vector <string> a = {"abc ", "ab ", "Acb ", "!234123 "};
    sort(a.begin(), a.end());
    for (int i = 0; i < a.size(); ++i)
    {
        cout << a[i];
    }
    return 0;
}