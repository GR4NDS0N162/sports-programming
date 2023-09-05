import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int n = scanner.nextInt();

        scanner.close();

        System.out.println(n == 1 ? n : (n - 1) * 4);
    }
}
