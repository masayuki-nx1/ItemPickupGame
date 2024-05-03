#define _CRT_NONSTDC_NO_WARNINGS
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

#include<stdio.h>
#include<conio.h>//キー入力用
#include<Windows.h>//sleep()を使うため

//マップデータの定義
#define MAP_W 22
#define MAP_H 11
char map[MAP_H][MAP_W] = {
	"####################",
	"#                  #",
	"# ###          ### #",
	"# #              # #",
	"#     # ## ## #    #",
	"#     # #   # #    #",
	"#     # ## ## #    #",
	"# #              # #",
	"# ###          ### #",
	"#                  #",
	"####################",
};

//ゲームで扱う変数の定義
int pl_x = 1, pl_y = 1;
int score = 0;
int timer = 300;

//カーソル位置を指定する関数
void cursor(int x, int y) {
	printf("\x1b[%d;%dH", y + 1, x + 1);
}

//文字や文字列の色を指定する関数
enum { BLACK, RED, GREEN, YELLOW, MAGENTA, CYAN, WHITE };
void color(int col) {
	printf("\x1b[3%dm", col);
}

//ゲーム画面を描く関数
void draw_map(void) {
	for (int y = 0; y < MAP_H; y++) {
		for (int x = 0; x < MAP_W; x++) {
			if (map[y][x] == '#') color(GREEN);
			if (map[y][x] == 'G') color(YELLOW);
			cursor(x, y);
			printf("%c", map[y][x]);
		}
	}
}

//main関数
int main(void) {
	while (1) {
		int key = 0;
		if (kbhit()) key = getch(); //キー入力
		if (key == KEY_UP && map[pl_y - 1][pl_x] != '#')pl_y--;
		if (key == KEY_DOWN && map[pl_y + 1][pl_x] != '#')pl_y++;
		if (key == KEY_LEFT && map[pl_y][pl_x - 1] != '#')pl_x--;
		if (key == KEY_RIGHT && map[pl_y][pl_x + 1] != '#')pl_x++;
		draw_map();
		cursor(pl_x, pl_y);
		printf("p");
		//Gを取得したときの処理
		if (map[pl_y][pl_x] == 'G') {
			score += 1;
			timer += 20;
			map[pl_y][pl_x] = ' ';
		}
		timer--;
		//Gを設置する
		if (timer % 20 == 0) {
			int x = 1 + rand() % (MAP_W - 3);
			int y = 1 + rand() % (MAP_H - 2);
			if (map[y][x] == ' ')map[y][x] = 'G';
		}
		//スコア更新
		color(WHITE);
		cursor(0, MAP_H);
		printf("SCORE %d ", score);
		cursor(12, MAP_H);
		printf("TIME %d ", timer);
		Sleep(50);
		//ゲームオーバー処理
		if (timer == 0) {
			color(RED);
			cursor(MAP_W / 2 - 5, MAP_H / 2);
			printf("GAME OVER");
			cursor(0, MAP_H + 1);
			Sleep(1000);
			return 0;
		}
	}
}