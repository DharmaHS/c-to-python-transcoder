if __name__ == "__main__":
        n = 0
        n = int(input())
        arr = [0]*n
        i=0
        for i in range(0, n):
                arr[i] = int(input())

        i=0
        for i in range(0, n-1):
                j=0
                for j in range(0, n-i-1):
                        if(arr[j]>arr[j+1]):
                                temp = arr[j]
                                arr[j]=arr[j+1]
                                arr[j+1]=temp



        i=0
        for i in range(0, n):
                print(arr[i], end = " ")
