import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

min = 110
max = 200

df = pd.read_csv('data.csv')

interval = []
intervalColors = colors = {'1':'red', '2':'yellow', '3':'green', '4':'blue'}

def getInterval(distance: int):
    temp = 0
    if (distance < min + 5):
        temp = 1
    elif (distance < min + 10):
        temp = 2
    elif (distance < min + 15):
        temp = 3
    else:
        temp = 4
    return temp

# filter range
for x in df.index:
    if df.loc[x, "Distance"] < min or df.loc[x, "Distance"] > max:
        df.drop(x, inplace = True)
    else:
        interval.append(getInterval(df.loc[x, "Distance"]))

# add intervals to dataframe
df['Interval'] = interval

df.plot(kind = 'scatter', x = 'x', y = 'y', c = 'Distance', colormap= 'viridis')
plt.show()

print(df.to_string())