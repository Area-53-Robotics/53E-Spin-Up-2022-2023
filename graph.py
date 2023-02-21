import pandas as pd
import matplotlib.pyplot as plt

headers = ["Power", "P", "I", "D"]
df = pd.read_csv("log.csv", delimiter=",", names=headers)

y = []
index = 0
for line in df.Power:
    y.append(index)
    index += 1


plt.plot(y, df["Power"], "y", df["P"], "r", df["I"], "g", df["D"], "b")
plt.xlabel("Power = yellow, P = red, I = green, D = blue")

plt.show()
