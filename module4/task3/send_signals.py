#!/usr/bin/python3

import os
import random
import signal
import sys
import time

pid = int(sys.argv[1])
n = random.randint(1, 100)
s1 = 0
s2 = 0

for _ in range(n):
    m = random.randint(0, 1)
    if m == 0:
        s1 += 1
        os.kill(pid, signal.SIGUSR1)
    else:
        s2 += 1
        os.kill(pid, signal.SIGUSR2)
    # Иначе сигналы могут считаться некорректно
    time.sleep(0.05)

os.kill(pid, signal.SIGTERM)

print(s1, s2)
