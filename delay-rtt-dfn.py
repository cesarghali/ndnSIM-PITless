#!/usr/bin/python

import sys
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages
from mpl_toolkits.mplot3d import Axes3D

binSize = 1000000000
width = 0.35

def main(argv):
    rtts = {}
    fileNames = ["delay-rtt-pitfull-dfn",
                 "delay-rtt-pitless-dfn"]
    numberOfFiles = 9
    colors = {fileNames[0]: "y",
              fileNames[1]: "g"}
    legendLabels = ["Stateful",
                    "Stateless"]

    for fileName in fileNames:
        rtt = {}
        counter = {}

        for num in range(1, numberOfFiles + 1):
            print "Processing '" + fileName + "-" + str(num) + ".txt'..."

            with open(fileName + "-" + str(num) + ".txt", "r") as fd:
                for line in fd:
                    if line.split("\t")[0] == "Time":
                        continue

                    key = float(line.split("\t")[3])
                    if key not in rtt:
                        rtt[key] = 0
                        counter[key] = 0

                    rtt[key] += (float(line.split("\t")[2]) / 1000000)
                    counter[key] += 1

        tmp1 = []
        tmp2 = []
        for key in rtt:
            tmp1.append(key)
        tmp1.sort()

        for key in tmp1:
            tmp2.append(float(rtt[key]) / float(counter[key]))

        rtts[fileName] = [tmp1, tmp2]

    fig, ax = plt.subplots()
    shift = 0
    for fileName in fileNames:
        ax.bar([x + shift for x in rtts[fileName][0]],
               rtts[fileName][1], width, color=colors[fileName])
        shift += width

    ax.set_xlabel("Hop Count")
    ax.set_ylabel("Consumer Round-Trip Time (msec)")
    ax.legend(legendLabels, loc=1)
    ax.set_xticks([x + width for x in rtts[fileNames[0]][0]])
    ax.set_xticklabels([int(x) for x in rtts[fileNames[0]][0]])

    pdf = PdfPages("delay-rtt-dfn.pdf")
    pdf.savefig(fig)
    pdf.close()

if __name__ == "__main__":
    main(sys.argv)
