import matplotlib.pyplot as plt
import csv

cnt = 0.0
x = []
target = []
actual = []

with open("/home/tim/Desktop/plot.txt",'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=' ')
    headers = next(plots, None)
    for row in plots:
        x.append(cnt)
        cnt = cnt + 0.01
        actual.append(row[0])
        target.append(row[1])

plt.plot(x, target, 'b')
plt.ylim(bottom=0)
plt.show()