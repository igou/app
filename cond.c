In Thread1:
pthread_mutex_lock(&m_mutex);   
pthread_cond_wait(&m_cond,&m_mutex);   
pthread_mutex_unlock(&m_mutex);  
 
 In Thread2:
 pthread_mutex_lock(&m_mutex);   
 pthread_cond_signal(&m_cond);   
 pthread_mutex_unlock(&m_mutex);  
  
  为什么要与pthread_mutex 一起使用呢？ 这是为了应对 线程1在调用pthread_cond_wait()但线程1还没有进入wait cond的状态的时候，此时线程2调用了 cond_singal 的情况。 如果不用mutex锁的话，这个cond_singal就丢失了。加了锁的情况是，线程2必须等到 mutex 被释放（也就是 pthread_cod_wait() 释放锁并进入wait_cond状态 ，此时线程2上锁） 的时候才能调用cond_singal.
