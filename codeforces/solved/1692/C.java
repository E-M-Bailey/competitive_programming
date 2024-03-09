import java.util.*;

public class C {
	public static void main(String[] args) {
		try (Scanner sc = new Scanner(System.in)) {
			int t = sc.nextInt();
			char grid[][] = new char[8][];
			for (int tc = 0; tc < t; tc++) {
				// read input
				for (int i = 0; i < 8; i++) {
					grid[i] = sc.next().toCharArray();
				}

				// Scan for solution top-to-bottom, left-to-rignt
				outer: for (int i = 1; i < 7; i++) {
					for (int j = 1; j < 7; j++) {
						// The first time we see #.#, the bishop is below the . in the middle.
						if (grid[i - 1][j - 1] == '#' && grid[i - 1][j + 1] == '#') {
							System.out.printf("%d %d\n", i + 1, j + 1);
							break outer;
						}
					}
				}
			}
		}
	}
}