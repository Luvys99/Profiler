#include "Profiler.h"
using namespace std;

void Test1()
{
    PROFILE;
    int a = 0;
    for (int i = 0; i < 1000000; i++)
    {
        a++;
    }

}

void Test2()
{
    PROFILE;
    int a = 0;
    for (int i = 0; i < 10000; i++)
    {
        a++;
    }

}

void Test3()
{
    PROFILE;
    int a = 0;
    for (int i = 0; i < 1000; i++)
    {
        a++;
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

