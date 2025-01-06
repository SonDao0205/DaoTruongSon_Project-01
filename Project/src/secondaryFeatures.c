#include "../include/secondaryFeatures.h"

void goodBye(){
    printf("========  Thank You! =========\n");
    printf("======== See You Soon ========\n");
}

void backMenu() {
    while (1) {
        printf("BACK TO MENU (B)? EXIT (0)? : ");
        char x;
        fflush(stdin);
        scanf("%c", &x);
        x = toupper(x);
        switch (x) {
            case 'B':
                return;
            case '0':
                goodBye();
                exit(0);
            default:
                printf("Lua chon khong hop le!\n");
        }
    }
}
