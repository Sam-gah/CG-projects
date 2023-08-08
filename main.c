#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>

void drawSquare(int x, int y, int size)
{
    rectangle(x, y, x + size, y + size);
}

void drawCircle(int x, int y, int radius)
{
    circle(x, y, radius);
}

void drawEllipse(int x, int y, int a, int b)
{
    ellipse(x, y, 0, 360, a, b);
}
int myRound(double x)
{
    return (int)(x >= 0 ? x + 0.5 : x - 0.5);
}

void performTransformation(int *x, int *y, int size, int tx, int ty)
{

    *x += tx;
    *y += ty;
}

void performRotation(int *x, int *y, int size, int angle)
{

    int centerX = *x + size / 2;
    int centerY = *y + size / 2;

    double radians = (double)angle * M_PI / 180.0;

    int tempX = *x;
    *x = centerX + myRound((tempX - centerX) * cos(radians) - (*y - centerY) * sin(radians));
    *y = centerY + myRound((tempX - centerX) * sin(radians) + (*y - centerY) * cos(radians));
}
void scaleObject(int *size)
{
    char ch;
    int scalingFactor = 5;

    do
    {
        cleardevice();
        drawSquare(getmaxx() / 2 - (*size) / 2, getmaxy() / 2 - (*size) / 2, *size);

        printf("\nUse '+' to zoom in and '-' to zoom out (Press 'q' to exit scaling mode).\n");

        ch = getch();
        if (ch == '+')
        {

            *size += scalingFactor;
        }
        else if (ch == '-')
        {

            if (*size > scalingFactor)
            {
                *size -= scalingFactor;
            }
        }
    } while (ch != 'q'); // Press 'q' to exit scaling mode
}

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    int x, y;
    int size = 100;

    printf("Enter the initial position (x y) of the square: ");
    scanf("%d %d", &x, &y);

    drawSquare(x, y, size);

    printf("Initial square drawn at position (%d, %d) with size %d.\n", x, y, size);

    int choice;
    int exitFlag = 0;

    while (!exitFlag)
    {
        // Display the menu options
        printf("\nUse the following options to interact with the square:\n");
        printf("1. Change Coordinates\n");
        printf("2. Transformation\n");
        printf("3. Rotation\n");
        printf("4. 2D to 3D Scaling\n");
        printf("5. Draw Circle Inside Square\n");
        printf("6. Draw Ellipse Inside Square\n");
        printf("7. Exit\n");

        printf("Enter your choice (1-7): ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("You chose: Change Coordinates\n");
            // Interaction to change coordinates
            printf("Enter the new position (x y) of the square: ");
            scanf("%d %d", &x, &y);
            break;

        case 2:
            printf("You chose: Transformation\n");
            printf("Enter the translation values (tx ty): ");
            int tx, ty;
            scanf("%d %d", &tx, &ty);
            performTransformation(&x, &y, size, tx, ty);
            break;

        case 3:
            printf("You chose: Rotation\n");
            printf("Enter the rotation angle (in degrees): ");
            int angle;
            scanf("%d", &angle);
            performRotation(&x, &y, size, angle);
            break;

        case 4:
            printf("You chose: 2D to 3D Scaling\n");

            scaleObject(&size);
            break;

        case 5:
            printf("You chose: Draw Circle Inside Square\n");

            int centerX_circle = x + size / 2;
            int centerY_circle = y + size / 2;

            int radius_circle = size / 2;

            drawCircle(centerX_circle, centerY_circle, radius_circle);
            break;

        case 6:

            printf("You chose: Draw Ellipse Inside Square\n");

            int centerX_ellipse = x + size / 2;
            int centerY_ellipse = y + size / 2;

            int a_ellipse = size / 2;
            int b_ellipse = size / 4;

            cleardevice();
            drawSquare(x, y, size);

            drawEllipse(centerX_ellipse, centerY_ellipse, a_ellipse, b_ellipse);
            break;

        case 7:
            exitFlag = 1;
            printf("Exiting the program.\n");
            break;

        default:
            printf("Invalid choice! Please select again.\n");
            break;
        }

        cleardevice();
        drawSquare(x, y, size);
    }

    closegraph();
    return 0;
}
