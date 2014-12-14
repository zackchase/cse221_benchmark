#!/bin/bash

for i in {11..30}
do
	new=foo$i.txt
	cp foo1.txt $new
    echo "finished" $new
done