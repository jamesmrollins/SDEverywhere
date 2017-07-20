const path = require('path')
const sh = require('shelljs')
const { modelPathProps, buildDir } = require('./Helpers')

let command = 'clean <model>'
let describe = 'clean out the build, output, and html directories for a model'
let builder = {
  modeldir: {
    describe: 'model directory',
    type: 'string',
    alias: 'm'
  }
}
let handler = argv => {
  clean(argv.model, argv)
}
let clean = (model, opts) => {
  // Remove the directories generated by SDEverywhere.
  let { modelDirname, modelName, modelPathname } = modelPathProps(model)
  let buildDirname = path.join(opts.modeldir || modelDirname, 'build')
  let outputDirname = path.join(opts.modeldir || modelDirname, 'output')
  let htmlDirname = path.join(opts.modeldir || modelDirname, 'html')
  let silentState = sh.config.silent
  sh.config.silent = true
  sh.rm('-r', buildDirname)
  sh.rm('-r', outputDirname)
  sh.rm('-r', htmlDirname)
  sh.config.silent = silentState
}
module.exports = {
  command,
  describe,
  builder,
  handler,
  clean
}
