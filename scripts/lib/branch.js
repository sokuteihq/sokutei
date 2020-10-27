const issue = require('./issue')

/**
 * Matches branch names like this:
 *   * #1-some-branch
 *   * #127-another-very-nice98_asd-branch
 *   * #17-asd-2
 * Test at https://regexr.com/51eee
 */
const EPHEMERAL_BRANCH_REGEX = /^#([1-9][0-9]*)-((?:[a-z0-9_]+-)*?[a-z0-9_]+?)(?:-([1-9][0-9]*))?$/g

async function branchNameForIssue (owner, repository, issueNumber, index) {
  const i = await issue.retrieveOpenIssueByNumber(owner, repository, issueNumber)

  if (!i) {
    return null
  }

  const namePart = i.title
    .toLowerCase()
    .replace(/[ :,/]/g, '-')

  const unindexed = `#${i.number}-${namePart}`

  if (index === undefined) {
    return unindexed
  } else {
    return `${unindexed}-${index}`
  }
}

async function hasIssueForBranch (owner, repository, actualBranchName) {
  const split = splitBranchName(actualBranchName)

  if (!split) {
    return false
  }

  return issue.retrieveOpenIssueByNumber(owner, repository, split.number)
}

function splitBranchName (branchName) {
  EPHEMERAL_BRANCH_REGEX.lastIndex = 0
  const result = EPHEMERAL_BRANCH_REGEX.exec(branchName)

  if (!Array.isArray(result) || result.length < 3) {
    return null
  }

  return {
    number: result[1],
    title: result[2],
    index: result[3]
  }
}

function guardInvalidBranchName (persistentBranches, currentBranch) {
  console.log(`
The name of the current branch "${currentBranch}" does not match the branch naming policy.
The branch name must
  * either match one of the persistent names: 
  
      ${persistentBranches.join(', ')}
  * or match an ephemeral name enforced by the following regex: 
    
      ${EPHEMERAL_BRANCH_REGEX.toString()} (test at https://regexr.com/51eee)
`)

  process.exit(1)
}

async function guardNoIssueForBranch (owner, repository, actualBranchName) {
  const openIssues = (await issue.retrieveAllOpenIssues(owner, repository))
    .map(i => `#${i.number} - ${i.title}`)

  console.log(`
There is no open issue with the number set in the current branch "${actualBranchName}".
Open issues:
  * ${openIssues.join('\n  * ')}
`)

  process.exit(1)
}

function guardBranchTitleDoesNotMatchExpected (expectedBranchTitle, actualBranchTitle) {
  console.log(`
The title part of the current branch does not match the one generated using the title of the issue.
  Actual: "${actualBranchTitle}"
  Expected: "${expectedBranchTitle}"
`)

  process.exit(1)
}

async function checkBranchName (owner, repository, persistentBranches, actualBranchName) {
  if (persistentBranches.includes(actualBranchName)) {
    return
  }

  if (!actualBranchName.match(EPHEMERAL_BRANCH_REGEX)) {
    guardInvalidBranchName(persistentBranches, actualBranchName)
  }

  if (!(await hasIssueForBranch(owner, repository, actualBranchName))) {
    guardNoIssueForBranch(owner, repository, actualBranchName)
  }

  const actualSplit = splitBranchName(actualBranchName)
  const expectedBranchName = await branchNameForIssue(owner, repository, actualSplit.number)
  const expectedSplit = splitBranchName(expectedBranchName)

  if (expectedSplit.title !== actualSplit.title) {
    guardBranchTitleDoesNotMatchExpected(expectedSplit.title, actualSplit.title)
  }
}

module.exports = {
  branchNameForIssue,
  hasIssueForBranch,
  splitBranchName,
  checkBranchName
}
