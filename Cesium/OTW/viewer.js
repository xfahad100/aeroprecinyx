var widget = new Cesium.CesiumWidget('cesiumContainer');

var hdg_true_deg = 264.6;
var pitch_deg = 0.0;
var roll_deg = 0.0;

// LIMMA - final approach fix at LAX RWY 25L
var lon_deg = -118.273731;
var lat_deg = 33.9484444;
var alt_ft = 1900.0;

widget.camera.setView({
     position : Cesium.Cartesian3.fromDegrees(lon_deg, lat_deg, alt_ft),
     heading : Cesium.Math.toRadians(hdg_true_deg),
     pitch: Cesium.Math.toRadians(pitch_deg),
     roll : Cesium.Math.toRadians(roll_deg)
});