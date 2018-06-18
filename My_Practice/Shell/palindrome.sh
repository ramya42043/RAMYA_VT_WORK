echo "Enter a number:"
read -p "Number=>" number
temp=$number
reverse=0
while [ $temp -ne 0 ]
do
modulus=`expr $temp % 10`
mul=`expr $reverse \* 10`
reverse=`expr $mul + $modulus`
temp=`expr $temp / 10`
done
if [ $number -eq $reverse ]
then
echo "Palindrome"
else
echo "Not a palindrome"
fi
