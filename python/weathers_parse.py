"""
Parses weather data to answer specific questions about temperature and precipitation.

This script reads "weather_data.txt" using Pandas and determines:
a. The day(s) with the highest actual precipitation.
b. The average actual max temperature for July 2014.
c. The days where the actual max temperature equaled the record max temperature.
d. The total rainfall in October 2014.
e. The days with actual low temperature below 60 and actual max temperature above 90.
"""

import pandas as pd

def main():
    """
    Main function to execute the weather data analysis.
    """
    try:
        df = pd.DataFrame(pd.read_csv('weather_data.txt'))
    except FileNotFoundError:
        print("Error: 'weather_data.txt' not found.")
        return

    print("-------------------- Part A --------------------")
    # What day(s) had the highest actual precipitation?
    maxList = pd.DataFrame()
    maxList = df[df['actual_precipitation'] ==
                 df['actual_precipitation'].max(axis=0)]

    # print(data.sort_values(by="actual_precipitation"))
    print(maxList[['date', 'actual_precipitation']])

    print("-------------------- Part B --------------------")
    # What was the average actual max temp for July 2014?
    # Assuming the first 31 days correspond to July 2014 based on file structure knowledge
    List = df.loc[:30]
    List = List['actual_max_temp']
    print(List.mean())

    print("-------------------- Part C --------------------")
    # What days was the actual max temp the record max temp?
    List = df[df['actual_max_temp'] == df['record_max_temp']]
    print(List['date'])
    # print(df.sort_values(
    #     ["actual_max_temp", "record_max_temp"], ascending=False)['date'])

    print("-------------------- Part D --------------------")
    # How much did it rain in October 2014?
    # Assuming specific indices correspond to October 2014
    List = df.loc[92:122]
    print(List[['date', 'actual_precipitation']])
    List = List['actual_precipitation']
    print(List.sum())

    print("-------------------- Part E --------------------")
    # What day(s), if any, was the actual low temperature below 60 degrees and actual max
    # temperature above 90 degrees on the same day?
    print(df[(df['actual_min_temp'] < 60)
          & (df['actual_max_temp'] > 90)])

if __name__ == "__main__":
    main()
