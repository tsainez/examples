//
// 	GoodHeuristic
//
// 	This class extends the Heuristic class, providing a reasonable
// 	implementation of the heuristic function method. The provided "good"
// 	heuristic function is admissible.
//
// 	Anthony Sainez -- 16 October 2020
//

/**
 * Implements an admissible heuristic function for pathfinding.
 *
 * This heuristic estimates the cost to the destination by calculating the
 * straight-line distance divided by the maximum possible velocity in the map.
 * This ensures the heuristic never overestimates the true cost (admissible).
 */
public class GoodHeuristic extends Heuristic {
	/** The roadmap being searched. */
	public RoadMap map;
	/** The maximum velocity found on any road in the map. */
	public double velocity;

	/**
	 * Constructor for GoodHeuristic.
	 *
	 * @param map The roadmap containing locations and roads.
	 * @param destination The target destination for the search.
	 */
	public GoodHeuristic(RoadMap map, Location destination) {
		this.map = map;
		this.velocity = velocity();
		super.setDestination(destination);
	}

	/**
	 * Calculates the heuristic value for a given node.
	 *
	 * @param thisNode The node to evaluate.
	 * @return The estimated cost from the node to the destination.
	 */
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

	/**
	 * Calculates the maximum velocity across all roads in the map.
	 *
	 * Velocity is defined here as distance / cost.
	 *
	 * @return The maximum velocity.
	 */
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

	/**
	 * Calculates the straight-line distance (Euclidean distance) between two locations.
	 *
	 * @param loc1 The first location.
	 * @param loc2 The second location.
	 * @return The distance between the two locations.
	 */
	public double timeCost(Location loc1, Location loc2) {
		double x, y;

		x = loc1.latitude - loc2.latitude;
		y = loc1.longitude - loc2.longitude;

		return Math.hypot(x, y);
	}

}
