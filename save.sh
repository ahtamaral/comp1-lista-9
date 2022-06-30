#!/bin/bash

# This script assumes a configured github account and a SSH key registered on it.

if [[ `git status --porcelain` ]]; then
	printf "Changes were found on the repository. Saving on remote.\n"
	git add .
	git commit -m "Adding zettels."
	git push
else
	printf "No changes were found on the repository. Nothing to do.\n"
fi
