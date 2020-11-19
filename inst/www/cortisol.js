/*
 * Cortisol Demonstrator
 * Version 1.0.0.1
 * (c) 2020 Medimatics
 *
 */

 // Request start time
var t0;

// jQuery entry point
$(document).ready(function () 
{
    // Create the sliders
    gui();

    // Simulate default values
    calc();
    
});

// Create the sliders
function gui()
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

    // Set default server depending on host name
    if (window.location.href.indexOf("ocpu") > -1) $("#OpenCPU").prop("checked", true)
    else                                           $("#ASPNET").prop("checked", true)

    // Trigger calculation after clicking radio button
    $("input[type='radio']").change(function () { calc(); });

    // Hidy busy image
    $("#uiBusy").hide(); 
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
    // Record request start time 
    t0 = performance.now();

    // Show busy image
    $("#uiBusy").show();

    // Collect the input data from all sliders
    var data = {};
    data.dose = slider('#slider1'); 
    data.tint = slider('#slider2'); 
    data.ndos = slider('#slider3'); 
    data.nseq = slider('#slider4'); 

    // Select server
    if ($("#OpenCPU").prop("checked"))
    {
        /***  R on OpenCPU (RxODE)  ***/

        // Perform the request using ocpu client library

        // Set url for cross domain call
        if (!window.location.href.indexOf("ocpu") > -1)
        {
            ocpu.seturl("https://ncpunt.ocpu.io/cortisol/R");                         // Short URL
            //ocpu.seturl("https://cloud.opencpu.org/ocpu/apps/ncpunt/cortisol/R");   // Long URL
            //ocpu.seturl(" http://localhost:5656/ocpu/library/cortisol/R");          // Localhost                         // Short URL
        }
        var req = ocpu.rpc("cortisol", {
                args: data
            }, function (output) {
                plot(JSON.parse(output));
            });

        // If R returns an error, alert the error message
        req.fail(function () {
            alert("Server error: " + req.responseText);
        });
    }
    else
    {
        /***  C# on ASP.NET (NeoEngine)  ***/

        // Perform the request using jquery ajax library

        // Service URL
        var url = "https://www.medimatics.nl/corapi"  

        // Service Controller
        var method = "api/CorData" 

        // Setup ajax options
        var options =
        {
            url: url + '/' + method,
            type: "POST",
            cache: false,    // Avoids instant insanity
            async: true,
            contentType: "application/json; charset=utf-8",
            dataType: "json",
            data: JSON.stringify(data),
            xhrFields: { withCredentials: false },
            success: function (output) { plot(output); }, 
            error: function (XMLHttpRequest, textStatus, errorThrown) { alert(errorThrown + "\n\n" + XMLHttpRequest.responseText); }
        }

        // Post ajax request
        $.ajax(options);
    }
}

// Plot the simulation results
function plot(data) {

    // Get number of msec taken for response
    var elapsed = Math.trunc(performance.now() - t0);

    // Show trip time
    $("#Msg").text("(C) 2020 Medimatics (" + elapsed + " ms)");

    // Show processing time in msec
    $("#tcpu").text("CPU = " + data.tcpu + " ms");

    // Define (x,y) point arrays
    var ct = [], cu = [], fu = [];

    // Convert (t, C) to (x, y) points
    for (var i = 0; i < data.sim.length; i++){
        ct.push({x: data.sim[i].t, y: data.sim[i].C  ? data.sim[i].C  : data.sim[i].c  });
        cu.push({x: data.sim[i].t, y: data.sim[i].Cu ? data.sim[i].Cu : data.sim[i].cu });
        fu.push({x: data.sim[i].t, y: data.sim[i].fu });
    }
    // Note that the members C and Cu are uppercase in OpenCPU and lowercase (c, cu) in ASP.NET
    
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

    // Hide busy image
    $("#uiBusy").hide();  
}