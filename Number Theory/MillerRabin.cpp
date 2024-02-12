/**
 * author : toerso
 * to     : mazda
 * date   : 28.01.24
 */

/* Problem ID: id-cf */
#include<iostream>
#include<random>

#define gcd std::__gcd
#define mod %

using ui64 = uint64_t;

namespace MazdaXtoerso {
   using ui128 = __uint128_t;

   template<typename Tn> struct MillerRabin{
    public:
        bool isPrime(Tn p) {
            if(p < 4) return p == 2 || p == 3;
            int s = 0; Tn d = p - 1;

            while((d&1) == 0) {
                d >>= 1, s++;
            }

            auto isComposite = [&d, &s, &p, this](int a) -> bool {
                Tn x = pow(a, d, p);

                if(x == 1 || x == p - 1) return false;

                for (int r = 1; r < s; ++r) {
                    x = mult(x, x, p);
                    if(x == p - 1) return false;
                }

                return true;
            };

            for(int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
                if(static_cast<Tn>(a) == p) return true;

                if(isComposite(a)) return false;
            }

            return true;
        }


    private:
        inline Tn mult(Tn a, Tn b, Tn modval) {
            return static_cast<Tn>(static_cast<ui128>(a) * b mod modval);
        }

        Tn pow(Tn base, Tn power, Tn p) {
            Tn res = 1;
            Tn newBase = base mod p;
            while(power) {
                if(power & 1) res = mult(res, newBase, p);
                newBase = mult(newBase, newBase, p);
                power >>= 1;
            }

            return res;
        }
   };
}

int main(int argc, char *argv[]) {
   int q; ui64 n;
   std::cin >> q;

   MazdaXtoerso::MillerRabin<ui64> mr;

   for (int i = 0; i < q; ++i) {
      std::cin >> n;

      if(mr.isPrime(n)) std::cout << "YES" << "\n";
      else std::cout << "NO" << "\n";
   }

   return 0;
}
