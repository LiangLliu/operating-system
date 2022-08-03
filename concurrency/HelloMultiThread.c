#include "./../lib/thread.h"

void Ta() { while (1) { printf("a"); } }
void Tb() { while (1) { printf("b"); } }

int main() {
  create(Ta);
  create(Tb);
}

/*

gcc HelloMultiThread.c -lpthread -o HelloMultiThread.out && ./HelloMultiThread.out

*/