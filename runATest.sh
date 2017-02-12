fileInfo=$(du -sh $1)
echo -e "\n\n\nTesting with input file |$fileInfo|\n"
time sh 25381.sh $1