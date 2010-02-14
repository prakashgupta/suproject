#include <irrlicht/irrlicht.h>
#include "../api/player.pb.h"
#include "../api/Network.h"
#include "../api/Thread.h"
#include "../api/Core.h"

int main(void) {
  stringc ex;
  list<stringc> el;
  Network network;
  
  network.Startup(2000, 3);
  //  while(network.getSize()<3) usleep(1);
  usleep(100);
  while(1) {
    sleep(3);
    std::cout << "NUM: " << network.getSize() << std::endl;
    network.ReceiveAll(&el);
    if(!el.getSize()) continue;
    list<stringc>::Iterator sp = el.begin();
  //  std::cout << std::endl << ex.size() << std::endl;
  //  for(int i=0; i<512; i++)
  //std::cout << ex[i] << " ";
  //  std::cout << ex.c_str() << std::endl;
    for(int i=0; i<el.getSize(); i++) {
      std::cout << sp->c_str() << std::endl;
      sp++;
    }
    std::cout.flush();
  //  ex.append("1234567891011121314151617181920");
  //  network.SendAll(&ex);
  //  std::cout << "Enviei" << std::endl;
  //  std::cout.flush();
    std::cout << "FINISH" << std::endl;
    //    sleep(5);
  }
  sleep(10);
  return 0;

}
