"""
Parses weather data and generates temperature and precipitation plots.

This script reads "weather_data.txt" using Pandas and creates:
a. A line chart comparing actual maximum and minimum temperatures.
b. A histogram of actual precipitation.
"""

import pandas as pd
import matplotlib.pyplot as plt

def main():
    """
    Main function to execute the weather data plotting logic.
    """
    try:
        data = pd.read_csv("weather_data.txt")
    except FileNotFoundError:
        print("Error: 'weather_data.txt' not found.")
        return

    print("-------------------- Part A --------------------")

    df = pd.DataFrame(data, columns=[
                      'date', 'actual_max_temp', 'actual_min_temp'])
    df.plot(title='actual_max_temp vs. actual_min_temp',
            legend='true', x='date', xlabel='Date', ylabel='Temperature',
            use_index='true', kind='line', style={'actual_max_temp': 'r',
                                                  'actual_min_temp': 'b'}, rot=90)
    plt.show()

    print("-------------------- Part B --------------------")

    df = pd.DataFrame(data, columns=['date', 'actual_precipitation'])
    df.plot(kind='hist')
    plt.show()

if __name__ == "__main__":
    main()
