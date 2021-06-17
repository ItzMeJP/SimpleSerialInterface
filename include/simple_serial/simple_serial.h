//
// Created by joaopedro on 20/05/21.
//

#ifndef MIMIC_GRASPING_SERVER_SIMPLE_SERIAL_H
#define MIMIC_GRASPING_SERVER_SIMPLE_SERIAL_H

#include <boost/asio.hpp>
#include <iostream>
#include <time.h>
#include <boost/utility.hpp>
//#include <blocking_reader.h>

class SimpleSerial{

public:
    SimpleSerial(std::string _port, unsigned int _baud_rate);
    SimpleSerial();
    ~SimpleSerial();
    void setPort(std::string _port);
    void setBaudRate(unsigned int _baud_rate);
    void setConfig(std::string _port, unsigned int _baud_rate);
    void writeString(std::string _s);
    std::string readLine();
    std::string readLine(float _timeout_in_ms);

    unsigned int getBaudRate();
    std::string getPort();
    void setTerminator(std::string _t);
    bool start(std::string &_error);
private:
    std::shared_ptr<boost::asio::io_service> io_;
    //boost::asio::io_service io_;

    std::shared_ptr<boost::asio::serial_port> serial_;
    //boost::asio::serial_port serial_;
    std::string port_ = "";
    std::string terminator_ = "\r\n";
    unsigned int baud_rate_ = 0;

};

#endif //MIMIC_GRASPING_SERVER_SIMPLE_SERIAL_H
