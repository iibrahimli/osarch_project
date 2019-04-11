#! /bin/bash

for test in test/test-*.sh; do
    ./$test > /dev/null \
    && echo "$test passed" \
    || echo "$test failed";
done

# clean up after tests
mkdir -p test_logs
mv -f *.log test_logs 2> /dev/null

if ls *.tmp >/dev/null 2>&1
then
   rm -f *.tmp
fi

# tidy up after coverage run
mkdir -p cov

if ls build/src/*.gc* >/dev/null 2>&1
then
    mv -f build/src/*.gc* cov 2> /dev/null
fi