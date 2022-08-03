#include "./../lib/thread.h"

#define N 100000000

long sum = 0;

void Tsum() {
  for (int i = 0; i < N; i++) {
    sum++;
  }
}

int main() {
  create(Tsum);
  create(Tsum);
  join();
  printf("sum = %ld\n", sum);
}

/*
gcc sum.c -lpthread -o sum.out && ./sum.out

while true; do ./sum.out; done;

gcc -O1 sum.c -lpthread -o sum.out && ./sum.out
sum = 100000000
gcc -O2 sum.c -lpthread -o sum.out && ./sum.out
sum = 200000000

gcc -O1 sum.c -o sum.out && objdump -d sum.out

*/