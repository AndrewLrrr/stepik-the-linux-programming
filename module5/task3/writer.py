#!/usr/bin/env python3

import random
import socket
import sys

HOST = '127.0.0.1'
PORT = int(sys.argv[1])
WORDS = """
Where the Baker had met with the Snark.
He had softly and suddenly vanished away
In the midst of his laughter and glee,
Where the Baker had met with the Snark.
Not a button, or feather, or mark,
Where the Baker had met with the Snark.
He had softly and suddenly vanished away
Then, silence. Some fancied they heard in the air
In the midst of his laughter and glee,
A weary and wandering sigh
That sounded like -jum! but the others declare,
Where the Baker had met with the Snark.
"""

words = set([l.strip() + '\0' for l in WORDS.replace('\n', ' ').split()])
sorted_words = []
max_word_len = 0

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    print('Connect to sort-server.')
    num_of_words = random.randint(5, 30)
    print('Start to send data. Number of words {}:'.format(num_of_words))
    for i, word in enumerate(words):
        if i == num_of_words:
            break
        print('Send:   ', word)
        s.sendall(word.encode('utf-8'))
        resp = s.recv(8192)
        print('Receive:', resp.decode('utf-8'))
        print('--------')
    s.sendall('OFF\0'.encode('utf-8'))
    print('Disconnect from sort-server')
