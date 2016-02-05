

def sherlockArray() :
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

def sherlock_and_minimax(A, P, Q):
    A.sort()

    pValues = [abs(val - P) for val in A]
    print pValues
    pMin = min(pValues)

    qValues = [abs(val - Q) for val in A]
    print qValues
    qMin = min(qValues)

    firstP = P
    firstQ = P
    firstPIndex = 0
    for index in range(len(A)):
        if (P >= A[index]):
            firstP = A[index]
            firstPIndex = index

        if (Q >= A[index]):
            firstQ = A[index]

    if (firstP == firstQ):
        firstQ = A[firstPIndex + 1]

    median = (firstP + firstQ) / 2
    print firstP
    print firstQ
    print median
    medianValues = [abs(median - val) for val in A]
    print medianValues

    medianMin = min(medianValues)


    if pMin >= qMin and pMin >= medianMin:
        return P
    elif medianMin >= qMin and medianMin > pMin:
        return median
    else :
        return Q

def sherlock_minimax_main():
    N = int(raw_input())

    A = map(int, (raw_input().split(' ')))
    P, Q = map(int, raw_input().split())
    B = sherlock_and_minimax(A, P, Q)
    print B

def two_arrays_main() :
    testCases = int(raw_input())
    for i in range(testCases):
        [N, K] = map(int, raw_input().split(' '))

        A = map(int, raw_input().split(' '))
        B = map(int, raw_input().split(' '))

        A.sort()
        B.sort(reverse=True)

        found = True
        for i in range(N):
            if (A[i] + B[i] < K):
                found = False
                break

        if found:
            print 'YES'
        else:
            print 'NO'

def priyanka_main():
    N = int(raw_input())
    A = map(int, raw_input().split(' '))
    A.sort()
    count = 1
    current = A[0]
    for index in range(1, len(A)):
        if A[index] <= (current + 5):
            continue
        else:
            count += 1
            current = A[index]

    print count


if __name__ == '__main__' :
    main()