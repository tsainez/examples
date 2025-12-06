//
//  AStarSearch
//
//  This class implements the A* search algorithm. Uses f = g + h.
//  It does not use the searchDisplay display utility.
//  Upon submission, it matches the test logs provided.
//
//  Anthony Sainez -- 16 October 2020
//

import java.util.*;

/**
 * Implements the A* Search algorithm.
 *
 * This class performs an A* search on a given roadmap graph,
 * finding the optimal path from an initial location to a destination
 * by minimizing the total estimated cost f(n) = g(n) + h(n).
 */
public class AStarSearch {
    // Data Declaration Section
    /** The graph representing the map. */
    public RoadMap graph;
    /** The name of the starting location. */
    public String initialLoc;
    /** The name of the destination location. */
    public String destinationLoc;
    /** The depth limit for the search. */
    public int limit;
    /** The number of nodes expanded during the search. */
    public int expansionCount;
    /** The heuristic function used for cost estimation. */
    public Heuristic heuristic;

    /**
     * Constructor for AStarSearch.
     *
     * @param graph The map graph to search.
     * @param initialLoc The starting location name.
     * @param destinationLoc The destination location name.
     * @param limit A limit on the search depth.
     * @param display A display utility (unused in this implementation but kept for compatibility).
     */
    public AStarSearch(RoadMap graph, String initialLoc, String destinationLoc, int limit, SearchDisplay display) {
        this.heuristic = new GoodHeuristic(graph,graph.findLocation(destinationLoc));
        this.graph= graph;
        this.initialLoc= initialLoc;
        this.destinationLoc = destinationLoc;
        this.limit = limit;

    }

    /**
     * Performs the A* Search.
     *
     * @param stateChecking If true, enables visited state checking to prevent cycles and redundant work.
     * @return The goal Node if found, otherwise null.
     */
    public Node search(boolean stateChecking) {
        SortedFrontier frontier = new SortedFrontier(SortBy.f);
        Node iNode = new Node(graph.findLocation(initialLoc));
        HashSet<String> explore = new HashSet<String>();
        expansionCount = 0;

        while(!frontier.isEmpty())
            frontier.removeTop();

        // We are already here!
        if(initialLoc == destinationLoc)
            return iNode;

        frontier.addSorted(iNode);
        explore.add(iNode.loc.name);

        while(!frontier.isEmpty() && iNode.depth < limit) {
            iNode = frontier.removeTop();

            if(iNode.isDestination(destinationLoc))
                return iNode;

            iNode.expand(heuristic); expansionCount++;

            if(stateChecking) {
                for (Node i: iNode.children) {
                    if (!explore.contains(i.loc.name)) {
                        frontier.addSorted(i);
                        explore.add(i.loc.name);
                    } else {
                        if (frontier.contains(i.loc.name)) {
                            Node higher = frontier.find(i);
                            if (i.partialPathCost <higher.partialPathCost) {
                                frontier.remove(higher);
                                frontier.addSorted(i);
                            }
                        }
                    }
                } // end for (Node i: parent.children)
            } else { // stateChecking != true
                frontier.addSorted(iNode.children);
            }
        } // end while(!frontier.isEmpty() && parent.depth < limit)
        return null;
    }

}
