import string
import random
import subprocess

for i in range(1000):
    a = int("".join(random.choice(string.digits) for x in range(random.randint(80, 160)))) * random.choice([-1, 1])
    b = int("".join(random.choice(string.digits) for y in range(random.randint(80, 160)))) * random.choice([-1, 1])
    print('test #', i)
    print("a is ", a, "\nb is ", b, '\n')
    result = subprocess.check_output(["/home/esdeath/homework/long_arithmetic/a.out", '+', str(a), str(b), ]).decode("utf-8")
    if str(a + b) == result:
        print('a + b = ', a + b, '\n')
    else:
        print("Wrong answer! Operator +\n")
    print("answer: ", str(a + b), '\n')
    result = subprocess.check_output(["/home/esdeath/homework/long_arithmetic/a.out", '-', str(a), str(b), ]).decode("utf-8")
    if str(a - b) == result:
        print('a - b = ', a - b, '\n')
    else:
        print("Wrong answer! Operator -\n")
    print("answer: ", str(a - b), '\n')
    result = subprocess.check_output(["/home/esdeath/homework/long_arithmetic/a.out", '*', str(a), str(b), ]).decode("utf-8")
    if str(a * b) == result:
        print('a * b = ', a * b, '\n')
    else:
        print("Wrong answer! Operator *\n")
    print("answer: ", str(a * b), '\n')
