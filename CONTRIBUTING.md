# Contributing to Sokutei



**Table of Contents**
  * [Code Style](#code-style)
    * [Commit Messages](#commit-messages)
  * [Scripts](#scripts)
    * [Generate Branch Name](#generate-branch-name)



## Code Style

### Commit Messages

Commit messages follow the [Convetional Commits](https://www.conventionalcommits.org/en/v1.0.0/) specification.



## Scripts

### Generate Branch Name

Branches must be named according to the following convention:

~~~~
#<issue number>-<lowercase title of the issue with hyphens>[-index if multiple branches are created]
~~~~

Examples:

  * `#17-some-issue`,
  * `#17-some-issue-2`,
  * `#123-you_may-include-2838-numbers`

This is enforced using a `pre-push` hook.

You can use the `npm run generate:branch` command to automatically generate a new branch for an issue:

  * `npm run generate:branch -- 17`
    * Results in: `#17-some-issue`
  * `npm run generate:branch -- 17 2`
    * Results in: `#17-some-issue-2`
