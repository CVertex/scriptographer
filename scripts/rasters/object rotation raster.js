include("raster.js");

var size = 10;
var scale = 100;

function createDot(x, y, dot, radius) {
	if (radius > 0) {
		var art = dot.clone();
		var m = new Matrix();
		m.translate(x * size, y * size);
		m.scale(radius * scale);
		m.rotate(radius * Math.PI * 2);
		art.transform(m); 
		return art;
	}
	return null;
}

if (initRaster()) {
	values = Dialog.prompt("Enter Raster Values:", [
		{ value: size, description: "Grid Size:", width: 50},
		{ value: scale, description: "Object Scale (%):", width: 50}
	]);
	if (values) {
		size = values[0]
		scale = values[1] / 100.0;
		executeRaster(createDot);
	}
}
