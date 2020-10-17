//
// AStarSearch
//
// This class implements the A* search algorithm. Uses f = g + h.
//
// Anthony Sainez -- 16 October 2020
//

import java.util.*;

public class AStarSearch {
    // Data Declaration Section
    public RoadMap graph;
    public String initialLoc, destinationLoc;
    public int limit, expansionCount;
    public Heuristic heuristic;

    // Constructor Function
    public AStarSearch(RoadMap graph, String initialLoc, String destinationLoc, int limit, SearchDisplay display) {
        this.heuristic = new GoodHeuristic(graph,graph.findLocation(destinationLoc));
        this.graph= graph;
        this.initialLoc= initialLoc;
        this.destinationLoc = destinationLoc;
        this.limit = limit;

    }

    // Required Search Function
    public Node search(boolean checkvertex) {
        SortedFrontier frontier = new SortedFrontier(SortBy.f);
        HashSet<String> explore = new HashSet<String>();


        while(!frontier.isEmpty())
            frontier.removeTop();

        explore.clear();
        expansionCount = 0;
        Node iNode = new Node(graph.findLocation(initialLoc));

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

            if(!checkvertex)
                frontier.addSorted(iNode.children);

            else {
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
            }
        } // end while(!frontier.isEmpty() && parent.depth < limit)
        return null;
    }

}