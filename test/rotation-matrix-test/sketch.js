function rotateAroundOrigin(point, angle) {
	newCoords = [0, 0];
	newCoords[0] = Math.cos(angle) * point[0] - Math.sin(angle) * point[1];
	newCoords[1] = Math.sin(angle) * point[0] + Math.cos(angle) * point[1];
	return newCoords;
}

class box {
	constructor() {
		this.rotation = 0;
		this.vertices = [
			[-50, -50],
			[-50, 50 ],
			[50 , 50 ],
			[50 , -50]
		]
	}

	draw() {
		this.vertices.forEach((val, i) => {
			stroke(Math.floor((i+1) / this.vertices.length * 360), 100, 100);
			line(...this.vertices[i], ...this.vertices[(i+1) % this.vertices.length])
		});
	}

	rotate(rotation) {
		this.rotation += rotation;
		this.vertices.forEach((val, i) => {
			this.vertices[i] = rotateAroundOrigin(val, rotation);
		})
	}
}

var coolbox;
function setup() {
	createCanvas(windowWidth, windowHeight);
	colorMode(HSB);
	coolbox = new box();
}

function draw() {
	background(0);
	translate(windowWidth/2, windowHeight/2);
	scale(1, -1);
	strokeWeight(10);
	point(0, 0);
	strokeWeight(5);
	coolbox.rotate((mouseX - windowWidth/2) / 1000);
	coolbox.draw();
	// coolbox.rotation += 0.001;
}


