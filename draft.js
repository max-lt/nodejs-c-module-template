// import { Module } from './build/Release/module';
const mod = require('./build/Release/module');

console.log({ mod });

const { Module } = mod;

// console.log(Module());

function gc() {
  if (global.gc) {
    global.gc();
  } else {
    console.log('Garbage collection unavailable.  Pass --expose-gc when launching node to enable forced garbage collection.');
  }
}

let m1 = new Module();
let m2 = new Module();

console.log({ m1, m2 });

console.log(m1.init());
console.log(m2.init());
console.log(m1.randomBytes(7));
console.log(m1.randomBytes(5));
console.log(m2.randomBytes(9));
console.log('count m1', m1.getCount());
console.log('count m2', m2.getCount());

m1 = null;

gc();

m2 = null;

setTimeout(gc, 1000);

setTimeout(() => console.log('done.'), 3000);
