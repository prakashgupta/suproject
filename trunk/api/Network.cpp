#include "Network.h"

/*template<class T, void(T::*mem_fn)()> void* thunk(void* p) {
(static_cast<T*>(p)->*mem_fn)();
return 0;
}*/

 /*Network::Network(int p, int m) : port(p), max(m) {
  server = 1;
  }*/
/*
Network::Network(char *a, int p) : port(p), max(0) {
  address = a;
  server = 0;
  }*/

Network::~Network() {			       
  list<int>::Iterator it = fdnew.begin();
  
  for(int i=0; i<fdnew.getSize(); i++) {
    it+=i;
    close(*it);
  }
  close(fd);
}


int Network::Startup(int p, int m) {
  port = p;
  max = m;
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
int Network::Startup(const char *a, int p) {
  address = a;
  port = p;
  if (!(he=gethostbyname(address.c_str())))
    std::cerr << "gesthostbyname()";
  if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) std::cerr << "socket()";
  
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr = *((struct in_addr *)he->h_addr);
  bzero(&(addr.sin_zero), 8);
  
  
  if (connect(fd,(struct sockaddr *)&addr, sizeof(struct sockaddr)) ==-1) {
    std::cerr << "connect()";
    return -1;
  }
}

int Network::Close(void) {
  list<int>::Iterator it = fdnew.begin();
  
  for(int i=0; i<fdnew.getSize(); i++) {
    it+=i;
    close(*it);
  }
  close(fd);
}

void Network::Wait(void) {
  while(fd) {
    int fdtmp;
    std::cout << "Funcionando! " << max << " " << port;
    
    while(((fdtmp = accept(fd, (struct sockaddr *)&addr,&size)))<0)usleep(1);
    
    fdnew.push_back(fdtmp);
  }
}

int Network::getSize(void) {
  return fdnew.getSize();
}


int Network::Receive(int id, stringc *buffer) {
  list<int>::Iterator p = fdnew.begin();
  p+=id;
  char *btmp;
  int total, received, left;
  uint16_t bytes_nbo;

  recv(*p, &bytes_nbo, 2, 0);
  total = ntohs(bytes_nbo);
  std::cout << std::endl << total << std::endl;
  left = total;
  
  while(left > 0) {
    btmp = new char[left+1];
    received = recv(*p, btmp, left, NULL);
    btmp[left] = '\0';
    buffer->append(btmp);
    delete [] btmp;
    left -= received;
    std::cout << std::endl << received << std::endl;
  }
  

}

int Network::Receive(stringc *buffer) {
  char *btmp;
  int total, received, left;
  uint16_t bytes_nbo;

  recv(fd, &bytes_nbo, 2, 0);
  total = ntohs(bytes_nbo);
  std::cout << std::endl << total << std::endl;
  left = total;
  
  while(left > 0) {
    btmp = new char[left+1];
    received = recv(fd, btmp, left, NULL);
    btmp[left] = '\0';
    buffer->append(btmp);
    delete [] btmp;
    left -= received;
    std::cout << std::endl << received << std::endl;
  }


}

int Network::Send(int id, stringc *buffer) {
  uint16_t bytes_nbo;
  int left, bytes;
  bytes_nbo = htons(buffer->size());
  list<int>::Iterator p = fdnew.begin();
  p+=id;
  
  if(send(*p, &bytes_nbo, 2, NULL) != 2)
    std::cerr << "send()_nbo";
  left = buffer->size();
  while(left>0) {
    bytes = send(*p, buffer->c_str()+(buffer->size()-left), left, NULL);
    left -= bytes;
  }
}

int Network::SendAll(stringc *buffer) {
  uint16_t bytes_nbo;
  int left, bytes;
  bytes_nbo = htons(buffer->size());
  list<int>::Iterator p = fdnew.begin();
  //  p += 0;
  for(int i=0; i<fdnew.getSize(); p+=++i) {
    if(send(*p, &bytes_nbo, 2, NULL) != 2)
      std::cerr << "send()_nbo";
    left = buffer->size();
    while(left>0) {
      bytes = send(*p, buffer->c_str()+(buffer->size()-left), left, NULL);
      left -= bytes;
    }
  }
}

int Network::Send(stringc *buffer) {
  uint16_t bytes_nbo;
  int left, bytes;
  bytes_nbo = htons(buffer->size());
  if(send(fd, &bytes_nbo, 2, NULL) != 2)
    std::cerr << "send()_nbo";
  left = buffer->size();
  while(left>0) {
    bytes = send(fd, buffer->c_str()+(buffer->size()-left), left, NULL);
    left -= bytes;
  }
}


