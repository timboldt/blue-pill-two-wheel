# Copyright 2019 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

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
