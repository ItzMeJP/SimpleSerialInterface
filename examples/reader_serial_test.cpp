//
// Created by joaopedro on 20/05/21.
//

#include <simple_serial.h>
#include <iostream>

using namespace std;
using namespace boost;

int main(){

    string error = "", msg="";

    SimpleSerial serial;
    serial.setPort("/dev/ttyACM0");
    serial.setBaudRate(115200);

        if(serial.start(error)) {
            bool ctrl = serial.readLine(msg, error);
            while (ctrl) {
                cout << "Received : " << msg << endl;
                ctrl = serial.readLine(msg, error);
            }
            cout<<"Serial Error"<<endl<<error<<endl;
        }
        else
            cout<<"Serial Error"<<endl<<error<<endl;

}