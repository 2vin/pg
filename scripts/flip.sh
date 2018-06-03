DIR=`pwd`
cd $1

for i in *.jpg;
do 
	$DIR/../bin/flip $i $2 $3;
done
	

