

import sys
import random


sizes = [1000000, 10000000, 100000000, 500000000, 1000000000, 2000000000, 3000000000, 4000000000, 5000000000,6000000000,7000000000,8000000000,9000000000, 10000000000 ]

#sizes = [10]


for size in sizes:

    f = open ("da_fyillz/" + str(size)+ ".txt", "w")

    for i in xrange(size):
        #f.write(str(random.randint(0,9)))
        f.write(str(i%2))

    f.close()












