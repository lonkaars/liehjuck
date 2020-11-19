var boi;

function setup() {
	createCanvas(windowWidth, windowHeight);

	class camera {
		constructor() {
			this.x = windowWidth / 2;
			this.y = windowHeight / 2;
			this.cursorX = this.x;
			this.cursorY = this.y;
		}

		draw() {
			stroke(255, 0, 0);
			point(this.x, this.y);
		}

		move() {
			var dx = (this.cursorX - this.x) / 8
			var dy = (this.cursorY - this.y) / 8
			
			// stroke(0, 0, 255);
			// line(this.x, this.y, this.x + dx, this.y + dy);

			this.x += dx
			this.y += dy
		}

		drawCursor() {
			stroke(0, 255, 0);
			point(this.cursorX, this.cursorY);
		}

		moveCursor() {
			// this.cursorX = this.x
			// this.cursorY = this.y
			if (keyIsDown(UP_ARROW)) this.cursorY -= 10
			if (keyIsDown(DOWN_ARROW)) this.cursorY += 10
			if (keyIsDown(LEFT_ARROW)) this.cursorX -= 10
			if (keyIsDown(RIGHT_ARROW)) this.cursorX += 10
		}
	}
	boi = new camera();

	strokeWeight(2);
}

function draw() {
	background(0);
	boi.moveCursor();
	boi.move();
	boi.draw();
	// boi.drawCursor();
}


