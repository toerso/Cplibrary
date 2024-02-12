/**
 * author : toerso
 * date   : 05.11.23
 */

#include<iostream>
#include<tuple>

int extendedEuclid(int a, int b, int& x, int& y) {
   x = 1, y = 0;
   int x1 = 0, y1 = 1;

   while(b) {
      int q = a/b;
      std::tie(x, x1) = std::make_tuple(x1, x-q*x1);

      std::tie(y, y1) = std::make_tuple(y1, y-q*y1);

      std::tie(a, b) = std::make_tuple(b, a-b*q);
   }

   return a;
}

int findingAnySol(int a, int b, int c, int& x0, int& y0) {
   int g = extendedEuclid(a, b, x0, y0);
   if(c%g) return false;

   x0 *= c/g;
   y0 *= c/g;

   if(a < 0) x0 = -x0;
   if(b < 0) y0 = -y0;

   std::cout << x0 << " " << y0 << " " << g << "\n";


   return true;
}

int findingAllSolution(int a, int b, int c, int& x0, int& y0) {
   int g = extendedEuclid(a, b, x0, y0);
   if(c%g) return false;

   int k = 0;
   int x = x0+k*(b/g);
   int y = y0-k*(a/g);

   //For all possible k.(infinity)

   return true;
}

int main(int argc, char *argv[]) {
   int a, b, c, x, y;
   std::cin >> a >> b >> c;

   findingAnySol(a, b, c, x, y);

   return 0;
}
