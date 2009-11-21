#ifndef _NETWORK_H_
#define _NETWORK_H_

//#include<iterator>
//#include <list>
#include <irrlicht/irrlicht.h>
#include <irrlicht/irrString.h>
#include <irrlicht/irrList.h>
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Thread.h"
#define EOT 0x04
//using namespace std;
using namespace irr::core;
class Network {
public:
  Network(int, int);
  Network(char *, int);
  ~Network();
  int Startup();
  void Wait(void);
  int getSize(void);
  int Receive(int, stringc *);
  
 private:
  std::string address;
  const int port, max;
  int fd;
  list<int> fdnew;
  socklen_t size;
  struct sockaddr_in addr;
  ThNetwork NetworkThread;
};

#endif //_NETWORK_H_
//class NetThread : public Thread
