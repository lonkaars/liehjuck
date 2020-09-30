function rotate2D(point, angle) {
	newCoords = [0, 0];
	newCoords[0] = Math.cos(angle) * point[0] - Math.sin(angle) * point[1];
	newCoords[1] = Math.sin(angle) * point[0] + Math.cos(angle) * point[1];
	return newCoords;
}

class box {
	constructor() {
		this.rotation = [0, 0, 0];
		this.vertices = [
			[
				[-1.0, 1.0, 1.0],
				[1.0, -1.0, 1.0],
				[1.0, 1.0, 1.0]
			],
			[
				[1.0, -1.0, 1.0],
				[-1.0, -1.0, -1.0],
				[1.0, -1.0, -1.0]
			],
			[
				[-1.0, -1.0, 1.0],
				[-1.0, 1.0, -1.0],
				[-1.0, -1.0, -1.0]
			],
			[
				[1.0, 1.0, -1.0],
				[-1.0, -1.0, -1.0],
				[-1.0, 1.0, -1.0]
			],
			[
				[1.0, 1.0, 1.0],
				[1.0, -1.0, -1.0],
				[1.0, 1.0, -1.0]
			],
			[
				[-1.0, 1.0, 1.0],
				[1.0, 1.0, -1.0],
				[-1.0, 1.0, -1.0]
			],
			[
				[-1.0, 1.0, 1.0],
				[-1.0, -1.0, 1.0],
				[1.0, -1.0, 1.0]
			],
			[
				[1.0, -1.0, 1.0],
				[-1.0, -1.0, 1.0],
				[-1.0, -1.0, -1.0]
			],
			[
				[-1.0, -1.0, 1.0],
				[-1.0, 1.0, 1.0],
				[-1.0, 1.0, -1.0]
			],
			[
				[1.0, 1.0, -1.0],
				[1.0, -1.0, -1.0],
				[-1.0, -1.0, -1.0]
			],
			[
				[1.0, 1.0, 1.0],
				[1.0, -1.0, 1.0],
				[1.0, -1.0, -1.0]
			],
			[
				[-1.0, 1.0, 1.0],
				[1.0, 1.0, 1.0],
				[1.0, 1.0, -1.0]
			]
		]
	}

	scale(size) {
		this.vertices = this.vertices.map(tri => tri.map(vertex => vertex.map(pos => pos*size)));
	}
	translate(x, y, z) {
		this.vertices = this.vertices.map(tri => tri.map(vertex => [vertex[0] + x, vertex[1] + y, vertex[2] + z]));
	}

	_3DcoordTo2D(x, y, z) {
		// https://en.wikipedia.org/wiki/3D_projection#Perspective_projection
		var pos = [x, y, z]
		var camera = {
			displaySurface: [0, 0, -400],
			position: [0, 0, -500]
		}
		var d = pos.map((p, i) => p-camera.position[i]);
		return [
			(camera.displaySurface[2] / d[2]) * d[0] + camera.displaySurface[0],
			(camera.displaySurface[2] / d[2]) * d[1] + camera.displaySurface[1]
		];
	}

	draw() {
		stroke(255);
		this.vertices.forEach(tri => {
			tri.forEach((pos, i) => {
				line(...this._3DcoordTo2D(...tri[i]), ...this._3DcoordTo2D(...tri[(i+1)%tri.length]))
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
	coolbox.rotate([frameCount / 100, mouseY / 100, mouseX / 100]);
	coolbox.scale(100);
	coolbox.draw();
}


