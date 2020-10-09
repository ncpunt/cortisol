/*
 * Cortisol Demonstrator
 * Version 1.0.0.0
 * (c) 2020 Medimatics
 *
 */

// jQuery entry point
$(document).ready(function () 
{
    // Create the sliders
    sliders();

    // Simulate default values
    calc();
    
});

// Create the sliders
function sliders()
{
    // Dose
    $("#slider1").ionRangeSlider({
        skin: "big",
        min: 0,
        max: 100,
        from: 10,
        step: 5,
        from_min: 5,
        grid: true,
        force_edges: true,
        grid_snap: true,
        prefix: "Dose: ",
        postfix: " mg",
        hide_min_max: true,
        onFinish: function (data) { calc(); }
    });
    
    // Interval
    $("#slider2").ionRangeSlider({
        skin: "big",
        min: 0,
        max: 24,
        from: 6,
        step: 1,
        from_min: 1,
        grid: true,
        force_edges: true,
        grid_snap: true,
        prefix: "Interval: ",
        postfix: " hours",
        hide_min_max: true,
        onFinish: function (data) { calc(); }
    });
    
    // Number
    $("#slider3").ionRangeSlider({
        skin: "big",
        min: 1,
        max: 4,
        from: 3,
        step: 1,
        grid: true,
        force_edges: true,
        grid_snap: true,
        prefix: "Number: ",
        postfix: " per day",
        hide_min_max: true,
        onFinish: function (data) { calc(); }
    });
    
    // Period
    $("#slider4").ionRangeSlider({
        skin: "big",
        min: 1,
        max: 7,
        from: 1,
        step: 1,
        grid: true,
        force_edges: true,
        grid_snap: true,
        prefix: "Period: ",
        postfix: " days",
        hide_min_max: true,
        onFinish: function (data) { calc(); }
    });
}

// Read slider value
function slider(id)
{
    // The normal way is using the onFinish() callback for pushing the data.
    // In case of multiple sliders it is better to pull data from the slider.
    return $(id).data('ionRangeSlider').result.from;
}

// Execute simulation
function calc()
{
    // Collect the input data from all sliders
    var data = {};
    data.dose = slider('#slider1'); 
    data.tint = slider('#slider2'); 
    data.ndos = slider('#slider3'); 
    data.nseq = slider('#slider4'); 

    // Perform the request
    var req = ocpu.rpc("cortisol", {
            args: data
        }, function (output) {
            plot(JSON.parse(output));
        });

    // If R returns an error, alert the error message
    req.fail(function () {
        alert("Server error: " + req.responseText);
    });

    // After request complete, re-enable the button
    req.always(function () {
        $("#submitbutton").removeAttr("disabled");
    });
}

// Plot the simulation results
function plot(data) {
    
    // Define (x,y) point arrays
    var ct = [], cu = [], fu = [];

    // Convert (t, C) to (x, y) points
    for (var i = 0; i < data.sim.length; i++){
        ct.push({x: data.sim[i].t, y: data.sim[i].C  });
        cu.push({x: data.sim[i].t, y: data.sim[i].Cu });
        fu.push({x: data.sim[i].t, y: data.sim[i].fu });
    }
    
    // Chart confugration
    var config = {
        type: 'scatter',
        data: {
            datasets: [
                {
                    label: 'total',
                    yAxisID: 'Y1',
                    hidden: false,
                    showLine: true,
                    fill: false,
                    tension: 0,
                    borderColor: "blue",
                    borderWidth : 2,
                    data: ct
                },{
                    label: 'free',
                    yAxisID: 'Y1',
                    hidden: false,
                    showLine: true,
                    fill: false,
                    tension: 0,
                    borderColor: "red",
                    borderWidth : 2,
                    data: cu
                },{
                    label: 'free',
                    yAxisID: 'Y2',
                    hidden: false,
                    showLine: true,
                    fill: false,
                    tension: 0,
                    borderColor: "black",
                    borderWidth : 2,
                    data: fu
                }
            ]
        },
        options: {
            responsive: true,
            maintainAspectRatio: false,
            legend: {display: false},
            elements: {
                point:{
                    radius: 0
                }
            },
            layout: {
                padding: {
                    left: 20,
                    right: 20,
                    top: 20,
                    bottom: 20
                }
            },
            scales: {
                xAxes: [{
                    id: 'X1',
                    type: 'linear',
                    position: 'bottom',
                    gridLines: {drawOnChartArea: false, lineWidth: 2, color: "black"},
                    ticks: {fontSize: 16, padding: 4},
                    scaleLabel: {display: true, labelString: "Time (h)", fontSize: 16}
                },{
                    id: 'X2',
                    type: 'linear',
                    position: 'top',
                    gridLines: {drawOnChartArea: false, lineWidth: 2, color: "black", drawTicks: false},
                    ticks: {display: false, major: {enabled: false}}
                    
                }],
                yAxes: [{
                    id: 'Y1',
                    type: 'linear',
                    position: 'left',
                    gridLines: {drawOnChartArea: false, lineWidth: 2, color: "black"},
                    ticks: {fontSize: 16, padding: 4},
                    scaleLabel: {display: true, labelString: "Concentration (nM)", fontSize: 16}
                },{
                    id: 'Y2',
                    type: 'linear',
                    position: 'right',
                    gridLines: {drawOnChartArea: false, lineWidth: 2, color: "black"},
                    ticks: {fontSize: 16, padding: 4},
                    scaleLabel: {display: true, labelString: "Fraction Unbound (-)", fontSize: 16}
                }]
            }
        }
    };
    
    // Get the canvas context
    var ctx = $('#myChart');
    
    // Build the chart
    var chart = new Chart(ctx, config);
}