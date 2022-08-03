#include "./../lib/thread.h"

int x = 0, y = 0;

atomic_int flag; // 开关，初始值为0，开关是关的
#define FLAG atomic_load(&flag)
#define FLAG_XOR(val) atomic_fetch_xor(&flag, val) // 异或到某一个常数
#define WAIT_FOR(cond) while (!(cond)) ; // 等到某一个条件发生

 __attribute__((noinline))
void write_x_read_y() {
  x = 1;
  printf("%d ", y);
}

 __attribute__((noinline))
void write_y_read_x() {
   y = 1;
  printf("%d ", x);
}

void T1(int id) {
  while (1) {
    WAIT_FOR((FLAG & 1));
    write_x_read_y();
    FLAG_XOR(1);
  }
}

void T2() {
  while (1) {
    WAIT_FOR((FLAG & 2));
    write_y_read_x();
    FLAG_XOR(2);
  }
}

// 控制线程
void Tsync() {
  while (1) {
    x = y = 0; 
    __sync_synchronize(); // full barrier
    usleep(1);            // + delay
    assert(FLAG == 0);
    FLAG_XOR(3); // 原子操作，把两个开关同时推上去 1, 1
    // T1 and T2 clear 0/1-bit, respectively
    WAIT_FOR(FLAG == 0); // 等到开关为0
    printf("\n"); fflush(stdout);
  }
}

int main() {
  create(T1);
  create(T2);
  create(Tsync);
}


/*
gcc mem-ordering-1.c -lpthread -o mem-ordering-1.out && ./mem-ordering-1.out

统计结果
gcc mem-ordering-1.c -lpthread -o mem-ordering-1.out && ./mem-ordering-1.out | head -n 1000 | sort | uniq -c
*/