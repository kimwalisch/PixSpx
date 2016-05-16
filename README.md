# PixSumpx

Counting or Adding primes upto x

Let us note pi(x) the number of primes up to x

And Sp(x) the sum of primes up to x

The primes up to 10 are 2, 3, 5, 7, thus pi(10 = 4  and Sp(10) = 2+3+5+7 = 17.

This repository contains files to compute pi(x) and Sp(x) in time
O(x^(2/3)/log^2 x).

The algorithm for computing pi(x) is presented 

Computing Psi(x), M. Deléglise and  J. Rivat. Math. Comp. 67 (1998), no. 224, 1691-1696.

Let f a function defined on positive integers such that f(ab) = f(a) f(b).

The algorithm computing pi(x) can easily be adapted to the computation of
S_f(x) =sum{f(p), p <= x} with the same complexity O(x^(2/3)/log^2 x).

Once we have got the sources ant put them in a directory, you open a
command window in this this directory and execute

make

This will make four executable programms

pi64                       :  pi64  x  compute pi(x) for x <=2^63-1 
sump64                 :  sump64 x computes sp(x) for x <=2^63-1
prime64                 : prime64 n  computes the nth prime   (n <= 10^17)
invsump64            : invsump64 y computes the largest prime p such
                                that sp(p) <= y and the diffrence delta=y-sp(p) 



