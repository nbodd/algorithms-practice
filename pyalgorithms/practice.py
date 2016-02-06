from __future__ import print_function

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
            print ('YES')
        else:
            print ('NO')

def sherlock_and_minimax(A, P, Q):
    A.sort()

    pValues = [abs(val - P) for val in A]
    pMin = min(pValues)

    qValues = [abs(val - Q) for val in A]
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
    medianValues = [abs(median - val) for val in A]

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
    print(B)

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
            print('YES')
        else:
            print('NO')

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

    print(count)

def greedy_florist():
    N, K = raw_input().split()
    N = int(N)
    K = int(K)
    C = []

    numbers = raw_input()

    i = 0
    for number in numbers.split():
       C.append( int(number) )
       i = i + 1

    flowers = C
    flowers.sort(reverse=True)

    flowersPerPerson = [0] * K
    person = 0
    result = 0
    flowerNumber = 0
    while flowerNumber < len(flowers):
        flower = flowers[flowerNumber]
        result += (flowersPerPerson[person] + 1) * flower

        flowersPerPerson[person] += 1
        person = (person + 1) % K
        flowerNumber += 1

    print(result)


def main():
    [N, K] = map(int, raw_input().split(' '))
    A = map(int, raw_input().split(' '))


if __name__ == '__main__' :
    main()