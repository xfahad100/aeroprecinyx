
var viewer = new Cesium.Viewer('cesiumContainer', {
     baseLayerPicker : false,
     fullscreenButton : false,
     geocoder : false,
     homeButton : false,
     infoBox : false,
     sceneModePicker : false,
     selectionIndicator : false,
     timeline : false,
     navigationHelpButton : false,
     navigationInstructionsInitiallyVisible : false,
     animation: false
});

var terrainSource = new Cesium.CesiumTerrainProvider({
     url : '//assets.agi.com/stk-terrain/world',
     requestWaterMask : true,
     requestVertexNormals : true
});
viewer.terrainProvider = terrainSource; 

var displayLabel = document.getElementById('displayLabel');

var FT2M = 0.3048;
var DEG2RAD = 0.017453293;

// pilot (camera)
var look_down_angle = 0.0;

// default aircraft orientation
var hdg_true_deg = 264.6;
var pitch_deg = 0.0;
var roll_deg = 0.0;

// default aircraft position
// LIMMA - final approach fix at LAX RWY 25L
var lon_deg = -118.273731;
var lat_deg = 33.9484444;
var alt_ft = 1900.0;

// set the camera using the defaults
viewer.camera.setView({
     position : Cesium.Cartesian3.fromDegrees(lon_deg, lat_deg, (alt_ft * FT2M)),
     heading : (hdg_true_deg * DEG2RAD),
     pitch: ((pitch_deg + look_down_angle) * DEG2RAD),
     roll : (roll_deg * DEG2RAD)
});

// set the camera using values from JSBSim via QtJSBSim
function updateCamera() {
     viewer.camera.setView({
         positionCartographic : new Cesium.Cartographic(aircraft.lon() * DEG2RAD, aircraft.lat() * DEG2RAD, (aircraft.alt() * FT2M)),
         heading : (aircraft.hdg_true() * DEG2RAD),
         pitch: ((aircraft.pitch() + look_down_angle) * DEG2RAD),
         roll : (aircraft.roll() * DEG2RAD)
})
    displayLabel.textContent = (aircraft.alt() * FT2M);
}

// update camera 20 times per second
var timer = setInterval(updateCamera, 50);
