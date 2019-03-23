#!/usr/bin/python3

import os
import random
import sys
import time

PIPE_ONE = os.path.join(os.path.curdir, 'in1')
PIPE_TWO = os.path.join(os.path.curdir, 'in2')
SLEEP_TIME = 0.5

inp = int(sys.argv[1])

if not os.path.exists(PIPE_ONE):
    os.mkfifo(PIPE_ONE)

if not os.path.exists(PIPE_TWO):
    os.mkfifo(PIPE_TWO)

p1 = open(PIPE_ONE, 'w')
p2 = open(PIPE_TWO, 'w')

pipes = [p1, p2]

total = 0
for _ in range(inp):
    n = random.randint(0, 1)
    r = random.randint(0, 1000)
    print(r, file=pipes[n])
    total += r
    pipes[n].flush()
    time.sleep(SLEEP_TIME)

print(total)

p1.close()
p2.close()

if len(sys.argv) > 2 and sys.argv[2] == 'clear':
    os.remove(PIPE_ONE)
    os.remove(PIPE_TWO)
