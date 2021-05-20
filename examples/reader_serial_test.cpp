//
// Created by joaopedro on 20/05/21.
//

#include <simple_serial/simple_serial.h>
#include <iostream>

using namespace std;
using namespace boost;

int main(){

    string  error;

    SimpleSerial serial;
    serial.setPort("/dev/ttyUSB0");
    serial.setBaudRate(115200);

        if(serial.start(error)) {

            while (true) {
                cout << "Received : " << serial.readLine() << endl;
            }
        }
        else
            cout<<"Serial Error"<<endl<<error<<endl;

}