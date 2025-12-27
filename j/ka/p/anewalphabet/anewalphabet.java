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

public class anewalphabet {

	public static void main(String[] args) {
		try (Scanner sc = new Scanner(in)) {
			String line = sc.nextLine();
			line = tr(line, "a", "@");
			line = tr(line, "b", "8");
			line = tr(line, "c", "(");
			line = tr(line, "d", "|)");
			line = tr(line, "e", "3");
			line = tr(line, "f", "#");
			line = tr(line, "g", "6");
			line = tr(line, "h", "[-]");
			line = tr(line, "i", "|");
			line = tr(line, "j", "_|");
			line = tr(line, "k", "|<");
			line = tr(line, "l", "1");
			line = tr(line, "m", "[]\\/[]");
			line = tr(line, "n", "[]\\[]");
			line = tr(line, "o", "0");
			line = tr(line, "p", "|D");
			line = tr(line, "q", "(,)");
			line = tr(line, "s", "$");
			line = tr(line, "t", "']['");
			line = tr(line, "u", "|_|");
			line = tr(line, "v", "\\/");
			line = tr(line, "w", "\\/\\/");
			line = tr(line, "x", "}{");
			line = tr(line, "y", "`/");
			line = tr(line, "z", "2");
			line = tr(line, "r", "|Z");
			out.print(line);
		}
	}
	
	static String tr(String str, String old, String nw) {
		str = str.replace(old, nw);
		str = str.replace(old.toUpperCase(), nw);
		return str;
	}

}
