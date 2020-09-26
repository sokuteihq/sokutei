const got = require('got')

const request = got.extend({
  prefixUrl: 'https://api.github.com',
  headers: {
    accept: 'application/vnd.github.v3+json'
  },
  responseType: 'json'
})

let openIssues = null

async function retrieveAllOpenIssues (owner, repository) {
  if (!openIssues) {
    const path = `repos/${owner}/${repository}/issues?state=open`

    try {
      const response = await request(path)

      openIssues = response.body
        .filter(issue => !issue.pull_request)
    } catch {
      openIssues = []
    }
  }

  return openIssues
}

async function retrieveOpenIssueByNumber (owner, repository, issueNumber) {
  let issue
  if (!openIssues) {
    const path = `repos/${owner}/${repository}/issues/${issueNumber}`

    try {
      const response = await request(path)

      issue = response.body
    } catch {
      return null
    }
  } else {
    issue = openIssues.find(i => i.number === issueNumber)
  }

  if (issue.state !== 'open') {
    return null
  }

  if (issue.pull_request) {
    return null
  }

  return issue
}

module.exports = {
  retrieveAllOpenIssues,
  retrieveOpenIssueByNumber
}
