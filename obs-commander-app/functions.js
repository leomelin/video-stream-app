import osascript from 'node-osascript';
import fs from 'fs';
import util from 'util';

const readFile = util.promisify(fs.readFile);

async function getAppleScript(script) {
  return await readFile(`${script}.applescript`);
}

export const startStreaming = async () => {
  const startStream = await getAppleScript('start-stream');
  return new Promise((resolve, reject) => {
    osascript.execute(startStream, function (err, result, raw) {
      if (err) return reject(err);
      resolve({result, raw});
    });
  });
};
