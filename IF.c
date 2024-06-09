#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char name[20];
    int value;
} Player;

Player first_basemen[] = { {"오스틴", 5}, {"이우성", 5}, {"맥키넌", 4}, {"데이비슨", 4}, {"양석환", 3}, {"문상철", 3}, {"고명준", 2}, {"채은성", 2}, {"최주환", 1}, {"나승엽", 1} };
Player second_basemen[] = { {"김혜성", 5}, {"박민우", 5}, {"강승호", 4}, {"김선빈", 4}, {"신민재", 3}, {"천성호", 3}, {"고승민", 2}, {"류지혁", 2}, {"김성현", 1}, {"문현빈", 1} };
Player shortstops[] = { {"박성한", 5}, {"박찬호", 5}, {"김영웅", 4}, {"김휘집", 4}, {"김주원", 3}, {"김재호", 3}, {"오지환", 2}, {"황영묵", 2}, {"박승욱", 1}, {"김상수", 1} };
Player third_basemen[] = { {"김도영", 5}, {"허경민", 5}, {"노시환", 4}, {"최정", 4}, {"송성문", 3}, {"서호철", 3}, {"문보경", 2}, {"황재균", 2}, {"전병우", 1}, {"한동희", 1} };

int max_value = 12; // 가치 한계
int best_value = 0; // 최적의 가치를 저장할 변수
Player best_combination[4]; // 최적의 조합을 저장할 배열

// 배열을 무작위로 섞는 함수
void shuffle(Player* array, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Player temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

void backtrack(Player* players[], int num_players[], int current_value, int pos, Player selected[]) {
    if (current_value > max_value) {
        return; // 가치가 한계를 넘으면 종료
    }
    if (pos == 4) { // 모든 포지션을 다 선택한 경우
        if (current_value > best_value) {
            best_value = current_value;
            memcpy(best_combination, selected, sizeof(Player) * 4); // 최적의 조합을 저장
        }
        return;
    }

    // 현재 포지션의 선수들을 무작위로 섞음
    shuffle(players[pos], num_players[pos]);

    for (int i = 0; i < num_players[pos]; i++) {
        selected[pos] = players[pos][i];
        backtrack(players, num_players, current_value + players[pos][i].value, pos + 1, selected);
    }
}

int main() {
    srand(time(NULL)); // 난수 생성기 초기화

    Player* players[] = { first_basemen, second_basemen, shortstops, third_basemen };
    int num_players[] = { 10, 10, 10, 10 }; // 각 포지션별 선수 수
    Player selected[4]; // 현재 선택된 선수들을 저장할 배열

    // 백트래킹을 5회 실행하여 매번 다른 결과를 얻음
    for (int run = 0; run < 5; run++) {
        best_value = 0; // 초기화
        backtrack(players, num_players, 0, 0, selected);

        printf("최적의 내야진 (%d회차):\n", run + 1);
        for (int i = 0; i < 4; i++) {
            printf("%s (%d)\n", best_combination[i].name, best_combination[i].value);
        }
        printf("최대 가치: %d\n", best_value);
        printf("\n");
    }

    return 0;
}
