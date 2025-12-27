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

public class listgame {

	public static void main(String[] args) {
		try (Scanner sc = new Scanner(in)) {
			int X = sc.nextInt();
			int k = 0;
			while ((X & 1) == 0) {
				X >>= 1;
				k++;
			}
			while (X % 3 == 0) {
				X /= 3;
				k++;
			}
			while (X % 5 == 0) {
				X /= 5;
				k++;
			}
			for (int i = 7; i <= X;) {
				while (X % i == 0) {
					X /= i;
					k++;
				}
				i += 4;
				while (X % i == 0) {
					X /= i;
					k++;
				}
				i += 2;
				while (X % i == 0) {
					X /= i;
					k++;
				}
				i += 4;
				while (X % i == 0) {
					X /= i;
					k++;
				}
				i += 2;
				while (X % i == 0) {
					X /= i;
					k++;
				}
				i += 4;
				while (X % i == 0) {
					X /= i;
					k++;
				}
				i += 6;
				while (X % i == 0) {
					X /= i;
					k++;
				}
				i += 2;
				while (X % i == 0) {
					X /= i;
					k++;
				}
				i += 6;
			}
			out.print(k);
		}
	}

}
