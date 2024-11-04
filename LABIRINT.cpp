#include "LABIRINT.h"

COORD LABIRINT::CreateLab(int N, int M) //Создание лабиринта
{
    this->Clear();
    this->M = M;  //Количество ячеек по вертикали
    this->N = N;  //Количество ячеек по горизонтали
    arr = new int* [N];
    for (int i = 0; i < N; i++) {
        arr[i] = new int[M];
    }

    wall_gor = new int* [N];
    for (int i = 0; i < N; i++) {
        wall_gor[i] = new int[M + 1];
    }

    wall_vert = new int* [N + 1];
    for (int i = 0; i < N + 1; i++) {
        wall_vert[i] = new int[M];
    }

    int a, b;

    for (int j = 0; j < M; j++)
        for (int i = 0; i < N; i++)
            arr[i][j] = 0;

    for (int j = 0; j < M + 1; j++)
        for (int i = 0; i < N; i++)
            wall_gor[i][j] = 0;

    for (int j = 0; j < M; j++)
        for (int i = 0; i < N + 1; i++)
            wall_vert[i][j] = 0;

    a = rand() % N;
    b = rand() % M;
    COORD coord;
    coord.x = a;
    coord.y = b;
    arr[a][b] = 1; //Первая ячейка заполняется 1

    for (int i = 0; i < M * N - 1; i++) { //N - 1, так как первая ячейка уже заполнена
        while (true) {
            a = rand() % N;
            b = rand() % M;

            if (arr[a][b] == 1)
                continue;

            if (a < (N - 1) and arr[a + 1][b] == 1) { //Если есть ячейка справа
                arr[a][b] = 1;
                wall_vert[a + 1][b] = 1;
                break;
            }
            else if (a != 0 and arr[a - 1][b] == 1) {   //Если есть ячейка слева
                arr[a][b] = 1;
                wall_vert[a][b] = 1;
                break;
            }
            else if (arr[a][b + 1] == 1 and b < M - 1) {  //Если есть ячейка снизу
                arr[a][b] = 1;
                wall_gor[a][b + 1] = 1;
                break;
            }
            else if (b != 0 and arr[a][b - 1] == 1) {   //Если есть ячейка сверху
                arr[a][b] = 1;
                wall_gor[a][b] = 1;
                break;
            }
        }
    }
    
    
    for (int i = 0; i < 50; i++) {
        a = rand() % N;
        b = rand() % M;
        if (arr[a][b] == 1) {
            arr[a][b] = 2;

        }
    }

    int k = 0;
    while (k < 500) {
        int i = rand() % N;
        int j = rand() % (M - 1) + 1;
        if (wall_gor[i][j] != 1) {
            wall_gor[i][j] = 1;
            k++;
        }
            
    }
    k = 0;
    while (k < 400) {
        int i = rand() % (N - 2) + 1;
        int j = rand() % M;
        if (wall_vert[i][j] != 1) {
            wall_vert[i][j] = 1;
            k++;
        }
    }

    return coord;
}
void LABIRINT::Clear() //Очистка
{
	for (int i = 0; i < N; i++) {
		delete arr[i];
	}
	delete[] arr;
	arr = NULL;
	for (int i = 0; i < N; i++) {
		delete[] wall_gor[i];
	}
	delete[] wall_gor;
	wall_gor = NULL;
	for (int i = 0; i < N; i++) {
		delete wall_vert[i];
	}
	delete[] wall_vert;
	wall_vert = NULL;
	this->M = 0;
	this->N = 0;
}
LABIRINT::LABIRINT() //Конструктор
{
	;
}
LABIRINT::~LABIRINT() //Деструктор
{
	this->Clear();
}