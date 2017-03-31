#include<stdio.h>
#include<math.h>
#include<GL/GLUT.h>

float x1 = 0.5;
GLfloat C[8][3] = { { 0, 0, 0 }, { 1, 0, 0 }, { 0, 1, 0 }, { 1, 1, 0 }, { 0, 0, 1 }, { 1, 0, 1 }, { 1, 1, 1 }, { 0, 1, 1 } };
GLfloat t[] = { 0, 0, 0 };
int j = 1;
void road1(float x, float y, float z, float h, float w);
static GLfloat wall_mat[] = { 1.f, 1.f, 1.f, 1.f };
static GLfloat lightpos[] = { 50.f, 50.f, -320.f, 1.f };
static GLfloat theta[] = { 0.0, 0.0, 0.0 };
static GLint axis = 2;
static GLdouble viewer[] = { 0.0, 0.0, 5.0 }; /* initial viewer location */

float  h = 5, h1 = 6, d1 = 4, g = 1, g1 = 2;
void apart(float x, float y, float z);

float aa, bb, cc;
void pfindr(float a[], float b[], float a1[], float b1[])
{
	float c[2];
	c[0] = (b[0] + a[0]) / 2.0;
	c[1] = (b[1] + a[1]) / 2.0;

	a1[0] = (c[0] + a[0]) / 2.0;
	a1[1] = (c[1] + a[1]) / 2.0;

	b1[0] = (b[0] + c[0]) / 2.0;
	b1[1] = (b[1] + c[1]) / 2.0;

	a1[0] = (a1[0] + a[0]) / 2.0;
	a1[1] = (a1[1] + a[1]) / 2.0;

	b1[0] = (b[0] + b1[0]) / 2.0;
	b1[1] = (b[1] + b1[1]) / 2.0;

	a1[0] = (a1[0] + a[0]) / 2.0;
	a1[1] = (a1[1] + a[1]) / 2.0;

	b1[0] = (b[0] + b1[0]) / 2.0;
	b1[1] = (b[1] + b1[1]) / 2.0;
	aa += 0.02;
	bb += 0.02;
	cc += 0.02;

}

void dnd(float a[], float b[], float c[], float d[], int n)
{

	float a1[3], b1[3], c1[3], d1[3], a2[3], b2[3], c2[3], d2[3];
	if (n>0)
	{
		pfindr(a, b, a1, b1);
		pfindr(a, d, a2, d2);
		pfindr(b, c, b2, c2);
		pfindr(d, c, d1, c1);

		glBegin(GL_LINE_LOOP);
		glVertex3f(a[0], a[1], a[2]);
		glVertex3f(b[0], b[1], b[2]);
		glVertex3f(c[0], c[1], c[2]);
		glVertex3f(d[0], d[1], c[2]);
		glEnd();
		a1[1] = a2[1];
		b1[1] = b2[1];
		c1[1] = c2[1];
		d1[1] = d2[1];
		a1[2] = a[2] + 02;
		b1[2] = b[2] + 02;
		c1[2] = c[2] + 02;
		d1[2] = d[2] + 02;

		glColor3f(aa, bb, cc);
		glBegin(GL_POLYGON);
		glVertex3fv(a);
		glVertex3fv(b);
		glVertex3fv(b1);
		glVertex3fv(a1);
		glEnd();


		glBegin(GL_POLYGON);
		glVertex3fv(b);
		glVertex3fv(c);
		glVertex3fv(c1);
		glVertex3fv(b1);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3fv(d);
		glVertex3fv(c);
		glVertex3fv(c1);
		glVertex3fv(d1);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3fv(a);
		glVertex3fv(d);
		glVertex3fv(d1);
		glVertex3fv(a1);
		glEnd();


		dnd(a1, b1, c1, d1, n - 1);
	}
}

void stand(float x, float y, float z)
{
	glColor3f(1, 0.8, 0);
	glBegin(GL_POLYGON);
	glVertex3f(x, y, z);
	glVertex3f(x, y - h1, z + d1);
	glVertex3f(x + h, y - h1, z + d1);
	glVertex3f(x + h, y, z);
	glEnd();
	glColor3f(1, 0.5, 0);
	glBegin(GL_POLYGON);
	glVertex3f(x, y, z);
	glVertex3f(x + h, y, z);
	glVertex3f(x + h, y - h1, z - d1);
	glVertex3f(x, y - h1, z - d1);
	glEnd();

	glColor3f(0.6, 0.12, 0.4);

	glBegin(GL_POLYGON);
	glVertex3f(x, y - h1, z + d1);
	glVertex3f(x, y - h1 - 2, z + d1);
	glVertex3f(x + 1, y - h1 - 2, z + d1);
	glVertex3f(x + 1, y - h1, z + d1);
	glEnd();

	glColor3f(0.6, 0.12, 0.4);
	glBegin(GL_POLYGON);
	glVertex3f(x + h, y - h1, z + d1);
	glVertex3f(x + h, y - h1 - 2, z + d1);
	glVertex3f(x + h - 1, y - h1 - 2, z + d1);
	glVertex3f(x + h - 1, y - h1, z + d1);
	glEnd();

	glColor3f(0.6, 0.12, 0.4);

	glBegin(GL_POLYGON);
	glVertex3f(x, y - h1, z - d1);
	glVertex3f(x, y - h1 - 2, z - d1);
	glVertex3f(x + 1, y - h1 - 2, z - d1);
	glVertex3f(x + 1, y - h1, z - d1);
	glEnd();

	glColor3f(0.6, 0.12, 0.4);

	glBegin(GL_POLYGON);
	glVertex3f(x + h, y - h1, z - d1);
	glVertex3f(x + h, y - h1 - 2, z - d1);
	glVertex3f(x + h - 1, y - h1 - 2, z - d1);
	glVertex3f(x + h - 1, y - h1, z - d1);
	glEnd();
}


void house(float x, float y, float z)
{
	glColor3f(0.01, 0.05, 0.3);
	glBegin(GL_POLYGON);
	glVertex3f(x, y, z);
	glVertex3f(x, y, z + 30);
	glVertex3f(x, y + 15, z + 30);
	glVertex3f(x, y + 15, z);
	glEnd();

	glColor3f(0.01, 0.05, 0.3);
	glBegin(GL_POLYGON);
	glVertex3f(x - 15, y, z);
	glVertex3f(x - 15, y + 15, z);
	glVertex3f(x - 15, y + 15, z + 30);
	glVertex3f(x - 15, y, z + 30);
	glEnd();

	glColor3f(0.01, 0.05, 0.3);
	glBegin(GL_POLYGON);
	glVertex3f(x, y, z + 30);
	glVertex3f(x - 15, y, z + 30);
	glVertex3f(x - 15, y + 15, z + 30);
	glVertex3f(x, y + 15, z + 30);
	glEnd();

	glColor3f(0.01, 0.05, 0.3);
	glBegin(GL_POLYGON);
	glVertex3f(x - 15, y, z);
	glVertex3f(x - 15, y + 15, z);
	glVertex3f(x, y + 15, z);
	glVertex3f(x, y, z);
	glEnd();

	glColor3f(0.01, 0.05, 1.5);
	glBegin(GL_POLYGON);
	glVertex3f(x - 15, y, z);
	glVertex3f(x, y, z);
	glVertex3f(x, y, z + 30);
	glVertex3f(x - 15, y, z + 30);
	glEnd();


	glColor3f(0.51, 0.015, 0.008);
	glBegin(GL_POLYGON);
	glVertex3f(x + 1.69 * 3, y + 3.5 * 3, z);
	glVertex3f(x - 2.5 * 3, y + 7.5 * 3, z);
	glVertex3f(x - 2.5 * 3, y + 7.5 * 3, z + 30);
	glVertex3f(x + 1.69 * 3, y + 3.5 * 3, z + 30);
	glEnd();


	glColor3f(0.51, 0.015, 0.008);
	glBegin(GL_POLYGON);
	glVertex3f(x - 6.69 * 3, y + 3.5 * 3, z);
	glVertex3f(x - 6.69 * 3, y + 3.5 * 3, z + 30);
	glVertex3f(x - 2.5 * 3, y + 7.5 * 3, z + 30);
	glVertex3f(x - 2.5 * 3, y + 7.5 * 3, z);
	glEnd();


	glColor3f(0.1, 0.015, 0.13);
	glBegin(GL_POLYGON);
	glVertex3f(x, y + 15, z);
	glVertex3f(x - 15, y + 5, z);
	glVertex3f(x - 2.5 * 3, y + 7.5 * 3, z);
	glEnd();

	glColor3f(0.1, 0.015, 0.13);
	glBegin(GL_POLYGON);
	glVertex3f(x, y + 15, z + 30);
	glVertex3f(x - 15, y + 15, z + 30);
	glVertex3f(x - 2.5 * 3, y + 7.5 * 3, z + 30);
	glEnd();
}


void land()
{
	glColor3f(0.8, 0.6, 0.4);
	glBegin(GL_POLYGON);
	glVertex3f(-200, -200, 0);
	glVertex3f(200, -200, 0);
	glVertex3f(200, 200, 0);
	glVertex3f(-200, 200, 0);
	glEnd();

	//Main Road
	glPushMatrix();
	glTranslated(20, -30, 0);
	glRotated(90, 0, 0, 1);
	road1(-170, 25, 0.1, 30, 400);
	glPopMatrix();

	/////////////////////////////
	glPushMatrix();
	glTranslated(20, 5, 0);
	glRotated(180, 0, 0, 1);
	road1(-90, -50, 0.1, 12, 111);	glPopMatrix();

	glPushMatrix();
	glTranslated(20, -30, 0);
	glRotated(270, 0, 0, 1);
	road1(-93, 90, 0.1, 11, 263);
	glPopMatrix();


	glPushMatrix();
	glTranslated(20, -30, 0);
	glRotated(180, 0, 0, 1);
	road1(-180, 40, 0.1, 12, 90);
	glPopMatrix();


	glPushMatrix();
	glTranslated(20, -30, 0);
	glRotated(180, 0, 0, 1);
	road1(20, 120, 0.1, 12, 200);
	glPopMatrix();


	glPushMatrix();
	glTranslated(20, -30, 0);
	glRotated(180, 0, 0, 1);
	road1(20, -120, 0.1, 12, 200);
	glPopMatrix();


	glPushMatrix();
	glTranslated(20, -30, 0);
	glRotated(90, 0, 0, 1);
	road1(-119, 120, 0.1, 12, 240);
	glPopMatrix();


}



void road1(float x, float y, float z, float h, float w)
{

	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(x, y, z);
	glVertex3f(x, y - h, z);
	glVertex3f(x + w, y - h, z);
	glVertex3f(x + w, y, z);
	glEnd();

	glColor3f(0.3, 0.3, 0.3);
	glBegin(GL_POLYGON);
	glVertex3f(x, y - 1, z + 1);
	glVertex3f(x, y - h + 1, z + 1);
	glVertex3f(x + w, y - h + 1, z + 1);
	glVertex3f(x + w, y - 1, z + 1);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(x, y, z);
	glVertex3f(x, y - 1, z + 1);
	glVertex3f(x + w, y - 1, z + 1);
	glVertex3f(x + w, y, z);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(x, y - h, z);
	glVertex3f(x, y - h + 1, z + 1);
	glVertex3f(x + w, y - h + 1, z + 1);
	glVertex3f(x + w, y - h, z);

	glEnd();
}


void modl1(float x, float y, float z, float h, float wx, float wy)
{
	glColor3f(0, 0, 0.250);

	glBegin(GL_POLYGON);
	glVertex3f(x, y, z);
	glVertex3f(x + wx, y, z);
	glVertex3f(x + wx, y + wy, z);
	glVertex3f(x, y + wy, z);
	glEnd();
	glColor3f(0.7, 0.250, 0);

	glBegin(GL_POLYGON);
	glVertex3f(x, y, z - h / 4);
	glVertex3f(x + wx, y, z - h / 4);
	glVertex3f(x + wx, y + wy, z - h / 4);
	glVertex3f(x, y + wy, z - h / 4);
	glEnd();

	glColor3f(0.7, 0, 01);
	glBegin(GL_POLYGON);
	glVertex3f(x, y, z);
	glVertex3f(x, y, z - h / 4);
	glVertex3f(x + wx, y, z - h / 4);
	glVertex3f(x + wx, y, z);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(x, y + wy, z);
	glVertex3f(x, y + wx, z - h / 4);
	glVertex3f(x + wx, y + wx, z - h / 4);
	glVertex3f(x + wx, y + wx, z);
	glEnd();
	glColor3f(0.7, 0, 01);
	glBegin(GL_POLYGON);
	glVertex3f(x, y, z);
	glVertex3f(x, y, z - h / 4);
	glVertex3f(x, y + wy, z - h / 4);
	glVertex3f(x, y + wy, z);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(x + wx, y, z);
	glVertex3f(x + wx, y, z - h / 4);
	glVertex3f(x + wx, y + wx, z - h / 4);
	glVertex3f(x + wx, y + wx, z);
	glVertex3f(x + wx - wx / 8, y + wy / 4, z);

	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(x + wx / 8, y + wy / 4, z);//1
	glVertex3f(x + wx / 8, y + wy / 4, z + h);//1
	glVertex3f(x + wx / 8, y + wy - wy / 8, z + h);//4

	glVertex3f(x + wx / 8, y + wy - wy / 8, z);//4
	glEnd();
	glColor3f(0.7, 0, 01);
	glBegin(GL_POLYGON);
	glVertex3f(x + wx - wx / 8, y + wy / 4, z);//2
	glVertex3f(x + wx - wx / 8, y + wy / 4, z + h);//2
	glVertex3f(x + wx - wx / 8, y + wy - wy / 8, z + h);//3
	glVertex3f(x + wx - wx / 8, y + wy - wy / 8, z);//3
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + wx - wx / 8, y + wy - wy / 8, z + h);//3
	glVertex3f(x + wx - wx / 8, y + wy - wy / 8, z);//3
	glVertex3f(x + wx / 8, y + wy - wy / 8, z);//4

	glVertex3f(x + wx / 8, y + wy - wy / 8, z + h);//4
	glEnd();

	/////////////////////////////////////
	glColor3f(0.7, 0, 0.250);

	glBegin(GL_POLYGON);
	glVertex3f(x, y, z + h);
	glVertex3f(x + wx, y, z + h);
	glVertex3f(x + wx, y + wy, z + h);
	glVertex3f(x, y + wy, z + h);
	glEnd();
	glColor3f(0.7, 0.250, 0);

	glBegin(GL_POLYGON);
	glVertex3f(x, y, z + h + h / 4);
	glVertex3f(x + wx, y, z + h + h / 4);
	glVertex3f(x + wx, y + wy, z + h + h / 4);
	glVertex3f(x, y + wy, z + h + h / 4);
	glEnd();

	glColor3f(0.7, 0, 01);
	glBegin(GL_POLYGON);
	glVertex3f(x, y, z + h);
	glVertex3f(x, y, z + h / 4 + h);
	glVertex3f(x + wx, y, z + h / 4 + h);
	glVertex3f(x + wx, y, z + h);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(x, y + wy, z + h);
	glVertex3f(x, y + wx, z + h / 4 + h);
	glVertex3f(x + wx, y + wx, z + h / 4 + h);
	glVertex3f(x + wx, y + wx, z + h);
	glEnd();
	glColor3f(0.7, 0, 01);
	glBegin(GL_POLYGON);
	glVertex3f(x, y, z + h);
	glVertex3f(x, y, z + h + h / 4);
	glVertex3f(x, y + wy, z + h + h / 4);
	glVertex3f(x, y + wy, z + h);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(x + wx, y, z + h);
	glVertex3f(x + wx, y, z + h + h / 4);
	glVertex3f(x + wx, y + wx, z + h + h / 4);
	glVertex3f(x + wx, y + wx, z + h);
	glEnd();

}

void house1()
{
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	///stand(10,10,1);
	//house(150,0.1,-60);
	glPopMatrix();


	glPushMatrix();
	glRotated(90, 1, 0, 0);
	stand(-110, 10, 1);
	house(-60, 0.1, -10);
	glPopMatrix();

	glPushMatrix();
	glRotated(90, 1, 0, 0);
	//stand(10,10,1);
	house(-100, 0.1, -150);
	glPopMatrix();

	glPushMatrix();
	glRotated(90, 1, 0, 0);

	house(70, 0.1, 150);
	glPopMatrix();

	glPushMatrix();
	glRotated(90, 1, 0, 0);

	house(90, 0.1, -30);
	glPopMatrix();

	glPushMatrix();
	glRotated(90, 1, 0, 0);

	house(50, 0.1, -30);
	glPopMatrix();

	glPushMatrix();
	glRotated(90, 1, 0, 0);

	house(60, 0.1, 10);
	glPopMatrix();


	glPushMatrix();
	glRotated(90, 1, 0, 0);

	house(55, 0.1, 110);
	glPopMatrix();


	glPushMatrix();
	glRotated(90, 1, 0, 0);
	//stand(10,10,1);
	house(135, 0.1, 95);
	glPopMatrix();

	glPushMatrix();
	glRotated(90, 1, 0, 0);

	house(85, 0.1, 115);
	glPopMatrix();	glPopMatrix();

	glPushMatrix();
	glRotated(90, 1, 0, 0);

	apart(150, 0, -150);
	glPopMatrix();
	glPushMatrix();
	glRotated(90, 1, 0, 0);

	apart(39, 0, 50);
	glPopMatrix();
	glPushMatrix();
	glRotated(90, 1, 0, 0);

	apart(150, 0, -90);
	glPopMatrix();
	glPushMatrix();
	glRotated(90, 1, 0, 0);

	apart(150, 0, -30);
	glPopMatrix();

	glPushMatrix();
	glRotated(90, 1, 0, 0);

	apart(150, 0.1, -190);
	glPopMatrix();

	glColor3f(0.2, 0.2, 0.2);
	glPushMatrix();
	glTranslated(-167, -15, 5);
	glScalef(3, 5, 0.51);
	glutSolidCube(20);
	glPopMatrix();


}

void circle1(float c[20][2])
{
	float x = 0, y = 03;
	int i;
	for (i = 0; i<20; i++)
	{
		c[i][0] = x*cos((i + 1) * 36 * (3.142 / 360)) - y*sin((i + 1) * 36 * (3.142 / 360));
		c[i][1] = x*sin((i + 1) * 36 * (3.142 / 360)) + y*cos((i + 1) * 36 * (3.142 / 360));
	}

	for (i = 0; i<19; i++)
	{
		glBegin(GL_POLYGON);
		glVertex3f(c[i][0], c[i][1], 0);
		glVertex3f(c[i][0], c[i][1], 40);
		glVertex3f(c[i + 1][0], c[i + 1][1], 40);
		glVertex3f(c[i + 1][0], c[i + 1][1], 0);
		glEnd();
	}

	glBegin(GL_POLYGON);
	glVertex3f(c[0][0], c[0][1], 0);
	glVertex3f(c[0][0], c[0][1], 40);
	glVertex3f(c[19][0], c[19][1], 40);
	glVertex3f(c[19][0], c[19][1], 0);
	glEnd();

}
void forest()
{
	int i;
	float cc[20][2];
	for (i = 0; i<5; i++)
	{
		glColor3f(0.3, 0.015, 0.13);
		glPushMatrix();		glTranslatef(-105, -130 + 20 * i, 5);

		circle1(cc);
		glPopMatrix();

		glColor3f(0.015, 0.3, 0.13);
		glPushMatrix();		glTranslatef(-105, -130 + 20 * i, 45);
		glScalef(1, 1, 3);
		glutSolidSphere(10, 12, 4);
		glFlush();
		glPopMatrix();
	}
	for (i = 8; i<11; i++)
	{
		glColor3f(0.3, 0.015, 0.13);
		glPushMatrix();		glTranslatef(-105, -130 + 20 * i, 5);

		circle1(cc);
		glPopMatrix();

		glColor3f(0.015, 0.3, 0.13);
		glPushMatrix();		glTranslatef(-105, -130 + 20 * i, 45);
		glScalef(1, 1, 3);
		glutSolidSphere(10, 12, 4);
		glFlush();
		glPopMatrix();
	}
	for (i = 8; i<12; i++)
	{
		glColor3f(0.3, 0.015, 0.13);
		glPushMatrix();		glTranslatef(30 - 20 * i, -130, 5);

		circle1(cc);
		glPopMatrix();

		glColor3f(0.015, 0.3, 0.13);
		glPushMatrix();		glTranslatef(30 - 20 * i, -130, 45);
		glScalef(1, 1, 3);
		glutSolidSphere(10, 12, 4);
		glFlush();
		glPopMatrix();
	}

	for (i = 8; i<12; i++)
	{
		glColor3f(0.3, 0.015, 0.13);
		glPushMatrix();		glTranslatef(30 - 20 * i, 80, 5);

		circle1(cc);
		glPopMatrix();

		glColor3f(0.015, 0.3, 0.13);
		glPushMatrix();		glTranslatef(30 - 20 * i, 80, 45);
		glScalef(1, 1, 3);
		glutSolidSphere(10, 12, 4);
		glFlush();
		glPopMatrix();
	}

}

void circle()
{
	float c[20][2];
	float x = 0, y = 0.9;
	int i;
	for (i = 0; i<20; i++)
	{
		c[i][0] = x*cos((i + 1) * 36 * (3.142 / 360)) - y*sin((i + 1) * 36 * (3.142 / 360));
		c[i][1] = x*sin((i + 1) * 36 * (3.142 / 360)) + y*cos((i + 1) * 36 * (3.142 / 360));
	}

	for (i = 0; i<19; i++)
	{
		glBegin(GL_POLYGON);
		glVertex3f(c[i][0], c[i][1], 0);
		glVertex3f(c[i][0], c[i][1], 15);
		glVertex3f(c[i + 1][0], c[i + 1][1], 15);
		glVertex3f(c[i + 1][0], c[i + 1][1], 0);
		glEnd();
	}

	glBegin(GL_POLYGON);
	glVertex3f(c[0][0], c[0][1], 0);
	glVertex3f(c[0][0], c[0][1], 15);
	glVertex3f(c[19][0], c[19][1], 15);
	glVertex3f(c[19][0], c[19][1], 0);
	glEnd();
	x = 0, y = 04;

	for (i = 0; i<20; i++)
	{
		c[i][0] = x*cos((i + 1) * 36 * (3.142 / 360)) - y*sin((i + 1) * 36 * (3.142 / 360));
		c[i][1] = x*sin((i + 1) * 36 * (3.142 / 360)) + y*cos((i + 1) * 36 * (3.142 / 360));
	}

	glBegin(GL_POLYGON);
	for (i = 0; i<20; i++)
		glVertex3f(c[i][0], c[i][1], 15);

	glEnd();
	for (i = 0; i<19; i++)
	{
		glBegin(GL_POLYGON);
		glVertex3f(c[i][0], c[i][1], 17);
		glVertex3f(c[i][0], c[i][1], 15);
		glVertex3f(c[i + 1][0], c[i + 1][1], 15);
		glVertex3f(c[i + 1][0], c[i + 1][1], 17);
		glEnd();
	}

	glBegin(GL_POLYGON);
	glVertex3f(c[0][0], c[0][1], 17);
	glVertex3f(c[0][0], c[0][1], 15);
	glVertex3f(c[19][0], c[19][1], 15);
	glVertex3f(c[19][0], c[19][1], 17);
	glEnd();

	glBegin(GL_POLYGON);
	for (i = 0; i<20; i++)
		glVertex3f(c[i][0], 0, c[i][1]);

	glEnd();

}





void apart(float x, float y, float z)
{
	int i;
	glColor3f(0.6, 0.6, 0.6);
	glBegin(GL_POLYGON);
	glVertex3f(x, y, z + 0.5);
	glVertex3f(x + 45, y, z + 0.5);
	glVertex3f(x + 45, y + 100, z + 0.5);
	glVertex3f(x, y + 100, z + 0.5);
	glEnd();  glColor3f(0.8, 0.8, 0.8);
	for (j = 0; j<8; j++)
	{

		glPushMatrix();
		glTranslatef(0, -12 * j, 0);
		for (i = 0; i<4; i++)
		{
			glPushMatrix();
			glTranslatef(11 * i, 0, 0);
			glBegin(GL_POLYGON);
			glVertex3f(x + 2, y + 98, z);
			glVertex3f(x + 10, y + 98, z);
			glVertex3f(x + 10, y + 88, z);
			glVertex3f(x + 2, y + 88, z);
			glEnd();
			glPopMatrix();
		}glPopMatrix();
	}glColor3f(0, 0, 0);
	for (j = 0; j<8; j++)
	{

		glPushMatrix();
		glTranslatef(0, -12 * j, 0);
		for (i = 0; i<4; i++)
		{
			glPushMatrix();
			glTranslatef(11 * i, 0, 0);
			glBegin(GL_LINE_LOOP);
			glVertex3f(x + 2, y + 98, z);
			glVertex3f(x + 10, y + 98, z);
			glVertex3f(x + 10, y + 88, z);
			glVertex3f(x + 2, y + 88, z);
			glEnd();
			glPopMatrix();
		}glPopMatrix();
	}



	glColor3f(0.6, 0.6, 0.6);
	glBegin(GL_POLYGON);
	glVertex3f(x, y, z + 45 - 0.5);
	glVertex3f(x + 45, y, z + 45 - 0.5);
	glVertex3f(x + 45, y + 100, z + 45 - 0.5);
	glVertex3f(x, y + 100, z + 45 - 0.5);
	glEnd();  	glColor3f(0.8, 0.8, 0.8);

	for (j = 0; j<8; j++)
	{

		glPushMatrix();
		glTranslatef(0, -12 * j, 0);
		for (i = 0; i<4; i++)
		{
			glPushMatrix();
			glTranslatef(11 * i, 0, 0);
			glBegin(GL_POLYGON);
			glVertex3f(x + 2, y + 98, z + 45);
			glVertex3f(x + 10, y + 98, z + 45);
			glVertex3f(x + 10, y + 88, z + 45);
			glVertex3f(x + 2, y + 88, z + 45);
			glEnd();
			glPopMatrix();
		}glPopMatrix();
	}glColor3f(0, 0, 0);

	for (j = 0; j<8; j++)
	{

		glPushMatrix();
		glTranslatef(0, -12 * j, 0);
		for (i = 0; i<4; i++)
		{
			glPushMatrix();
			glTranslatef(11 * i, 0, 0);
			glBegin(GL_LINE_LOOP);
			glVertex3f(x + 2, y + 98, z + 45);
			glVertex3f(x + 10, y + 98, z + 45);
			glVertex3f(x + 10, y + 88, z + 45);
			glVertex3f(x + 2, y + 88, z + 45);
			glEnd();
			glPopMatrix();
		}glPopMatrix();
	}
	///////////////////////////

	glColor3f(0.6, 0.6, 0.6);
	glBegin(GL_POLYGON);
	glVertex3f(x + 0.5, y, z);
	glVertex3f(x + 0.5, y, z + 45);
	glVertex3f(x + 0.5, y + 100, z + 45);
	glVertex3f(x + 0.5, y + 100, z);
	glEnd();
	glColor3f(0.8, 0.8, 0.8);
	for (j = 0; j<8; j++)
	{

		glPushMatrix();
		glTranslatef(0, -12 * j, 0);
		for (i = 0; i<4; i++)
		{
			glPushMatrix();
			glTranslatef(0, 0, 11 * i);
			glBegin(GL_POLYGON);
			glVertex3f(x, y + 98, z + 2);
			glVertex3f(x, y + 98, z + 10);
			glVertex3f(x, y + 88, z + 10);
			glVertex3f(x, y + 88, z + 2);
			glEnd();
			glPopMatrix();
		}glPopMatrix();
	}glColor3f(0, 0, 0);
	for (j = 0; j<8; j++)
	{

		glPushMatrix();
		glTranslatef(0, -12 * j, 0);
		for (i = 0; i<4; i++)
		{
			glPushMatrix();
			glTranslatef(0, 0, 11 * i);
			glBegin(GL_LINE_LOOP);
			glVertex3f(x, y + 98, z + 2);
			glVertex3f(x, y + 98, z + 10);
			glVertex3f(x, y + 88, z + 10);
			glVertex3f(x, y + 88, z + 2);
			glEnd();
			glPopMatrix();
		}glPopMatrix();
	}
	///////////////////////////
	glColor3f(0.6, 0.6, 0.6);

	glBegin(GL_POLYGON);
	glVertex3f(x + 45 - 0.5, y, z - 0.5);
	glVertex3f(x + 45 - 0.5, y, z + 45 - 0.5);
	glVertex3f(x + 45 - 0.5, y + 100, z + 45 - 0.5);
	glVertex3f(x + 45 - 0.5, y + 100, z - 0.5);
	glEnd(); glColor3f(0.8, 0.8, 0.8);
	for (j = 0; j<8; j++)
	{

		glPushMatrix();
		glTranslatef(0, -12 * j, 0);
		for (i = 0; i<4; i++)
		{
			glPushMatrix();
			glTranslatef(0, 0, 11 * i);
			glBegin(GL_POLYGON);
			glVertex3f(x + 45, y + 98, z + 2);
			glVertex3f(x + 45, y + 98, z + 10);
			glVertex3f(x + 45, y + 88, z + 10);
			glVertex3f(x + 45, y + 88, z + 2);
			glEnd();
			glPopMatrix();
		}glPopMatrix();
	}
	glColor3f(0, 0, 0);
	for (j = 0; j<8; j++)
	{

		glPushMatrix();
		glTranslatef(0, -12 * j, 0);
		for (i = 0; i<4; i++)
		{
			glPushMatrix();
			glTranslatef(0, 0, 11 * i);
			glBegin(GL_LINE_LOOP);
			glVertex3f(x + 45, y + 98, z + 2);
			glVertex3f(x + 45, y + 98, z + 10);
			glVertex3f(x + 45, y + 88, z + 10);
			glVertex3f(x + 45, y + 88, z + 2);
			glEnd();
			glPopMatrix();
		}glPopMatrix();
	}

	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex3f(x, y, z - 0.5);
	glVertex3f(x + 45, y, z - 0.5);
	glVertex3f(x + 45, y, z + 45 - 0.5);
	glVertex3f(x, y, z + 45 - 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x, y + 100, z);
	glVertex3f(x + 45, y + 100, z);
	glVertex3f(x + 45, y + 100, z + 45);
	glVertex3f(x, y + 100, z + 45);
	glEnd();
}

void flag()
{
	glColor3f(0.3, 0, 0);

	glPushMatrix();
	glTranslated(90, 130, 5);
	glutSolidTorus(4, 15, 50, 15);
	glPopMatrix();
	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslated(90, 130, 10);
	glutSolidTorus(4, 10, 50, 15);
	glPopMatrix();
	glColor3f(0.3, 0, 0);
	glPushMatrix();
	glTranslated(90, 130, 15);
	glutSolidTorus(4, 5, 50, 20);
	glPopMatrix();

	float cc[20][2];
	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslated(90, 130, 15);
	glScalef(0.3, 0.3, 3);
	circle1(cc);
	glPopMatrix();
}


float setx = 0.0, sety = 0.0, setz = 0.0;
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glLoadIdentity();
	//	gluLookAt(viewer[0],viewer[1],viewer[2], viewer[3], viewer[4], viewer[5], setx, sety, setz);

	glPointSize(10);
	//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wall_mat);		glRotated(20,0,1,0);

	//glRotated(-80,1,0,0);

	house1();
	glPushMatrix();
	glRotated(180, 0, 1, 0);
	glScaled(0.5, 5, 0.1);
	glTranslated(-1, 20, -17);
	//circle();
	glPopMatrix();
	glPushMatrix();
	//glTranslated(-18,-48,0);
	//glRotated(10,1,0,0);
	land();
	glPopMatrix();


	aa = 0; bb = 0; cc = 0;
	float a[3] = { -30, 30, 25 }, b[3] = { 30, 30, 25 }, c[3] = { 30, -30, 25 }, d[3] = { -30, -30, 25 };
	glPushMatrix();

	glTranslatef(-167, -15, 17);
	dnd(a, b, c, d, 35);
	glPopMatrix();
	float cc[20][2];
	glPushMatrix();
	glTranslatef(-190, 9.8, 5);
	circle1(cc);
	glFlush();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-190, -39, 5);
	circle1(cc);
	glFlush();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-143, 9.8, 5);
	circle1(cc);
	glFlush();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-143, -39, 5);
	circle1(cc);
	glFlush();
	glPopMatrix();

	forest();
	flag();



	//glutPostRedisplay();

	glFlush();

	glutSwapBuffers();
}


void init()
{
	glClearColor(0.2, 0.6, 0.8, 0);
	glOrtho(-250, 250, -250, 250, -500, 500);

}

void sp()
{


	glRotatef(0.000000000000001, 0, 1, 0);
	glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) glRotatef(10, 1, 0.1, 0.1);
	if (btn == GLUT_MIDDLE_BUTTON&&state == GLUT_DOWN) glRotatef(10, 0, 1, 1);
	if (btn == GLUT_RIGHT_BUTTON&&state == GLUT_DOWN) glRotatef(10, 1, 1, 1);
	display();
}


void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	/* Use a perspective view */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) glFrustum(-250.0, 250.0, -250.0 * (GLfloat)h / (GLfloat)w, 250.0* (GLfloat)h / (GLfloat)w, 150.0, 400.0);
	else glFrustum(-250.0, 250.0, -250.0 * (GLfloat)w / (GLfloat)h, 250.0* (GLfloat)w / (GLfloat)h, 150.0, 400.0);


	// gluPerspective(45.0,w/h,-10.0,10.0);
	glMatrixMode(GL_MODELVIEW);
}
void kb(unsigned char k, int x, int y)
{
	if (k == 'x') viewer[0] -= 1.0;
	if (k == 'X') viewer[0] += 1.0;
	if (k == 'y') viewer[1] -= 1.0;
	if (k == 'Y') viewer[1] += 1.0;
	if (k == 'z') viewer[2] -= 1.0;
	if (k == 'Z') viewer[2] += 1.0;
	if (k == 'w') viewer[3] -= 1.0;
	if (k == 'W') viewer[3] += 1.0;
	if (k == 'm') viewer[4] -= 1.0;
	if (k == 'M') viewer[4] += 1.0;
	if (k == 'n') viewer[4] -= 1.0;
	if (k == 'N') viewer[4] += 1.0;

	if (k == '1'){ setx = 1.0; sety = 0, setz = 0; }
	if (k == '2'){ sety = 1.0; setx = 0, setz = 0; }
	if (k == '3'){ setz = 1.0; setx = 0; sety = 0; }
	display();
	if (k == 'q'){ glRotatef(10, 1, 0, 0); glutPostRedisplay(); }
	if (k == 'w'){ glRotatef(10, 0, 1, 0); glutPostRedisplay(); }
	if (k == 'e'){ glRotatef(10, 0, 0, 1); glutPostRedisplay(); }

}
void main(int argc, char **argv)

{
	glutInitWindowSize(1500, 900);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_ACCUM | GLUT_DOUBLE);
	glutCreateWindow("ex");
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(display);

	//glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	init();
	glEnable(GL_DEPTH_TEST);
	glPushMatrix();

	glRotatef(90, 1, 1, 1);
	display();
	glutPostRedisplay();
	glFlush();
	glPopMatrix();


	glutMouseFunc(mouse);
	glutKeyboardFunc(kb);
	glEnable(GL_DEPTH_TEST);

	glutMainLoop();
}

