# Template module in C
## Prerequisite

node 10, npm, compiler C/C++

## Development mode:
#### Install the node packages:
    $ npm install

#### Build 
    npx node-gyp configure build

#### Run development draft: 
    SEED='secret' node --expose-gc draft.js

#### Setup development environment (vscode + nvm)

In the `".vscode/c_cpp_properties.json"` file add `"/path/to/.nvm/versions/node/v10.9.0/include/node"`
