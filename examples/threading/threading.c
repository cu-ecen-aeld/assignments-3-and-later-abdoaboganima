#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

int sleep_ms(int ms)
{
  int ret=0;
  for (int i = 0; i < ms; ++i){
    ret=usleep(1000);
  }
  return ret;
}


void* threadfunc(void* thread_param)
{

    // TODO: wait, obtain mutex, wait, release mutex as described by thread_data structure
    // hint: use a cast like the one below to obtain thread arguments from your parameter
  struct thread_data* thread_func_args = (struct thread_data *) thread_param;

  puts("Executing the thread....");
    
  
  //wait
  sleep_ms(thread_func_args->wait_to_obtain_ms);

  
  //obtain mutex
  int rc= pthread_mutex_lock(thread_func_args->mutex);
  if(rc!=0){
    thread_func_args->thread_complete_success=0;
    errno=rc;
    perror("Mutex lock failed");
  }
  else{
    
    puts("The mutex is locked");

    //wait
    sleep_ms(thread_func_args->wait_to_release_ms);
      
    //release mutex
    pthread_mutex_unlock(thread_func_args->mutex);
    puts("The mutex is unlocked");

    //Completion status
    thread_func_args->thread_complete_success=1;
  }
    
  return thread_param;
  
  

}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    /**
     * TODO: allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread
     * using threadfunc() as entry point.
     *
     * return true if successful.
     *
     * See implementation details in threading.h file comment block
     */
  /*Allocate memory for thread data*/
  struct thread_data *t_data=malloc(sizeof(struct thread_data));
  
  /*setup mutex and wait arguments*/
  t_data->mutex                   = mutex;
  t_data->wait_to_obtain_ms       = wait_to_obtain_ms;
  t_data->wait_to_release_ms      = wait_to_release_ms;
  t_data->thread_complete_success = 0;
  
  /*pass thread_data to created thread  using threadfunc() as entry point.*/
  pthread_t t;
  int rc= pthread_create(&t, NULL, threadfunc, t_data);

  if(rc!=0)
    return false;
  
  *thread=t;

  return true;

}

