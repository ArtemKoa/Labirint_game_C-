#include "LABIRINT.h"
#include "TANK.h"
#include <iostream>
#pragma warning(disable : 4996)

int main() {
    srand(time(0));
    LABIRINT lab; //Создание экземпляра класса
    COORD coord = lab.CreateLab(50, 50);
    LincedList TANK;
    setlocale(LC_ALL, "ru");

    float offset_x = 0; 	//Сдвиг лабиринта в игровом окне
    float offset_y = 0;

    float rotation = 1; //Направление - 8 

    int X = 15; // С какого x рисуется лабиринт
    int Y = 15; // С какого y рисуется лабиринт

    int rectwidth = 50, rectheight = 50;
    int speed = 0;

    Texture texture_tank, texture_gor, texture_vert;
    texture_tank.loadFromFile("resources/TANK1.png");
    texture_gor.loadFromFile("resources/texture_gor.png");
    texture_vert.loadFromFile("resources/texture_vert.png");
    Sprite sprite_gor, sprite_vert, sprite_tank;
    sprite_tank.setTexture(texture_tank);
    sprite_gor.setTexture(texture_gor);
    sprite_vert.setTexture(texture_vert);
    float scx, scy;
    Vector2u t_size = texture_tank.getSize();
    scx = 64.0f / t_size.x;
    scy = 64.0f / t_size.y;
    sprite_tank.setScale(Vector2f(scx, scy));
    texture_tank.loadFromFile("resources/TANK1.png");


    // Устанавливаем центр спрайта в его центре по горизонтали
    Vector2u textureSize = texture_tank.getSize();
    sprite_tank.setOrigin(static_cast<float>(textureSize.x * 0.5), static_cast<float>(textureSize.y) * 0.5);

    DATA data;
    for (int i = 0; i < lab.N; i++) //Создание списка танков в зонах
        for (int j = 0; j < lab.M; j++) {
            if (lab.arr[i][j] == 2) {
                data.a = i;
                data.b = j;
                data.rotation = rand() % 9;
                TANK.push_front(&data);
            }
        }


    // Задаем область для захвата (captureArea)
    sf::IntRect captureArea(440, 146, 1060, 756); // x, y - координаты верхнего левого угла, width и height - ширина и высота области

    // Создаем объект для хранения скриншота
    sf::Image screenshot;

    // Захватываем только определенную область окна
    screenshot.create(1060, 756);


    RenderWindow window(VideoMode(window_width, window_height), L"Окно игры", Style::Default);
    while (window.isOpen()) //Пока открыто окно
    {
        Event event; //Событие
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) //Если нажали на крестик, то закрывается окно
                window.close();
        }
        window.clear();     //Очистка окна

        RectangleShape rect_room(Vector2f(width, height));    //Создание прямоугольника
        rect_room.setFillColor(Color(136, 112, 107));
        RectangleShape rect_zona(Vector2f(width - rectwidth / 3, height - rectheight / 3)); //База
        rect_zona.setFillColor(Color(0, 10, 100));
        RectangleShape rect_gor(Vector2f(width + rectwidth / 3, rectheight / 3)); //Горизонтальная стена
        rect_gor.setFillColor(Color(136, 112, 107));
        RectangleShape rect_vert(Vector2f(rectwidth / 3, height + rectheight / 3)); //Вертикальная стена
        rect_vert.setFillColor(Color(136, 112, 107));

        for (int i = X; i < X + Size_x + 1; i++)
            for (int j = Y; j < Y + Size_y + 1; j++) {
                if (i < 0)continue;
                if (j < 0)continue;
                if (i > lab.N - 1) continue;
                if (j > lab.M - 1) continue;
                if (lab.arr[i][j] == 1) {   //Рисование обычной ячейки
                    rect_room.setPosition(Vector2f((i - X) * width + Goffset_x - offset_x, (j - Y) * height + Goffset_y - offset_y));
                    window.draw(rect_room);
                }
                else if (lab.arr[i][j] == 2) {

                    //Рисует зеленым стены для баз
                    rect_gor.setSize(Vector2f(width, rectwidth / 3));
                    rect_gor.setPosition(Vector2f((i - X) * width + Goffset_x - offset_x, (j - Y) * height + Goffset_y - offset_y));
                    window.draw(rect_gor);
                    rect_vert.setSize(Vector2f(rectwidth / 3, height));
                    rect_vert.setPosition(Vector2f((i - X) * width + Goffset_x - offset_x, (j - Y) * height + Goffset_y - offset_y));
                    window.draw(rect_vert);

                    //Рисование базы
                    rect_zona.setPosition(Vector2f((i - X) * width + Goffset_x - offset_x + rectwidth / 3, (j - Y) * height + Goffset_y - offset_y + rectheight / 3));
                    window.draw(rect_zona);

                    Node* node;
                    for (Node* ptr = TANK.head; ptr != NULL; ptr = ptr->next) {
                        if (ptr->data.a == i and ptr->data.b == j) {
                            sprite_tank.setRotation(ptr->data.rotation * 45);
                            sprite_tank.setPosition(Vector2f((ptr->data.a - X) * width + Goffset_x - offset_x + rectwidth * 1.5, (ptr->data.b - Y) * height + Goffset_y - offset_y + rectheight * 1.5));
                            window.draw(sprite_tank);
                            break;
                        }
                    }
                }
            }

        //Рисование горизонтальных стен в окне
        int xx = 1;
        int yy = 1;
        if (offset_x == 0) xx = 0;
        if (offset_y == 0) yy = 0;
        for (int i = X - 1; i < X + Size_x + xx; i++)
            for (int j = Y; j < Y + Size_y + yy; j++) {
                if (i < 0)continue;
                if (j < 0)continue;
                if (i >= lab.N) continue;
                if (j > lab.M) continue;
                if (lab.wall_gor[i][j] == 0)
                {
                    int x = (i - X) * width + Goffset_x - offset_x;
                    int y = (j - Y) * height + Goffset_y - offset_y;
                    sprite_gor.setPosition(Vector2f(x, y));
                    window.draw(sprite_gor);

                }
            }

        //Рисование вертикальных стен в окне
        for (int i = X; i < X + Size_x + xx; i++)
            for (int j = Y - 1; j < Y + Size_y + yy; j++)
            {
                if (i < 0)continue;
                if (j < 0)continue;
                if (i > lab.N) continue;
                if (j >= lab.M) continue;
                if (lab.wall_vert[i][j] == 0)
                {
                    sprite_vert.setPosition(Vector2f((i - X) * width + Goffset_x - offset_x, (j - Y) * height + Goffset_y - offset_y));
                    window.draw(sprite_vert);
                }
            }


        for (int i = 0; i < 2; i++)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) and i == 1) {  //Поворот направо
                if (rotation <= 9) {
                    rotation += 0.0065;
                }
                else if (rotation > 9) {
                    rotation = 1;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) and i == 1) {   //Поворот налево
                if (rotation >= 1) {
                    rotation -= 0.007;
                }
                else if (rotation < 1) {
                    rotation = 9;
                }
            }
            sprite_tank.setRotation(rotation * 45 - 45);    //Поворот

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) and i == 1) {    //Тормоз
                if (speed > 0) {
                    speed -= speed / 400.0;
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) and i == 1) { //Газ
                speed += 1;
            }
            //if (speed > 0) {
            //    screenshot.copy(window.capture(), 0, 0, captureArea);
            //    // Сохраняем скриншот в файл
            //    screenshot.saveToFile("screenshot.png");
            //}

            if (i == 1) {
                if (rotation >= 8.51 or rotation < 1.5) {
                    if (offset_y <= 0) {
                        Y--;
                        offset_y = height;
                    }
                    if (speed > 0) {
                        if (speed < 1000) {
                            offset_y -= speed / 3000.;
                        }
                        else {
                            offset_y -= 0.33;
                        }
                    }
                }
                else if (rotation >= 1.51 and rotation < 2.5) {
                    if (offset_y <= 0) {
                        Y--;
                        offset_y = height;
                    }
                    if (offset_x >= width) {
                        X++;
                        offset_x = 0;
                    }
                    if (speed > 0) {
                        if (speed < 1000) {
                            offset_x += speed / 3000.;
                            offset_y -= speed / 3000.;
                        }
                        else {
                            offset_x += 0.33;
                            offset_y -= 0.33;
                        }
                    }
                }
                else if (rotation >= 2.51 and rotation <= 3.5) {
                    if (offset_x >= width) {
                        X++;
                        offset_x = 0;
                    }
                    if (speed > 0) {
                        if (speed < 1000) {
                            offset_x += speed / 3000.;
                        }
                        else {
                            offset_x += 0.33;
                        }
                    }
                }

                else if (rotation >= 3.51 and rotation <= 4.5) {
                    if (offset_x >= width) {
                        X++;
                        offset_x = 0;
                    }
                    if (offset_y >= height) {
                        Y++;
                        offset_y = 0;
                    }
                    if (speed > 0) {
                        if (speed < 1000) {
                            offset_x += speed / 3000.;
                            offset_y += speed / 3000.;
                        }
                        else {
                            offset_x += 0.33;
                            offset_y += 0.33;
                        }
                    }
                }
                else if (rotation >= 4.51 and rotation <= 5.5) {
                    sprite_tank.setPosition(window_width / 2 + 70, window_height * 0.478 + 70);
                    if (offset_y >= height) {
                        Y++;
                        offset_y = 0;
                    }
                    if (speed > 0) {
                        if (speed < 1000) {
                            offset_y += speed / 3000.;
                        }
                        else {
                            offset_y += 0.33;
                        }
                    }
                }
                else if (rotation >= 5.51 and rotation <= 6.5) {
                    if (offset_y >= height) {
                        Y++;
                        offset_y = 0;
                    }
                    if (offset_x <= 0) {
                        X--;
                        offset_x = width;
                    }
                    if (speed > 0) {
                        if (speed < 1000) {
                            offset_y += speed / 3000.;
                            offset_x -= speed / 3000.;
                        }
                        else {
                            offset_y += 0.33;
                            offset_x -= 0.33;
                        }
                    }
                }
                else if (rotation >= 6.51 and rotation < 7.5) {
                    if (offset_x <= 0) {
                        X--;
                        offset_x = width;
                    }
                    if (speed > 0) {
                        if (speed < 1000) {
                            offset_x -= speed / 3000.;
                        }
                        else {
                            offset_x -= 0.33;
                        }
                    }
                }
                else if (rotation >= 7.51 and rotation < 8.5) {
                    if (offset_x <= 0) {
                        X--;
                        offset_x = width;
                    }
                    if (offset_y <= 0) {
                        Y--;
                        offset_y = height;
                    }
                    if (speed > 0) {
                        if (speed < 1000) {
                            offset_x -= speed / 3000.;
                            offset_y -= speed / 3000.;
                        }
                        else {
                            offset_x -= 0.33;
                            offset_y -= 0.33;
                        }
                    }
                }
            }
        }


        data.a = 0;
        data.b = 0;
        data.mine = true;
        data.rotation = rotation;
        TANK.push_front(&data);


        rect_room.setFillColor(Color(0, 0, 0));
        rect_room.setSize(Vector2f(Size_x * width + width * 4 + 30, height + 30));
        rect_room.setPosition(Goffset_x - width * 2, Goffset_y - height - 30); //Верхнее закрашивание черным
        window.draw(rect_room);
        rect_room.setPosition(Goffset_x - width * 2 - 30, Goffset_y + height * Size_y); //Нижнее закрашивание черным
        window.draw(rect_room);

        rect_room.setSize(Vector2f(width * 2 + 20, Size_y * height));
        rect_room.setPosition(Goffset_x - width * 2 - 20, Goffset_y); //Левое закрашивание черным
        window.draw(rect_room);
        rect_room.setPosition(Goffset_x + width * Size_x, Goffset_y); //Правое закрашивание черным
        window.draw(rect_room);

        //Рисование границ окна
        rect_room.setFillColor(Color(0, 255, 0));
        rect_room.setSize(Vector2f(Size_x * width + 2, 1));
        rect_room.setPosition(Goffset_x - 1, Goffset_y - 1);
        window.draw(rect_room);
        rect_room.setPosition(Goffset_x - 1, Goffset_y + height * Size_y + 1);
        window.draw(rect_room);
        rect_room.setSize(Vector2f(1, Size_y * height + 2));
        rect_room.setPosition(Goffset_x - 1, Goffset_y - 1);
        window.draw(rect_room);
        rect_room.setPosition(Goffset_x + width * Size_x + 1, Goffset_y - 1);
        window.draw(rect_room);

        sprite_tank.setPosition(window_width / 2, window_height * 0.478);
        window.draw(sprite_tank);





        TANK.pop_front();
        window.display();   //Выводит объекты после очистки
    }
    TANK.~LincedList();
    return 0;
}