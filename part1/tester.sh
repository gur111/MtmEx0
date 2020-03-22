#!/bin/bash


prog=./mtm_tot

for i in 1 2 3 4
do
  $prog < test$i.in > tmptest.out
  diff tmptest.out test$i.out
done