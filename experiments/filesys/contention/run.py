
import os
import sys
import numpy as np
import matplotlib as plt

#num_proc = sys.argv[1]


avgs = []

def average_of_runs():

    for num_proc in range(1,31):

        print("running with " + str(num_proc) + " processes" )

        runs = []

        for i in xrange(10):

            os.system("")

            f = os.popen("./cont " + str(num_proc))
            runs.append(int(f.read()))


        avg = np.average(runs)
        std = np.std(runs)

        avgs.append(avg)

        print "Avg: " + str(avg)
        print "Std: " + str(std)

    return avgs

