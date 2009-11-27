#include "../api/Network.h"
#include "../api/Thread.h"
int main(void) {
  stringc ex;
  
  Network network;
  
  network.Startup(2000, 1);
  while(network.getSize()<1) usleep(1);
  //  network.Receive(0, &ex);
  //  std::cout << std::endl << ex.size() << std::endl;
  //  for(int i=0; i<512; i++)
  //std::cout << ex[i] << " ";
  //std::cout << ex.c_str() << std::endl;
  //  std::cout.flush();
  ex.append("1234567891011121314151617181920");
  network.SendAll(&ex);
  std::cout << "Enviei" << std::endl;
  std::cout.flush();
  std::cout << "FINISH" << std::endl;
  sleep(10);
  return 0;

}
