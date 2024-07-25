var FRAMERATE = 60 // frame per second

let ctx = target_canvas.getContext("2d");
target_canvas.width = 500;
target_canvas.height = 500;

var image = new Image();

// get fresh data before animation begins
const fetchAndInject = async () => {

	const newData = await window.mainAPI.fetchNext();
	image.src = "data:image/bmp;charset=utf-8;base64, ".concat(newData);
}

function frame() {

	fetchAndInject();
	//wipe off canvas before each redraw
	ctx.clearRect(0, 0, target_canvas.width, target_canvas.height);

	ctx.drawImage(image, 0, 0);
}

setInterval(frame, 1000 / FRAMERATE) 