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
These files, written in C++,  can be compiled using
the gnu compiler g++ and the library GNU MP.
 I tested them  on a PC using linux Ubuntu
 and on a mac-book pro 64 bits.

Once we have got the sources ant put them in a directory, open a
command window in this this directory and execute

> make

This will create four executable programms,
pi64, sump64, prime64, invsump64.

> pi64  x

computes pi(x) for x <=2^63-1

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

pi64 100000000000000000 2>/dev/null

#Remark 1
It is the same source main.cc that is  used to compute pi(x) or sp(x).
The only change is that, in the case of pi(x) the function f which is
summed other primes is the constant function 1, while, for computing
sp(x), the function f is replaced by the identity function f(x)=x.

#Remark 2
Usin files in  Repository PixSpx2015 you can  construct a program
pi for computin pi(x)  and a program ithprime for computing the
ithprime, that are three of four times faster than pi64 and prime64.







 



