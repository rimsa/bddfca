#include <io/IOException.h>

IOException::IOException(std::string &message) {
  msg = message.c_str( );  
}

IOException::IOException(const char *msg) {
  this->msg = msg;
}

IOException::~IOException( ) throw( ) {
}

const char *IOException::what( ) const throw( ) {
  return msg;
}

