function sleep(ms) {
	
	/* use: sleep(xxx).then(do_something()) 
	to execute a function do_something after xxx seconds.
	IMPORTANT: the whole block behaves asyncronously,
	that is whatever statement comes after sleep(..).then(...)
	is executed immediately! 
	> If you want this function to actually halt execution,
	  you need to call this with await in a async env */
	return new Promise(resolve => setTimeout(resolve, ms));
}

const fetchAndInject = async () => {

	// fetch from main
	const newData = await window.mainAPI.fetchNext();
	// inject
	var canvas = document.getElementById("target_canvas");
	canvas.width = 800;
	canvas.height = 600;
	var ctx = canvas.getContext("2d");
	var image = new Image();

	image.onload = function() {
		ctx.drawImage(image, 0, 0);
	};
	image.src = "data:image/bmp;charset=utf-8;base64, ".concat(newData);
}

const doDaLoopin = async () => {

	/* time loop; this MUST be done in a async function
	as the sleep function returns a promise and needs an
	await (otherwise it behaves as if it were async */

	for (let cntr = 0; cntr < 10000; ++cntr) {
		await sleep(100).then(() => { 
			fetchAndInject() 
		});
		
	}

}

// script
doDaLoopin()