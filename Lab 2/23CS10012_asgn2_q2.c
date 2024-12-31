// Model Solution
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

long long minTime(int* bus, int busSize, int totalTrips) {
    // Find the minimum time in bus array
    int mintime = INT_MAX; //or initialize with a very large number

    for (int i = 0; i < busSize; i++) {
        mintime = min(mintime, bus[i]);
    }

    long long left = 1, right = (long long)mintime * totalTrips; //int also acceptable

    while (left < right) {
        long long mid = (left + right) / 2;
        long long cnt = 0;

        // Calculate total trips possible in 'mid' time
        for (int i = 0; i < busSize; i++) {
            cnt += mid / bus[i];
        }

        // Adjust search boundaries
        if (cnt >= totalTrips) {
            right = mid; //or store answer in another variable
        } else {
            left = mid + 1;
        }
    }

    return left;
}

int main() {
    int totalTrips, busSize;

    printf("Enter the value of n (total required trips): ");
    scanf("%d", &totalTrips);

    printf("Enter the number of buses: ");
    scanf("%d", &busSize);

    int* bus = (int*)malloc(busSize * sizeof(int)); //int[busSize] also accepted

    printf("Enter the array bus[]: ");
    for (int i = 0; i < busSize; i++) {
        scanf("%d", &bus[i]);
    }

    long long result = minTime(bus, busSize, totalTrips);

    printf("Minimum time is %lld\n", result);

    free(bus);
    return 0;

}

/*
Test Cases:

5
3
1 2 3
Correct1: 3

100
5
1 2 3 4 5
Correct2: 45

10
1
5
Correct3: 50

12
4
2 2 2 2
Correct4: 6

1000000
3
10 20 30
Correct5: 5454550

100
5
1 100 100 100 100
Correct6: 100

1
3
5 7 9
Correct7: 5

10
2
1000 2000
Correct8: 7000

50
6
1111 2200 3030 5050 8800 1322
Correct9: 18887
*/