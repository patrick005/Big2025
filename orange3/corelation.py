import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

data = pd.read_csv("/home/aa/Big2025/orange3/basket_analysis.csv")
corr = data.corr()
print(corr)

sns.heatmap(corr, annot=True, cmap='coolwarm', vmin=-1, vmax=1) # -1 ~ 1 # 연관성이 높으면 적색, 연관성이 떨어지면 청색으로 그라데이션
plt.show() 
