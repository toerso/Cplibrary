/**
 * author : toerso
 * date   : 02.11.23
 * generate all etf value from 0-1e5+9
 */

#include<iostream>

const int N = 1e5+9;
int phi[N];

void totient() {
   for (int i = 0; i < N; ++i) phi[i] = i;

   for (int i = 2; i < N; ++i) {
      if(phi[i] == i) {
         for (int j = i; j < N; j += i) phi[j] -= phi[j]/i;
      }
   }
}

int main(int argc, char *argv[]) {
   totient();

   return 0;
}
