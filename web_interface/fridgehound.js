var database = firebase.database();
var ref = firebase.database().ref;
 
var newName = 0;
var newNameStr = '';
var newLife = 0;
var newSensor = 0;
var newTemperature = 0;
var dataToPush;
 
var foodsList = ['Fruit', 'Vegetables', 'Beef', 'Chicken', 'Pork', 'Fish', 'Eggs', 'Dairy', 'Other', 'No Food Stored'];
 
function fetchData() {
    console.log('attempting to fetch data...');
    var newData = firebase.database().ref('/foods').once('value').then(function (snapshot) {
        newName = snapshot.val().Food;
        newLife = snapshot.val().Days;
        newSensor = snapshot.val().Sensor;
        newTemperature = snapshot.val().Temperature
 
        newNameStr = foodsList[newName];
        newLife = parseInt(newLife);
        newSensor = parseFloat(newSensor);
        newTemperature = parseInt(newTemperature);
 
        dataToPush = {
            Name: newNameStr,
            Life: newLife,
            Sensor: newSensor,
            Temperature: newTemperature
        }
        updateData(dataToPush)
        console.log('data fetched successfully')
    });
}
 
var col_blue        = "#00B5B5";
var col_yellow      = "#EBBD63";
var col_red         = "#F1654C";
var col_gray        = "#F0F0F0";
var col_black       = "#3E4651";
var col_darkgray    = "#5C6D7E";
 
var myHoundsData = {Name: "No Food", Life: 0, Sensor: 0, Temperature: 0};
var myHoundsData2 = {Name: "Vegetables", Life: 3, Sensor: 0.0, Temperature: 0};
 
var width = parseInt(d3.select('body').style('width'));
var borderDim = 10;
var paddingDim = 10;
var houndPictureDim = parseInt(0.2 * width);
 
var xLifeScale = d3.scaleLinear()
    .domain([0, 10])
    .range([width * 0.2, width - houndPictureDim - 2 - (2 * borderDim) - (8 * paddingDim)]);
 
var xSensorScale = d3.scaleLinear()
    .domain([0.0, 1.0])
    .range([width * 0.2, width - houndPictureDim - 2 - (2 * borderDim) - (8 * paddingDim)]);
 
var LifeColor = d3.scaleLinear()
    .domain([0, 3, 5, 10])
    .range([col_red, col_yellow, col_blue, col_blue]);
 
var SensorColor = d3.scaleLinear()
    .domain([0, 0.3, 0.6, 1.0])
    .range([col_blue, col_blue, col_yellow, col_red]);
 
var myHounds = d3.select("#hounds")
    .append('svg');
 
var defs = myHounds.append('defs')
    .attr('id', 'pic1')
    .attr('patternUnits', 'userSpaceOnUse')
    .attr('width', houndPictureDim)
    .attr('height', houndPictureDim)
    .append('svg:image')
    .attr('src', 'media/vegetables.png')
    .attr("width", houndPictureDim)
    .attr("height", houndPictureDim)
    .attr("x", 0)
    .attr("y", 0);
 
myHounds.style('class', 'hound')
    .attr('width', (width - (2 * borderDim) - (2 * paddingDim)))
    .style('height', houndPictureDim + 'px')
    .style('margin', '10px')
    .style('margin-top', -10 + 'px')
    .style('border-top', 'solid')
    .style('border-color', col_red)
    .append('g');
 
 
var myHoundPic = myHounds.append('rect')
    .style('class', 'houndPicture')
    .attr('width', houndPictureDim + 'px')
    .style('height', houndPictureDim + 'px')
    .style('z-index', -5)
    .style('fill', 'url(#pic1)');
 
var lifeBar = d3.select('#hounds').select('svg').append('g').append('rect')
    .classed('lifeBar', true)
    .attr('stroke', LifeColor(myHoundsData.Life))
    .attr('fill', LifeColor(myHoundsData.Life))
    .style('stroke-width', '4px')
    .style('position', 'relative')
    .attr('width', xLifeScale(myHoundsData.Life))
    .style('transform', 'translate(' + (houndPictureDim + 2) + 'px, ' + (0.33 * houndPictureDim - 2) + 'px)')
    .style('height', function() {
        return 0.33 * houndPictureDim - 4;
    });
 
var lifeBarText = d3.select("#hounds").select('svg').append('g').append('text')
    .style('position', 'absolute')
    .style('font-size', houndPictureDim * 0.2 + 'px')
    .style('background', col_black)
    .style('fill', col_gray)
    .style('alignment-baseline', 'central')
    .style('transform', 'translate(' + (houndPictureDim + 10) + 'px, ' + (0.5 * houndPictureDim - 4) + 'px)')
    // .style('margin-top', (0.3 * houndPictureDim) + 'px')
    // .style('margin-left', '' + (-1 * (width - houndPictureDim - paddingDim * 2 - borderDim * 2) + 'px'))
    .text(function() {
        return "Days";
    });
 
var lifeBarTextVal = d3.select("#hounds").select('svg').append('g').append('text')
    .style('position', 'absolute')
    .style('font-size', houndPictureDim * 0.2 + 'px')
    .style('fill', col_blue)
    .style('alignment-baseline', 'central')
    .style('transform', 'translate(' + (houndPictureDim + 10 + xLifeScale(myHoundsData.Life)) + 'px, ' + (0.5 * houndPictureDim - 4) + 'px)')
    .text(function() {
        return myHoundsData.Life;
    });
 
var myHoundText = d3.select("#hounds").select('svg').append('g').append('text')
    .style('position', 'absolute')
    .style('font-size', houndPictureDim * 0.2 + 'px')
    .style('fill', col_blue)
    .style('alignment-baseline', 'central')
    .style('transform', 'translate(' + (houndPictureDim + 10) + 'px, ' + ((0.33 / 2) * houndPictureDim - 4) + 'px)')
    // .style('margin-top', (0.3 * houndPictureDim) + 'px')
    // .style('margin-left', '' + (-1 * (width - houndPictureDim - paddingDim * 2 - borderDim * 2) + 'px'))
    .text(function() {
        return myHoundsData.Name;
    });
 
var temperatureText = d3.select('#hounds').select('svg').append('g').append('text')
    .style('position', 'absolute')
    .style('font-size', houndPictureDim * 0.2 + 'px')
    .style('fill', col_blue)
    .style('alignment-baseline', 'central')
    .attr('text-anchor', 'end')
    .style('transform', 'translate(' + (width - 4 * borderDim) + 'px, ' + ((0.33 / 2) * houndPictureDim - 4) + 'px)')
    .text(function() {
        return myHoundsData.Temperature + 'ºF';
    });
 
var sensorBar = d3.select('#hounds').select('svg').append('svg').append('rect')
    .attr('stroke', SensorColor(myHoundsData.Sensor))
    .attr('fill', SensorColor(myHoundsData.Sensor))
    .style('stroke-width', '4px')
    .style('position', 'relative')
    .attr('width', xSensorScale(myHoundsData.Sensor))
    .style('transform', 'translate(' + (houndPictureDim + 2) + 'px, ' + (0.66 * houndPictureDim + 1) + 'px)')
    .style('height', function() {
        return 0.33 * houndPictureDim - 4;
    });
 
var sensorBarText = d3.select("#hounds").select('svg').append('g').append('text')
    .style('position', 'absolute')
    .style('font-size', houndPictureDim * 0.2 + 'px')
    .style('background', col_black)
    .style('fill', col_gray)
    .style('alignment-baseline', 'central')
    .style('transform', 'translate(' + (houndPictureDim + 10) + 'px, ' + ((0.66 + (0.33/2)) * houndPictureDim - 4) + 'px)')
    // .style('margin-top', (0.3 * houndPictureDim) + 'px')
    // .style('margin-left', '' + (-1 * (width - houndPictureDim - paddingDim * 2 - borderDim * 2) + 'px'))
    .text(function() {
        return "Sensor";
    });
 
var sensorBarTextVal = d3.select("#hounds").select('svg').append('g').append('text')
    .style('position', 'absolute')
    .style('font-size', houndPictureDim * 0.2 + 'px')
    .style('fill', col_blue)
    .style('alignment-baseline', 'central')
    .style('transform', 'translate(' + (houndPictureDim + 10 + xSensorScale(myHoundsData.Sensor)) + 'px, ' + ((0.66 + (0.33/2)) * houndPictureDim - 4) + 'px)')
    .text(function() {
        return parseInt(myHoundsData.Sensor * 100) + '%';
    });
 
function updateWindow() {
 
    width = window.innerWidth;
    parseInt(d3.select('body').style('width', width));
    houndPictureDim = parseInt(0.2 * width);
 
    xLifeScale.range([0, width - houndPictureDim]);
    xSensorScale.range([0, width - houndPictureDim]);
 
    lifeBar.attr('width', xLifeScale(myHoundsData.Life))
        .style('transform', 'translate(' + (houndPictureDim + 2) + 'px, ' + (0.33 * houndPictureDim - 2) + 'px)')
        .style('height', function() {
            return 0.33 * houndPictureDim - 4;
        });
    lifeBarText.style('transform', 'translate(' + (houndPictureDim + 10) + 'px, ' + (0.5 * houndPictureDim - 4) + 'px)')
        .style('font-size', houndPictureDim * 0.2 + 'px');
    lifeBarTextVal.style('transform', 'translate(' + (houndPictureDim + 10 + xLifeScale(myHoundsData.Life)) + 'px, ' + (0.5 * houndPictureDim - 4) + 'px)')
        .style('font-size', houndPictureDim * 0.2 + 'px')
        .text(function() {
            console.log(myHoundsData.Life);
            return myHoundsData.Life;
        });
 
 
    sensorBar.attr('width', xSensorScale(myHoundsData.Sensor))
        .style('transform', 'translate(' + (houndPictureDim + 2) + 'px, ' + (0.66 * houndPictureDim + 1) + 'px)')
        .style('height', function() {
            return 0.33 * houndPictureDim - 4;
        });
 
    sensorBarText.style('transform', 'translate(' + (houndPictureDim + 10) + 'px, ' + ((0.66 + (0.33/2)) * houndPictureDim - 4) + 'px)')
        .style('font-size', houndPictureDim * 0.2 + 'px');
 
    sensorBarTextVal.style('transform', 'translate(' + (houndPictureDim + 10 + xSensorScale(myHoundsData.Sensor)) + 'px, ' + ((0.66 + (0.33/2)) * houndPictureDim - 4) + 'px)')
        .style('font-size', houndPictureDim * 0.2 + 'px')
        .text(function() {
            return myHoundsData.Sensor;
        });
    temperatureText.style('transform', 'translate(' + (width - 4 * borderDim) + 'px, ' + ((0.33 / 2) * houndPictureDim - 4) + 'px)')
        .style('font-size', houndPictureDim * 0.2 + 'px')
        .text(function() {
            return myHoundsData.Temperature + 'ºF';
        });
 
    d3.select('#hounds').select('rect')
        .attr('width', houndPictureDim + 'px')
        .style('height', houndPictureDim + 'px');
 
    d3.select('#hounds').select('svg')
        .attr('width', (width - (2 * borderDim) - (2 * paddingDim)))
        .style('height', houndPictureDim + 'px')
 
    myHoundText.style('transform', 'translate(' + (houndPictureDim + 10) + 'px, ' + ((0.33 / 2) * houndPictureDim - 4) + 'px)')
        .style('font-size', houndPictureDim * 0.2 + 'px')
}
 
function animateBars(newData) {
    lifeBar.transition().duration(1000).attr('width', xLifeScale(newData.Life))
        .attr('stroke', LifeColor(myHoundsData.Life))
        .attr('fill', LifeColor(myHoundsData.Life));
    lifeBarTextVal.transition().duration(1000).style('transform', 'translate(' + (houndPictureDim + 10 + xLifeScale(newData.Life)) + 'px, ' + (0.5 * houndPictureDim - 4) + 'px)')
                    .text(function() {
                        console.log(newData.Life);
                        return newData.Life;
                    });
    sensorBar.transition().duration(1000).attr('width', xSensorScale(newData.Sensor))
        .attr('stroke', SensorColor(myHoundsData.Sensor))
        .attr('fill', SensorColor(myHoundsData.Sensor));
    sensorBarTextVal.transition().duration(1000).style('transform', 'translate(' + (houndPictureDim + 10 + xSensorScale(newData.Sensor)) + 'px, ' + ((0.66 + (0.33/2)) * houndPictureDim - 4) + 'px)')
                    .text(function() {
                        console.log(newData.Sensor);
                        return parseInt(newData.Sensor * 100) + '%';
                    });
    myHoundText.text(function() {
        return newData.Name;
    })
    temperatureText.text(function() {
        return newData.Temperature + 'ºF'
    })
}
 
function updateData(newData) {
    myHoundsData = {Name: newData.Name,
                    Life: newData.Life,
                    Sensor: newData.Sensor,
                    Temperature: newData.Temperature};
    animateBars(newData);
}
 
function  randomizeSensorData() {
    myHoundsData.Sensor = 0.15 + (Math.random() * 0.1)
    myHoundsData.Temperature = parseInt(Math.random() * 10 + 50);
    console.log(myHoundsData.Temperature);
    updateData(myHoundsData);
}
 
d3.select(window).on('resize', updateWindow);
 
 
window.setInterval(fetchData, 1000);