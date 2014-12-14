
import os
import sys
from optparse import OptionParser
import numpy as np
import matplotlib.pyplot as plt


parser = OptionParser()
parser.add_option("-i", "--iterations", dest="iterations",
                  help="number of iterations to run")

parser.add_option ("-t", "--threshold", dest="threshold",
                   help="Specifies amount of time above which measurement will be discarded")

parser.add_option ("-g", "--graph",
                    action="store_true", dest="histogram", default=False,
                    help="show histogram of times")

(options, args) = parser.parse_args()

prog = sys.argv[1]

# print options
# print ("iterations: " + options.iterations)
# print "program: " + prog

os.system("gcc -pthread " + prog )

iterations = int(options.iterations)
threshold = int(options.threshold)

sum = 0
runs = []


i = 0
while i < iterations:
    if i % 100 == 0:
        print "iteration " + str(i+1) + "..."

    f = os.popen("./a.out")
    experiment_value = float(f.read())

    runs.append(experiment_value)

    if experiment_value < threshold:
        sum += experiment_value
        i += 1

    f.close()




print (sum * 1.0)/ iterations
if options.histogram:
    plt.hist(runs, bins=50)
    plt.show()
