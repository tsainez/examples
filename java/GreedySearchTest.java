import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Comparator;

public class GreedySearchTest {

    public static void main(String[] args) {
        System.out.println("Running GreedySearch tests...");
        int passed = 0;
        int failed = 0;

        Runnable[] tests = {
            GreedySearchTest::testAlreadyAtDestination,
            GreedySearchTest::testUnreachableGoal,
            GreedySearchTest::testStateCheckingHappyPath,
            GreedySearchTest::testNoStateCheckingHappyPath,
            GreedySearchTest::testDepthLimitReached
        };

        for (Runnable test : tests) {
            try {
                test.run();
                passed++;
            } catch (AssertionError | Exception e) {
                System.err.println("Test failed!");
                e.printStackTrace();
                failed++;
            }
        }

        System.out.println("Tests passed: " + passed + ", Failed: " + failed);
        if (failed > 0) {
            System.exit(1);
        }
    }

    private static RoadMap buildMockGraph() {
        RoadMap map = new RoadMap();

        Location a = new Location("A", 0, 0);
        Location b = new Location("B", 0, 10);
        Location c = new Location("C", 10, 10);
        Location d = new Location("D", 10, 0);
        Location goal = new Location("Goal", 20, 20);
        Location unreachable = new Location("Unreachable", -10, -10);

        a.roads = Arrays.asList(new Road(a, b, 1), new Road(a, c, 5));
        b.roads = Arrays.asList(new Road(b, c, 1), new Road(b, a, 1));
        c.roads = Arrays.asList(new Road(c, d, 2), new Road(c, goal, 2));
        d.roads = Arrays.asList(new Road(d, goal, 1)); // D -> Goal is closer
        goal.roads = Arrays.asList(); // no outgoing
        unreachable.roads = Arrays.asList(); // isolated

        map.addLocation(a);
        map.addLocation(b);
        map.addLocation(c);
        map.addLocation(d);
        map.addLocation(goal);
        map.addLocation(unreachable);

        return map;
    }

    private static void assertNotNull(Object obj) {
        if (obj == null) throw new AssertionError("Expected not null");
    }

    private static void assertNull(Object obj) {
        if (obj != null) throw new AssertionError("Expected null, but got " + obj);
    }

    private static void assertEquals(Object expected, Object actual) {
        if (expected == null && actual == null) return;
        if (expected == null || !expected.equals(actual)) {
            throw new AssertionError("Expected " + expected + ", but got " + actual);
        }
    }

    private static void testAlreadyAtDestination() {
        RoadMap map = buildMockGraph();
        GreedySearch search = new GreedySearch(map, "A", "A", 10, new SearchDisplay());
        Node result = search.search(true);
        assertNotNull(result);
        assertEquals("A", result.loc.name);
        System.out.println("testAlreadyAtDestination passed.");
    }

    private static void testUnreachableGoal() {
        RoadMap map = buildMockGraph();
        GreedySearch search = new GreedySearch(map, "A", "Unreachable", 10, new SearchDisplay());
        Node result = search.search(true);
        assertNull(result);
        System.out.println("testUnreachableGoal passed.");
    }

    private static void testStateCheckingHappyPath() {
        RoadMap map = buildMockGraph();
        GreedySearch search = new GreedySearch(map, "A", "Goal", 10, new SearchDisplay());
        Node result = search.search(true);
        assertNotNull(result);
        assertEquals("Goal", result.loc.name);
        System.out.println("testStateCheckingHappyPath passed.");
    }

    private static void testNoStateCheckingHappyPath() {
        RoadMap map = buildMockGraph();
        GreedySearch search = new GreedySearch(map, "A", "Goal", 10, new SearchDisplay());
        Node result = search.search(false);
        assertNotNull(result);
        assertEquals("Goal", result.loc.name);
        System.out.println("testNoStateCheckingHappyPath passed.");
    }

    private static void testDepthLimitReached() {
        RoadMap map = buildMockGraph();
        GreedySearch search = new GreedySearch(map, "A", "Goal", 0, new SearchDisplay());
        Node result = search.search(false);
        assertNull(result);
        System.out.println("testDepthLimitReached passed.");
    }
}

// ---------------------------------------------------------
// Minimal Stubs needed to test GreedySearch
// ---------------------------------------------------------

class Location {
    public String name;
    public double latitude;
    public double longitude;
    public List<Road> roads = new ArrayList<>();

    public Location(String name, double latitude, double longitude) {
        this.name = name;
        this.latitude = latitude;
        this.longitude = longitude;
    }
}

class Road {
    public Location fromLocation;
    public Location toLocation;
    public double cost;

    public Road(Location fromLocation, Location toLocation, double cost) {
        this.fromLocation = fromLocation;
        this.toLocation = toLocation;
        this.cost = cost;
    }
}

class RoadMap {
    public List<Location> locations = new ArrayList<>();

    public Location findLocation(String name) {
        for (Location loc : locations) {
            if (loc.name.equals(name)) {
                return loc;
            }
        }
        return null;
    }

    public void addLocation(Location loc) {
        locations.add(loc);
    }
}

abstract class Heuristic {
    public Location destination;

    public void setDestination(Location destination) {
        this.destination = destination;
    }

    public abstract double heuristicValue(Node thisNode);
}

class SearchDisplay {
}

enum SortBy {
    h, f
}

class SortedFrontier {
    private PriorityQueue<Node> queue;

    public SortedFrontier(SortBy sortBy) {
        if (sortBy == SortBy.h) {
            queue = new PriorityQueue<>(Comparator.comparingDouble(n -> n.heuristicValue));
        } else {
            queue = new PriorityQueue<>(Comparator.comparingDouble(n -> n.partialPathCost + n.heuristicValue));
        }
    }

    public boolean isEmpty() {
        return queue.isEmpty();
    }

    public Node removeTop() {
        return queue.poll();
    }

    public void addSorted(Node n) {
        queue.add(n);
    }

    public void addSorted(List<Node> nodes) {
        queue.addAll(nodes);
    }

    public boolean contains(String name) {
        for (Node n : queue) {
            if (n.loc.name.equals(name)) return true;
        }
        return false;
    }

    public boolean contains(Node n) {
        return queue.contains(n);
    }

    public void remove(Node n) {
        queue.remove(n);
    }

    public Node find(Node node) {
        for (Node n : queue) {
            if (n.loc.name.equals(node.loc.name)) return n;
        }
        return null;
    }
}

class Node {
    public Location loc;
    public double heuristicValue;
    public double partialPathCost;
    public int depth;
    public List<Node> children = new ArrayList<>();

    public Node(Location loc) {
        this.loc = loc;
        this.depth = 0;
        this.partialPathCost = 0;
    }

    public Node(Location loc, double partialPathCost, int depth) {
        this.loc = loc;
        this.partialPathCost = partialPathCost;
        this.depth = depth;
    }

    public boolean isDestination(String destinationLoc) {
        return loc.name.equals(destinationLoc);
    }

    public void expand(Heuristic val) {
        if (children.isEmpty() && loc.roads != null) {
            for (Road r : loc.roads) {
                Node child = new Node(r.toLocation, this.partialPathCost + r.cost, this.depth + 1);
                child.heuristicValue = val.heuristicValue(child);
                children.add(child);
            }
        }
    }
}
