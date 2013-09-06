#ifndef _IO_EXCEPTION_H
#define _IO_EXCEPTION_H

#include <iostream>
#include <exception>

class IOException: public virtual std::exception {
  private:
    const char *msg;
  public:
    IOException(std::string &message);
    IOException(const char *msg);
    ~IOException( ) throw( );
    const char *what( ) const throw( );
};

#endif
