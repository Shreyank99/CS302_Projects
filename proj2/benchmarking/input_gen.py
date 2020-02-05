# input_gen.py

# outputs a quantity of random ints according to a argument
# run input_gen.pu -h for more info

import argparse
import random

parser = argparse.ArgumentParser(description='generate random ints')
parser.add_argument('count', metavar='N', type=int, nargs=1,
                   help='the number of ints to output')

args = parser.parse_args()
count = args.count[0]

randList = [random.randint(0, 500000000) for i in range(count)]

for i in randList:
    print(i)