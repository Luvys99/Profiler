#include "Profile.h"
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
    int count = 0;
    while (1)
    {
        count++;

        Test1();
        Test2();
        Test3();

        if (GetAsyncKeyState(VK_RETURN) & 0x0001)
        {
            ProfileManager::GetInstance().WriteProfile("ProfileReport.txt");
        }

        if (count == 5000)
        {
            ProfileManager::GetInstance().ResetProfile();
        }

        if (GetAsyncKeyState(VK_ESCAPE))
        {
            break;
        }
    }

    return 0;
}

