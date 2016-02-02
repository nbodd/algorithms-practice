

def main() :
    testCases = int(raw_input())
    for test in range(testCases):
        length = int(raw_input())
        A = map(int, raw_input().split(' '))

        totalSum = 0
        sumA = []
        found = False
        for val in A:
            totalSum += val
            sumA.append(totalSum)

        for i in range(len(A)):
            lhs = 0
            if (i != 0) :
                lhs = sumA[i-1]

            rhs = 0
            if (i != len(A) - 1):
                rhs = totalSum - sumA[i]

            if lhs == rhs:
                found = True

        if found:
            print 'YES'
        else:
            print 'NO'

if __name__ == '__main__' :
    main()