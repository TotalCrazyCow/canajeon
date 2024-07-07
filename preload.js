const { contextBridge, ipcRenderer } = require('electron/renderer')

// expose stuff from main to renderer and prepare message passing
contextBridge.exposeInMainWorld('mainAPI', {
  fetchNext: () => ipcRenderer.invoke('renderer:gimmeNext') // renderer asks for next, main gives
})

