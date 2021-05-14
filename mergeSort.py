import array

def mergeSort(arr):
    if len(arr) > 1:
        m = len(arr)//2
        l = arr[:m]
        r = arr[m:]

        mergeSort(l)
        mergeSort(r)

        i = j = k = 0

        while i < len(l) and j < len(r):
            if l[i] <= r[j]:
                arr[k] = l[i]
                i += 1
            else:
                arr[k] = r[j]
                j += 1
            k += 1

        while i < len(l):
            arr[k] = l[i]
            i += 1
            k += 1

        while j < len(r):
            arr[k] = r[j]
            j += 1
            k += 1


def printL(arr):
    for i in arr:
        print(i, end=" ")
    print()


if __name__ == '__main__':
    myArr = [(int)]
    file = open("arr.txt", "r")
    line = file.readline()
    myArr = line.split()
    file.close()
    printL(myArr)

    mergeSort(myArr)
    printL(myArr)
