# 3. In Pandas, parse the file “weather_data.txt” and output the answers to the following:
#     a. What day(s) had the highest actual precipitation?
#     b. What was the average actual max temp for July 2014?
#     c. What days was the actual max temp the record max temp?
#     d. How much did it rain in October 2014?
#     e. What day(s), if any, was the actual low temperature below 60 degrees and actual max
#     temperature above 90 degrees on the same day?


import pandas as pd

print("-------------------- Part A --------------------")

df = pd.DataFrame(pd.read_csv('weather_data.txt'))
maxList = pd.DataFrame()
maxList = df[df['actual_precipitation'] ==
             df['actual_precipitation'].max(axis=0)]

# print(data.sort_values(by="actual_precipitation"))
print(maxList[['date', 'actual_precipitation']])

print("-------------------- Part B --------------------")

List = df.loc[:30]
List = List['actual_max_temp']
print(List.mean())

print("-------------------- Part C --------------------")

List = df[df['actual_max_temp'] == df['record_max_temp']]
print(List['date'])
# print(df.sort_values(
#     ["actual_max_temp", "record_max_temp"], ascending=False)['date'])

print("-------------------- Part D --------------------")

List = df.loc[92:122]
print(List[['date', 'actual_precipitation']])
List = List['actual_precipitation']
print(List.sum())

print("-------------------- Part E --------------------")

print(df[(df['actual_min_temp'] < 60)
      & (df['actual_max_temp'] > 90)])
