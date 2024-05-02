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
        git checkout $BRANCH
        git pull origin $BRANCH
        git rebase $UPDATE_BRANCH
        if [ $? -ne 0 ]; then
            echo "Conflicts detected. Please resolve conflicts manually and continue the rebase."
            exit 2
        fi
        git push origin $BRANCH --force-with-lease
    fi
done

# Finally, checkout the original branch passed in
git checkout $UPDATE_BRANCH
echo "All branches updated successfully."
