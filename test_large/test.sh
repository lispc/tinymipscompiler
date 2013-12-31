cd ../nas; make nas > /dev/null; mv nas ../test_large; make clean
cd ../compiler; make mcc > /dev/null; mv mcc ../test_large; make clean
cd ../test_large;
./mcc sorting.sc > sorting.as
#./nas sorting.as
