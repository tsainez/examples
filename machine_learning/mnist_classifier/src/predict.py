import numpy as np
from torchvision import datasets
from sklearn.metrics import accuracy_score
import joblib
import os

def load_test_data():
    """
    Loads and preprocesses the MNIST test dataset.
    """
    # Create the data directory if it doesn't exist
    if not os.path.exists('../data'):
        os.makedirs('../data')

    # Import the data from torchvision
    test_data_th = datasets.MNIST(root='../data', download=True, train=False)

    test_data, test_targets = test_data_th.data, test_data_th.targets

    data_test = np.array(test_data[:]).reshape(-1, 784).astype(np.float32)

    # We need to use the same mean as the training data for consistency
    # For simplicity, we'll recalculate it here. In a real-world scenario,
    # this mean would be saved during training and loaded here.
    train_data_th = datasets.MNIST(root='../data', download=True, train=True)
    data_train = np.array(train_data_th.data[:]).reshape(-1, 784).astype(np.float32)
    data_train = (data_train / 255)
    dtrain_mean = data_train.mean(axis=0)

    data_test = (data_test / 255).astype(np.float32)
    data_test -= dtrain_mean

    return data_test, test_targets

def predict(model, x_test):
    """
    Makes predictions on the test set.
    """
    predictions = model.predict(x_test)
    return predictions

if __name__ == '__main__':
    print("Loading model...")
    model = joblib.load('../models/mnist_rf_model.joblib')

    print("Loading test data...")
    x_test, y_test = load_test_data()

    print("Making predictions...")
    predictions = predict(model, x_test)

    accuracy = accuracy_score(y_test, predictions)
    print(f"Test Accuracy: {accuracy:.4f}")
