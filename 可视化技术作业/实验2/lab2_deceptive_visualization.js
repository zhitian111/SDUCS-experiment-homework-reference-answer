myChart.showLoading();
$.get(ROOT_PATH + '/data/asset/geo/USA.json', function (usaJson) {
  myChart.hideLoading();
  echarts.registerMap('USA', usaJson, {
    Alaska: {
      left: -131,
      top: 25,
      width: 15
    },
    Hawaii: {
      left: -110,
      top: 28,
      width: 5
    },
    'Puerto Rico': {
      left: -76,
      top: 26,
      width: 2
    }
  });
  option = {
    title: {
      text: 'United States COVID-19 Deaths by State',
      subtext: 'Question: What is the situation of the COVID-19 death in all states of the United States? ',
      left: 'left'
    },
    tooltip: {
      trigger: 'item',
      showDelay: 0,
      transitionDuration: 0.2
    },
    visualMap: {
      left: 'right',
      pieces: [
    {gt: 2100000,label: '>2100000 (Death Number)'},            // (1500, Infinity]
    {gt: 160000, lte: 2100000,label: '160000 - 2100000 (Death Number)'},  // (310, 1000]

   // {gt: 120000, lte: 160000,label: '120000 - 160000 (State Total Deaths)'},   // (200, 300]
    {gt: 80000, lte: 160000,label: '80000 - 160000 (Death Number)'},   // (200, 300]
    {gt: 10000, lte: 80000,label: '40000 - 80000 (Death Number)'},   // (200, 300]
    {gt: 2000, lte: 10000,label: '20000 - 40000 (Death Number)'},
    { lte: 2000,label: '≤ 20000 (Death Number)'},

],


    },
    toolbox: {
      show: true,
      //orient: 'vertical',
      left: 'right',
      top: 'top',
      feature: {
        dataView: { readOnly: false },
        restore: {},
        saveAsImage: {}
      }
    },
    series: [
      {
        name: 'USA PopEstimates',
        type: 'map',
        roam: true,
        map: 'USA',
        emphasis: {
          label: {
            show: true
          }
        },

        data: [

{name:"Alabama",value:"20505"},
{name:"Alaska",value:"1377"},
{name:"American Samoa",value:"34"},
{name:"Arizona",value:"31515"},
{name:"Arkansas",value:"12396"},
{name:"California",value:"95810"},
{name:"Colorado",value:"13378"},
{name:"Connecticut",value:"11423"},
{name:"Delaware",value:"3136"},
{name:"District of Columbia",value:"1392"},
{name:"Florida",value:"81907"},
{name:"Georgia",value:"40552"},
{name:"Guam",value:"401"},
{name:"Hawaii",value:"1702"},
{name:"Idaho",value:"5203"},
{name:"Illinois",value:"39875"},
{name:"Indiana",value:"24864"},
{name:"Iowa",value:"10153"},
{name:"Kansas",value:"9601"},
{name:"Kentucky",value:"17191"},
{name:"Louisiana",value:"18138"},
{name:"Maine",value:"2630"},
{name:"Maryland",value:"15497"},
{name:"Massachusetts",value:"21841"},
{name:"Michigan",value:"39092"},
{name:"Minnesota",value:"13422"},
{name:"Mississippi",value:"12945"},
{name:"Missouri",value:"21804"},
{name:"Montana",value:"3569"},
{name:"Nebraska",value:"532246"},
{name:"Nevada",value:"851300"},
{name:"New Hampshire",value:"354928"},
{name:"New Jersey",value:"2775804"},
{name:"New Mexico",value:"623532"},
{name:"New York City",value:"2913849"},
{name:"New York",value:"3286617"},
{name:"North Carolina",value:"3231473"},
{name:"North Dakota",value:"271085"},
{name:"Northern Mariana Islands",value:"13171"},
{name:"Ohio",value:"3162278"},
{name:"Oklahoma",value:"1202398"},
{name:"Oregon",value:"905882"},
{name:"Palau",value:"5490"},
{name:"Pennsylvania",value:"3292134"},
{name:"Puerto Rico",value:"970438"},
{name:"Rhode Island",value:"406926"},
{name:"South Carolina",value:"1718600"},
{name:"South Dakota",value:"263468"},
{name:"Tennessee",value:"2351887"},
{name:"Texas",value:"7983954"},
{name:"United States of America",value:"97063357"},
{name:"Utah",value:"1043012"},
{name:"Vermont",value:"144346"},
{name:"Virgin Islands",value:"23276"},
{name:"Virginia",value:"2107974"},
{name:"Washington",value:"1830508"},
{name:"West Virginia",value:"605326"},
{name:"Wisconsin",value:"1885519"},
{name:"Wyoming",value:"178032"}

        ]
      }
    ]
  };
  myChart.setOption(option);
});
