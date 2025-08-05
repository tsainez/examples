//
// 	GoodHeuristic
//
// 	This class extends the Heuristic class, providing a reasonable
// 	implementation of the heuristic function method. The provided "good"
// 	heuristic function is admissible.
//
// 	Anthony Sainez -- 16 October 2020
//

public class GoodHeuristic extends Heuristic {
	public RoadMap map;
	public double velocity;

	// Constructor
	public GoodHeuristic(RoadMap map, Location destination) {
		this.map = map;
		this.velocity = velocity();
		super.setDestination(destination);
	}

	// heuristicValue -- Return the appropriate heuristic values for the
	// given search tree node. Note that the given Node should not be
	// modified within the body of this function.
	public double heuristicValue(Node thisNode) {
		/*
		// If you want to remove the timeCost function, you can do it this way, too.
		double x, y;

		x = thisNode.loc.latitude - destination.latitude;
		y = thisNode.loc.longitude - destination.longitude;

		Math.hypot(x, y);

		return Math.hypot(x, y) / velocity;
		 */
		return (timeCost(thisNode.loc, destination) / velocity); // I'm a bigger fan of one-liners, though.
	}

	// Helps find the minimum cost route.
	// "Want to preserve velocity."
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
