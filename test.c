int main(int argc, char **argv) {
    int a = 0;
    for (int i = 0 ; i < 20 ; i *= 2) {
        for (int j = 0; j < 15; j++) {
            a++;
        }
    }

    a = 0;
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < i; j++) {
            a--;
        }
    }

    a = 0;
    for(int i = 0; i < 20; i++) {
        a *= 2;
        for(int j = 0; j < 5; j++) {
            a++;
        }
    }
}