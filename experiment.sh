#!/bin/bash

./waf --run="pitfull-att --time=1000 --intdelay=delay-int-pitfull-att.txt --contentdelay=delay-data-pitfull-att.txt"
./waf --run="pitfull-dfn --time=1000 --intdelay=delay-int-pitfull-dfn.txt --contentdelay=delay-data-pitfull-dfn.txt"
./waf --run="pitless-att --time=1000 --delay=delay-pitless-att.txt"
./waf --run="pitless-dfn --time=1000 --delay=delay-pitless-dfn.txt"