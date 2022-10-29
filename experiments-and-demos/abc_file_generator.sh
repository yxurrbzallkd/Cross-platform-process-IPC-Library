n=$1; shift
files=$@

echo $n
echo $files

for file in $files
do
	echo processing $file
	echo > $file
	for letter in {a..z}
	do
		s=$letter
		k=$RANDOM
		let "k %= $n"
		for i in $(seq $k)
		do
		   s="$s$letter"
		done
		echo $s >> $file
	done
done
