//
// Created by joaopedro on 20/05/21.
//

#include <simple_serial/simple_serial.h>

SimpleSerial::SimpleSerial() {

}

SimpleSerial::SimpleSerial(std::string _port, unsigned int _baud_rate) {
    setConfig(_port,_baud_rate);
}

SimpleSerial::~SimpleSerial() {

}

void SimpleSerial::setPort(std::string _port) {
    port_ = _port;
}

void SimpleSerial::setBaudRate(unsigned int _baud_rate) {
    baud_rate_ = _baud_rate;
}

bool SimpleSerial::start(std::string &_error){

    try {
        io_ = std::make_shared<boost::asio::io_service>();
        serial_ = std::make_shared<boost::asio::serial_port>(*io_, port_);
        serial_->set_option(boost::asio::serial_port_base::baud_rate(baud_rate_));

    } catch(boost::system::system_error& e)
    {
        _error = e.what();
        //std::cout<<"Serial Error: "<< e.what() <<std::endl;
        return false;
    }

    return true;

}

void SimpleSerial::setConfig(std::string _port, unsigned int _baud_rate){
    setPort(_port);
    setBaudRate(_baud_rate);
}

std::string SimpleSerial::getPort() {
    return port_;
}

unsigned int SimpleSerial::getBaudRate() {
    return baud_rate_;
}

void SimpleSerial::writeString(std::string _s){
    _s += terminator_;
    boost::asio::write(*serial_,boost::asio::buffer(_s.c_str(),_s.size()));
}

void SimpleSerial::setTerminator(std::string _t) {
    terminator_ = _t;
}

std::string SimpleSerial::readLine()
{
    char c;
    std::string result;
    for(;;)
    {
        boost::asio::read(*serial_,boost::asio::buffer(&c,1));
        switch(c)
        {
            case '\r':
                break;
            case '\n':
                return result;
            default:
                result+=c;
        }
    }
}