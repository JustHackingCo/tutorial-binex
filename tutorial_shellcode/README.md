# Tutorial: Shellcode

## Category: Binary Exploitation

## Description
```
The tutorial set of challenges are basic binary exploitation challenges designed to teach people various binary exploitation techniques. The recommended order to complete these challenges is ret2win, ROP, Shellcode, Canary, ASLR. These challenges can be completed without downloading and analyzing the binaries; however, they have been provided. If you need help with any of these challenges, feel free to reach out in the Discord.
```

### Flag: flag{d55f315d6e28d6aa347a6c99876301ab}

---
# Docker
Run the challenge with docker.  
```bash
$ docker build -t tutorial_shellcode .
$ docker run -p 9999:9999 tutorial_shellcode
```
Connect with netcat.
```bash
$ nc localhost 9999
```
