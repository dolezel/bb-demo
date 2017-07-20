const addon = require('bindings')('addon');
const MyObject = addon.MyObject;

const obj = new MyObject(10);
console.log(obj.plusOne()); // 11
console.log(obj.plusOne()); // 12
console.log(obj.plusOne()); // 13

console.log(obj.multiply().value()); // 13
console.log(obj.multiply(10).value()); // 130

const newobj = obj.multiply(-1);
console.log(newobj.value()); // -13
console.log(obj === newobj); // false

console.log('------------------------');

console.log(obj.val);
console.log(obj.val = 10);
console.log(obj.val);

console.log('------------------------');

const obj1 = MyObject(1);
const obj2 = MyObject(2);

console.log(obj1.value());
console.log(obj2.value());
console.log(obj1.value.call(obj2));
