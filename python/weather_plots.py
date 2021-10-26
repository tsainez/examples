# 4. In Pandas, parse the file “weather_data.txt” and create the following plots (with titles, labels and a legend):
#     a. Actual max temperature and actual min temperature on the same line chart (max
#     should be a red line, min should be blue)
#     b. A histogram of actual precipitation

import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("weather_data.txt")

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
