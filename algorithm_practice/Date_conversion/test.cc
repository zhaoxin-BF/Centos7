#include <iostream>

using namespace std;

int main()
{
    int arr[12] = {31,59,90,120,151,181,212,
                    243,273,304,334,365};
    int year,mouth,day,sum;
    while(cin>>year>>mouth>>day)
    {
        sum = 0;
        sum = arr[mouth-2];
        sum += day;

        if(mouth > 2)
        {
            if((year%4 == 0 && year%100 != 0)||year%400 == 0)
                sum += 1;
        }
        cout<<sum<<endl;
    }
}
