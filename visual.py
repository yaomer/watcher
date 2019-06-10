import pandas as pd
import matplotlib.pyplot as plt

# 统计人数
users = len(open("./.mac.conf", "r").readlines())
this_week_lines = users * 7

# 正常显示中文
plt.rcParams['font.sans-serif']=['KaiTi']

# 过滤数据
csv = pd.read_csv("./.res.csv")
date = csv.iloc[[0, -1], 0]
start = -1 - this_week_lines
name = csv.iloc[start:start + users, 1].tolist()
time = csv.iloc[start:-1, 2].tolist()

# 构造DataFrame
week_days = [ "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" ]
time_list = [[0] * users for row in range(len(week_days))]

i = j = 0
for it in time:
    if j >= users:
        j = 0
        i += 1
    time_list[i][j] = it
    j += 1

i = 0
dic = dict()
for it in week_days:
    dic.setdefault(it, time_list[i])
    i += 1

# 绘图
df = pd.DataFrame(dic, index=name)
df.plot.barh(stacked=True)
title = "XiyouLinux: " + " ～ ".join(date)
plt.title(title)
plt.ylabel('姓名', fontsize=14)
plt.xlabel('时间', fontsize=14)
plt.show()