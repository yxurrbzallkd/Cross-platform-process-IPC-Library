minix_dir="C:\Users\Diana\Desktop\OS\minix\MINIX-LCOM\shared"
minix_dir="/mnt/c/Users/Diana/Desktop/OS/minix/MINIX-LCOM/shared"


ls $minix_dir

for var in "$@"
do
	if [[ -d $var ]]
	then
		cp -r $var $minix_dir
	else
		cp $var $minix_dir
	fi
done

ls $minix_dir