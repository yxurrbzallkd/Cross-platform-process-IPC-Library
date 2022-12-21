ERRORS_FILE="ERRORS.txt"
EXENAME="basic_process_test";
g++ basic_process_test.cpp -o $EXENAME

echo Basic tests:

TESTS=("echo hello world" "ls" "ls -l");
for i in ${!TESTS[@]}; do
	COMMAND=${TESTS[$i]}
	OUT_P=$(./$EXENAME $COMMAND)
	OUT=$($COMMAND)
	STRING="Test $i : $COMMAND"
	if [[ $OUT_P == $OUT ]]
	then echo $STRING - success
	else 
		echo $STRING - failure
	fi
done;

echo
echo Forwarding tests:

FILE=file.txt
CMD_FILE=cmdfile.txt

touch $FILE
touch $CMD_FILE

#!!! Problem: bash probably steals the forwarding from the command

COMMAND="echo hello world"
FORWARD_TESTS=(">" ">>");
for i in ${!FORWARD_TESTS[@]}; do
	flag=${FORWARD_TESTS[$i]}
	OUT_P=$(./$EXENAME $COMMAND $flag $FILE)
	OUT=$($COMMAND $flag $CMD_FILE)
	STRING="Test $i : $COMMAND $flag <file>"
	diff  $FILE  $CMD_FILE >>$ERRORS_FILE 2>&1
	if [[ $? -ne 0 ]]
	then echo $STRING - failure
	else 
		echo $STRING - success
	fi
done;

rm $EXENAME $FILE $CMD_FILE $ERRORS_FILE
