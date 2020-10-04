function rotate2D(point, angle) {
	newCoords = [0, 0];
	var cos = Math.cos(angle);
	var sin = Math.sin(angle);
	newCoords[0] = cos * point[0] - sin * point[1];
	newCoords[1] = sin * point[0] + cos * point[1];
	return newCoords;
}

class box {
	constructor() {
		this.rotation = [0, 0, 0];
		this.vertices = m // m is defined in model.js
	}

	scale(size) {
		this.vertices = this.vertices.map(tri => tri.map(vertex => vertex.map(pos => pos*size)));
	}
	translate(x, y, z) {
		this.vertices = this.vertices.map(tri => tri.map(vertex => [vertex[0] + x, vertex[1] + y, vertex[2] + z]));
	}

	_3DcoordTo2D(input) {
		// https://en.wikipedia.org/wiki/3D_projection#Perspective_projection
		var a = { x:input[0], y:input[1], z:input[2] } // point
		var c0 = { x:0, y:0, z:-500 } // camera pos
		var e = { x:0, y:0, z:-900 } // display surface
		var o = { x:(mouseY - (windowHeight / 2)) / 500, y:(mouseX - (windowWidth / 2)) / 500, z:0 } // camera rotation

		// wikipedia abbreviations
		var x = a.x - c0.x
		var y = a.y - c0.y
		var z = a.z - c0.z

		var s = {
			x: Math.sin(o.x),
			y: Math.sin(o.y),
			z: Math.sin(o.z)
		}

		var c = {
			x: Math.cos(o.x),
			y: Math.cos(o.y),
			z: Math.cos(o.z)
		}

		// camera transform
		var d = {
			x: c.y*(s.z*y + c.z*x) - s.y*z,
			y: s.x*(c.y*z + s.y*(s.z*y + c.z*x)) + c.x*(c.z*y - s.z*x),
			z: c.x*(c.y*z + s.y*(s.z*y + c.z*x)) - s.x*(c.z*y - s.z*x),
		}

		// screen coordinates
		var b = [
			(e.z / d.z) * d.x + e.x,
			(e.z / d.z) * d.y + e.y
		]

		return b;
	}

	draw() {
		stroke(255);
		strokeWeight(1);
		this.vertices.forEach(tri => {
			tri.forEach((pos, i) => {
				stroke(i * 120 + 120, 100, 100)
				line(...this._3DcoordTo2D(tri[i]), ...this._3DcoordTo2D(tri[(i+1)%tri.length]))
				// point(...this._3DcoordTo2D(...pos))
			})
		});
	}

	rotate(rotation) {
		this.rotation = this.rotation.map((r, i) => r += rotation[i]);
		this.vertices = this.vertices.map(tri => {
			return tri.map(pos => {
				var rz = rotate2D([pos[0], pos[1]], rotation[2])
				pos = [rz[0], rz[1], pos[2]];

				var ry = rotate2D([pos[0], pos[2]], rotation[1])
				pos = [ry[0], pos[1], ry[1]];

				var rx = rotate2D([pos[1], pos[2]], rotation[0])
				pos = [pos[0], rx[0], rx[1]];

				return pos;
			})
		});
	}
}

var coolbox;
function setup() {
	createCanvas(windowWidth, windowHeight);
	colorMode(HSB);
}

function draw() {
	background(0);
	translate(windowWidth/2, windowHeight/2);
	scale(1, -1);
	strokeWeight(10);
	strokeWeight(1);
	coolbox = new box();
	coolbox.scale(100);
	coolbox.rotate([1, 0, 0]);
	coolbox.draw();
}


