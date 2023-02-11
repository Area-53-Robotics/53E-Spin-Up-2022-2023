import pandas as pd
import matplotlib.pyplot as plt

headers = ["Power", "P", "I", "D"]
df = pd.read_csv("output.csv", delimiter=",", names=headers)

y = []
index = 0
for line in df.Power:
    y.append(index)
    index += 1


plt.plot(y, df["Power"], "y")
plt.plot(y, df["P"], "r")
plt.plot(y, df["I"], "g")
plt.plot(y, df["D"], "b")

plt.show()
