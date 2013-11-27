cd ../test
FILES=($(ls | cut -d'.' -f1 | uniq))
cd ../compiler
mkdir error
make; mv mcc ./error
make clean
cd ../nas; make nas; mv nas ../compiler/error; make clean
cd ../test
for FILE in ${FILES[@]}
do
  cp $FILE.sc ../compiler/error
  cp $FILE.sample_out ../compiler/error
done
cd ../compiler/error
touch report
for FILE in ${FILES[@]}
do
  ./mcc $FILE.sc > $FILE.as
  ./nas $FILE.as > $FILE.output
  if diff $FILE.output $FILE.sample_out > $FILE.cmp
  then
    echo -e "\033[32mSuccess: $FILE\033[0m" >> report
    rm $FILE.sc; rm $FILE.as; rm $FILE.sample_out; rm $FILE.output; rm $FILE.cmp
  else
    echo -e "\033[31mFail: $FILE\033[0m" >> report
    mkdir $FILE
    mv $FILE.sc ./$FILE
    mv $FILE.as ./$FILE
    mv $FILE.sample_out ./$FILE
    mv $FILE.output ./$FILE
    mv $FILE.cmp ./$FILE
  fi
done
cd ..
cat ./error/report
