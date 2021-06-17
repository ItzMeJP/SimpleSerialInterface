//
// Created by joaopedro on 20/05/21.
//

#include <simple_serial.h>
#include <iostream>

using namespace std;
using namespace boost;

int main(){

    string str, error;

    SimpleSerial serial("/dev/ttyUSB0", 115200);

    if(serial.start(error)) {

        while (true) {
            cout << "Type a msg" << endl;
            cin >> str;
            serial.writeString(str);

        }
    }
    else
        cout<<"Serial Error"<<endl<<error<<endl;

}