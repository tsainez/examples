//
// GoodHeuristic
//
// This class extends the Heuristic class, providing a reasonable
// implementation of the heuristic function method. The provided "good"
// heuristic function is admissible.
//
// Anthony Sainez -- 16 October 2020
//


// IMPORT ANY PACKAGES THAT YOU NEED.

public class GoodHeuristic extends Heuristic {
	public RoadMap map;
	public double velocity;

	public GoodHeuristic(RoadMap map, Location destination) {
		this.map = map;
		this.velocity = velocity();
		super.setDestination(destination);
	}

	// heuristicValue -- Return the appropriate heuristic values for the
	// given search tree node. Note that the given Node should not be
	// modified within the body of this function.
	public double heuristicValue(Node thisNode) {
		return (timeCost(thisNode.loc, destination) / velocity);
	}

	// Velocity helps find the minimum cost route which is admissible heuristic function.
	public double velocity() {
		double temp, velocity = 0.0;

		for(Location location : map.locations) {
			for(Road road : location.roads) {
				temp = timeCost(road.fromLocation, road.toLocation) / road.cost;

				if (velocity < temp)
					velocity = temp;
			}
		}
		return velocity;
	}

	// Time cost is also just the distance between two points on a graph.
	// Math.hypot comes in useful here, since it just calculates the distance
	// formula for us.
	public double timeCost(Location loc1, Location loc2) {
		double x, y;

		x = loc1.latitude - loc2.latitude;
		y = loc1.longitude - loc2.longitude;

		return Math.hypot(x, y);
	}

}
