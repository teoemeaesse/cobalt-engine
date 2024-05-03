#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

if [ "$#" -ne 1 ]; then
    echo -e "${RED}Usage: $0 <branch-name>${NC}"
    exit 1
fi

UPDATE_BRANCH=$1
BRANCHES=("main" "dev" "docs")

echo -e "${GREEN}Fetching the latest updates from the origin...${NC}"
git fetch origin

for BRANCH in "${BRANCHES[@]}"; do
    if [ "$BRANCH" != "$UPDATE_BRANCH" ]; then
        echo -e "${GREEN}Updating branch $BRANCH with changes from $UPDATE_BRANCH...${NC}"

        echo -e "${GREEN}Stashing all changes and untracked files...${NC}"
        git stash push --include-untracked --all

        git checkout $BRANCH || {
            echo -e "${RED}Failed to checkout $BRANCH. Aborting update.${NC}"
            git stash pop
            continue
        }

        echo -e "${GREEN}Cleaning and resetting submodules...${NC}"
        git submodule foreach --recursive 'git clean -fdx && git reset --hard'
        git submodule update --init --recursive

        echo -e "${GREEN}Pulling latest changes for $BRANCH...${NC}"
        git pull origin $BRANCH

        echo -e "${GREEN}Rebasing $BRANCH onto $UPDATE_BRANCH...${NC}"
        git rebase $UPDATE_BRANCH || {
            echo -e "${RED}Conflicts detected. Please resolve conflicts manually and continue the rebase.${NC}"
            git rebase --abort
            git stash pop
            exit 2
        }

        echo -e "${GREEN}Pushing updated $BRANCH to origin...${NC}"
        git push origin $BRANCH --force-with-lease
        echo -e "${GREEN}$BRANCH successfully updated and pushed.${NC}"

        echo -e "${GREEN}Restoring previously stashed changes...${NC}"
        git stash pop
    fi
done

echo -e "${GREEN}Checking out back to $UPDATE_BRANCH...${NC}"
git checkout $UPDATE_BRANCH
echo -e "${GREEN}All branches updated successfully.${NC}"
