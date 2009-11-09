#include "Network.h"

/*template<class T, void(T::*mem_fn)()> void* thunk(void* p) {
(static_cast<T*>(p)->*mem_fn)();
return 0;
}*/

Network::Network(int p, int m) : port(p), max(m) {
}

Network::~Network() {			       
  list<int>::Iterator it = fdnew.begin();
  
  for(int i=0; i<fdnew.getSize(); i++) {
    it+=i;
    close(*it);
  }

  close(fd);
}

int Network::Startup() {


  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  //addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  memset(&(addr.sin_zero), 0, 8);
  
  if((fd = socket(AF_INET, SOCK_STREAM, 0))==0)
    std::cerr << "socket()";
  
  if((bind(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr)))==-1)
    std::cerr << "bind()";
  
  listen(fd, max);
  NetworkThread.Start(this);
}

void Network::Wait(void) {
  int fdtmp;
  std::cout << "Funcionando! " << max << " " << port;
  
  while(((fdtmp = accept(fd, (struct sockaddr *)&addr,&size)))<0)usleep(1);
  
  fdnew.push_back(fdtmp);
}


int Network::Receive(int id, char *buffer) {
  //int p = fdnew[0];
}


