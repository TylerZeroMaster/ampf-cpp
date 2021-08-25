# Concurrent Queue Example

## About
This program finds [Mersenne prime numbers](https://en.wikipedia.org/wiki/Mersenne_prime) in the sequence discovered starting at three. It accomplishes this with the help of [The GNU Multiple Precision Arithmetic Library.](https://gmplib.org/) I made this program so that I would become more familiar with multi-threading in C++. It utilizes my implementations of a concurrent queue and an [optimized modulo](https://en.wikipedia.org/wiki/Lucas%E2%80%93Lehmer_primality_test#Time_complexity) operation.

## Usage
```
concurrent_queue_ex [number of Mersenne prime exponents to find]
```