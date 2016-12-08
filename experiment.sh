#!/bin/bash

mkdir data_OnInterest
mkdir data_OnData
mkdir data_RTT

for i in `seq 1 10`
do
   echo $i

   echo ./waf --run="pitfull-dfn --time=1000 --intdelay=data_OnInterest/delay-int-pitfull-dfn-${i}.txt --contentdelay=data_OnData/delay-data-pitfull-dfn-${i}.txt --rttdelay=data_RTT/delay-rtt-pitfull-dfn-${i}.txt"
   ./waf --run="pitfull-dfn --time=1000 --intdelay=data_OnInterest/delay-int-pitfull-dfn-${i}.txt --contentdelay=data_OnData/delay-data-pitfull-dfn-${i}.txt --rttdelay=data_RTT/delay-rtt-pitfull-dfn-${i}.txt"

   echo ./waf --run="pitless-dfn --time=1000 --intdelay=data_OnInterest/delay-int-pitless-dfn-${i}.txt --contentdelay=data_OnData/delay-data-pitless-dfn-${i}.txt --rttdelay=data_RTT/delay-rtt-pitless-dfn-${i}.txt"
   ./waf --run="pitless-dfn --time=1000 --intdelay=data_OnInterest/delay-int-pitless-dfn-${i}.txt --contentdelay=data_OnData/delay-data-pitless-dfn-${i}.txt --rttdelay=data_RTT/delay-rtt-pitless-dfn-${i}.txt"

   echo ./waf --run="pitless-hybrid-dfn --time=1000 --intdelay=data_OnInterest/delay-int-pitless-hybrid-dfn-${i}.txt --contentdelay=data_OnData/delay-data-pitless-hybrid-dfn-${i}.txt --rttdelay=data_RTT/delay-rtt-pitless-hybrid-dfn-${i}.txt"
   ./waf --run="pitless-hybrid-dfn --time=1000 --intdelay=data_OnInterest/delay-int-pitless-hybrid-dfn-${i}.txt --contentdelay=data_OnData/delay-data-pitless-hybrid-dfn-${i}.txt --rttdelay=data_RTT/delay-rtt-pitless-hybrid-dfn-${i}.txt"

   echo ./waf --run="pitfull-att --time=1000 --intdelay=data_OnInterest/delay-int-pitfull-att-${i}.txt --contentdelay=data_OnData/delay-data-pitfull-att-${i}.txt --rttdelay=data_RTT/delay-rtt-pitfull-att-${i}.txt"
   ./waf --run="pitfull-att --time=1000 --intdelay=data_OnInterest/delay-int-pitfull-att-${i}.txt --contentdelay=data_OnData/delay-data-pitfull-att-${i}.txt --rttdelay=data_RTT/delay-rtt-pitfull-att-${i}.txt"

   echo ./waf --run="pitless-att --time=1000 --intdelay=data_OnInterest/delay-int-pitless-att-${i}.txt --contentdelay=data_OnData/delay-data-pitless-att-${i}.txt --rttdelay=data_RTT/delay-rtt-pitless-att-${i}.txt"
   ./waf --run="pitless-att --time=1000 --intdelay=data_OnInterest/delay-int-pitless-att-${i}.txt --contentdelay=data_OnData/delay-data-pitless-att-${i}.txt --rttdelay=data_RTT/delay-rtt-pitless-att-${i}.txt"

   echo ./waf --run="pitless-hybrid-att --time=1000 --intdelay=data_OnInterest/delay-int-pitless-hybrid-att-${i}.txt --contentdelay=data_OnData/delay-data-pitless-hybrid-att-${i}.txt --rttdelay=data_RTT/delay-rtt-pitless-hybrid-att-${i}.txt"
   ./waf --run="pitless-hybrid-att --time=1000 --intdelay=data_OnInterest/delay-int-pitless-hybrid-att-${i}.txt --contentdelay=data_OnData/delay-data-pitless-hybrid-att-${i}.txt --rttdelay=data_RTT/delay-rtt-pitless-hybrid-att-${i}.txt"
done
