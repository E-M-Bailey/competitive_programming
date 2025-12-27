import java.lang.reflect.*;
import java.math.*;
import java.text.*;
import java.time.*;
import java.time.chrono.*;
import java.time.format.*;
import java.time.temporal.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.concurrent.atomic.*;
import java.util.function.*;
import java.util.regex.*;
import java.util.stream.*;
import static java.lang.System.in;
import static java.lang.System.out;

public class fourthought {

	public static void main(String[] args) {
		try (Scanner sc = new Scanner(in)) {
			int m = sc.nextInt();
			for (int i = 0; i < m; i++) {
				int n = sc.nextInt();
				out.println(process(n));
			}
		}
	}

	static String process(int n) {
		for (int opCode = 0; opCode < 64; opCode++) {
			int o1 = opCode / 16 % 4;
			int o2 = opCode / 4 % 4;
			int o3 = opCode % 4;
			List<Integer> vals = new ArrayList<>(4);
			for (int i = 0; i < 4; i++)
				vals.add(4);
			List<Integer> ops = new ArrayList<>(3);
			ops.add(o1);
			ops.add(o2);
			ops.add(o3);
			outer: for (int iter = 0; iter < 3; iter++) {
				for (int i = 0; i < 3 - iter; i++) {
					int op = ops.get(i);
					if (op > 1) {
						ops.remove(i);
						vals.set(i, eval(vals.get(i), vals.remove(i + 1), op));
						continue outer;
					}
				}
				int op = ops.remove(0);
				vals.set(0, eval(vals.get(0), vals.remove(1), op));
			}
			int val = vals.get(0);
			char[] ch = {'+', '-', '*', '/'};
			if (val == n) {
				return "4 " + ch[o1] + " 4 " + ch[o2] + " 4 " + ch[o3] + " 4 = " + n;
			}
		}
		return "no solution";
	}

	static int eval(int i, int j, int op) {
		switch (op) {
		case 0:
			return i + j;
		case 1:
			return i - j;
		case 2:
			return i * j;
		default:
			return i / j;
		}
	}

}
