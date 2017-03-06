#include <iostream>
#include <string>
#include "govt.hpp"


using namespace std;

int main()
{
    human yo = govt::matchhuman(0);

    cout << yo.getage();

    return 0;
}
