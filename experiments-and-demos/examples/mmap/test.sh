for f in "a" "b" "c" "d"
do
	echo $f
	if [ $f == "a" ]
	then
		echo "contains 1 global variable - a list of 10 integers and mmaps file.txt"
	fi
	if [ $f == "b" ]
	then
		echo "mmaps file.txt"
	fi
	if [ $f == "c" ]
	then
		echo "mmaps an anonymous region of size of file.txt with MAP_PRIVATE flag"
	fi
	if [ $f == "d" ]
	then
		echo "mmaps an anonymous region of size of file.txt with MAP_PRIVATE"
	fi
	$(g++ $f.cpp -o $f -W)
	$(size -A -d $f > $f.txt)
	cat $f.txt
	#cat $f.txt | grep -E 'Total|.text'
	#rm $f.txt $f
done




