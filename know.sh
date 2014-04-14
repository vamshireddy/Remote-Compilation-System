
counter=0

ipprefix="12.34.8."

while [ $counter -lt 1 ]
do
	a=`expr $RANDOM % 256`
	b=`expr $RANDOM % 256`
	c=`expr $RANDOM % 256`
	d=`expr $RANDOM % 256`
	ip="$a.$b.$c.$d"
	echo "Ip Address is $ip"
	echo
	echo "`whois $ip|grep 'NetRange:\|OrgName'`" >> ip
	counter=`expr $counter + 1`
done

