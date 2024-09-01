#!/bin/bash
make all
##base option test

#stack

./dbms -f a.dat -q 'SPUSH mystack a'
./dbms -f a.dat -q 'SPUSH mystack b'
./dbms -f a.dat -q 'SPUSH mystack c'
./dbms -f a.dat -q 'SPUSH mystack d'

./dbms -f a.dat -q 'SPOP mystack'
./dbms -f a.dat -q 'SPOP mystack'
./dbms -f a.dat -q 'SPOP mystack'
./dbms -f a.dat -q 'SPOP mystack'

#set

./dbms -f a.dat -q 'SADD myset a'
./dbms -f a.dat -q 'SADD myset b'
./dbms -f a.dat -q 'SADD myset c'
./dbms -f a.dat -q 'SADD myset d'

./dbms -f a.dat -q 'SISMEMBER myset a'
./dbms -f a.dat -q 'SISMEMBER myset b'
./dbms -f a.dat -q 'SISMEMBER myset c'
./dbms -f a.dat -q 'SISMEMBER myset d'

./dbms -f a.dat -q 'SREM myset a'
./dbms -f a.dat -q 'SREM myset b'
./dbms -f a.dat -q 'SREM myset c'
./dbms -f a.dat -q 'SREM myset d'

#queue

./dbms -f a.dat -q 'QPUSH myqueue a'
./dbms -f a.dat -q 'QPUSH myqueue b'
./dbms -f a.dat -q 'QPUSH myqueue c'
./dbms -f a.dat -q 'QPUSH myqueue d'

./dbms -f a.dat -q 'QPOP myqueue'
./dbms -f a.dat -q 'QPOP myqueue'
./dbms -f a.dat -q 'QPOP myqueue'
./dbms -f a.dat -q 'QPOP myqueue'

#hashmap

./dbms -f a.dat -q 'HSET mymap a w'
./dbms -f a.dat -q 'HSET mymap b x'
./dbms -f a.dat -q 'HSET mymap c y'
./dbms -f a.dat -q 'HSET mymap d z'

./dbms -f a.dat -q 'HGET mymap a'
./dbms -f a.dat -q 'HGET mymap b'
./dbms -f a.dat -q 'HGET mymap c'
./dbms -f a.dat -q 'HGET mymap d'

./dbms -f a.dat -q 'HDEL mymap a'
./dbms -f a.dat -q 'HDEL mymap b'
./dbms -f a.dat -q 'HDEL mymap c'
./dbms -f a.dat -q 'HDEL mymap d'

##null test

./dbms -f a.dat -q 'SPOP nmystack'
./dbms -f a.dat -q 'SREM nmyset d'
./dbms -f a.dat -q 'QPOP nmyqueue'
./dbms -f a.dat -q 'HDEL nmymap a'

./dbms -f a.dat -q 'SISMEMBER nmyset d'
./dbms -f a.dat -q 'HGET nmymap e'

##incorrect option test

#set

./dbms -f a.dat -q 'SADD myset a'
./dbms -f a.dat -q 'SADD myset b'
./dbms -f a.dat -q 'SADD myset c'
./dbms -f a.dat -q 'SADD myset d'

./dbms -f a.dat -q 'SISMEMBER myset t'
./dbms -f a.dat -q 'SREM myset t'

#hashmap

./dbms -f a.dat -q 'HSET mymap a w'
./dbms -f a.dat -q 'HSET mymap b x'
./dbms -f a.dat -q 'HSET mymap c y'
./dbms -f a.dat -q 'HSET mymap d z'

./dbms -f a.dat -q 'HGET mymap t'
./dbms -f a.dat -q 'HDEL mymap t'

make clear
