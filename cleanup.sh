# Remove the history from 
rm -rf .git

# recreate the repos from the current content only
git init

#git config --global user.email "you@example.com"
#git config --global user.name "Your Name"
# to set your account's default identity.
# Omit --global to set the identity only in this repository. 

git config user.email "moxoron@gmail.com"
git config user.name "bdpx"
echo user info added

# push to the github remote repos ensuring you overwrite history
git remote add origin git@github.com:bdpx/bdpx.github.io.git
echo remote added

git commit --allow-empty -m "root commit"
echo empty commit added

git add --all .
git add -f ./postrisc/build/.gitignore
echo content added

git commit -m "cleanup"
git push -u --force origin master