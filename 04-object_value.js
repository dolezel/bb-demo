const addon = require('bindings')('addon');
const PropObject = addon.PropObject;

const o1 = new PropObject(1);
const o2 = new PropObject(2);

console.log(o1.value);
console.log(o2.value);

o1.value = 10;
console.log(o1.value);

console.log('------------------------');

console.log(o1.nonExistentProperty);
o1.nonExistentProperty = 'abc';
console.log(o1.nonExistentProperty);
