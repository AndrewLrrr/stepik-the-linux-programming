#!/usr/bin/env python3

import random
import sys


def gen_zeros(n):
    while n:
        yield 0
        n -= 1


def gen_other(n):
    while n:
        yield random.randint(1, 9)
        n -= 1


inp = int(sys.argv[1])
zeros = random.randint(1, inp)
other = inp - zeros
gen_zeros = gen_zeros(zeros)
gen_other = gen_other(other)

gens = [gen_zeros, gen_other]

while True:
    if len(gens) == 0:
        break
    n = 0
    if len(gens) == 2:
        n = random.randint(0, 1)
    gen = gens[n]
    try:
        print(next(gen), end='')
    except StopIteration:
        del gens[n]
