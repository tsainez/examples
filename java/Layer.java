//
// Layer
//
// This class implements a layer of processing units.
//
// David Noelle -- Tue Apr 24 15:51:19 PDT 2007
//

import java.util.*;

/**
 * Represents a layer of neurons in a neural network.
 *
 * This class handles the activation of units, calculation of deltas (errors),
 * and updating of bias weights. It supports input, hidden, and output layers.
 */
public class Layer {

	/** The number of units (neurons) in the layer. */
	public int n;
	/** The minimum activation level. */
	public double min;
	/** The maximum activation level. */
	public double max;
	/** The net input levels of the units. */
	public Vector net;
	/** The activation levels of the units. */
	public Vector act;
	/** The current target values for output layers. */
	public Vector targ;
	/** The delta values (error terms) for the units. */
	public Vector delta;
	/** The bias weights for the units. */
	public Vector bias;
	/** The accumulated delta values for the bias weights. */
	public Vector biasDelta;
	/** The list of projections feeding into this layer. */
	public List<Projection> inputs;
	/** The list of projections emanating from this layer. */
	public List<Projection> outputs;

	/**
	 * Default constructor. Initializes an invalid layer.
	 */
	public Layer() {
		this.n = -1;
		this.min = 0.0;
		this.max = 1.0;
		this.net = null;
		this.act = null;
		this.targ = null;
		this.delta = null;
		this.bias = null;
		this.biasDelta = null;
		this.inputs = new LinkedList<Projection>();
		this.outputs = new LinkedList<Projection>();
	}

	/**
	 * Constructor with specified size and activation range.
	 *
	 * @param size The number of units in the layer.
	 * @param min The minimum activation value.
	 * @param max The maximum activation value.
	 */
	public Layer(int size, double min, double max) {
		if ((size > 0) && (min < max)) {
			this.n = size;
			this.min = min;
			this.max = max;
			this.net = new Vector(size);
			this.act = new Vector(size);
			this.targ = null;
			this.delta = new Vector(size);
			this.bias = new Vector(size);
			this.biasDelta = new Vector(size);
			this.inputs = new LinkedList<Projection>();
			this.outputs = new LinkedList<Projection>();
		} else {
			this.n = -1;
			this.min = 0.0;
			this.max = 1.0;
			this.net = null;
			this.act = null;
			this.targ = null;
			this.delta = null;
			this.bias = null;
			this.biasDelta = null;
			this.inputs = new LinkedList<Projection>();
			this.outputs = new LinkedList<Projection>();
		}
	}

	/**
	 * Constructor with specified size and default activation range (0.0 to 1.0).
	 *
	 * @param size The number of units in the layer.
	 */
	public Layer(int size) {
		this(size, 0.0, 1.0);
	}

	/**
	 * Change the size of this layer.
	 *
	 * Activation and delta values may be lost. All input and output projections are discarded.
	 *
	 * @param size The new number of units.
	 */
	public void resize(int size) {
		if (size > 0) {
			n = size;
			net = new Vector(size);
			act = new Vector(size);
			targ = null;
			delta = new Vector(size);
			bias = new Vector(size);
			biasDelta = new Vector(size);
			inputs = new LinkedList<Projection>();
			outputs = new LinkedList<Projection>();
		} else {
			n = -1;
			net = null;
			act = null;
			targ = null;
			delta = null;
			bias = null;
			biasDelta = null;
			inputs = new LinkedList<Projection>();
			outputs = new LinkedList<Projection>();
		}
	}

	/**
	 * Change the minimum and maximum activation values for the units in this layer.
	 *
	 * @param min The new minimum activation value.
	 * @param max The new maximum activation value.
	 */
	public void setActivationRange(double min, double max) {
		if (min < max) {
			this.min = min;
			this.max = max;
		}
	}

	/**
	 * Add a projection to the list of inputs coming into this layer.
	 *
	 * @param p The projection to add.
	 */
	public void addInputProjection(Projection p) {
		if (p.outputN == n) {
			inputs.add(p);
			p.output = this;
		}
	}

	/**
	 * Add a projection to the list of outputs coming out of this layer.
	 *
	 * @param p The projection to add.
	 */
	public void addOutputProjection(Projection p) {
		if (p.inputN == n) {
			outputs.add(p);
			p.input = this;
		}
	}

	/**
	 * Set all net input values in the layer to zero.
	 */
	public void clearNetInputs() {
		for (int i = 0; i < net.dim(); i++)
			net.set(i, 0.0);
	}

	/**
	 * Set all activation values in the layer to zero.
	 */
	public void clearActivation() {
		for (int i = 0; i < act.dim(); i++)
			act.set(i, 0.0);
	}

	/**
	 * Set all unit delta values in the layer to zero.
	 */
	public void clearUnitDeltas() {
		for (int i = 0; i < delta.dim(); i++)
			delta.set(i, 0.0);
	}

	/**
	 * Set all bias weight deltas in the layer to zero.
	 */
	public void clearBiasDeltas() {
		for (int i = 0; i < biasDelta.dim(); i++)
			biasDelta.set(i, 0.0);
	}

	/**
	 * Set the bias weights to random values sampled uniformly from the given range.
	 *
	 * @param min The minimum random value.
	 * @param max The maximum random value.
	 */
	public void randomizeBiases(double min, double max) {
		bias.randomize(min, max);
	}

	/**
	 * Load the given vector of values into the activation vector for this layer.
	 *
	 * @param v The vector of input values.
	 * @return true if successful, false otherwise.
	 */
	public boolean loadInput(Vector v) {
		if (act.valid() && v.valid() && (act.dim() == v.dim())) {
			for (int i = 0; i < act.dim(); i++)
				act.set(i, v.get(i));
			return (true);
		} else {
			// The vectors don't match ...
			return (false);
		}
	}

	/**
	 * Load the given vector of values into the target vector for this layer.
	 *
	 * @param v The vector of target values.
	 * @return true if successful, false otherwise.
	 */
	public boolean loadTarget(Vector v) {
		if (act.valid() && v.valid() && (act.dim() == v.dim())) {
			targ = v;
			return (true);
		} else {
			// The vector doesn't match the layer ...
			return (false);
		}
	}

	/**
	 * Calculate the activation values of the units in this layer based on their inputs and bias weights.
	 */
	public void computeActivation() {
		if (!(inputs.isEmpty())) {
			// This is not an input layer, so we can update it ...
			// Add in the bias values to the net inputs ...
			net = net.copy(bias);
			// Sum up the contributions of each projection ...
			for (Projection p : inputs)
				net = net.sum(p.W.product(p.input.act));
			act = net.squash(min, max);
		}
	}

	/**
	 * Calculate the unit delta values for this output layer.
	 */
	public void computeOutputDelta() {

		// PLACE YOUR CODE HERE ...
		// I felt this video was useful for refreshing my memory on backpropagation.
		// This vector will calculate the difference between the target and the activation levels of the unit.
		Vector diff = new Vector(targ.difference(act));

		// This vector will calculate the derivative of the net, which is the activation function.
		Vector deriv = new Vector(net.derivative(min, max));

		// Initialize a new delta with an initialValue of 0.0 and dimension n.
		delta = new Vector(n, 0.0);

		// The gradient values that make up delta are given by multiplying the
		// diff and deriv vectors on each level.
		for(int i = 0; i < n; i++) {
			delta.set(i, diff.get(i) * deriv.get(i));
		}

		delta.sumOfElements();

		return; // Standard procedure for void functions.
	}

	/**
	 * Calculate the unit delta values for this hidden layer.
	 */
	public void computeHiddenDelta() {

		// PLACE YOUR CODE HERE ...
		// The diff vector stores the error with dimension n, since there are already input values.
		Vector diff = new Vector(n, 0.0);

		// The deriv vector calculates the derivative of the net which is the activation function.
		Vector deriv = new Vector(net.derivative(min, max));

		// We must, again, reinitialize delta with dimension n.
		delta = new Vector(n, 0.0);

		// For all of the downstream units in the network: all the units  whose inputs include the output of a given unit.
		for(Projection i : outputs) {
			// The transpose of a matrix switches the row and column indices. This is learned in linear algebra.
			Matrix temp = (i.W.transpose());
			diff = diff.sum(temp.product(i.output.delta));
		}

		// The gradient values are given by multiplying diff and deriv at every level.
		for(int i = 0; i < n; i++) {
			delta.set(i, diff.get(i) * deriv.get(i));
		}

		delta.sumOfElements();

		return; // Standard procedure for void functions.
	}

	/**
	 * Calculate the unit delta values for this layer.
	 *
	 * Dispatches to computeOutputDelta or computeHiddenDelta based on layer type.
	 */
	public void computeDelta() {
		if (outputs.isEmpty()) {
			// This is an output layer ...
			computeOutputDelta();
		} else {
			// No point in computing unit delta values for input layers,
			// as those values are not used ...
			if (!(inputs.isEmpty())) {
				// This is a hidden layer ...
				computeHiddenDelta();
			}
		}
	}

	/**
	 * Update the accumulated bias deltas based on current unit deltas.
	 */
	public void incrementBiasDeltas() {
		biasDelta = biasDelta.sum(delta);
	}

	/**
	 * Update the bias weights using the accumulated deltas and a learning rate.
	 *
	 * @param learningRate The learning rate factor.
	 */
	public void updateBiases(double learningRate) {
		bias = bias.sum(biasDelta.multiplyByScalar(learningRate));
	}

}
