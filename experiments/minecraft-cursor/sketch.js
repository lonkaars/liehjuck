function draw_cursor(rx, ry) {
	var length = 30;
	var updown = constrain(ry, -Math.PI/2, Math.PI/2);
	translate(windowWidth / 2, windowHeight / 2);
	stroke(0, 0, 255);

	var z = [0, Math.cos(updown) * -length];
	line(0, 0, z[0], z[1]);

	console.log(updown)
	var x = [Math.sin(rx) * length,  Math.cos(rx) * length * (updown / (Math.PI / 2))];
	var y = [Math.cos(rx) * length, -Math.sin(rx) * length * (updown / (Math.PI / 2))];

	stroke(255, 0, 0);
	line(0, 0, x[0], x[1]);
	stroke(0, 255, 0);
	line(0, 0, y[0], y[1]);
}

function setup() {
	createCanvas(windowWidth, windowHeight);
}

function draw() {
	background(0);
	var rx = (mouseX - windowWidth / 2) / 100;
	var ry = (mouseY - windowHeight / 2) / 100;
	strokeWeight(4);
	draw_cursor(rx, ry);
}

