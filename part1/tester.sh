#!/bin/bash
# The output of this script should be empty if it succeeds
# To run this script of the csl3 do the following (while you're in the folder with the executable and the test files):
# `http://pastebin.com/raw/4UCQDwa2 | sh -`

prog=./mtm_tot

for i in 1 2 3 4; do
  $prog <test$i.in >tmptest.out
  diff tmptest.out test$i.out
done
