if __name__ == "__main__":
        str = []*100
        str = input()
        i = 0
        j = len(str)-1
        flag = 0
        while(i<j):
                if(str[i]!=str[j]):
                        flag=0
                        break

                else:
                        flag=1

                i+=1
                j-=1

        if(flag):
                print("True\n")

        else:
                print("False\n")