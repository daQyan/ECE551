echo "Test started"
for i in {1..4..1}
do 
    echo "container$i":
    ./"container$i"

done
echo "Test ended"
