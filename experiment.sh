#!/bin/bash

mkdir data_OnInterest
mkdir data_OnData

for i in `seq 1 1`
do
   echo $i
   ./waf --run="pitfull-dfn --time=1000 --intdelay=data_OnInterest/delay-int-pitfull-dfn-${i}.txt --contentdelay=data_OnData/delay-data-pitfull-dfn-${i}.txt --firstinterestdatadelay=data_RTT/delay-rtt-pitfull-dfn-${i}.txt"
   ./waf --run="pitless-dfn --time=1000 --intdelay=data_OnInterest/delay-int-pitless-dfn-${i}.txt --contentdelay=data_OnData/delay-data-pitless-dfn-${i}.txt --firstinterestdatadelay=data_RTT/delay-rtt-pitless-dfn-${i}.txt"
   ./waf --run="pitfull-att --time=1000 --intdelay=data_OnInterest/delay-int-pitfull-att-${i}.txt --contentdelay=data_OnData/delay-data-pitfull-att-${i}.txt --firstinterestdatadelay=data_RTT/delay-rtt-pitfull-att-${i}.txt"
   ./waf --run="pitless-att --time=1000 --intdelay=data_OnInterest/delay-int-pitless-att-${i}.txt --contentdelay=data_OnData/delay-data-pitless-att-${i}.txt --firstinterestdatadelay=data_RTT/delay-rtt-pitless-att-${i}.txt"
done
