

#include "Menu.h"
#include <stdbool.h>

void assignString(char* token, char root[]) {
    for (int i = 0; i < strlen(token); ++i) {
        root[i] = token[i];
    }
}

void readData(const char* filename, MemberNode** list) {
    char row[1000];

    FILE* file;
    file = fopen(filename, "r");
    bool isDataInfo = false;
    char *token;

    while (!feof(file)) {
        fgets(row, 1000, file);

        if (!isDataInfo) {
            isDataInfo = true;
            continue;
        }

        // printf("Row: %s", row);

        token = strtok(row, ",");
        Member currMember;
        int cnt = 0;

        while(token != NULL) {
            ++cnt;
            switch (cnt) {
                case 1:
                    assignString(token, currMember.uid);
                    break;

                case 2:
                    assignString(token, currMember.roomNumber);
                    break;

                case 3:
                    assignString(token, currMember.name);
                    break;

                case 4:
                    assignString(token, currMember.licensePlate);
                    break;
            }
            // printf("Token: %s\n", token);
            token = strtok(NULL, ",");
        }

        // getMember(&currMember);
        createMember(list, currMember);
    }

    fclose(file);
}

void writeData(const char* filename, MemberNode** list) { 
    FILE* file;
    file = fopen(filename, "w");

    MemberNode *currNode = *list;
    printf("uID,roomNumber,name,licensePlates\n");
    while (currNode != NULL) {
        printf("%s,%s,%s,%s\n", currNode->data.uid, currNode->data.roomNumber, currNode->data.name, currNode->data.licensePlate);
        currNode = currNode->next;
    }

    fclose(file);
}

void Menu(const char* filename, MemberNode** list) {
    readData(filename, list);
    int choice_input = 0;
    
    printf ("=========Danh Sach Chuc Nang=========\n");
    printf("1. Them 1 dan cu moi.\n");
    printf("2. So luong dan cu.\n");
    printf("3. In ra toan bo thong tin dan cu sinh song.\n");
    printf("4. Tim kiem thong tin dan cu theo UID.\n");
    printf("5. Chinh sua thong tin dan cu.\n");
    printf("6. Xoa dan cu ra khoi danh sach.\n");
    printf("7. Thoat chuong trinh.\n");

    while (choice_input != 7) {
        printf("Nhap chuc nang ban  chon : ");
        scanf("%d", &choice_input);

        switch (choice_input) {
        case 1:
            printf("Moi Ban nhap thong tin 1 sinh vien : \n");
            addMember(list);
            break;
        case 2:
            printf("Số lượng dân cư : %d \n", calcPopulation(*list));
            break;
        case 3:
            printf("Danh Sach thông tin dân cư : \n");
            printList(*list);
            break;
        case 4:
            printf("Tìm kiếm thông tin dân cư : \n");
            searchMember(*list);
            break;
        case 5:
            printf("Thông tin dân cư cần chỉnh sửa : \n");
            editMember(*list);
            break;
        case 6:
            printf("Nhập thông tin dân cư xóa khỏi danh sach : \n");
            deleteMember(*list);
            break;
        default:
            break;
        }
    }

    // writeData(filename, list);
}
