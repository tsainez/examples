//
// GreedySearch
//
// This class implements the greedy search algorithm.
//  It does not use the searchDisplay display utility.
//  Upon submission, it matches the test logs provided.
//
// Anthony Sainez -- 16 October 2020
//

import java.util.*;

/**
 * Implements the Greedy Best-First Search algorithm.
 *
 * This class performs a greedy search on a given roadmap graph,
 * attempting to find a path from an initial location to a destination.
 * It uses a heuristic function to guide the search.
 */
public class GreedySearch {
    /** The depth limit for the search (though greedy search doesn't strictly use depth limit like IDDFS). */
    public int limit;
    /** The number of nodes expanded during the search. */
    public int expansionCount;
    /** The name of the starting location. */
    public String initialLoc;
    /** The name of the destination location. */
    public String destinationLoc;
    /** The graph representing the map. */
    public RoadMap graph;

    /**
     * Constructor for GreedySearch.
     *
     * @param graph The map graph to search.
     * @param initialLoc The starting location name.
     * @param destinationLoc The destination location name.
     * @param limit A limit on the search depth (used in non-state-checking mode).
     * @param display A display utility (unused in this implementation but kept for compatibility).
     */
    public GreedySearch(RoadMap graph, String initialLoc, String destinationLoc, int limit, SearchDisplay display) {
        this.initialLoc = initialLoc;
        this.graph = graph;
        this.destinationLoc = destinationLoc;
        this.limit = limit;
    }

    /**
     * Performs the Greedy Best-First Search.
     *
     * @param stateChecking If true, enables visited state checking to prevent cycles and redundant work.
     * @return The goal Node if found, otherwise null.
     */
    public Node search(boolean stateChecking) {
        GoodHeuristic val = new GoodHeuristic(graph, graph.findLocation(destinationLoc));
        SortedFrontier priorityQueue = new SortedFrontier(SortBy.h);
        Node iNode = new Node(graph.findLocation(initialLoc));
        HashSet<String> visitedNodes = new HashSet<String>();
        priorityQueue.addSorted(iNode);
        expansionCount = 0;

        if (stateChecking) {
            while(true) {
                if (priorityQueue.isEmpty())
                    return null;

                iNode = priorityQueue.removeTop();

                // We are already here!
                if (iNode.isDestination(destinationLoc))
                    return iNode;

                if(!visitedNodes.contains(iNode.loc.name)) {
                    visitedNodes.add(iNode.loc.name);
                    iNode.heuristicValue = val.heuristicValue(iNode);
                    iNode.expand(val); expansionCount++;
                }

                for (Node i: iNode.children) {
                    if (!visitedNodes.contains(i.loc.name) && !priorityQueue.contains(i.loc.name)) {
                        priorityQueue.addSorted(i);
                    } else if (priorityQueue.contains(i) && i.partialPathCost >= iNode.partialPathCost) {
                        priorityQueue.remove(iNode);
                        priorityQueue.addSorted(i);
                    }
                } // end for (Node i: initialNode.children)

                if (priorityQueue.isEmpty())
                    return null;
            }
        } else { // stateChecking != true
            while (!priorityQueue.isEmpty() && iNode.depth < limit) {
                iNode = priorityQueue.removeTop();

                if (iNode.isDestination(destinationLoc))
                    return iNode;

                iNode.heuristicValue = val.heuristicValue(iNode);
                iNode.expand(val); expansionCount++;

                priorityQueue.addSorted(iNode.children);
            }
            return null;
        } // end else
    }
}
