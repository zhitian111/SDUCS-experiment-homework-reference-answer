import * as d3 from "https://cdn.jsdelivr.net/npm/d3@7/+esm";
// 数据
const data1 = [
    { age: "0-4", male: 4619544, female: 4589196 },
    { age: "5-9", male: 4465783, female: 4390483 },
    { age: "10-14", male: 4057669, female: 4001749 },
    { age: "15-19", male: 3774846, female: 3801743 },
    { age: "20-24", male: 3694038, female: 3751061 },
    { age: "25-29", male: 3389280, female: 3236056 },
    { age: "30-34", male: 2918964, female: 2665174 },
    { age: "35-39", male: 2633883, female: 2347737 },
    { age: "40-44", male: 2261070, female: 2004987 },
    { age: "45-49", male: 1868413, female: 1648025 },
    { age: "50-54", male: 1571038, female: 1411981 },
    { age: "55-59", male: 1161908, female: 1064632 },
    { age: "60-64", male: 916571, female: 887508 },
    { age: "65-69", male: 672663, female: 640212 },
    { age: "70-74", male: 454747, female: 440007 },
    { age: "75-79", male: 268211, female: 265879 },
    { age: "80-84", male: 127435, female: 132449 },
    { age: "85-89", male: 44008, female: 48614 },
    { age: "90以上", male: 15164, female: 20093 }
    ]
    
    
    
    const data2 = [
    { age: "0-4", male: 9735380, female: 9310714 },
    { age: "5-9", male: 10552146, female: 10069564 },
    { age: "10-14", male: 10563233, female: 10022524 },
    { age: "15-19", male: 10237419, female: 9692669 },
    { age: "20-24", male: 9731315, female: 9324244 },
    { age: "25-29", male: 9659493, female: 9518507 },
    { age: "30-34", male: 10205879, female: 10119296 },
    { age: "35-39", male: 11475182, female: 11635647 },
    { age: "40-44", male: 11320252, female: 11488578 },
    { age: "45-49", male: 9925006, female: 10261253 },
    { age: "50-54", male: 8507934, female: 8911133 },
    { age: "55-59", male: 6459082, female: 6921268 },
    { age: "60-64", male: 5123399, female: 5668961 },
    { age: "65-69", male: 4453623, female: 4804784 },
    { age: "70-74", male: 3792145, female: 5184855 },
    { age: "75-79", male: 2912655, female: 4355644 },
    { age: "80-84", male: 1902638, female: 3221898 },
    { age: "85-89", male: 970357, female: 1981156 },
    { age: "90以上", male: 336303, female: 1064581 }
    ]
const shadow = {
    "male": "男",
    "female": "女"
}
// 为每个数据项计算 total
data1.forEach(d => { d.total = d.male + d.female; });
data2.forEach(d => { d.total = d.male + d.female; });
const svg_width = 1440; // 加倍宽度以容纳两个图表
const svg_height = 405;
const margin = { top: svg_height * 0.1, right: svg_width * 0.1, bottom: svg_height * 0.1, left: svg_width * 0.1 };
const width = (svg_width - margin.left - margin.right) / 2; // 每个图表宽度减半
const height = svg_height - margin.top - margin.bottom;

// 为每个数据项计算 total
data1.forEach(d => { d.total = d.male + d.female; });
data2.forEach(d => { d.total = d.male + d.female; });
// 创建 SVG
const svg = d3.select("#graph")
    .attr("width", svg_width)
    .attr("height", svg_height);

// 创建 tooltip
const tooltip = d3.select("body").append("div")
    .attr("class", "tooltip");

// 绘制两个图表
const years = [
    { data: data1, year: "1900", xOffset: margin.left },
    { data: data2, year: "2000", xOffset: width + margin.left + 20 } // 增加间距
];

years.forEach(yearData => {
    const g = svg.append("g")
        .attr("transform", `translate(${yearData.xOffset},${margin.top})`);

    const stack = d3.stack().keys(['male', 'female']);
    const stackedData = stack(yearData.data);

    const x = d3.scaleBand()
        .domain(yearData.data.map(d => d.age))
        .range([0, width])
        .padding(0.2);

    const y = d3.scaleLinear()
        .domain([0, d3.max([...data1, ...data2], d => d.male + d.female)]) // 统一 Y 轴范围
        .range([height, 0]);

    // 绘制堆叠图层
    const layer = g.selectAll(".layer")
        .data(stackedData)
        .enter().append("g")
        .attr("class", "layer")
        .attr("fill", (d, i) => i === 0 ? "steelblue" : "pink");

    // 绘制矩形
    const rects = layer.selectAll("rect")
        .data(d => d)
        .enter().append("rect")
        .attr("x", d => x(d.data.age))
        .attr("y", d => y(d[1]))
        .attr("height", d => y(d[0]) - y(d[1]))
        .attr("width", x.bandwidth())
        .on("mouseover", function (event, d) {
            d3.select(this).attr("opacity", 0.7);
            const key = d3.select(this.parentNode).datum().key;
            const value = d.data[key];
            const percent = Math.round((value / d.data.total) * 100);
            tooltip
                .style("opacity", 1)
                .html(`年份: ${yearData.year}<br>性别: ${shadow[key]}<br>数量: ${value}<br>比例: ${percent}%`);
        })
        .on("mousemove", function (event, d) {
            tooltip
                .style("left", event.pageX + 10 + "px")
                .style("top", event.pageY + 5 + "px");
        })
        .on("mouseout", function () {
            tooltip.style("opacity", 0);
            d3.select(this).attr("opacity", 1);
        });

    // 比例文本
    layer.selectAll("text.percent")
        .data(d => d)
        .enter().append("text")
        .attr("class", "percent")
        .attr("x", d => x(d.data.age) + x.bandwidth() / 2)
        .attr("y", d => y(d[1]) + (y(d[0]) - y(d[1])) / 2)
        .attr("dy", "0.35em")
        .attr("text-anchor", "middle")
        .attr("fill", "white")
        .attr("font-size", "12px")
        .text(function (d) {
            const key = d3.select(this.parentNode).datum().key;
            const value = d.data[key];
            const percent = Math.round((value / d.data.total) * 100);
            return `${percent}%`;
        });

    // 总数文本
    g.selectAll("text.total")
        .data(yearData.data)
        .enter().append("text")
        .attr("class", "total")
        .attr("x", d => x(d.age) + x.bandwidth() / 2)
        .attr("y", d => y(d.total))
        .attr("dy", "-5px")
        .attr("text-anchor", "middle")
        .attr("fill", "black")
        .attr("font-size", "6px")
        .text(d => d.total);

    // 坐标轴
    g.append("g")
        .attr("class", "x-axis")
        .attr("transform", `translate(0,${height})`)
        .call(d3.axisBottom(x))
        .selectAll("text")
        .attr("font-size", "9px")

    if (yearData.year === "2000") { // 仅对 2025 年图表（第二个图）应用右侧 Y 轴
        g.append("g")
            .attr("class", "y-axis")
            .attr("transform", `translate(${width},0)`) // 移到右侧
            .call(d3.axisRight(y))
            .selectAll("text")
            .attr("font-size", "12px")
            .attr("fill", "black");
    } else {
        g.append("g")
            .attr("class", "y-axis")
            .call(d3.axisLeft(y))
            .selectAll("text")
            .attr("font-size", "12px")
            .attr("fill", "black");
    }
    // 年份标签
    g.append("text")
        .attr("class", "year-label")
        .attr("x", width / 2)
        .attr("y", -15)
        .attr("text-anchor", "middle")
        .attr("font-size", "14px")
        .attr("fill", "black")
        .text(`年份: ${yearData.year}`);
});

// 添加标题
svg.append("text")
    .attr("class", "chart-title")
    .attr("x", svg_width / 2)
    .attr("y", margin.top / 2)
    .attr("text-anchor", "middle")
    .attr("font-size", "16px")
    .attr("fill", "black")
    .text("人口年龄与性别分布 (1900 vs 2000)");

// 添加图例
const legend = svg.append("g")
.attr("class", "legend")
.attr("transform", `translate(${svg_width - 100}, 0)`);

const legendItems = [
{ color: "steelblue", label: "男" },
{ color: "pink", label: "女" }
];

legend.selectAll(".legend-item")
.data(legendItems)
.enter().append("g")
.attr("class", "legend-item")
.attr("transform", (d, i) => `translate(0, ${i * 20})`)
.each(function(d) {
  d3.select(this).append("rect")
    .attr("width", 18)
    .attr("height", 18)
    .attr("fill", d.color);
  d3.select(this).append("text")
    .attr("x", 24)
    .attr("y", 9)
    .attr("dy", "0.35em")
    .attr("font-size", "12px")
    .attr("fill", "black")
    .text(d.label);
});