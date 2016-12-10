#!/bin/bash

mkdir data_OnInterest
mkdir data_OnData
mkdir data_RTT

for i in `seq 1 5`
do
   echo $i

   # DFN, no cache
   echo ./waf --run="pitfull-dfn --time=1000 --intdelay=data_OnInterest/delay-int-pitfull-dfn-${i}.txt --contentdelay=data_OnData/delay-data-pitfull-dfn-${i}.txt --rttdelay=data_RTT/delay-rtt-pitfull-dfn-${i}.txt"
   ./waf --run="pitfull-dfn --time=1000 --intdelay=data_OnInterest/delay-int-pitfull-dfn-${i}.txt --contentdelay=data_OnData/delay-data-pitfull-dfn-${i}.txt --rttdelay=data_RTT/delay-rtt-pitfull-dfn-${i}.txt"

   echo ./waf --run="pitless-dfn --time=1000 --intdelay=data_OnInterest/delay-int-pitless-dfn-${i}.txt --contentdelay=data_OnData/delay-data-pitless-dfn-${i}.txt --rttdelay=data_RTT/delay-rtt-pitless-dfn-${i}.txt"
   ./waf --run="pitless-dfn --time=1000 --intdelay=data_OnInterest/delay-int-pitless-dfn-${i}.txt --contentdelay=data_OnData/delay-data-pitless-dfn-${i}.txt --rttdelay=data_RTT/delay-rtt-pitless-dfn-${i}.txt"

   echo ./waf --run="pitless-hybrid-dfn --time=1000 --intdelay=data_OnInterest/delay-int-pitless-hybrid-dfn-${i}.txt --contentdelay=data_OnData/delay-data-pitless-hybrid-dfn-${i}.txt --rttdelay=data_RTT/delay-rtt-pitless-hybrid-dfn-${i}.txt"
   ./waf --run="pitless-hybrid-dfn --time=1000 --intdelay=data_OnInterest/delay-int-pitless-hybrid-dfn-${i}.txt --contentdelay=data_OnData/delay-data-pitless-hybrid-dfn-${i}.txt --rttdelay=data_RTT/delay-rtt-pitless-hybrid-dfn-${i}.txt"

   # AT&T, no cache
   echo ./waf --run="pitfull-att --time=1000 --intdelay=data_OnInterest/delay-int-pitfull-att-${i}.txt --contentdelay=data_OnData/delay-data-pitfull-att-${i}.txt --rttdelay=data_RTT/delay-rtt-pitfull-att-${i}.txt"
   ./waf --run="pitfull-att --time=1000 --intdelay=data_OnInterest/delay-int-pitfull-att-${i}.txt --contentdelay=data_OnData/delay-data-pitfull-att-${i}.txt --rttdelay=data_RTT/delay-rtt-pitfull-att-${i}.txt"

   echo ./waf --run="pitless-att --time=1000 --intdelay=data_OnInterest/delay-int-pitless-att-${i}.txt --contentdelay=data_OnData/delay-data-pitless-att-${i}.txt --rttdelay=data_RTT/delay-rtt-pitless-att-${i}.txt"
   ./waf --run="pitless-att --time=1000 --intdelay=data_OnInterest/delay-int-pitless-att-${i}.txt --contentdelay=data_OnData/delay-data-pitless-att-${i}.txt --rttdelay=data_RTT/delay-rtt-pitless-att-${i}.txt"

   echo ./waf --run="pitless-hybrid-att --time=1000 --intdelay=data_OnInterest/delay-int-pitless-hybrid-att-${i}.txt --contentdelay=data_OnData/delay-data-pitless-hybrid-att-${i}.txt --rttdelay=data_RTT/delay-rtt-pitless-hybrid-att-${i}.txt"
   ./waf --run="pitless-hybrid-att --time=1000 --intdelay=data_OnInterest/delay-int-pitless-hybrid-att-${i}.txt --contentdelay=data_OnData/delay-data-pitless-hybrid-att-${i}.txt --rttdelay=data_RTT/delay-rtt-pitless-hybrid-att-${i}.txt"

   # DFN, cache
   echo ./waf --run="pitfull-cache-dfn --time=1000 --intdelay=data_OnInterest/delay-int-pitfull-cache-dfn-${i}.txt --contentdelay=data_OnData/delay-data-pitfull-cache-dfn-${i}.txt --rttdelay=data_RTT/delay-rtt-pitfull-cache-dfn-${i}.txt"
   ./waf --run="pitfull-cache-dfn --time=1000 --intdelay=data_OnInterest/delay-int-pitfull-cache-dfn-${i}.txt --contentdelay=data_OnData/delay-data-pitfull-cache-dfn-${i}.txt --rttdelay=data_RTT/delay-rtt-pitfull-cache-dfn-${i}.txt"

   echo ./waf --run="pitless-cache-dfn --time=1000 --intdelay=data_OnInterest/delay-int-pitless-cache-dfn-${i}.txt --contentdelay=data_OnData/delay-data-pitless-cache-dfn-${i}.txt --rttdelay=data_RTT/delay-rtt-pitless-cache-dfn-${i}.txt"
   ./waf --run="pitless-cache-dfn --time=1000 --intdelay=data_OnInterest/delay-int-pitless-cache-dfn-${i}.txt --contentdelay=data_OnData/delay-data-pitless-cache-dfn-${i}.txt --rttdelay=data_RTT/delay-rtt-pitless-cache-dfn-${i}.txt"

   echo ./waf --run="pitless-cache-hybrid-dfn --time=1000 --intdelay=data_OnInterest/delay-int-pitless-cache-hybrid-dfn-${i}.txt --contentdelay=data_OnData/delay-data-pitless-cache-hybrid-dfn-${i}.txt --rttdelay=data_RTT/delay-rtt-pitless-cache-hybrid-dfn-${i}.txt"
   ./waf --run="pitless-cache-hybrid-dfn --time=1000 --intdelay=data_OnInterest/delay-int-pitless-cache-hybrid-dfn-${i}.txt --contentdelay=data_OnData/delay-data-pitless-cache-hybrid-dfn-${i}.txt --rttdelay=data_RTT/delay-rtt-pitless-cache-hybrid-dfn-${i}.txt"

   # AT&T, cache
   echo ./waf --run="pitfull-cache-att --time=1000 --intdelay=data_OnInterest/delay-int-pitfull-cache-att-${i}.txt --contentdelay=data_OnData/delay-data-pitfull-cache-att-${i}.txt --rttdelay=data_RTT/delay-rtt-pitfull-cache-att-${i}.txt"
   ./waf --run="pitfull-cache-att --time=1000 --intdelay=data_OnInterest/delay-int-pitfull-cache-att-${i}.txt --contentdelay=data_OnData/delay-data-pitfull-cache-att-${i}.txt --rttdelay=data_RTT/delay-rtt-pitfull-cache-att-${i}.txt"

   echo ./waf --run="pitless-cache-att --time=1000 --intdelay=data_OnInterest/delay-int-pitless-cache-att-${i}.txt --contentdelay=data_OnData/delay-data-pitless-cache-att-${i}.txt --rttdelay=data_RTT/delay-rtt-pitless-cache-att-${i}.txt"
   ./waf --run="pitless-cache-att --time=1000 --intdelay=data_OnInterest/delay-int-pitless-cache-att-${i}.txt --contentdelay=data_OnData/delay-data-pitless-cache-att-${i}.txt --rttdelay=data_RTT/delay-rtt-pitless-cache-att-${i}.txt"

   echo ./waf --run="pitless-cache-hybrid-att --time=1000 --intdelay=data_OnInterest/delay-int-pitless-cache-hybrid-att-${i}.txt --contentdelay=data_OnData/delay-data-pitless-cache-hybrid-att-${i}.txt --rttdelay=data_RTT/delay-rtt-pitless-cache-hybrid-att-${i}.txt"
   ./waf --run="pitless-cache-hybrid-att --time=1000 --intdelay=data_OnInterest/delay-int-pitless-cache-hybrid-att-${i}.txt --contentdelay=data_OnData/delay-data-pitless-cache-hybrid-att-${i}.txt --rttdelay=data_RTT/delay-rtt-pitless-cache-hybrid-att-${i}.txt"
done
