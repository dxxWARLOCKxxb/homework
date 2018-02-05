import numpy as np

file = open("/tmp/matrix_input.txt")
s = list(map(int,file.readline().split()))
A = np.array(list(map(int,file.readline().split()))).reshape(s[0], s[1])
s = list(map(int,file.readline().split()))
B = np.array(list(map(int,file.readline().split()))).reshape(s[0], s[1])
file.close()

file = open("/tmp/matrix_output.txt")
s = list(map(int,file.readline().split()))
C = np.array(list(map(int,file.readline().split()))).reshape(s[0], s[1])
file.close()
C_python = np.dot(A,B)

print((C == C_python).all())