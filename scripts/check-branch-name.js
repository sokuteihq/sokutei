const { execSync } = require('child_process')

const config = require('./config')

const branch = require('./lib/branch')

const CURRENT_BRANCH_COMMAND = 'git rev-parse --abbrev-ref HEAD';

(async function main () {
  const currentBranch = execSync(CURRENT_BRANCH_COMMAND, { encoding: 'utf-8' }).trim()

  await branch.checkBranchName(
    config.get('repository.owner'),
    config.get('repository.name'),
    config.get('branches.persistent'),
    currentBranch)
})()
