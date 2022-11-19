import pandas as pd
import matplotlib.pyplot as plt
import math

min = 0 #37
max = 100 #47

df = pd.read_csv('paper1.csv')
df['Distance'] = pd.to_numeric(df['Distance'])

def getValues(x, y , distance): 
    values = []
    values.append(distance * math.cos(math.radians(y)) * math.sin(math.radians(x)))
    values.append(distance * math.cos(math.radians(x)) * math.sin(math.radians(y)))
    values.append(distance * math.cos(math.radians(y)) * math.cos(math.radians(x)))
    return values

def getX(x):
    return x

def getY(y):
    return y

for x in df.index:
    values = getValues(df.loc[x, 'x'], df.loc[x, 'y'], df.loc[x, 'Distance'])

    # filter range
    if values[2] < min or values[2] > max:
        df.drop(x, inplace = True)
    
    # convert from angle to distance
    else:
        df.loc[x, 'x'] = values[0]
        df.loc[x, 'y'] = values[1]
        df.loc[x, 'Distance'] = values[2]

df.plot(kind = 'scatter', x = 'x', y = 'y', c = 'Distance', colormap= 'viridis')

plt.xlim([-20,20])
plt.ylim([-2,34])
plt.show()



# interval = []
# intervalColors = colors = {'1':'red', '2':'yellow', '3':'green', '4':'blue'}

# def getInterval(distance: int):
#     temp = 0
#     if (distance < min + 5):
#         temp = 1
#     elif (distance < min + 10):
#         temp = 2
#     elif (distance < min + 15):
#         temp = 3
#     else:
#         temp = 4
#     return temp

# # add intervals to dataframe
# df['Interval'] = interval