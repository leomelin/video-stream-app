const fs = require('fs');
const util = require('util');
const osascript = require('node-osascript');

const readFile = util.promisify(fs.readFile);

async function getAppleScript(script) {
  return await readFile(`${script}.applescript`);
}

(async () => {
  const startStream = await getAppleScript('start-stream');
  osascript.execute(startStream, function (err, result, raw) {
    if (err) return console.error(err);
    console.log(result, raw);
  });
})();



