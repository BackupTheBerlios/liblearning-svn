#!/bin/sh
rm -f data/*
find .. -maxdepth 1 -name "*.hpp" -exec ./parse.pl {} template.html data \;
find ../bits -maxdepth 1 -name "*.hpp" -exec ./parse.pl {} template.html data \;
cp ../*.hpp ../bits/*.hpp data/
cp *.html data/
cat index.html | sed "s/::CREATED::/$(date)/g" >data/index.html

for i in $(ls *.html | grep -v index.html | grep -v template.html | grep -v template_page.html); do
	echo $i;
	./substitute.pl <$i >data/$i
done
