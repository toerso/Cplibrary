/**
 * author : toerso
 * date   : 04.11.23
 */

#include<iostream>
#include<tuple>

int extendedEuclid(int a, int b, int& x, int& y) {
   if(b==0) {
      x = 1;
      y = 0;
      return a;
   }

   int x1, y1;
   int gcd1 = extendedEuclid(b, a%b, x1, y1);

   x = y1;
   y = x1-(a/b)*y1;

   return gcd1;
}

int extendedEuclidIter(int a, int b, int& x, int& y) {
   x = 1, y = 0;
   int x1 = 0, y1 = 1;

   while(b) {
      int q = a/b;
      std::tie(x, x1) = std::make_tuple(x1, x-q*x1);
      std::tie(y, y1) = std::make_tuple(y1, y-q*y1);
      std::tie(a, b) = std::make_tuple(b, a-q*b);
   }

   return a;
}

int main() {
   int x = 0, y = 0;
   int a, b;
   std::cin >> a >> b;

   int gcd = extendedEuclidIter(a, b, x, y);

   std::cout << x << y << gcd << "\n";

   return 0;
}
