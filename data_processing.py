import pandas as pd
import matplotlib.pyplot as plt
import math
import serial

min = 0 #37
max = 25 #47

stepAngle = 3

def getValues(x, y , distance): 
    values = []
    # values.append(x)
    # values.append(y)
    # values.append(distance)
    values.append(distance * math.cos(math.radians(y)) * math.sin(math.radians(x)))
    values.append(distance * math.cos(math.radians(x)) * math.sin(math.radians(y)))
    values.append(distance * math.cos(math.radians(y)) * math.cos(math.radians(x)))
    return values

# ser = serial.Serial('/dev/cu.usbserial-10')
# df = pd.DataFrame(columns=['x', 'y', 'Distance'])
# while(ser.isOpen()):
#     line = ser.readline().decode("utf-8").rstrip()
#     print(line)

#     if line == 'end':
#         break
#     line = line.split(',')
#     values = getValues(float(line[0]) * stepAngle, float(line[1]) * stepAngle, float(line[2]))
    
#     if values[2] > min and values[2] < max:
#         df.loc[len(df.index)] = values
# print("connection closed")

df = pd.read_csv('test.csv')
for x in df.index:
    values = getValues(stepAngle* df.loc[x, 'x'], stepAngle * df.loc[x, 'y'], df.loc[x, 'Distance'])

    # filter range
    if values[2] < min or values[2] > max:
        df.drop(x, inplace = True)
    
    # convert from angle to distance
    else:
        df.loc[x, 'x'] = values[0]
        df.loc[x, 'y'] = values[1]
        df.loc[x, 'Distance'] = values[2]


df.to_csv('processed_data.csv', encoding='utf-8', index=False)
df.plot(kind = 'scatter', x = 'x', y = 'y', c = 'Distance', colormap= 'viridis')

# plt.xlim([-40,40])
# plt.ylim([-2,50])
plt.show()
