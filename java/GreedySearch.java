import java.io.*;
import java.util.*;

public class GreedySearch {
    public int limit, expansionCount;
    public String initialLoc, destinationLoc;
    public RoadMap graph;
    public SearchDisplay display;

    public GreedySearch(RoadMap graph, String initialLoc, String destinationLoc, int limit, SearchDisplay display) {
        this.initialLoc = initialLoc;
        this.graph = graph;
        this.destinationLoc= destinationLoc;
        this.limit = limit;
    }

    public int getExpansionCount() {
        return expansionCount;
    }

    public Node search(boolean repeatedState) {
        Node initialNode = new Node(graph.findLocation(initialLoc));
        SortedFrontier priorityQueue = new SortedFrontier(SortBy.h);
        priorityQueue.addSorted(initialNode);

        HashSet<String> visitedNodes = new HashSet<String>();

        expansionCount = 0;

        GoodHeuristic val = new GoodHeuristic(graph, graph.findLocation(destinationLoc));

        if (repeatedState) {
            while(true) {
                if (priorityQueue.isEmpty())
                    return null;

                initialNode = priorityQueue.removeTop();

                if (initialNode.isDestination(destinationLoc))
                    return initialNode;

                if(!visitedNodes.contains(initialNode.loc.name)) {
                    visitedNodes.add(initialNode.loc.name);
                    initialNode.heuristicValue = val.heuristicValue(initialNode);
                    initialNode.expand(val); expansionCount++;
                }

                for(Node i: initialNode.children) {
                    if(!visitedNodes.contains(i.loc.name) && !priorityQueue.contains(i.loc.name)) {
                        priorityQueue.addSorted(i);
                    } else if (priorityQueue.contains(i) && i.partialPathCost >= initialNode.partialPathCost) {
                        priorityQueue.remove(initialNode);
                        priorityQueue.addSorted(i);
                    }
                } // end for

                if (priorityQueue.isEmpty())
                    return null;
            }
        } else { // repeatedState != true
            while(!priorityQueue.isEmpty() && initialNode.depth < limit) {
                initialNode = priorityQueue.removeTop();

                if (initialNode.isDestination(destinationLoc))
                    return initialNode;

                initialNode.heuristicValue = val.heuristicValue(initialNode);
                initialNode.expand(val); expansionCount++;

                priorityQueue.addSorted(initialNode.children);
            }
            return null;
        }
    }
}
