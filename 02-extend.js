const addon = require('bindings')('addon');
const MyObject = addon.MyObject;

class eObject extends MyObject {
  constructor(v) {
    console.log(`constructor: ${v}`);
    super(v + 1);
  }
}

const eobj1 = new eObject(1);
const eobj2 = new eObject(2);

console.log(eobj1.value());
console.log(eobj2.value());
console.log(eobj1.value.call(eobj2));

const o = new eObject('a');
console.log(o.value());
