In Thread1:
pthread_mutex_lock(&m_mutex);   
pthread_cond_wait(&m_cond,&m_mutex);   
pthread_mutex_unlock(&m_mutex);  
 
 In Thread2:
 pthread_mutex_lock(&m_mutex);   
 pthread_cond_signal(&m_cond);   
 pthread_mutex_unlock(&m_mutex);  
  
  为什么要与pthread_mutex 一起使用呢？ 这是为了应对 线程1在调用pthread_cond_wait()但线程1还没有进入wait cond的状态的时候，此时线程2调用了 cond_singal 的情况。 如果不用mutex锁的话，这个cond_singal就丢失了。加了锁的情况是，线程2必须等到 mutex 被释放（也就是 pthread_cod_wait() 释放锁并进入wait_cond状态 ，此时线程2上锁） 的时候才能调用cond_singal.

  /*add:
  ，就是说pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)函数传入的参数mutex用于保护条件，因为我们在调用pthread_cond_wait时，如果条件不成立我们就进入阻塞，但是进入阻塞这个期间，如果条件变量改变了的话，那我们就漏掉了这个条件。因为这个线程还没有放到等待队列上，所以调用pthread_cond_wait前要先锁互斥量，即调用pthread_mutex_lock(),pthread_cond_wait在把线程放进阻塞队列后，自动对mutex进行解锁，使得其它线程可以获得加锁的权利。这样其它线程才能对临界资源进行访问并在适当的时候唤醒这个阻塞的进程。当pthread_cond_wait返回的时候又自动给mutex加锁*/
