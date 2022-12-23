_=$(g++ test.cpp -o "test")
OUT=$(./test.exe)
if [[ $OUT == $(echo "hello world!") ]]; then
	echo success
else
	echo failure
fi