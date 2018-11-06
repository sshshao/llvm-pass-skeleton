int main(int argc, char **argv) {
    for (int i = 0 ; i < 20 ; i *= 2) {
        if ((i & 0x1) == 0) {
            for (int j = 0; j < 15; j++) {
                i++;
            }
        } else {
            for (int k = 0; k < 15; k++) {
                i += 2;
            }
        }
    }

    int j;
    for (int i = 0; i < 50; i++) {
        j = i;
    }
    for(int i = 0; i < 40; i++) {
        j -= i;
        for(int k = 0; k < 5; k++) {
            j += 2;
        }
    }
}