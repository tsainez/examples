import numpy as np
from sklearn.model_selection import train_test_split
from torchvision import datasets
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score
import joblib
import os

def data_loader():
    """
    Loads and preprocesses the MNIST dataset.
    """
    # Create the data directory if it doesn't exist
    if not os.path.exists('../data'):
        os.makedirs('../data')

    # Import the data from torchvision
    train_data_th = datasets.MNIST(root='../data', download=True, train=True)

    train_data, train_targets = train_data_th.data, train_data_th.targets

    data_train = np.array(train_data[:]).reshape(-1, 784).astype(np.float32)

    # Normalize and center the data
    data_train = (data_train / 255)
    dtrain_mean = data_train.mean(axis=0)
    data_train -= dtrain_mean

    x_train, x_val, y_train, y_val = train_test_split(data_train, train_targets, train_size=0.8, random_state=1778, shuffle=True)

    return x_train, x_val, y_train, y_val

def train_model(x_train, y_train):
    """
    Trains a RandomForestClassifier model.
    """
    rf = RandomForestClassifier(n_estimators=500, random_state=1778, n_jobs=-1)
    rf.fit(x_train, y_train)
    return rf

if __name__ == '__main__':
    print("Loading data...")
    x_train, x_val, y_train, y_val = data_loader()

    print("Training model...")
    model = train_model(x_train, y_train)

    print("Evaluating model...")
    predictions = model.predict(x_val)
    accuracy = accuracy_score(y_val, predictions)
    print(f"Validation Accuracy: {accuracy:.4f}")

    # Create the models directory if it doesn't exist
    if not os.path.exists('../models'):
        os.makedirs('../models')

    print("Saving model...")
    joblib.dump(model, '../models/mnist_rf_model.joblib')

    print("Training complete.")
