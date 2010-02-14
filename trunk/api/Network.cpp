#include "Network.h"

Network::Network(void) {
  tv.tv_sec = 0;
  tv.tv_usec = 0;
}

Network::~Network() {			       
  list<int>::Iterator it = remoteFD.begin();
  
  for(int i=0; i<remoteFD.getSize(); i++) {
    close(*it);
    it++;
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
  list<int>::Iterator it = remoteFD.begin();
  
  for(int i=0; i<remoteFD.getSize(); i++) {
    it+=i;
    close(*it);
  }
  close(fd);
}

int Network::Close(int id) {
  list<int>::Iterator it = remoteFD.begin();
  it+=id;
  close(*it);
  remoteFD.erase(it);
  
  list<stringc>::Iterator ip = remoteIP.begin();
  ip += id;
  remoteIP.erase(ip);
  
  std::cout << "CLOSE: " << id << std::endl;
}

void Network::Wait(void) {
  while(fd) {
    socklen_t size;
    int fdtmp;
    char iptmp[16];
    //    std::cout << "Funcionando! " << max << " " << port;
    
    while((((fdtmp = accept(fd, (struct sockaddr *)&addr,&size)))<0)||(remoteFD.getSize()>=max))usleep(1);
    inet_ntop(addr.sin_family, &addr.sin_addr, iptmp, INET_ADDRSTRLEN);
    remoteIP.push_back(iptmp);
    std::cout << iptmp << " " << fdtmp << " conectado.\n";
    remoteFD.push_back(fdtmp);
  }
}

int Network::getSize(void) {
  return remoteFD.getSize();
}


int Network::Receive(int id, stringc *buffer) {
  list<int>::Iterator fp = remoteFD.begin();
  fp+=id;
  char *btmp;
  int total, received, left;
  uint16_t bytes_nbo;

  recv(*fp, &bytes_nbo, 2, 0);
  total = ntohs(bytes_nbo);
  std::cout << std::endl << total << std::endl;
  left = total;
  
  while(left > 0) {
    btmp = new char[left+1];
    received = recv(*fp, btmp, left, NULL);
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

int Network::ReceiveAll(list<stringc> *buffer) {
  if(!remoteFD.getSize())
    return -1;
  char *btmp;
  int total, received, left, rv;
  uint16_t bytes_nbo;  
  
  buffer->clear();  
    //  list<stringc>::Iterator sp = buffer->begin();
  
  
  ufds = new struct pollfd[remoteFD.getSize()];

  list<int>::Iterator fp = remoteFD.begin();
  //  std::cout << *fp << *(fp+1) << *(fp+2);

  for(int i=0; i<remoteFD.getSize(); i++) {
    buffer->push_back("aaaaaaa");
    ufds[i].fd = *fp;
    ufds[i].events = POLLIN | POLLHUP | POLLERR;
    fp++;
  }
  
  rv = poll(ufds, remoteFD.getSize(), 0);
  std::cout << "RV: " << rv << std::endl;
  if(rv<1)
    return rv;
  
  fp = remoteFD.begin(); 
  list<stringc>::Iterator sp = buffer->begin();
  for(int i=0; i<remoteFD.getSize(); i++) {
    
    if(ufds[i].revents & POLLIN) {    
      
      if(!recv(*fp, &bytes_nbo, sizeof(uint16_t), NULL))
	{
	  std::cout << "CLOSE!!!!!" << std::endl;
	  this->Close(i);
	  i--;
	  continue;
	}
      total = ntohs(bytes_nbo);
	std::cout << "FP: " << *fp << std::endl << "TOTAL: " << total << std::endl << "Buffer: " << sp->c_str() << std::endl;
	left = total;
	while(left > 0) {
	  btmp = new char[left+1];
	  received = recv(*fp, btmp, left, NULL);
	  btmp[left] = '\0';
	  *sp = btmp;
	  delete [] btmp;
	  left -= received;
	  std::cout << std::endl << received << std::endl;
	}
      }
      sp++;
      fp++;
    }
    
    
  delete [] ufds;
}


int Network::Send(int id, stringc *buffer) {
  uint16_t bytes_nbo;
  int left, bytes;
  bytes_nbo = htons(buffer->size());
  list<int>::Iterator p = remoteFD.begin();
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
  list<int>::Iterator fp = remoteFD.begin();
  //  p += 0;
  for(int i=0; i<remoteFD.getSize(); fp+=++i) {
    if(send(*fp, &bytes_nbo, 2, NULL) != 2)
      std::cerr << "send()_nbo";
    left = buffer->size();
    while(left>0) {
      bytes = send(*fp, buffer->c_str()+(buffer->size()-left), left, NULL);
      left -= bytes;
    }
  }
}

int Network::Send(stringc *buffer) {
  uint16_t bytes_nbo;
  int left, bytes;
  bytes_nbo = htons(buffer->size());
  if(send(fd, &bytes_nbo, sizeof(uint16_t), NULL) != 2)
    std::cerr << "send()_nbo";
  left = buffer->size();
  while(left>0) {
    bytes = send(fd, buffer->c_str()+(buffer->size()-left), left, NULL);
    left -= bytes;
  }
}

int Network::getIP(int id, stringc *buffer) {
  list<stringc>::Iterator sp = remoteIP.begin();
  sp+=id;
  *buffer = *sp;
}
