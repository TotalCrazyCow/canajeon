const { app, BrowserWindow, ipcMain } = require('electron/main')
const path = require('node:path')
const { Grid } = require("./build/Release/addon.node");

// the next value is updated upon request from renderer and passed to renderer
var step = 0
var frame = ""
let sol = new Grid();

const createWindow = () => {
	/* generates window with desired settings */
	const win = new BrowserWindow({
		width: 600,
		height: 600,
		webPreferences: {
			preload: path.join(__dirname, 'preload.js')
		}
	})
	win.loadFile('index.html')
}


const handleDrawReq = () => {
	return sol.drawNext()
}


app.whenReady().then(() => {
	/* a sort of main */

	// handle requests from renderer
	//ipcMain.handle('renderer:gimmeNext', handleNumberReq)
	ipcMain.handle('renderer:gimmeNext', handleDrawReq)

	createWindow()

	// for macos: if no window is open an you click on icon in dock,
	// open a new window
	app.on('activate', () => {
		if (BrowserWindow.getAllWindows().length === 0) {
			createWindow()
		}
	})

})


// for windows and linux: if no window open, terminate
app.on('window-all-closed', () => {
	if (process.platform !== 'darwin') {
		app.quit()
	}
})