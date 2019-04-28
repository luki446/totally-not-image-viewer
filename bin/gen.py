#script used to make some example images to show
import random

height = 650
width = 745

with open("obrazek.pbm", "w+") as fp:
    fp.write("P1\n")
    fp.write(f"{width} {height}\n")
    for i in range(0, height):
        for j in range(0, width):
            fp.write(f"{random.randint(0, 1)} ")
        fp.write('\n')