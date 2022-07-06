for f in mediantest/*.in; do
	echo "${f%%.*}";
	cat $f > test.in;
	time ./A;
	diff -w "${f%%.*}.out" test.out || break;
done
