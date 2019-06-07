import 'mocha';
import * as assert from 'assert';

import * as js from '../src';

const native = require('../build/Release/module');

const modules = { native, js };

// tslint:disable-next-line:forin
for (const name in modules) {

  const { Module } = modules[name];

  describe(`${name} module instanciation`, () => {

    it('Class "Module" should be instanciable', () => {
      let m;
      assert.equal(typeof Module, 'function');
      assert.doesNotThrow(() => m = new Module);
      assert(m.__proto__);
    });

    it('Class "Module" should throw if called without new', () => {
      assert.equal(typeof Module, 'function');
      assert.throws(() => Module());
    });

    ['init', 'getCount', 'randomBytes'].forEach((prop) => {
      const m = new Module();
      it(`My instance should have a "${prop}" function as property`, () => {
        assert(m[prop], `missing "${prop}" property`);
        assert.equal(typeof m[prop], 'function', `The "${prop}" property must be a function`);
      });
    });

    const mod = new Module();
    it('init should not throw if called', () => {
      assert.doesNotThrow(() => mod.init());
    });

    it('getCount should increment when randomBytes called', () => {
      assert.equal(mod.getCount(), 0);
      assert.doesNotThrow(() => mod.randomBytes(9));
      assert.equal(mod.getCount(), 1);
    });

    it('randomBytes should return buffer', () => {
      const buf: Buffer = mod.randomBytes(9);
      assert.equal(buf.length, 9);
    });

  });

}
