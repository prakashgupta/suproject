#ifndef _THREAD_H_
#define _THREAD_H_

#include <pthread.h>
#include <sys/signal.h>
#include <sys/types.h>
/*struct ThreadArgs {
  void *Function;
  };*/

class Thread {
public:
  Thread();
  ~Thread();
  int Start(void *);
protected:
  void * Arg;
  int Run();
  virtual void Setup();
  virtual void Execute();
  /*      void * Arg() const {return Arg_;}
	  void Arg(void* a){Arg_ = a;}*/
private:
  pthread_t pid;
  static void *EntryPoint(void *);
};

class ThNetwork : public Thread {
private:
  void Execute();
};

#endif //_THREAD_H_
