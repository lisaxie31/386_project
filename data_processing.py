import pandas as pd
import matplotlib.pyplot as plt

min = 10 #37
max = 50 #47

df = pd.read_csv('rock1.csv')
df['Distance'] = pd.to_numeric(df['Distance'])

def getDistance(x, y , distance): 
    new_distance = distance
    return new_distance

def getX(x):
    return x

def getY(y):
    return y

for x in df.index:
    cur_distance = getDistance(df.loc[x, 'x'], df.loc[x, 'y'], df.loc[x, 'Distance'])

    # filter range
    if cur_distance < min or cur_distance > max:
        df.drop(x, inplace = True)
    
    # convert from angle to distance
    else:
        df.loc[x, 'x'] = getX(df.loc[x, 'x'])
        df.loc[x, 'y'] = getY(df.loc[x, 'y'])
        df.loc[x, 'Distance'] = cur_distance

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