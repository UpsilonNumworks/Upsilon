#include "script_template.h"

namespace Code {

constexpr ScriptTemplate emptyScriptTemplate(".py", "\x01" R"(from math import *
from mathsup import *
)");

constexpr ScriptTemplate mathsupScriptTemplate("mathsup.py","\x01" R"(
from random import random, uniform
from math import log2

primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101,
          103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211,
          223, 227, 229, 233, 239, 241, 251, 257]


def fact(x: int) -> int:
    r = 1
    for i in range(x):
        r *= (i + 1)
    return int(r)


def combi(n: int, k: int) -> int:
    if k > n:
        return None
    x = fact(n) / (fact((n - k)) * fact(k))
    return int(x)


def arran(n: int, k: int) -> int:
    if k > n:
        return None
    x = fact(n) / fact((n - k))
    return int(x)


def permut(n: int) -> int:
    return int(fact(n))


def disc(a: float, b: float, c: float) -> int:
    d = (b**2) - (4*a*c)
    return d


def q(a: int, b: int) -> int:
    q, r = a//b, a % b
    if r > b or r < 0:
        r -= b
        q += 1
    return int(q)


def r(a: int, b: int) -> int:
    r = a % b
    if r > b:
        r -= b
    elif r < 0:
        r += b
    return int(r)


def dive(a: int, b: int) -> int:
    qu, re = q(a, b), r(a, b)
    return qu, re


def iscong(a: int, b: int, n: int) -> int:
    return r(a - b, n) == 0


def cong(a: int, n: int) -> tuple:
    b = r(a, n)
    if b == 0:
        return int(b)
    else:
        if b < 0 or n < 0:
            c = b+n
        else:
            c = b-n
    return b, c


def congi(a: int, n: int) -> int:
    (b, c) = cong(a, n)
    if abs(b) >= abs(c):
        return c
    else:
        return b


def egcd(a: int, b: int) -> tuple:
    x0, x1, y0, y1 = 0, 1, 1, 0
    while a != 0:
        (q, a), b = dive(b, a), a
        y0, y1 = y1, y0 - q * y1
        x0, x1 = x1, x0 - q * x1
    return (b, x0, y0)


def pgcd(a: int, b: int) -> int:
    gcd, _, _ = egcd(a, b)
    return gcd


def ppcm(a: int, b: int) -> int:
    a, b = abs(a), abs(b)
    return q(a*b, pgcd(a, b))


def modinv(a: int, b: int) -> int:
    g, x, _ = egcd(a, b)
    if g != 1:
        return None
    return x % b


def prime(n: int) -> bool:
    L = primes
    n = abs(n)
    if n == 1:
        return False
    for k in L:
        if n % k == 0:
            if n == k:
                return True
            return False
    for i in range(257, int(n**0.5)+1, 2):
        if i > int(n**0.5)+2:
            return True
        if n % i == 0:
            return False
        S = splitter(i)
        S.reverse()
        if S[0] == 3:
            i += 2
    return True


def factor(n: int) -> list:
    div, L = 2, []
    if prime(n):
        return [n]
    while n > 1:
        if n % div == 0:
            L.append(div)
            n /= div
        else:
            div += 1
    return L


def divint(n: int) -> list:
    n, L = abs(n), []
    for i in range(1, int(n**0.5) + 1):
        if n % i == 0:
            L.append(i)
            L.append(n//i)

    return sorted(k for k in L if not(L.count(k) > 1))


def dioph(a: int, b: int, c=1, l=0) -> int:
    if c % pgcd(a, b) != 0:
        return None
    if c == 1:
        _, u, v = egcd(a, b)
        return (u, v)
    L = []
    r = abs(a) + abs(b)
    for u in range(-r, r):
        for v in range(-r, r):
            if (a*u) + (b*v) == c:
                L.append((u, v))
    if l:
        return L
    else:
        return L[int(len(L)/2)]


def nbdiv(n: int) -> int:
    f, nbr, L = factor(n), 1, []
    [k for k in range(len(f)) if L.count(k) == 0]

    for k in L:
        nbr *= len(divint(k**f.count(k)))
    return nbr


def nprime(n: int) -> list:
    return [k for k in range(n) if prime(k)]


def divcom(a: int, b: int) -> list:
    L_a, L_b = divint(a), divint(b)
    return [i for i in L_a if L_b.count(i) > 0]


def sdiv(n: int) -> int:
    return divint(n)[1]


def gdiv(n: int) -> int:
    d = divint(n)
    return d[len(d)-2]


def sprdiv(n: int) -> int:
    return factor(n)[0]


def gprdiv(n: int) -> int:
    f = factor(n)
    return f[len(f)-1]


def pi(n: int) -> float:
    c, t = 0, 0
    for _ in range(0, n + 1):
        x, y = random(), random()
        if x**2 + y**2 <= 1:
            c += 1
        t += 1
    return 4*(c/t)


def rng(x: float) -> float:
    r = uniform(0.75, 1.25)
    return x*r


def tp(x: int, y: int, z: int) -> bool:
    return (x*x) + (y*y) == z*z and x < y < z


def lstbin(n: int) -> list:
    a = n
    L = []
    lg2 = int(log2(n))
    for k in range(lg2, 0, -1):
        if (2**k) <= a:
            a -= 2**k
            L.append(2**k)
    if r(n, 2) == 1:
        L.append(1)
    return L


def max2int(a: int, b: int) -> int:
    return q(a + b + abs(a-b), 2)


def based(n: str, base: int, base_out: int = 10, bits: int = 8) -> str:
    assert base < 36 or base_out < 36
    if isinstance(n, int):
        n = str(n)
    assert not n.startswith("-")
    symbs = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f", "g",
             "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"]
    symbsofbase = symbs[0:base]

    s = n
    virg = (s.count(".") > 0)

    if virg and base_out != 10:
        return ValueError("Number with ',' only when output is base 10")
    if virg:
        lt = s.split(".")
        l1 = list(lt[0])
        l2 = list(lt[1])
        l1.reverse()

        nbase10 = 0
        for k in range(len(l1)):
            nbase10 += symbsofbase.index(l1[k])*base**k
        for k in range(len(l2)):
            nbase10 += symbsofbase.index(l2[k])*base**(-(k+1))
        if base_out == 10:
            return nbase10
    else:
        l = list(s)
        l.reverse()

        nbase10 = 0
        for k in range(len(l)):
            nbase10 += symbsofbase.index(l[k])*base**k
        if base_out == 10:
            return nbase10

    symbsofoutbase = symbs[0:base_out]
    k = nbase10
    l_out = []
    while k > 0:
        l_out.append(symbsofoutbase[r(k, base_out)])
        k = q(k, base_out)
    l_out.reverse()
    s_out = "".join(l_out)
    return s_out


def cplmt2(n: int, bits: int = 8) -> str:
    b = based(str(abs(n)), 10, 2)

    if n >= 0:
        return b
    if len(b) < bits:
        b = "0" * (bits - len(b)) + b
    c = ""
    for k in b:
        if k == "0":
            c += "1"
        else:
            c += "0"
    c = int(bin(based(c, 2)), 2) + 1
    return based(str(c), 10, 2)


def joiner(L: list) -> float:
    if not isinstance(L, list):
        return None
    return float("".join(str(L[i]) for i in range(len(L))))


def splitter(s: str) -> list:
    p = 0
    if not isinstance(s, str) and isinstance(s, int):
        p = 1
        s = str(s)
    L = [c for c in s]

    if p == 1:
        L = [int(L[k]) for k in range(len(L))]
    return L)"
);

const ScriptTemplate * ScriptTemplate::Empty() {
  return &emptyScriptTemplate;
}

const ScriptTemplate * ScriptTemplate::Mathsup(){
  return &mathsupScriptTemplate;
}

}
