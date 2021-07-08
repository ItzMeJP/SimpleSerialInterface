//
// Created by joaopedro on 20/05/21.
//

#include <simple_serial.h>

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
        io_.reset(new boost::asio::io_service());
        serial_.reset(new boost::asio::serial_port(*io_, port_));
        serial_->set_option(boost::asio::serial_port_base::baud_rate(baud_rate_));

        //timer_reset(new boost::asio::deadline_timer(*io_);
    } catch(boost::system::system_error& e)
    {
        _error = e.what();
        return false;
    }
    _error = "Serial communication established.";
    return true;
}

bool SimpleSerial::stop(std::string &_error){

    try {
        serial_->close();
    } catch(boost::system::system_error& e)
    {
        _error = e.what();
        return false;
    }
    _error = "Serial communication closed.";
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

bool SimpleSerial::readLine(std::string &_result, std::string& _error)
{
    char c;
    std::string r;
    for(;;)
    {
        try {
            boost::asio::read(*serial_,boost::asio::buffer(&c,1)); // TODO: if none msg is transferred it will be stuck
        } catch(boost::system::system_error& e){
            _error = e.what();
            return false;
        }

        switch(c)
        {
            case '\r':
                break;
            case '\n':
                _result = r;
                return true;
            default:
                r+=c;
        }

    }
}
/*
std::string SimpleSerial::readLine(float _timeout_in_ms)// TODO: improve it...
{
    blocking_reader reader(io_,serial_, _timeout_in_ms);
    char c;

    std::string rsp;

    // read from the serial port until we get a
    // \n or until a read times-out (500ms)
    while (reader.read_char(c) && c != '\n') {
        rsp += c;

    }

    if (c != '\n') {
        // it must have timed out.
        //std::cout << "Read timed out!" << std::endl;
        //std::cout << "received " << c << std::endl;

    }

    return rsp;

}
*/
