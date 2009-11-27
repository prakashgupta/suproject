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
#include <netdb.h>
#include "Thread.h"
#define EOT 'b'
//using namespace std;
using namespace irr::core;
class Network {
public:
  //  Network(int, int);
  //  Network(char *, int);
  ~Network();
  int Startup(int, int);
  int Startup(const char *, int);
  int Close(void);
  void Wait(void);
  int getSize(void);
  int Receive(int, stringc *);
  int Receive(stringc *);
  int Send(int, stringc *);
  int SendAll(stringc *);
  int Send(stringc *);
 private:
  int server;
  stringc address;
  int fd;
  int port, max;
  list<int> fdnew;
  socklen_t size;
  struct hostent *he;
  struct sockaddr_in addr;
  ThNetwork NetworkThread;
};

#endif //_NETWORK_H_
//class NetThread : public Thread
