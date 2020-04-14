// Autorzy:
// Daria Wiśniewska, nr indeksu: 129 795
// Sebastian Jarząbek, nr indeksu: 129 674
// Gr. Lab. 1

#include <iostream>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#define _USE_MATH_DEFINES


//using namespace std;

// stałe do obsługi menu podręcznego
enum
{
    wSKALOWANIE_SLONCE,
    mSKALOWANIE_SLONCE,
    wSKALOWANIE_ORBITY,
    mSKALOWANIE_ORBITY,
    ELIPSA,
    ORGINAL,
    EXIT // wyjście
};

// rozmiary bryły obcinania
const GLdouble left = -1.0;
const GLdouble right = 1.0;
const GLdouble bottom = -1.0;
const GLdouble top = 1.0;
const GLdouble nearr = 2.0;
const GLdouble farr = 100.0;

GLfloat size = 0.5;
GLfloat scale = 1.0;            // współczynnik skalowania
GLfloat orbit = 1.0;            // współczynnik odległości orbitowania
GLfloat elipsax = 1.0;
GLfloat rings = 10;
GLfloat radius = 0.3;


int button_state = GLUT_UP;     // wskaźnik naciśnięcia lewego przycisku myszki

int button_x, button_y;         // położenie kursora myszki

GLfloat PI = 3.14;
GLfloat alfa = -PI / 2;
GLfloat skok_point = 0.5f;       //odleglosc punktu obserwowania
GLfloat skok_eye = 1.0f;         //do pozycji oka
GLfloat eyex = 0;                //wspolrzedne pozycji oka
GLfloat eyey = 0;
GLfloat eyez = 40;
GLfloat pointx = skok_point * cos(alfa); //wspolrzedne punktu, w ktory sie patrzymy
GLfloat pointy = 0.0;
GLfloat pointz = skok_point * sin(alfa);

// funkcja generująca scenę 3D
void Display()
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t * 90.0;
    // kolor tła - zawartość bufora koloru
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // czyszczenie bufora koloru
    glClear(GL_COLOR_BUFFER_BIT);
    // slonce   //////////////////
    glPushMatrix();

    gluLookAt(eyex, eyey, eyez, pointx, pointy, pointz, 0.0, 1.0, 0.0);
    // wybór macierzy modelowania
    glMatrixMode(GL_MODELVIEW);
    // macierz modelowania = macierz jednostkowa
    glLoadIdentity();
    // przesunięcie układu współrzędnych obiektu do środka bryły odcinania
    glTranslatef(0, 0, -20);
    // skalowanie obiektu
    glScalef(scale, scale, scale);
    // obroty obiektu
    glRotatef(t, 0, 0, 1);
    // kolor krawędzi obiektu
    glColor3f(1.0, 1.0, 0.0);
    // rysowanie obiektu
        // kula
    glutWireSphere(size + 1.5, 20, 10);        //slonce

        // ziemia    ///////////////
        // przesunięcie układu współrzędnych obiektu do środka bryły odcinania
    glTranslatef(6 * orbit * elipsax * cos(t), 6 * orbit * sin(t), 0);
    // skalowanie obiektu
    glScalef(scale, scale, scale);
    // obroty obiektu 
    glRotatef(a, 0, 0, 1);
    // kolor krawędzi obiektu
    glColor3f(0.0, 0.5, 1.0);
    // rysowanie obiektu
    glutWireSphere(size + 0.5, 30, 10);        //ziemia

        // ksiezyc
    glColor3f(1, 1, 1);                         // kolor
    glTranslatef(2 * orbit * cos(t), 2 * orbit * sin(t), 0);    // przesuniecie WZGLEDEM ZIEMI (dzialamy na tej samej macierzy)
    glRotatef(t, 0, 0, 1);                      // obrot zgodny z faktycznym obrotem ksiezyca (z Ziemi widac tylko jego jedna strone)
    glutWireSphere(size, 15, 5);                 // narysowanie ksiezyca

    glLoadIdentity();
    glTranslatef(0, 0, -20);    // przesuniecie z powrotem do srodka ukladu wspolrzednych
    glColor3f(0, 0.9, 0);
    glTranslatef(10 * orbit * elipsax * cos(t / 2), 10 * orbit * sin(t / 2), 0);
    glRotatef(-a / 2, 0, 0, 1);
    glutWireSphere(size + 0.3, 20, 10);        // zielona planeta
    glColor3f(0.5, 0.0, 0.3);
    glScalef(1, 1, 0.1);
    glutWireTorus(radius, size + 1.0, rings, rings);    // pierscien zielonej planety
    
        
    glPopMatrix();


    // skierowanie poleceń do wykonania
    glFlush();

    glutPostRedisplay();
    // zamiana buforów koloru
    glutSwapBuffers();
}

// zmiana wielkości okna
void Reshape(int width, int height)
{
    // obszar renderingu - całe okno
    glViewport(0, 0, width, height);

    // wybór macierzy rzutowania
    glMatrixMode(GL_PROJECTION);

    // macierz rzutowania = macierz jednostkowa
    glLoadIdentity();

    // wysokość okna większa od wysokości okna
    if (width < height && width > 0)
        glFrustum(left, right, bottom * height / width, top * height / width, nearr, farr);
    else
        // szerokość okna większa lub równa wysokości okna
        if (width >= height && height > 0)
            glFrustum(left * width / height, right * width / height, bottom, top, nearr, farr);

    // generowanie sceny 3D
    Display();
}

// obsługa kamery strzałkami
void SpecialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        alfa -= PI / 32;
        pointx = skok_point * cos(alfa) + eyex;
        pointz = skok_point * sin(alfa) + eyez;
        break;
    case GLUT_KEY_RIGHT:
        alfa += PI / 32;
        pointx = skok_point * cos(alfa) + eyex;
        pointz = skok_point * sin(alfa) + eyez;
        break;
    case GLUT_KEY_UP:
        skok_eye += 1.0f;
        eyex = skok_eye * cos(alfa) + eyex;
        eyez = skok_eye * sin(alfa) + eyez;
        pointx = skok_point * cos(alfa) + eyex;
        pointz = skok_point * sin(alfa) + eyez;
        skok_eye = 0.0f;
        break;
    case GLUT_KEY_DOWN:
        skok_eye -= 1.0f;
        eyex = skok_eye * cos(alfa) + eyex;
        eyez = skok_eye * sin(alfa) + eyez;
        pointx = skok_point * cos(alfa) + eyex;
        pointz = skok_point * sin(alfa) + eyez;
        skok_eye = 0.0f;
        break;
    }
    Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

// obsługa menu podręcznego

void Menu(int value)
{
    switch (value)
    {
    case wSKALOWANIE_SLONCE:
        size += 0.7;
        rings += 2;
        radius += 0.1;
        break;
    case mSKALOWANIE_SLONCE:
        size -= 0.7;
        rings -= 2;
        radius -= 0.1;
        break;
    case wSKALOWANIE_ORBITY:
        orbit += 0.2;
        break;
    case mSKALOWANIE_ORBITY:
        orbit -= 0.2;
        break;
    case ELIPSA:
        elipsax = 2.0;
        break;
    case ORGINAL:
        size = 0.5;
        orbit = 1;
        elipsax = 1.0;
        rings = 10;
        radius = 0.3;
        break;
        // wyjście
    case EXIT:
        exit(0);
    }
}



int main(int argc, char* argv[])
{
    // inicjalizacja biblioteki GLUT
    glutInit(&argc, argv);

    // inicjalizacja bufora ramki
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // rozmiary głównego okna programu
    glutInitWindowSize(800, 800);

    // utworzenie głównego okna programu
#ifdef WIN32

    glutCreateWindow("Przekształcenia");
#else

    glutCreateWindow("Przeksztalcenia");
#endif

    // dołączenie funkcji generującej scenę 3D
    glutDisplayFunc(Display);

    // dołączenie funkcji wywoływanej przy zmianie rozmiaru okna
    glutReshapeFunc(Reshape);


    // dołączenie funkcji obsługi klawiszy funkcyjnych i klawiszy kursora
    glutSpecialFunc(SpecialKeys);

    // menu główne
    glutCreateMenu(Menu);
    glutAddMenuEntry("Skalowanie wzgledem slonca (zwieksz odleglosc)", wSKALOWANIE_SLONCE);
    glutAddMenuEntry("Skalowanie wzgledem slonca (zmniejsz odleglosc)", mSKALOWANIE_SLONCE);
    glutAddMenuEntry("Skalowanie wzgledem orbit (zwieksz odleglosc)", wSKALOWANIE_ORBITY);
    glutAddMenuEntry("Skalowanie wzgledem orbit (zmniejsz odleglosc)", mSKALOWANIE_ORBITY);
    glutAddMenuEntry("Ruch po elipsach", ELIPSA);
    glutAddMenuEntry("Ustawienia domyslne", ORGINAL);
#ifdef WIN32

    glutAddMenuEntry("Wyjscie", EXIT);
#else

    glutAddMenuEntry("Wyjscie", EXIT);
#endif

    // określenie przycisku myszki obsługującego menu podręczne
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    std::cout << "Przedstawienie przeksztalcen obiektow trojwymiarowych\n"
        << "Klawisze strzalek przesuwaja kamere\n"
        << "Prawy przycisk myszy otwiera menu" << std::endl;


    // wprowadzenie programu do obsługi pętli komunikatów
    glutMainLoop();

    return 0;
}

