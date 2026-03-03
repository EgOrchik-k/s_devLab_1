#include <stdlib.h>
#include <time.h>
#include <vector>
#include <math.h>
#include <glut.h>				// Заголовочник  GLUT
#include <algorithm>
using namespace std;
GLint Width = 333, Height = 333;// Начальные размеры окна
int delay = 20;				    // Задержка в МС между последними IDLE
long time0 = 0;					// Отметка системного времени

struct Circle
{
    float x, y;
    float radius;
    float speed;
    bool isFalling;
    int layer;
};

vector<Circle> circles;
int timerInterval = 400;
int circleSegments = 32;
float gravity = 0.05f;
float minSpeed = 0.2f;
float maxSpeed = 1.0f;

bool CirclesIntersect(const Circle& a, const Circle& b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    float minDistance = a.radius + b.radius;
    return (dx * dx + dy * dy) < (minDistance * minDistance); // Без sqrt для оптимизации
}

// прототипы функцийСо
void Initialize();
void Timer(int value);
void DrawCircle(float x, float y, float radius);
void UpdateCircles();
void Display(void);
void Reshape(GLint w, GLint h);
void Keyboard(unsigned char key, int x, int y);
void Idle();

void Initialize() {
    srand(time(NULL));

    // Запускаем таймер
    glutTimerFunc(timerInterval, Timer, 0);
}

void Timer(int value) {
    // Создаем новый круг
    Circle newCircle;
    newCircle.x = rand() % (Width - 100) + 50;
    newCircle.y = Height + 20;
    newCircle.radius = 5;
    newCircle.speed = minSpeed + (rand() % 100) / 100.0f * (maxSpeed - minSpeed);

    // Добавляем в вектор
    circles.push_back(newCircle);

    glutPostRedisplay();
    glutTimerFunc(timerInterval, Timer, 0);
}

void UpdateCircles() {
    // Сортируем круги по Y
    sort(circles.begin(), circles.end(),
        [](const Circle& a, const Circle& b) { return a.y > b.y; });

    for (size_t i = 0; i < circles.size(); i++) {
        if (!circles[i].isFalling) {
            continue; // Круг уже лежит
        }

        // Проверяем столкновение с нижней границей
        if (circles[i].y - circles[i].speed <= circles[i].radius) {
            circles[i].y = circles[i].radius;
            circles[i].speed = 0;
            circles[i].isFalling = false;
            continue;
        }

        // Проверяем столкновение с другими кругами
        bool canFall = true;
        float newY = circles[i].y - circles[i].speed;

        for (size_t j = 0; j < circles.size(); j++) {
            if (i == j || circles[j].isFalling) {
                continue; // Не проверяем с падающими или с собой
            }

            Circle temp = circles[i];
            temp.y = newY;

            if (CirclesIntersect(temp, circles[j])) {
                // Находим точку касания
                circles[i].y = circles[j].y + circles[j].radius + circles[i].radius;
                circles[i].speed = 0;
                circles[i].isFalling = false;
                canFall = false;
                break;
            }
        }

        if (canFall) {
            circles[i].y = newY;
            circles[i].speed += gravity;
        }
    }
}

void DrawCircle(float x, float y, float radius) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);

    for (int i = 0; i <= circleSegments; i++) {
        float angle = 2.0f * 3.1415926f * float(i) / float(circleSegments);
        float dx = radius * cosf(angle);
        float dy = radius * sinf(angle);
        glVertex2f(x + dx, y + dy);
    }

    glEnd();
}

void Display(void) {				// Вывод на экран
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    for (const auto& circle : circles) {
        DrawCircle(circle.x, circle.y, circle.radius);
    }
    glFinish();
}



void Reshape(GLint w, GLint h) {		// Событие - изменение размеров окна
    Width = w;						// Запомнить новые размеры
    Height = h;
    glViewport(0, 0, w, h);			// Область отображения
    glMatrixMode(GL_PROJECTION);	// Ортографическая проекция
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Keyboard(unsigned char key, int x, int y) {
#define ESCAPE '\033'	// Событие - символ клавиатуры
    if (key == ESCAPE)		// Клавиша ESCAPE
        exit(0);			// Закрыть программу
}

void Idle() {				// Постоянное событие - IDLE
    if (clock() - time0 < delay)
        return;				// Не истек интервал delay
    time0 = clock();			// Запомнить новую отметку времени
    UpdateCircles();
    glutPostRedisplay();	// Иниициировать событие Display
}

int main(int argc, char* argv[]) {
    time0 = clock();					// Системное время в МС
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(Width, Height);	// Размер окна
    glutCreateWindow("Snowrain");
    Initialize();
    glutDisplayFunc(Display);			// Функция отображения
    glutReshapeFunc(Reshape);			// Функция смены размерности окна
    glutKeyboardFunc(Keyboard);			// Функция обраболтки клавиатуры
    glutIdleFunc(Idle);					// Функцция простоя IDLE
    glutMainLoop();						// Main библиотеки
}