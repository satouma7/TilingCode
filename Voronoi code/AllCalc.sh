make -B &&

for i in `seq 1 12`
do
./test_program -p0 $i -p1 0
done
    
# 13 - 17: Roi
for i in `seq 13 17`

do
./test_program -p0 $i -p1 0
done

# 13 - 17: Roi
for i in `seq 13 17`

do
./test_program -p0 $i -p1 1
done
