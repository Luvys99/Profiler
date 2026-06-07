#include "Profiler.h"
#include <vector>
using namespace std;

void Test1()
{
    PROFILE
    vector<int> vec;
    for (int i = 0; i < 100000; i++)
    {
        vec.push_back(i);
    }

}

void Test2()
{
    PROFILE
    Sleep(1000);

}

void Test3()
{
    PROFILE

        volatile int num = 0;
    for (int j = 0; j < 100000; j++)
    {
        num += sin(j) * cos(j);
    }

}


int main()
{
    Profiler p;
    int count = 0;

    while (1)
    {
        count++;

        Test1();
        Test2();
        Test3();

        if (GetAsyncKeyState(VK_RETURN) & 0x0001)
        {
            p.WriteProfile(L"ProfileReport.txt");
        }

        if (count == 5000)
        {
            p.ResetProfile();
        }

        if (GetAsyncKeyState(VK_ESCAPE))
        {
            break;
        }
    }

    return 0;
}

