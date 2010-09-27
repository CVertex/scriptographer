////////////////////////////////////////////////////////////////////////////////
// Values

tool.minDistance = 10;

var values = {
	curviness: 0.5,
	distance: tool.minDistance,
	offset: 10,
	mouseOffset: true
};

////////////////////////////////////////////////////////////////////////////////
// Interface

var components = {
	curviness: {
		label: 'Curviness', type: 'slider',
		range: [0, 1]
	},
	distance: {
		label: 'Min Distance', type: 'number',
		steppers: true,
		min: 0,
		onChange: function(value) {
			tool.minDistance = value;
		}
	},
	mouseOffset: {
		label: 'Dynamic size', type: 'checkbox',
		onChange: function(checked) {
			palette.components.offset.enabled = !checked;
		}
	},
	offset: {
		label: 'Size', type: 'number',
		min: 0,
		enabled: false
	}
};

var palette = new Palette('Wave', components, values);

////////////////////////////////////////////////////////////////////////////////
// Mouse handling

var path;
function onMouseDown(event) {
	path = new Path();
}

var mul = 1;
function onMouseDrag(event) {
	var step = event.delta.clone();
	
	if (!values.mouseOffset)
		step.length = values.offset;

	var vector = step.rotate((90).toRadians() * mul);
	var segment = new Segment(event.point + vector);
	segment.handleIn = -event.delta * values.curviness;
	segment.handleOut = event.delta * values.curviness;
	path.add(segment);
	mul *= -1;
}