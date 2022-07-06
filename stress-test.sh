for ((i=1;;i++)); do
  echo $i
  ./C
  ./A > out2
  ./B > out1
  diff -w out1 out2 || break;
done