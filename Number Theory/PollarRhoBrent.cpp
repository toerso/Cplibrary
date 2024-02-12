
#include<bits/stdc++.h>
#define mod %

using ui64 = uint64_t;

namespace MazdaXtoerso {
    using ui128 = __uint128_t; constexpr int MAXLIMIT = 1e6+9;

    template<typename Tn> struct PollardRho {
    private:
        //Declare Smallest Prime Factors Array
        int spf[MAXLIMIT];

    private:
        inline Tn mult(Tn a, Tn b, Tn p) {
            return static_cast<Tn>(static_cast<ui128>(a)*b mod p);
        }

        inline Tn f(Tn x, Tn c, Tn n) {
            return (mult(x, x, n) + c) mod n;
        }

        inline Tn diff(Tn a, Tn b) {
            return (a > b) ? a - b : b - a;
        }

        inline Tn rand(Tn lower, Tn upper) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<Tn> dist(lower, upper);

            return dist(gen);
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

        Tn gcd(Tn a, Tn b) {
            while(b) {
                a %= b; std::swap(a, b);
            }

            return a;
        }

        void init() {
            spf[1] = 1; int sqrtn = static_cast<int>(std::sqrt(MAXLIMIT));

            for (int i = 2; i < MAXLIMIT; ++i) spf[i] = i;
            for(int i = 4; i < MAXLIMIT; i += 2) spf[i] = 2;
            for (int i = 3; i <= sqrtn ; i += 2) {
                if(spf[i] != i) continue;

                for(int j = i*i; j < MAXLIMIT; j += i) {
                if(spf[j] != j) continue;
                spf[j] = i;
                }
            }
        }

        bool millerRabin(Tn p) {
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

        Tn pollardRhoBrent(Tn n) {
            Tn har = rand(2, n), c = rand(2, n), po = 1, q = 1;
            const Tn m = 128;
            Tn g, hars, tor;

            do {
                tor = har;
                for(Tn i = 0; i < po; ++i) har = f(har, c, n);

                Tn k = 0;

                do{
                    hars = har;

                    for(Tn i = 0; i < std::min(m, po - k); ++i) {
                        har = f(har, c, n);
                        q = mult(q, diff(har, tor), n);
                    }

                    g = gcd(q, n);
                    k += m;
                }while(k < po && g == 1);

                po <<= 1;
            }while(g == 1);

            if(g == n) {
                do {
                    hars = f(hars, c, n);
                    g = gcd(diff(hars, tor), n);
                }while(g == 1);
            }

            return g;
        }
    public:
        PollardRho() {//constructor
            init();
        }

    public:
        std::vector<Tn> primeFactorize(Tn n) {
            if(n <= 1) return {};
            if(millerRabin(n)) return {n};

            std::vector<Tn> primes, helper;

            if(n > 1 && n < MAXLIMIT) {
                do {
                    primes.emplace_back(spf[n]); n /= spf[n];
                }while(n != 1);

                return primes;
            }

            Tn p = pollardRhoBrent(n);
            p = (p != 0 && p != n) ? p : pollardRhoBrent(n);
            primes = primeFactorize(p);
            helper = primeFactorize(n/p);
            primes.insert(primes.end(), helper.begin(), helper.end());

            return primes;
        }
    };
};

int32_t main() {
    MazdaXtoerso::PollardRho<ui64> pr;
    ui64 n;

    std::cin >> n; auto primes = pr.primeFactorize(n);

    for(auto& elem: primes) std::cout << elem << " ";

    return 0;
}



