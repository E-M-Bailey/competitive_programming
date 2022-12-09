#include "template.h"
#include "number theory.h"

constexpr i64 MOD = 1e9 + 7;
typedef mod_int<i64, MOD> mod;
typedef vector<mod> vmod;

void go()
{
    vmod VM(50);
    for (int i = 0; i < 50; i++)
        VM[i] *= 4;
}
