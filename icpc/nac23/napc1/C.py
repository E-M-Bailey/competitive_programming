import math


def parse_two_line(exp, r, c):
	buf = ""
	st = []
	i = 0
	while i < c:
		if exp[1][i] == '\\':
			pos = i+2
			i += 2
			while i < c and exp[0][i] == '_': i += 1
			buf += str(int(math.sqrt(eval(exp[1][pos:i]))))
		else:
			buf += exp[1][i]
			i += 1
	return eval(buf)

def parse_three_line(exp, r, c):
	i = 0
	buf = ""
	while i < c:
		if exp[1][i] == '\\':
			pos = i+2
			i += 2
			while i < c and exp[0][i] == '_': i += 1
			buf += str(int(math.sqrt(eval(exp[1][pos:i]))))
		elif exp[1][i] == '=':
			pos = i
			while i < c and exp[1][i] == '=': i += 1
			buf += str(eval(exp[0][pos:i]) // eval(exp[2][pos:i]))
		else:
			buf += exp[1][i]
			i += 1
	return eval(buf)
	
def main():
	r, c = map(int, input().split())
	exp = [input() for _ in range(r)]
	if r == 1: print(eval(exp[0]))
	elif r == 2: print(parse_two_line(exp,r,c))
	else: print(parse_three_line(exp,r,c))
	
if __name__ == '__main__':
	main()