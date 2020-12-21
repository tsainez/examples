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

public class GreedySearch {
    public int limit, expansionCount;
    public String initialLoc, destinationLoc;
    public RoadMap graph;

    // Constructor
    public GreedySearch(RoadMap graph, String initialLoc, String destinationLoc, int limit, SearchDisplay display) {
        this.initialLoc = initialLoc;
        this.graph = graph;
        this.destinationLoc = destinationLoc;
        this.limit = limit;
    }

    // Required Search Function
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
