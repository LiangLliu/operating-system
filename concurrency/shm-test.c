/**
 * 共享内存验证
 */
#include "./../lib/thread.h"

int x = 0;

void Thello(int id)
{
  printf("Thread id : %d\n", id);
  usleep(id * 100000); // 微秒, 根据线程的id不同休眠不同
  printf("Hello from thread #%c\n", "123456789ABCDEF"[x++]);
}

int main()
{
  for (int i = 0; i < 10; i++)
  {
    create(Thello);
  }
}

/*
 gcc shm-test.c -lpthread -o shm-test.out && ./shm-test.out
*/
