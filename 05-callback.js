const addon = require('bindings')('addon');
const RunCallback = addon.RunCallback;

RunCallback('hello world', (msg) => {
  console.log(msg);
});

try {
  RunCallback('hello', 'world');
} catch (e) {
  console.log(e.message)
}