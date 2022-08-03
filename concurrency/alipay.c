#include "./../lib/thread.h"

unsigned long balance = 100;

void Alipay_withdraw(int amt) {
  if (balance >= amt) {
    usleep(1); // unexpected delays
    balance -= amt;
  }
}

void Talipay(int id) {
  Alipay_withdraw(100);
}

int main() {
  create(Talipay);
  create(Talipay);
  join();
  printf("balance = %lu\n", balance);
}

/*
gcc alipay.c -lpthread -o alipay.out && ./alipay.out

循环执行
while true; do ./alipay.out; done

8446744073709551516 整数溢出
*/