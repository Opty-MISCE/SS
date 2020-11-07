#!/usr/bin/env python
from pwn import *
from re import findall

SERVER = "mustard.stt.rnl.tecnico.ulisboa.pt"
PORT = 15001

# Run a Remote Process
s = remote(SERVER, PORT)

# Interact With It
trg, crr = findall(r"\d+", s.recvuntil("(type FINISH)?").decode("UTF-8"))

while crr != trg:
    s.sendline("MORE")
    crr = findall(r"\d+", s.recvuntil("(type FINISH)?").decode("UTF-8"))[-1]

s.sendline("FINISH")
print(s.recvuntil("}").decode("UTF-8"))
s.close()
