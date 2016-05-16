# PixSumpx,  Counting or Adding primes upto x

Let us denote pi(x) the number of primes up to x and sp(x) the sum of primes up to x

The primes up to 10 are 2, 3, 5, 7, thus pi(10 = 4  and Sp(10) = 2+3+5+7 = 17.

This repository contains files to compute pi(x) and Sp(x) in time
O(x^(2/3)/log^2 x) for x up to 2^63-1

The algorithm for computing pi(x) is presented in:

Computing Psi(x), M. Deléglise and  J. Rivat. Math. Comp. 67 (1998), no. 224, 1691-1696.

Let f a function defined on positive integers such that f(ab) = f(a) f(b).

The algorithm computing pi(x) can easily be adapted to the computation of
S_f(x) =sum{f(p), p <= x} with the same complexity O(x^(2/3)/log^2 x).

This is explained in:
Maximal product of primes whose sum is bounded. With J.-L. Nicolas.
Proceedings of the Steklov Institute of Mathematics (2013), 282, Issue
1, p. 73-102.

Or in Arxiv, http://arxiv.org/abs/1207.0603, pages 25-35.


# How to use these files
These files, written in C++,  can be compiled using C++
 I tested them  on a PC using linux Ubuntu
 and on a mac-book pro 64 bits.

Once we have got the sources ant put them in a directory, you open a
command window in this this directory and execute

> make

This will create four executable programms,
pi64, sump64, prime64, invsump64.

> pi64  x

compute pi(x) for x <=2^63-1

> sump64 x

computes sp(x) for x <=2^63-1

> prime64 n

computes the nth prime   (n <= 10^17)

> invsump64 y

computes the largest prime p such that sp(p) <= y
and the diffrence Delta = y-sp(p).
Here y must be less than 10^35

These programms are verbose. A lot of informations are written on
stderr. If you want a less verbose output you can redirect stderr to
null, using, for example,

pi64 10000000000000000000 2>/dev/null

These programms were written long ago, about ten years.
It is possible to compute for larger values of x by making,
for example,

> make pi

creates an executable which was used to compute pi(x) for x until
10^20. But I made some changes several years ago that introduced
some arithmetic overflows. So it is better to not use these long versions.




 



