/*let canvas = document.getElementById("target_canvas");
canvas.height = innerHeight;
canvas.width = innerWidth;

let ctx = canvas.getContext("2d");

imgToRender = new Image();
imgToRender.onload = () => {
	ctx.drawImage(img, 0, 0);
};
imgToRender.src = "data:image/gif;base64,R0lGODlhCwALAIAAAAAA3pn/ZiH5BAEAAAEALAAAAAALAAsAAAIUhA+hkcuO4lmNVindo7qyrIXiGBYAOw==";
*/


const ctx = document.getElementById("targetcanvas").getContext("2d");
const img = new Image();
img.onload = () => {
    ctx.drawImage(img, 0, 0);
    ctx.beginPath();
    ctx.moveTo(30, 96);
    ctx.lineTo(70, 66);
    ctx.lineTo(103, 76);
    ctx.lineTo(170, 15);
    ctx.stroke();
};
img.src = "backdrop.png";



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
	imgToRender.src = "data:image/bmp;charset=utf-8;base64, ".concat(newData);
	//ctx.drawImage(imgToRender,0,0);
}

const doDaLoopin = async () => {

	/* time loop; this MUST be done in a async function
	as the sleep function returns a promise and needs an
	await (otherwise it behaves as if it were async */

	for (let cntr = 0; cntr < 10000; ++cntr) {
		await sleep(100).then(() => { 
			fetchAndInject() 
			console.log(cntr)
		});
		
	}

}

// script
//doDaLoopin()