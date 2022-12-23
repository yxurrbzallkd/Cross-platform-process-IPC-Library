g++ piping_test.cpp -o piping_test
mkdir "test"
cd "test"
touch hello.txt
echo hello world > hello.txt
touch redme.md
echo hello Diana > name_hello.txt
cd ..
X=$(./piping_test test)
if [[ $X == $(ls "test" | grep .txt | ./rw | wc) ]]; then
	echo success
else
	echo failure
fi
rm -r "test"
