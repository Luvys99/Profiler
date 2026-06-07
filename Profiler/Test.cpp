#include "Profiler.h"
#include <vector>
using namespace std;

void Test1()
{
    PROFILE

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

void Test4()
{
    PROFILE

}
void Test5()
{
    PROFILE

}
void Test6()
{
    PROFILE

}
void Test7()
{
    PROFILE

}
void Test8()
{
    PROFILE

}

void Test9()
{
    PROFILE

}

void Test10()
{
    PROFILE

}

void Test11()
{
    PROFILE

}

void Test12()
{
    PROFILE

}
void Test13()
{
    PROFILE

}
void Test14()
{
    PROFILE

}
void Test15()
{
    PROFILE

}
void Test16()
{
    PROFILE

}
void Test17()
{
    PROFILE

}
void Test18()
{
    PROFILE

}
void Test19()
{
    PROFILE

}
void Test20()
{
    PROFILE

}
void Test21()
{
    PROFILE

}
void Test22()
{
    PROFILE

}
void Test23()
{
    PROFILE

}
void Test24()
{
    PROFILE

}
void Test25()
{
    PROFILE

}
void Test26()
{
    PROFILE

}

void Test27()
{
    PROFILE

}

void Test28()
{
    PROFILE

}

void Test29()
{
    PROFILE
    //Sleep(1000);

}

int main()
{
    Profiler p;
    int count = 0;

    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();
    Test8();
    Test9();
    Test10();
    Test11();
    Test12();
    Test13();
    Test14();
    Test15();
    Test16();
    Test17();
    Test18();
    Test19();
    Test20();
    Test21();
    Test22();
    Test23();
    Test24();
    Test25();
    Test26();
    Test27();
    Test28();
    Test29();

    while (1)
    {
        count++;

        Test1();
        //Test2();
        Test29();
        //Test3();

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

