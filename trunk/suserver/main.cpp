#include "Network.h"
#include "Thread.h"
int main(void) {

  Network network(2000, 1);
  
  network.Startup();
  sleep(1);
  return 0;

}
