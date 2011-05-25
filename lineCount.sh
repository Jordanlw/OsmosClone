find . -type f| grep -v Compile.sh | grep -v .git | grep -v Resource | grep -v xOsmosClone | grep -v lineCount.sh |xargs cat | wc -l
