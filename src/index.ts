import * as crypto from 'crypto';

export class Module {
  private _initialized = false;
  private _count = 0;
  private _seed;

  public async init(): Promise<void> {
    this._initialized = true;
    this._seed = process.env.SEED || null;
  }

  public getCount(): number {
    return this._count;
  }

  public randomBytes(n: number): Buffer {
    this._count++;
    return crypto.randomBytes(n);
  }
}
