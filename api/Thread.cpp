#include "Thread.h"
#include "Network.h"


Thread::Thread() {
  on = 0;
}

Thread::~Thread() {
  if(on)
  pthread_cancel(pid);
}

int Thread::Start(void * arg)
{
   Arg = arg; // store user data
   on=1;
   int code = pthread_create(&(pid), NULL, &Thread::EntryPoint, this);
   return code;
 }

int Thread::Run()
{
   Setup();
   Execute();
}

/*static */
void *Thread::EntryPoint(void *pthis)
{
  //  Thread *pt = reinterpret_cast<Thread>(pthis);
  //   (*pthis).Run();
  ((Thread*)pthis)->Run();
}

void Thread::Setup()
{
        
}

void Thread::Execute()
{
        
}

void ThNetwork::Execute() {
  ((Network*)Arg)->Wait();
}
