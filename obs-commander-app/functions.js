import osascript from 'node-osascript';
import fs from 'fs';
import util from 'util';

const readFile = util.promisify(fs.readFile);
const writeFile = util.promisify(fs.writeFile);

async function getAppleScript(script) {
  return await readFile(`${script}.applescript`);
}

export const startStreaming = async () => {
  const startStream = await getAppleScript('start-stream');
  return new Promise((resolve, reject) => {
    osascript.execute(startStream, function (err, result, raw) {
      if (err) return reject(err);
      resolve({ result, raw });
    });
  });
};

export const setYoutubeStreamKey = async (streamKey) => {
  const serviceConfig = '/Users/leo.melin/Library/Application\ Support/obs-studio/basic/profiles/Kokeilu/service.json';
  const contents = JSON.parse((await readFile(serviceConfig)).toString());
  contents.settings.key = streamKey;
  return writeFile(serviceConfig, JSON.stringify(contents, null, 2), 'utf8');
};
