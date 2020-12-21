//
//  UniformCostSearch
//
//  This class implements the uniform cost search algorithm.
//  It does not use the searchDisplay display utility.
//  Upon submission, it matches the test logs provided.
//
//  Anthony Sainez -- 16 October 2020
//

import java.util.*;

public class UniformCostSearch {
    public RoadMap graph;
    public String initialLoc, destinationLoc;
    public int limit, expansionCount;

    // Constructor
    public UniformCostSearch(RoadMap graph, String initialLoc, String destinationLoc, int limit, SearchDisplay display) {
        this.graph= graph;
        this.initialLoc= initialLoc;
        this.destinationLoc = destinationLoc;
        this.limit = limit;
    }

    // Required Search Function
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

            iNode.expand(); expansionCount++;

            if (stateChecking) {
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
                } // end for (Node i: iNode.children)
            } else { // stateChecking != true
                frontier.addSorted(iNode.children);
            }
        } // end while(!frontier.isEmpty() && parent.depth < limit)
        return null;
    }

}