echo "Chose branch:"
read branch
git checkout $branch
make clean
git add .
echo "Comment for the push:"
read comment
echo "$comment"
git commit -m "$branch - $(date) -- $comment"
git push
