int timesTwo(int num, int iteration);

int main(int argc, char **argv) {
    int a = 0;

    for (int i = 0 ; i < 20 ; i *= 2) {
        for (int j = 0; j < 15; j++) {
            a++;
        }
    }

    for(int i = 0; i < 20; i++) {
        for(int j = i; j < 20; j++) {
            a--;
        }
    }

    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 5; j++, i++) {
            a++;
        }
    }

    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 5-i; j++) {
            a++;
        }
        timesTwo(a, 100);
        for(int j = 0; j < 5; j++) {
            a--;
        }
    }

    for(int i = 0; i < 20; i++) {
        if(a > 50) {
            break;
        }
        for(int j = 0; j < 5; j++) {
            a--;
        }
    }
}

int timesTwo(int num, int iteration) {
    return timesTwo(num*2, iteration-1);
}