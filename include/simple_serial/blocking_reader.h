//
// blocking_reader.h - a class that provides basic support for
// blocking & time-outable single character reads from
// boost::asio::serial_port.
//
// use like this:
//
// 	blocking_reader reader(port, 500);
//
//	char c;
//
//	if (!reader.read_char(c))
//		return false;
//
// Kevin Godden, www.ridgesolutions.ie
//

#ifndef MIMIC_GRASPING_SERVER_BLOCKING_READER_H
#define MIMIC_GRASPING_SERVER_BLOCKING_READER_H

#include <boost/asio/serial_port.hpp>
#include <boost/bind.hpp>

class blocking_reader
{
    std::shared_ptr<boost::asio::serial_port> port_;
    std::shared_ptr<boost::asio::io_service> io_;
    size_t timeout_;
    char c;
    std::shared_ptr<boost::asio::deadline_timer> timer_;
    bool read_error=true;

    // Called when an async read completes or has been cancelled
    void read_complete(const boost::system::error_code& error,
                       size_t bytes_transferred) {

        read_error = (error || bytes_transferred == 0);

        // Read has finished, so cancel the
        // timer.
        timer_->cancel();
    }

    // Called when the timer's deadline expires.
    void time_out(const boost::system::error_code& error) {

        // Was the timeout was cancelled?
        if (error) {
            // yes
            return;
        }

        // no, we have timed out, so kill
        // the read operation
        // The read callback will be called
        // with an error
        port_->cancel();
    }

public:

    // Constructs a blocking reader, pass in an open serial_port and
    // a timeout in milliseconds.
    blocking_reader(std::shared_ptr<boost::asio::io_service> _io, std::shared_ptr<boost::asio::serial_port> _port, size_t _timeout) {

        io_ = _io;
        timer_ = std::make_shared<boost::asio::deadline_timer>(*io_);
        port_=_port;
        timeout_ = _timeout;

    }

    // Reads a character or times out
    // returns false if the read times out
    bool read_char(char& val) {

        val = c = '\0';

        // After a timeout & cancel it seems we need
        // to do a reset for subsequent reads to work.
        io_->reset();

        // Asynchronously read 1 character.
        boost::asio::async_read(*port_, boost::asio::buffer(&c, 1),
                                boost::bind(&blocking_reader::read_complete,
                                            this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred));

        // Setup a deadline time to implement our timeout.
        timer_->expires_from_now(boost::posix_time::milliseconds(timeout_));
        timer_->async_wait(boost::bind(&blocking_reader::time_out,
                                     this, boost::asio::placeholders::error));

        // This will block until a character is read
        // or until the it is cancelled.
        io_->run();

        if (!read_error)
            val = c;

        return !read_error;
    }

    ~blocking_reader(){

    }
};


#endif //MIMIC_GRASPING_SERVER_BLOCKING_READER_H
