#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <branch-name>"
    exit 1
fi

UPDATE_BRANCH=$1
BRANCHES=("main" "dev" "docs")

git fetch origin

for BRANCH in "${BRANCHES[@]}"; do
    if [ "$BRANCH" != "$UPDATE_BRANCH" ]; then
        echo "Updating branch $BRANCH with changes from $UPDATE_BRANCH..."

        git stash push --include-untracked --all
        echo "Stashed all changes and untracked files."

        git checkout $BRANCH || {
            echo "Failed to checkout $BRANCH. Aborting update."
            git stash pop
            continue
        }

        echo "Cleaning and resetting submodules..."
        git submodule foreach --recursive 'git clean -fdx && git reset --hard'
        git submodule update --init --recursive

        git pull origin $BRANCH

        git rebase $UPDATE_BRANCH || {
            echo "Conflicts detected. Please resolve conflicts manually."
            git rebase --abort
            git stash pop
            exit 2
        }

        git push origin $BRANCH --force-with-lease
        echo "$BRANCH successfully updated and pushed."


        git stash pop
        echo "Restored previously stashed changes."
    fi
done
git checkout $UPDATE_BRANCH
echo "All branches updated successfully."
