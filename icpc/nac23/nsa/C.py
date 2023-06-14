p = int(input())
g = int(input())
y = int(input())
C = int(input())
q = int(input())

H = pow(g, C, p)
X = C * pow(g, -q, p) % p
print("VALID" if X == pow(y, H, p) else "INVALID")