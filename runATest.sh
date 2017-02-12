fileSize=$(wc -c <$1)
if [ $fileSize -le 2000 ]; then
    fileInfo="$fileSize B\t$1"
else
	fileInfo=$(du -sh $1)
fi

echo -e "\n\n\nTesting with input file |$fileInfo|\n"
time sh 25381.sh $1