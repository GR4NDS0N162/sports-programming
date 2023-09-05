import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int m = scanner.nextInt();

        HashMap<Integer, Integer> detailShelf = new HashMap<>();

        PriorityQueue<Integer> freeShelves = new PriorityQueue<>();
        for (int i = 1; i <= m; i++) freeShelves.add(i);

        ArrayList<Integer> ans = new ArrayList<>();

        for (int i = 0; i < m; i++) {
            String action = scanner.next();
            int detail = scanner.nextInt();

            if (Objects.equals(action, "+")) {
                int shelf = freeShelves.isEmpty() ? 0 : freeShelves.poll(); // Занять полку
                detailShelf.put(detail, shelf); // Положить на полку

                ans.add(shelf);
            } else {
                int shelf = detailShelf.get(detail); // Узнать полку
                freeShelves.add(shelf); // Освободить полку
            }
        }
        scanner.close();

        for (int shelf : ans) {
            System.out.println(shelf);
        }
    }
}
