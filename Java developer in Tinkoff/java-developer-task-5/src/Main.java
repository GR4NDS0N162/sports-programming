import java.util.*;

public class Main {
    static class Element implements Comparable<Element> {
        int to;
        int height;

        public Element(int to, int height) {
            this.to = to;
            this.height = height;
        }

        @Override
        public int compareTo(Element other) {
            return Integer.compare(other.height, this.height);
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int n = scanner.nextInt();
        int m = scanner.nextInt();

        PriorityQueue<Element>[] heights = new PriorityQueue[n];
        for (int i = 0; i < n; i++) {
            heights[i] = new PriorityQueue<>();
        }

        for (int s, f, h, i = 0; i < m; i++) {
            s = scanner.nextInt();
            f = scanner.nextInt();
            h = scanner.nextInt();
            heights[s - 1].add(new Element(f - 1, h));
            heights[f - 1].add(new Element(s - 1, h));
        }

        scanner.close();

        HashSet<Integer> visited = new HashSet<>(n);
        HashSet<Integer> unvisited = new HashSet<>(n);
        for (int i = 0; i < n; i++)
            unvisited.add(i);
        unvisited.remove(0);
        visited.add(0);

        int minMaxHeight = Integer.MAX_VALUE;

        while (!unvisited.isEmpty()) {
            Element maxHeightElement = new Element(0, 0);

            for (int from : visited) {
                while (!heights[from].isEmpty() && visited.contains(heights[from].peek().to))
                    heights[from].remove();

                if (!heights[from].isEmpty() && heights[from].peek().height > maxHeightElement.height)
                    maxHeightElement = heights[from].poll();
            }

            if (maxHeightElement.height < minMaxHeight)
                minMaxHeight = maxHeightElement.height;

            unvisited.remove(maxHeightElement.to);
            visited.add(maxHeightElement.to);
        }

        System.out.println(minMaxHeight);
    }
}
