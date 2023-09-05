import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int m = scanner.nextInt();
        scanner.close();

        int[][] grid = new int[m][n];
        int num = 1;

        for (int diagSum = 2; diagSum <= n + m; diagSum++) {
            for (int i = 1; i <= m; i++) {
                int j = diagSum - i;
                if (j >= 1 && j <= n)
                    grid[i - 1][j - 1] = num++;
            }
        }

        for (int i = 0; i < m; i++) {
            System.out.print(grid[i][0]);
            for (int j = 1; j < n; j++)
                System.out.print(" " + grid[i][j]);
            System.out.println();
        }
    }
}
