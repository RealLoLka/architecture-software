wrk -d 20 -t 10 -c 10 --latency -s ./cache.lua http://localhost:8080/