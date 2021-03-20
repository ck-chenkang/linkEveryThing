#include "setexAPI.h"
using namespace std;

void test()
{
    setexAPI *setexcon = new setexAPI();
    int ch[10] = {0, 1, 0, 0, 1, 0, 0, 1, 1, 1};

    int value = 0;
    unsigned uvalue = 0;
    bool bvalue = false;

    const char *deviceip = "192.168.13.202";
    cout << setexcon->initialize(deviceip) << endl;
    cout << setexcon->getPictureLayers(ch) << endl;
    cout << setexcon->setPictureLayers(ch) << endl;

    cout << "-----------------";
    cout << "read inforword" << endl;
    cout << "-----------------";
    for (int i = 1; i <= 200; i++)
    {
        cout << "read getInfoWord index:" << i << " function return" << 
        setexcon->getInfoWord(i, value) << "value: " << value << endl;
    }

    cout << "-----------------";
    cout << "read getInfoDoubleWord" << endl;
    cout << "-----------------";
    for (int i = 1; i <= 500; i++)
    {
        cout << "read getInfoDoubleWord index:" << i << " function return" <<
         setexcon->getInfoDoubleWord(i, uvalue) << "uvalue: " << uvalue << endl;
    }

    cout << "-----------------";
    cout << "read getInfoBit" << endl;
    cout << "-----------------";
    for (int i = 1; i <= 500; i++)
    {
        cout << "read getInfoBit index:" << i << " function return" <<
         setexcon->getInfoBit(i, bvalue) << "bvalue: " << bvalue << endl;
    }


    cout << "-----------------";
    cout << "read getFunctionInitMarker" << endl;
    cout << "-----------------";
    for (int i = 1; i <= 1000; i++)
    {
        cout << "read getFunctionInitMarker index:" << i << " function return" <<
         setexcon->getFunctionInitMarker(i, bvalue) << "bvalue: " << bvalue << endl;
    }


    cout << "-----------------";
    cout << "read getFunctionActivationMarker" << endl;
    cout << "-----------------";
    for (int i = 1; i <= 1000; i++)
    {
        cout << "read getFunctionActivationMarker index:" << i << " function return" <<
         setexcon->getFunctionInitMarker(i, bvalue) << "bvalue: " << bvalue << endl;
    }
}

int main()
{
    cout << "program start" << endl;
    test();

    cout << "program end" << endl;
    return 0;
}