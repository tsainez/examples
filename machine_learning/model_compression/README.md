# Model Compression with Learning-Compression (LC)

This project demonstrates model compression techniques using the Learning-Compression (LC) algorithm. Model compression is a critical aspect of machine learning engineering, as it allows for the deployment of large, complex models in resource-constrained environments, such as mobile devices or edge servers.

## Overview

The Jupyter notebook in this directory, `LC_algorithm.ipynb`, showcases the following compression techniques on a simple neural network trained on a subset of the MNIST dataset:

*   **Pruning:** Removing redundant weights from the network to reduce its size.
*   **Quantization:** Reducing the precision of the weights (e.g., from 32-bit floats to 8-bit integers) to decrease memory usage.
*   **Low-Rank Factorization:** Decomposing large weight matrices into smaller, low-rank matrices to achieve significant compression.

## Setup

To run the notebook, you first need to install the required dependencies. The `lc` library is installed directly from its Git repository.

```bash
pip install -r requirements.txt
```

After installing the dependencies, you should be able to run the `LC_algorithm.ipynb` notebook. Note that the notebook requires a GPU to run efficiently.

## Results

The notebook includes visualizations of the trade-off between model compression and accuracy. It demonstrates that significant compression can be achieved with only a small drop in model performance, which is a key consideration for deploying machine learning models in production.
