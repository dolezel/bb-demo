const addon = require('bindings')('addon');
const MyObject = addon.MyObject;

const o1val = MyObject(11);
const o1 = {};
o1.value = MyObject.prototype.value;

console.log(o1.value.call(o1val));

try {
  console.log(o1.value());
} catch (e) {
  console.log(e.message);
}

console.log('------------------------');

const o2val = MyObject(12);
const o2 = {};
o2.value = o2val.value;

console.log(o2.value.call(o2val));

try {
  console.log(o2.value());
} catch (e) {
  console.log(e.message);
}

console.log('------------------------');

const o3val = MyObject(13);
const o3 = {};
o3.__proto__ = o3val;

console.log(o3.value.call(o3val));

try {
  console.log(o3.value());
} catch (e) {
  console.log(e.message);
}
