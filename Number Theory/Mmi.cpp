/**
 * author : toerso
 * date   : 04.11.23
 */

#include<iostream>
#include<tuple>

int extendedEuclid(int a, int b, int& x) {
   x = 0;
   int x1 = 1;

   while(b) {
      int q = a/b;
      std::tie(x, x1) = std::make_tuple(x1, x-q*x1);
      std::tie(a, b) = std::make_tuple(b, a-q*b);
   }

   return a;
}


int main(int argc, char *argv[]) {
   int a, x, m;
   std::cin >> a >> m;

   //where m > a;

   if(extendedEuclid(m,a, x) == 1) {
      std::cout << (x%m + m)%m << "\n";
   }else
      std::cout << "Not exist!" << "\n";


   return 0;
}
