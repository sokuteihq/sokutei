const convict = require('convict')

const config = convict({
  repository: {
    owner: {
      doc: 'The owner of the repository.',
      format: String,
      default: 'sokuteihq'
    },
    name: {
      doc: 'The name of the repository.',
      format: String,
      default: 'sokutei'
    }
  },
  branches: {
    persistent: {
      doc: 'Array of persistent branches, such as master, dev etc.',
      default: ['master', 'release']
    }
  }
})

config.validate({
  allowed: 'strict'
})

module.exports = config
