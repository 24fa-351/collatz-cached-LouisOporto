rm log.csv
echo "Testing LRU caching technique"

echo "$(./collatz.exe 1000 1 500000 LRU 500000)" >> log.csv
