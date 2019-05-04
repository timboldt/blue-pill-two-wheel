import matplotlib.pyplot as plt
import csv
import sys

cnt = 0.0
x = []
target = []
actual = []
power = []

with open(sys.argv[1],'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=' ')
    headers = next(plots, None)
    for row in plots:
        x.append(cnt)
        cnt = cnt + 0.01
        target.append(int(row[0]))
        actual.append(int(row[1]))
        power.append(int(row[3]))

plt.plot(x, target, x, actual, x, power)
plt.show()