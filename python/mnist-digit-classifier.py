# -*- coding: utf-8 -*-

# -- Sheet --

# #                                                       Digit Classifer

"""
This script implements a digit classifier (specifically for 8s and 9s) using the MNISTmini dataset.
It explores different data preprocessing techniques and compares the performance of Logistic Regression
and Random Forest classifiers using grid search for hyperparameter tuning.
"""

# ## Import Statements


import numpy as np
from sklearn.utils import shuffle
from sklearn.metrics import confusion_matrix, ConfusionMatrixDisplay
from sklearn.linear_model import LogisticRegression
from sklearn.ensemble import RandomForestClassifier
from sklearn.tree import plot_tree
from sklearn.model_selection import GridSearchCV, KFold
from sklearn.pipeline import make_pipeline
from sklearn.preprocessing import StandardScaler, MinMaxScaler
import scipy.io
import matplotlib.pyplot as plt
# Handle warnings as they come in so we can more easily see what sklearn is complaining about
import warnings
import time

def load_and_preprocess_data():
    """
    Loads the MNISTmini dataset, extracts 8s and 9s, and prepares training and testing sets.

    Returns:
        tuple: A tuple containing (X_train, y_train, test_set, test_labels).
               X_train and y_train are shuffled training data and labels.
               test_set and test_labels are the test data and labels.
    """
    mnist_mini = scipy.io.loadmat('MNISTmini.mat')
    mnist_mini

    X_train = mnist_mini["train_fea1"]
    y_train = mnist_mini['train_gnd1']
    X_test = mnist_mini['test_fea1']
    y_test = mnist_mini['test_gnd1']

    # ## Getting only 8s and 9s, creating labels array


    # Grab all datapoints where label is 9
    indices, _ = np.asarray(y_train == 9).nonzero()
    nines = X_train[indices]
    # Create labels array for nines (all nines with same length as nines)
    nine_labels = np.ones(len(indices), dtype=np.uint8) * 9

    # Grab all datapoints where label is 8
    indices, _ = np.asarray(y_train == 8).nonzero()
    eights = X_train[indices]
    # Create labels array for eights
    eight_labels = np.ones(len(indices), dtype=np.uint8) * 8

    # Repeat with test set
    indices, _ = np.asarray(y_test == 9).nonzero()
    nines_test = X_test[indices]
    nine_test_labels = np.ones(len(indices), dtype=np.uint8) * 9

    indices, _ = np.asarray(y_test == 8).nonzero()
    eights_test = X_test[indices]
    eight_test_labels = np.ones(len(indices), dtype=np.uint8) * 8

    print(len(nines))
    print(len(eights))
    print(len(nines_test))
    print(len(eights_test))

    # Put 8s and 9s into training data and labels arrays
    train_set = np.concatenate((eights, nines), axis=0)
    train_labels = np.concatenate((eight_labels, nine_labels), axis=0)
    print(len(train_labels))

    # Put test 8s and 9s into testing data and labels arrays
    test_set = np.concatenate((eights_test, nines_test), axis=0)
    test_labels = np.concatenate((eight_test_labels, nine_test_labels), axis=0)
    print(len(test_labels))

    # ## Shuffling Dataset


    # Shuffle training set
    X_train, y_train = shuffle(train_set, train_labels, random_state=1778)

    # Checking that data was shuffled and labels are still correct
    # for i in range(10):
    #     plt.imshow(np.transpose(X_train[i].reshape(10,10)))
    #     plt.title(y_train[i])
    #     plt.show()

    return X_train, y_train, test_set, test_labels

def main():
    """
    Main function to execute the digit classification workflow.
    """
    try:
        X_train, y_train, test_set, test_labels = load_and_preprocess_data()
    except FileNotFoundError:
        print("MNISTmini.mat not found. Please ensure the dataset is in the correct directory.")
        return

    # ## Data Preprocessing


    ## sklearn implements many preprocessing methods in the preprocessing package
    # using one of these may make cross-validation across pipelines easier

    # Create 3 sets of data with slightly different preprocessing to see how they compare when training the model
    int_train_data = X_train # Data is given in integer values

    float_train_data = X_train/255.0 # Convert int in range 0-255 to float in range 0-1

    # Standardize data to have mean 0 and variance 1
    standardized_train_data = np.zeros(float_train_data.shape, dtype=float)
    for i in range(len(X_train)):
        standardized_train_data[i] = (float_train_data[i] - float_train_data[i].mean()) / float_train_data[i].std()

    # Take a take a quick look at the data
    # plt.imshow(np.transpose(int_train_data[0].reshape(10,10)))
    # plt.title("int data")
    # plt.colorbar()
    # plt.show()

    # plt.imshow(np.transpose(float_train_data[0].reshape(10,10)))
    # plt.title("float data")
    # plt.colorbar()
    # plt.show()

    # plt.imshow(np.transpose(standardized_train_data[0].reshape(10,10)))
    # plt.title("standardized float data")
    # plt.colorbar()
    # plt.show()

    # # Logistic Regression


    log_reg = LogisticRegression() # Logistic Regression

    # ## Parameters


    # Logistic regression parameters

    # data = {"uint8 data": int_train_data, "float data": float_train_data, "0 mean unit variance data": standardized_train_data}
    data = {"uint8 data": int_train_data}

    #solvers = ['newton-cg', 'lbfgs', 'liblinear', 'sag', 'saga']
    #solvers = ['liblinear', 'sag', 'saga']
    #solvers = ['newton-cg', 'liblinear', 'lbfgs']
    #solvers = ['newton-cg']
    solvers = ['lbfgs']

    #penalties = ['l2', 'l1', 'none']

    # max_iterations = [100, 1000, 10000, 100000]

    #C_values = [.0001, .001, .01, .1, 1, 10, 100]
    #C_values = [1, 10, 100, 1000, 10000]
    C_values = [.1, .5, 1, 1.5, 5, 10]
    #C_values = [.1, .2, .3, .4, .5, .6, .7, .8, .9, 1]
    #C_values = [.00001, .00005, .0001, .0001, .0005]
    #C_values = [.00005, .000075, .0001, .0002]

    # ## Grid Search using above parameters


    num_folds = 4
    cv_folds = KFold(n_splits=num_folds) # No shuffling, folds are kept constant across runs (data was shuffled earlier)

    # Axis 0 of scores: datasets; axis 1: solver; axis 2: C
    scores = np.zeros((1,len(solvers),len(C_values)), dtype=float)

    log_reg.penalty = 'l2'
    log_reg.max_iter = 6000

    start_time = time.time()
    for i, dataset in enumerate(data):
        for j, solver in enumerate(solvers):
            for l, c in enumerate(C_values):
                # Since each dataset has the same order of data, just with different preprocessing, we can use the same k-folds for
                # each variant of the data (same applies for labels)
                folds = cv_folds.split(int_train_data, y_train)

                # Changing hyperparameter for this run
                log_reg.solver = solver
                log_reg.C = c

                lap = time.time() - start_time
                print("Start time: %d m %.2f s" % (int(lap / 60) , lap - (int(lap / 60) * 60)))
                print("Training logisitic regression model on %s with solver: %s" % (dataset, solver))
                with warnings.catch_warnings(record=True) as w:
                    # Cause all warnings to always be triggered.
                    warnings.simplefilter("always")

                    cross_val_scores = np.zeros(num_folds, dtype=float)
                    # K fold cross-validation, saving the score for each version of the model in scores
                    for k, (train, val) in enumerate(folds):
                        log_reg.fit(np.take(data[dataset], train, axis=0), np.take(y_train, train))
                        cross_val_scores[k] = log_reg.score(np.take(data[dataset], val, axis=0), np.take(y_train, val))
                    scores[i,j,l] = 1 - cross_val_scores.mean() # Get mean validation error rather than mean accuracy
                    print(scores[i,j,l])

                    if len(w):
                        for warn in w:
                            print(warn.message)

    lap = time.time() - start_time
    print("Finish time: %d m %.2f s" % (int(lap / 60) , lap - (int(lap / 60) * 60)))
    print(scores)

    # Initially ran into trouble with logistic regression sometimes failing to converge with the default solver and number of
    # max_iterations. Keeping C constant, and without looking at generalization ability, tried different solvers with different
    # numbers of max iterations to see what it takes to get the model to converge in different training scenarios. Note: tol=1e-4
    # for all tests. Also varied the preprocessing of the data, between ints in the range 0-255, floats in the range 0-1, and floats
    # with standardization to mean 0 and unit variance. One of sklearn's recommendations for reaching convergence was to apply
    # preprocessing on the data, standardization was among the simpler techniques given.

    # All of below results for a C value of .1 and using l2 penalty
    # All results below were also done without Kfold cross validation - we were only looking at convergence and runtime
    #
    # newton-cg converges within 100 iteration on all datasets - much faster on float datasets (overall takes about 10 s to run)
    # same as newton-cg for liblinear (overall takes about 11 s to run)
    # sag solver fails to converge within 100 or 1000 iterations on int data - takes 1 min 20 s for all runs on int data
    #       on float data, converges within 100 iterations and runs much faster - takes about 1 s for all runs on float data
    #       on standardized data, fails to converge within 100 iterations - takes about 5 s for all runs on standardized data
    # saga solver reaches convergence in the same intervals as sag, but runs slower across the board (total 3m 40s for all runs)
    # lbfgs solver reaches convergence in the same intervals as sag and saga, but much faster than them (total < 13 s for all runs)

    # l1 penalty, C=.1:
    #
    # newton-cg, lbfgs, and sag not supported with l1 penalty
    # liblinear solver converges for all datasets within 100 iterations and does so very quickly (2.0 s total)
    # saga solver runs much faster on float data than on int data (a couple secs vs a couple mins) and converges on float
    #       data within 100 iterations. On int data, fails to converge in less than or equal to 1000 iteration

    # no penalty (C value irrelevant)
    #
    # newton-cg fails to converge within 1000 iteration on int data, takes several minutes for iterations > 1000
    #       converges much faster (within a couple mins even for max_iter=100000) and within 100 iterations for float data
    #       fails to converge in 100 iterations or less on standardized data and but a bit faster for greater max_iterations
    # lbfgs fails to converge within 100 iterations on int data, but runs quickly (< 1m for all runs on int data)
    #       fails to converge within 1000 iterations on float data, runs relatively quickly (slightly slower than on int data)
    #       fails to converge within 100 iterations on standardized data, otherwise converges quickly (comparable to int data)
    # sag fails to converge within 1000 iterations on int data, takes about 3.5 mins for all runs with int data
    #       fails to converge within 1000 iterations on float data, takes about 2min 20s for all runs
    #       fails to converge within 1000 iterations on standardized float data, takes about 3.25 mins for all runs
    # saga fails to converge within 1000 iteration on all types of data
    #       all runs on int data take about 2 m 20 s
    #       all runs on float data take about 2 m
    #       all runs on standardized float data take about 2 m

    # l2 works for all solvers. newton-cg can converge within 100 iterations for any of the datasets, and runs pretty quickly. lbfgs
    # also runs quickly, and works with both l1 and l2 penalties, but takes between 1000 and 10000 iteration to converge. We could
    # get a smaller range of iterations by trying out values between 1000 and 10,000 for lbfgs. It would be worthwhile to first check
    # if any solver-penalty combo works better than the others to see if the trade-off of computation time is worth the model's
    # accuracy, otherwise we could just use the fastest solver-penalty combo

    # Given sufficient time to converge, each solver can achieve comparable accuracy. - with the exception of newton-cg not converging
    # with high C values on uint8 dataset
    # On initial grid search, the integer dataset had the best validation accuracy with the newton-cg solver and a C of 1, but
    # looking at the graph of accuracy vs. C, it looked like the accuracy peaked and began to drop for a higher C. On the float
    # datasets, however, some solvers seemed to have increasing accuracies as C got larger. I decided to try higher values of C,
    # since previously the highest I looked at was 100, to see if this trend on the float datasets would result in accuracies higher
    # than that which could be obtained on the int dataset at C=1. Also decided to cut the sag and saga solvers out of the grid search,
    # since they were taking longer to evaluate with no gains in accuracy. Also cut out newton-cg since it stops working on the int
    # dataset for high C values. C values of first grid search: [.0001, .001, .01, .1, 1, 10, 100]
    # C values of second grid search: [1, 10, 100, 1000, 10000] - Second grid search did not yield results better than first
    # Third grid search: only considering uint8 dataset, solved with newton-cg, liblinear, and lbfgs.
    #       C values are [.1, .5, 1, 1.5, 5, 10]
    #       Third grid search results showed no solver doing better than newton-cg on the int data
    # Final grid search: only considered uint8 dataset, solved with newton-cg. C values are n/10 where n = {1, 2, ..., 10}
    # best result was tied between all values besides 1/10, including 1

    # Decided to give sag, saga, and liblinear another chance on low C values since they did unusually well on low Cs in initial grid search
    # C-values: [.00001, .00005, .0001, .0001, .0005]
    # Validation accuracy to beat (solver='newton-cg', C=1) is 0.9782203389830508
    # High validation accuracy at exactly C=1e-4 and 5e-5, but still unable to beat above results
    # Second attempt: C-values: [.00005, .000075, .0001, .0002]
    # Sag and saga couldn't beat previous results at .0001, but liblinear does slightly better at .000075 than at .0001
    #       the slight improvement doesn't top newton-cg at C=1 though, with a val accuracy at 0.9767796610169491

    # ## Best classifier


    print(np.unravel_index(np.argmin(scores), scores.shape))
    print(np.min(scores))

    # ## Error Plots


    # for i, dataset in enumerate(data):
    #     for j, solver in enumerate(solvers):
    #         fig = plt.figure()
    #         ax = plt.gca()
    #         ax.scatter(C_values, scores[i,j,:])
    #         ax.set_xlabel('C')
    #         ax.set_ylabel('Validation Error')
    #         ax.set_title("%s, with %s solver" % (dataset, solver))
    #         ax.set_xscale('linear')

    # ## Classifier trained with best parameters that we found


    model = LogisticRegression(C=1, solver='newton-cg', max_iter=6000)
    model.fit(X_train, y_train)
    model.score(test_set, test_labels)

    cm = confusion_matrix(test_labels, model.predict(test_set))
    disp = ConfusionMatrixDisplay(confusion_matrix=cm, display_labels=[8, 9])
    # disp.plot()
    # plt.show()

    # ## Using sklearn Grid Search function to do equivalent search


    # Pipeline of transforms ending in logistic regression classifier:
    # MinMaxScaler: scales data to range 0-1
    # StandardScaler: standardizing data, giving each data point mean 0 and variance 1
    pipeline = make_pipeline(MinMaxScaler(), StandardScaler(), LogisticRegression(max_iter=6000))

    # Verify results with built-in sklearn grid search

    num_folds = 4
    cv_folds = KFold(n_splits=num_folds) # No shuffling, folds are kept constant across runs (data was shuffled earlier)
    hyperparams = {'logisticregression__solver': ['newton-cg', 'lbfgs', 'liblinear', 'sag', 'saga'],
    # Modifying the preprocessing pipeline as a hyperparameter
    'steps': [  [('logisticregression', LogisticRegression())],#, # Logistic regression on base data
                # Scale to 0-1, then standardize, then logistic regression
                [('minmaxscaler', MinMaxScaler()), ('standardscaler', StandardScaler()), ('logisticregression', LogisticRegression())],
                # Only scale to 0-1, then logistic regression
                [('minmaxscaler', MinMaxScaler()), ('logisticregression', LogisticRegression())]],
    'logisticregression__C': [.1, .5, 1, 1.5, 5, 10]
    }

    clf = GridSearchCV(estimator=pipeline, param_grid=hyperparams, cv=cv_folds)
    clf.fit(X_train, y_train)
    print(clf.best_estimator_)

    # Result of sklearn grid search
    clf.best_estimator_ # In our tests, values C = [.2, .3, .4, .5, .6, .7, .8, .9, 1] had equivalent validation error

    # # Random Forest Classifier


    # Create a pipeline to test different preprocessing techniques with only one tree in forest
    pipeline = make_pipeline(MinMaxScaler(), StandardScaler(), RandomForestClassifier(n_estimators=1, random_state=1778))

    # ## First search holding everything but data preprocessing constant (1 tree)


    # Search over preprocessing techniques
    num_folds = 4
    cv_folds = KFold(n_splits=num_folds) # No shuffling, folds are kept constant across runs (data was shuffled earlier)
    hyperparams = {
    # Modifying the preprocessing pipeline as a hyperparameter
    'steps': [  [('randomforestclassifier', RandomForestClassifier(n_estimators=1, random_state=1778))], # Logistic regression on base data
                # Scale to 0-1, then standardize, then logistic regression
                [('minmaxscaler', MinMaxScaler()), ('standardscaler', StandardScaler()), ('randomforestclassifier', RandomForestClassifier(n_estimators=1, random_state=1778))],
                # Only scale to 0-1, then logistic regression
                [('minmaxscaler', MinMaxScaler()), ('randomforestclassifier', RandomForestClassifier(n_estimators=1, random_state=1778))]]

    }

    clf = GridSearchCV(estimator=pipeline, param_grid=hyperparams, cv=cv_folds)
    clf.fit(X_train, y_train)
    print(clf.best_estimator_)

    # Assign best one to a separate classifier to test and search for optimal n_estimators
    tree = clf.best_estimator_

    # ## Test results on single tree using best data preprocessing technique (standardization)


    # Single tree accuracy
    tree.fit(X_train, y_train)
    print(tree.score(test_set, test_labels))
    cm = confusion_matrix(test_labels, tree.predict(test_set))
    disp = ConfusionMatrixDisplay(confusion_matrix=cm, display_labels=[8, 9])
    # disp.plot()
    # plt.show()

    # ## Doing a second search using optimal preprocessing to find best number of trees


    # Hyperparameter search with 4 fold cross validation
    num_folds = 4
    cv_folds = KFold(n_splits=num_folds) # No shuffling, folds are kept constant across runs (data was shuffled earlier)
    hyperparams = {
        'randomforestclassifier__n_estimators': [1, 10, 100, 1000, 10000]
    }

    clf = GridSearchCV(estimator=tree, param_grid=hyperparams, cv=cv_folds)
    clf.fit(X_train, y_train)
    print(clf.best_estimator_)

    rf = clf.best_estimator_
    print(rf)

    # ## Results of best set of parameters


    # Accuracy of best estimator
    rf.fit(X_train, y_train)
    print(rf.score(test_set, test_labels))
    cm = confusion_matrix(test_labels, rf.predict(test_set))
    disp = ConfusionMatrixDisplay(confusion_matrix=cm, display_labels=[8, 9])
    # disp.plot()
    # plt.show()

    # fig = plt.figure(figsize=(15, 10))
    # plot_tree(rf.estimators_[0],
    #           feature_names=wine.feature_names, # wine variable is not defined in the code, this would fail if run
    #           class_names=wine.target_names,
    #           filled=True, impurity=True,
    #           rounded=True)

    # ## Checking if accuracy can be improved significantly with more trees


    rf = RandomForestClassifier(n_estimators=15000)
    rf.fit(X_train, y_train)
    print(rf.score(test_set, test_labels))
    cm = confusion_matrix(test_labels, rf.predict(test_set))
    disp = ConfusionMatrixDisplay(confusion_matrix=cm, display_labels=[8, 9])
    # disp.plot()
    # plt.show()

if __name__ == "__main__":
    main()
