#include <window.h>
#include <GL/glu.h>
#include <GL/glut.h>

/* Criador - Naylor-C
 * Objetivo : Game of Azumanga Daioh
 * Referência do Código: OpenGL Programming Guide - RedBook
 */

GLfloat angle, fAspect, eyex, eyey, eyez;

void init(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    angle = 45;
    eyex = 0.0;
    eyey = 80.0;
    eyez = 200.0;
}

void visao(void)
{
    // Especifica sistema de coordenadas de projeção
    glMatrixMode(GL_PROJECTION);
    // Inicializa sistema de coordenadas de projeção
    glLoadIdentity();
    // Especifica a projeção perspectiva
    gluPerspective(angle, fAspect, 0.1, 500);
    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    // Inicializa sistema de coordenadas do modelo
    glLoadIdentity();
    // Especifica posição do observador e do alvo
    gluLookAt(eyex, eyey, eyez, 0, 0, 0, 0, 1, 0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
    // Desenha a esfera com a cor corrente (wire-frame)
    glutWireSphere(20, 25, 25);
    // Executa os comandos OpenGL

    59 glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h)
{
    // Para previnir uma divisão por zero
    if (h == 0)
        h = 1;
    // Especifica o tamanho da viewport
    glViewport(0, 0, w, h);
    // Calcula a correção de aspecto
    fAspect = (GLfloat)w / (GLfloat)h;
    visao();
}
/* Controla os eventos de teclado
ao se pressionar as teclas X, Y ou Z
os valores do parametro relativo a eye da
função glLookAt serão modificados
*/
void teclado(unsigned char tecla, int x, int y)
{
    switch (tecla)
    {
    case 'x':
    case 'X': // Incrementa o valor de eyex
        eyex = eyex + 5;
        break;
    case 'y':
    case 'Y': // Incrementa o valor de eyey
        eyey = eyey + 5;
        break;
    case 'Z':
    case 'z': // Incrementa o valor de eyez
        eyez = eyez + 5;
        break;
    case 'O':
    case 'o':
        eyex = 0.0;
        eyey = 80.0;
        eyez = 200.0;
        break;
    }
    visao();
    glutPostRedisplay();
}

void GMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
        if (state == GLUT_DOWN)
        { // Zoom-in
            if (angle >= 10)
                angle -= 5;
        }
    if (button == GLUT_RIGHT_BUTTON)
        if (state == GLUT_DOWN)
        { // Zoom-out
            if (angle <= 130)
                angle += 5;
        }
    visao();
    glutPostRedisplay();
}
/*Programa principal */
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Exemplo 5 - Visualização 3D Wireframe");
    glutKeyboardFunc(teclado);
    glutMouseFunc(GMouse);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}