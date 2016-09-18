#! usr/bin/env python

mediancomparison = 0

#A method to partition around the median
def partition_median(array, leftend, rightend):
    left = array[leftend]
    right = array[rightend-1]
    length = rightend - leftend
    m = 0
    if length % 2 == 0:
        m = leftend + (length/2) - 1
    else:
        m = leftend + (length/2)
    middle = array[m]
 
    pivot = 0
    if left > middle:
        if right > left:
            pivot = left
            array[leftend] = array[leftend]
        elif right < middle:
            pivot = middle
            array[m] = array[leftend]
        else:
            pivot = right
            array[rightend-1] = array[leftend]
    else:
        if right < left:
            pivot = left
            array[leftend] = array[leftend]
        elif right > middle:
            pivot = middle
            array[m] = array[leftend]
        else:
            pivot = right
            array[rightend-1] = array[leftend]

    array[leftend] = pivot

    i = leftend + 1
    for j in range(leftend + 1, rightend):
        if array[j] < pivot:
            temp = array[j]
            array[j] = array[i]
            array[i] = temp
            i += 1

    leftendval = array[leftend]
    array[leftend] = array[i-1]
    array[i-1] = leftendval
    return i - 1 

    
#Implement quicksort while partitioning around the first index
def quicksort_median(array, leftindex, rightindex):
     global mediancomparison
     if leftindex < rightindex:

         newpivotindex = partition_median(array, leftindex, rightindex)

         mediancomparison += (rightindex - leftindex - 1)

         quicksort_median(array, leftindex, newpivotindex)

         quicksort_median(array, newpivotindex + 1, rightindex)


f = open("IntegerArray.txt", "r")
intarray = []
for line in f:
    intarray.append(int(line))
f.close()

#test on an array of length 10000
mediancomparison = 0
quicksort_median(intarray, 0, len(intarray))
print mediancomparison
