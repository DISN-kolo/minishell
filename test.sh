v="asd"
c='echo | < > echo $v'
$c
c="echo | < > echo $v"
$c
v="as\"d"
b="q\"we"
ls i$v$b
q="asd\nqwe"
echo $q
ls $q

cat << H1 && echo "hello" && cat << H2
asd
qwe
H1
zxc
123
H2
