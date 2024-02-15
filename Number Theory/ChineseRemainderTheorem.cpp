/**
 * author : toerso
 * to     : mazda
 * date   : 15.02.24
 */

#include<bits/stdc++.h>
#define mod %

using ui64 = uint64_t;

namespace MazdaXtoerso {
   template<typename Tp> struct Crt {
   private:
      Tp extendedEuclid(Tp a, Tp b, Tp& x, Tp& y) {
         x = 1, y = 0;
         Tp x1 = 0, y1 = 1;
         while (b) {
            Tp q = a / b;
            std::tie(x, x1) = std::make_tuple(x1, x - q * x1);
            std::tie(y, y1) = std::make_tuple(y1, y - q * y1);
            std::tie(a, b) = std::make_tuple(b, a - q * b);
         }

         return a;
       }

   public:
      std::pair<Tp, Tp> exec(Tp firstRem, Tp firstModVal, Tp secondRem, Tp secondModVal) {
         Tp x, y;
         Tp g = extendedEuclid(firstModVal, secondModVal, x, y);
         Tp diff = firstRem - secondRem;

         if(diff mod g != 0) return std::make_pair(0, -1);

         Tp k = diff / g;
         Tp lcm = firstModVal/g * secondModVal;
         Tp sol = firstRem - firstModVal*((k*x) mod (secondModVal/g));

         return std::make_pair(sol, lcm);
      }
   };
}

int32_t main() {
   MazdaXtoerso::Crt<long long> crt;
   auto p = crt.exec(4, 5, 6, 7);
   std::cout << p.first << "\n";

   return 0;
}
