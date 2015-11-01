var widget = new Cesium.CesiumWidget('cesiumContainer');

var FT2M = 0.3048;
var DEG2RAD = 0.017453293;

// pilot (camera)
var look_down_angle = 0.0;

// aircraft orientation
var hdg_true_deg = 264.6;
var pitch_deg = 0.0;
var roll_deg = 0.0;

// aircraft position
// LIMMA - final approach fix at LAX RWY 25L
var lon_deg = -118.273731;
var lat_deg = 33.9484444;
var alt_ft = 1900.0;

widget.camera.setView({
     position : Cesium.Cartesian3.fromDegrees(lon_deg, lat_deg, (alt_ft * FT2M)),
     heading : (hdg_true_deg * DEG2RAD),
     pitch: ((pitch_deg + look_down_angle) * DEG2RAD),
     roll : (roll_deg * DEG2RAD)
});
