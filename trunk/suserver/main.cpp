#include "Network.h"
#include "Thread.h"
int main(void) {
  stringc ex;
  
  Network network(2000, 1);
  
  network.Startup();
  while(network.getSize()<1) usleep(1);
  network.Receive(0, &ex);
  std::cout << ex.c_str();
  std::cout.flush();`
  sleep(10);
  return 0;

}
