/* define functions */

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
  const information = document.getElementById('info');
  information.innerText = `Message from main: ${newData}`
}


const doDaLoopin = async() => {
  /* time loop; this MUST be done in a async function
  as the sleep function returns a promise and needs an
  await (otherwise it behaves as if it were async */

  for (let cntr = 0; cntr < 100; ++cntr) {
    await sleep(1000).then(() => {fetchAndInject()});
  }

}



/* script */

doDaLoopin()
