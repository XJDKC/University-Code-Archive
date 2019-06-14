import pty
import os
import select
import random
from time import sleep
# /dev/pts/20
if __name__ == "__main__":

    master, slave = pty.openpty()
    s_name = os.ttyname(slave)

    print(s_name)

    res = b""
    opt = ['T','S']
    while 1:
        if random.randint(0, 1) == 1:
            command = "T%d.%d\n"%(random.randint(26,26),random.randint(0,99))
        else:
            command = 'S%d\n'%(random.randint(0,63))
        print(command)
        os.write(master, command.encode())
        sleep(0.5)