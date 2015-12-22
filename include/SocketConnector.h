// Definition of the ServerSocket class

#ifndef SocketConnector_class
#define SocketConnector_class

#include "Socket.h"


class SocketConnector : public fprime::Socket
{
 public:

  SocketConnector ( int port );
  SocketConnector ( std::string host, int port );
  SocketConnector (){};
  virtual ~SocketConnector();

  const SocketConnector& operator << ( const std::string& ) const;
  const SocketConnector& operator >> ( std::string& ) const;

  void accept ( SocketConnector* );

};


#endif
