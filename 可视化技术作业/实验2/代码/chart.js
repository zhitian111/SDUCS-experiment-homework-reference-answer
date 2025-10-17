import define1 from "./dependency.js";

function _1(md){return(
md`<div style="color: grey; font: 13px/25.5px var(--sans-serif); text-transform: uppercase;"><h1 style="display: none;">World choropleth</h1><a href="https://d3js.org/">D3</a> › <a href="/@d3/gallery">Gallery</a></div>

# World choropleth

Health-adjusted life expectancy, 2016. Data: [WHO](https://www.who.int/gho/publications/world_health_statistics/2018/en/)`
)}

function _chart(d3,hale,Legend,countries,countrymesh)
{

  // Specify the chart’s dimensions.
  const width = 928;
  const marginTop = 46;
  const height = width / 2 + marginTop;

  // Fit the projection.
  const projection = d3.geoEqualEarth().fitExtent([[2, marginTop + 2], [width - 2, height]], {type: "Sphere"});
  const path = d3.geoPath(projection);

  // Index the values and create the color scale.
  const valuemap = new Map(hale.map(d => [d.name, d.hale]));

  function interpolateBluesStronger(t) {
    const start = 0.3; // 裁掉最浅 20%
    const end = 1.0;
    const adjusted = start + t * (end - start);
    return d3.interpolateBlues(adjusted);
  }
  
  const color = d3.scaleSequential()
    .domain(d3.extent(valuemap.values()))
    .interpolator(interpolateBluesStronger)
    .clamp(true);
  
  // Create the SVG container.
  const svg = d3.create("svg")
      .attr("width", width)
      .attr("height", height)
      .attr("viewBox", [0, 0, width, height])
      .attr("style", "max-width: 100%; height: auto;");

  // Append the legend.
  svg.append("g")
      .attr("transform", "translate(20,0)")
      .append(() => Legend(color, {title: "世界贫困人口分布（截至2024）", width: 260}));

  // Add a white sphere with a black border.
  svg.append("path")
    .datum({type: "Sphere"})
    .attr("fill", "white")
    .attr("stroke", "currentColor")
    .attr("d", path);

  // Add a path for each country and color it according te this data.
  svg.append("g")
    .selectAll("path")
    .data(countries.features)
    .join("path")
      .attr("fill", d => color(valuemap.get(d.properties.name)))
      .attr("d", path)
    .append("title")
    .text(d => {
      const record = hale.find(r => r.name === d.properties.name);
      if (!record) return d.properties.name;
      return `${d.properties.name}\n贫困人口数：${record.hale.toFixed(2)}百万\n年份：${record.year}`;
    });
    

  // Add a white mesh.
  svg.append("path")
    .datum(countrymesh)
    .attr("fill", "none")
    .attr("stroke", "white")
    .attr("d", path);

  return svg.node();
}


function _3(md){return(
md`The *hale* dataset regrettably doesn’t include ISO 3166-1 numeric identifiers; it only has country names. Country names are often recorded inconsistently, so here we use a *rename* map to patch a handful of country names to the values used by our GeoJSON which comes from [Natural Earth](https://naturalearthdata.com) by way of the [TopoJSON World Atlas](https://github.com/topojson/world-atlas). If your data has ISO 3166-1 numeric identifiers, then you should use those and drop the *featureId* option above.`
)}

async function _hale(FileAttachment,rename){return(
(await FileAttachment("hale.csv").csv()).map(d => ({name: rename.get(d.country) || d.country, hale: +d.hale, year:d.year}))
)}

function _rename(){return(
new Map([
  ["Antigua and Barbuda", "Antigua and Barb."],
  ["Bolivia (Plurinational State of)", "Bolivia"],
  ["Bosnia and Herzegovina", "Bosnia and Herz."],
  ["Brunei Darussalam", "Brunei"],
  ["Central African Republic", "Central African Rep."],
  ["Cook Islands", "Cook Is."],
  ["Democratic People's Republic of Korea", "North Korea"],
  ["Democratic Republic of the Congo", "Dem. Rep. Congo"],
  ["Dominican Republic", "Dominican Rep."],
  ["Equatorial Guinea", "Eq. Guinea"],
  ["Iran (Islamic Republic of)", "Iran"],
  ["Lao People's Democratic Republic", "Laos"],
  ["Marshall Islands", "Marshall Is."],
  ["Micronesia (Federated States of)", "Micronesia"],
  ["Republic of Korea", "South Korea"],
  ["Republic of Moldova", "Moldova"],
  ["Russian Federation", "Russia"],
  ["Saint Kitts and Nevis", "St. Kitts and Nevis"],
  ["Saint Vincent and the Grenadines", "St. Vin. and Gren."],
  ["Sao Tome and Principe", "São Tomé and Principe"],
  ["Solomon Islands", "Solomon Is."],
  ["South Sudan", "S. Sudan"],
  ["Swaziland", "eSwatini"],
  ["Syrian Arab Republic", "Syria"],
  ["The former Yugoslav Republic of Macedonia", "Macedonia"],
  // ["Tuvalu", ?],
  ["United Republic of Tanzania", "Tanzania"],
  ["Venezuela (Bolivarian Republic of)", "Venezuela"],
  ["Viet Nam", "Vietnam"]
])
)}

function _6(md){return(
md`The world geometries are represented in TopoJSON, which we convert into GeoJSON using topojson.feature. (TopoJSON, like D3, is available by default in all Observable notebooks.) These geometries are represented in spherical coordinates (*i.e.*, latitude and longitude in degrees); therefore we’ll need the *projection* option above to convert to screen coordinates (*i.e.*, pixels).`
)}

function _world(FileAttachment){return(
FileAttachment("countries-50m.json").json()
)}

function _countries(topojson,world){return(
topojson.feature(world, world.objects.countries)
)}

function _9(md){return(
md`The *countrymesh* is just the internal borders between countries, *i.e.*, everything but the coastlines. This avoids an additional stroke on the perimeter of the map, which would otherwise mask intricate features such as islands and inlets. (Try removing the last argument to topojson.mesh below to see the effect.)`
)}

function _countrymesh(topojson,world){return(
topojson.mesh(world, world.objects.countries, (a, b) => a !== b)
)}

function _12(md){return(
md`Alternatively, use [Observable Plot](https://observablehq.com/plot)’s concise API to create [maps](https://observablehq.com/@observablehq/plot-mapping) with the [geo mark](https://observablehq.com/plot/marks/geo).`
)}

function _13(Plot,countries,hale,countrymesh){return(
Plot.plot({
  projection: "equal-earth",
  width: 928,
  height: 928 / 2,
  color: {scheme: "YlGnBu", unknown: "#ccc", label: "Healthy life expectancy (years)", legend: true},
  marks: [
    Plot.sphere({fill: "white", stroke: "currentColor"}),
    Plot.geo(countries, {
      fill: (map => d => map.get(d.properties.name))(new Map(hale.map(d => [d.name, d.hale]))),
    }),
    Plot.geo(countrymesh, {stroke: "white"}),
 ]
})
)}

export default function define(runtime, observer) {
  const main = runtime.module();
  function toString() { return this.url; }
  const fileAttachments = new Map([
    ["hale.csv", {url: new URL("./files/data.csv", import.meta.url), mimeType: "text/csv", toString}],
    ["countries-50m.json", {url: new URL("./files/world_map.json", import.meta.url), mimeType: "application/json", toString}]
  ]);
  main.builtin("FileAttachment", runtime.fileAttachments(name => fileAttachments.get(name)));
  main.variable(observer()).define(["md"], _1);
  main.variable(observer("chart")).define("chart", ["d3","hale","Legend","countries","countrymesh"], _chart);
  main.variable(observer()).define(["md"], _3);
  main.variable(observer("hale")).define("hale", ["FileAttachment","rename"], _hale);
  main.variable(observer("rename")).define("rename", _rename);
  main.variable(observer()).define(["md"], _6);
  main.variable(observer("world")).define("world", ["FileAttachment"], _world);
  main.variable(observer("countries")).define("countries", ["topojson","world"], _countries);
  main.variable(observer()).define(["md"], _9);
  main.variable(observer("countrymesh")).define("countrymesh", ["topojson","world"], _countrymesh);
  const child1 = runtime.module(define1);
  main.import("Legend", child1);
  main.variable(observer()).define(["md"], _12);
  main.variable(observer()).define(["Plot","countries","hale","countrymesh"], _13);
  main.variable(observer("chart_fake")).define("chart_fake", ["d3","hale","Legend","countries","countrymesh"], _chart_fake);

  return main;
}



function _chart_fake(d3,hale,Legend,countries,countrymesh)
{

  // Specify the chart’s dimensions.
  const width = 928;
  const marginTop = 46;
  const height = width / 2 + marginTop;

  // Fit the projection.
  const projection = d3.geoEqualEarth().fitExtent([[2, marginTop + 2], [width - 2, height]], {type: "Sphere"});
  const path = d3.geoPath(projection);

  // Index the values and create the color scale.
  const valuemap = new Map(hale.map(d => [d.name, d.hale]));

  function interpolateBluesCheating(t) {
    // 先让整体颜色偏深（例如保留 30%~100% 的色带）
    const start = 0.4;
    const end = 1.0;
  
    // 加非线性变换，让大数值（贫困高）变亮
    // 指数越大 -> 高端更亮、低端更深
    const gamma = 3.0;
    const adjusted = start + Math.pow(1 - t, gamma) * (end - start);
  
    return d3.interpolateReds(adjusted);
  }
  
  
  
  
  const color = d3.scaleSequential()
    .domain(d3.extent(valuemap.values()))
    .interpolator(interpolateBluesCheating)
    .clamp(true);
  
  // Create the SVG container.
  const svg = d3.create("svg")
      .attr("width", width)
      .attr("height", height)
      .attr("viewBox", [0, 0, width, height])
      .attr("style", "max-width: 100%; height: auto;");

  // Append the legend.
  svg.append("g")
      .attr("transform", "translate(20,0)")
      .append(() => Legend(color, {title: "世界贫困严重程度分布（截至2024）", width: 260}));

  // Add a white sphere with a black border.
  svg.append("path")
    .datum({type: "Sphere"})
    .attr("fill", "white")
    .attr("stroke", "currentColor")
    .attr("d", path);

  // Add a path for each country and color it according te this data.
  svg.append("g")
    .selectAll("path")
    .data(countries.features)
    .join("path")
      .attr("fill", d => color(valuemap.get(d.properties.name)))
      .attr("d", path)
      .append("title")
      .text(d => {
        const record = hale.find(r => r.name === d.properties.name);
        if (!record) return d.properties.name;
        if (record.name === "India") {
          return `${d.properties.name}\n贫困人口数：${record.hale.toFixed(2)} m\n年份：${record.year}`;
        }
        return `${d.properties.name}\n贫困人口数：${(record.hale*1000000).toFixed(0)}\n年份：${record.year}`;
      });

  // Add a white mesh.
  svg.append("path")
    .datum(countrymesh)
    .attr("fill", "none")
    .attr("stroke", "white")
    .attr("d", path);

  return svg.node();
}