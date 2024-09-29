rm resultLRU.csv
rm resultRR.csv

echo "Running cacheHits for LRU and RR"
echo "Testing LRU Caching..."

echo "Cache Size, LRU Cache Hit" >> resultLRU.csv

for i in {1..10};
do
  echo "0, $(./collatz 10000 1 500000 LRU 0)" >> resultLRU.csv
done
for i in {1..10};
do
  echo "10, $(./collatz 10000 1 500000 LRU 10)" >> resultLRU.csv
done
for i in {1..10};
do
  echo "100, $(./collatz 10000 1 500000 LRU 100)" >> resultLRU.csv
done
for i in {1..10};
do
  echo "1000, $(./collatz 10000 1 500000 LRU 1000)" >> resultLRU.csv
done
for i in {1..10};
do
  echo "2000, $(./collatz 10000 1 500000 LRU 2000)" >> resultLRU.csv
done
for i in {1..10};
do
  echo "3000, $(./collatz 10000 1 500000 LRU 3000)" >> resultLRU.csv
done
for i in {1..10};
do
  echo "4000, $(./collatz 10000 1 500000 LRU 4000)" >> resultLRU.csv
done
for i in {1..10};
do
  echo "5000, $(./collatz 10000 1 500000 LRU 5000)" >> resultLRU.csv
done

echo "Now testing RR Caching..."
echo "Cache Size, LRU Cache Hit" >> resultRR.csv

for i in {1..10};
do
  echo "0, $(./collatz 10000 1 500000 LRU 0)" >> resultRR.csv
done
for i in {1..10};
do
  echo "10, $(./collatz 10000 1 500000 LRU 10)" >> resultRR.csv
done
for i in {1..10};
do
  echo "100, $(./collatz 10000 1 500000 LRU 100)" >> resultRR.csv
done
for i in {1..10};
do
  echo "1000, $(./collatz 10000 1 500000 LRU 1000)" >> resultRR.csv
done
for i in {1..10};
do
  echo "2000, $(./collatz 10000 1 500000 LRU 2000)" >> resultRR.csv
done
for i in {1..10};
do
  echo "3000, $(./collatz 10000 1 500000 LRU 3000)" >> resultRR.csv
done
for i in {1..10};
do
  echo "4000, $(./collatz 10000 1 500000 LRU 4000)" >> resultRR.csv
done
for i in {1..10};
do
  echo "5000, $(./collatz 10000 1 500000 LRU 5000)" >> resultRR.csv
done

echo "Complete Analysis..."
