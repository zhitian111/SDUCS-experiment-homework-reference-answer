# 实验2文件解释
> 因为我是基于observablehq上的一个项目修改的，所以文件中包含一些observablehq的相关代码
> [参照的项目链接在此](https://observablehq.com/@d3/world-choropleth/2)

## index.html
页面文件，包含了可视化页面的引导代码和部分样式表等。

## index.js
js代码，用于中转

## chart.js
图表的**核心代码**，主要是用d3.js绘制了世界地图的热力图。

## dependency.js
加载d3.js和observablehq相关的库文件。

## runtime.js
npm生成的runtime文件，用于在不安装node.js的情况下加载依赖库文件。

##  files/data.csv
处理后的，将要被可视化的数据文件

## files/world_map.json
世界地图的矢量图表示文件

## 202300130183-宋浩宇-实验2.pdf
实验报告本身

## 启动脚本.bat
用于windows系统，快速启动一个支持该页面的http服务

## 启动脚本.sh
用于linux系统，功能同上