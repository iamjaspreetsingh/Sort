#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<GL/glut.h>
#define MAX 200		// Number of random values in the sample
int a[MAX];			// Sample Array
int i=0,j=0;
int flag=0;			// For Insertion Sort
int dirflag=0;		// For Ripple Sort
int count=1;		// For Ripple Sort
int sort_no=0;      // Insertion, Selection, Bubble, Ripple, Heap
int n; //for heap sort


void initialize()
{
    // make random nos 0 to 199
    for(int i=0;i<MAX;i++){
		a[i]=rand()%200;
		printf("%d ",a[i]);
	}

	int n = sizeof(a)/sizeof(a[0]); //for heap sort

    //define 2d shape
	glClearColor(1,1,1,1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 699,0,999);
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
    for(int i=0;i<MAX;i++)
    {
        glColor3f(1,0,0);
        glBegin(GL_LINE_LOOP);
        // making vertices of rectangle dividing screen equally
        glVertex2f(10+(700/(MAX+1))*i,50);
        glVertex2f(10+(700/(MAX+1))*(i+1),50);
        glVertex2f(10+(700/(MAX+1))*(i+1),50+a[i]*4);
        glVertex2f(10+(700/(MAX+1))*i,50+a[i]*4);
        glEnd();
    }

	glFlush();
}

// Sorting algorithms functions
void insertionsort()
{
    printf("Insertion sort");
	int temp;
	while(i<MAX)
	{
		if(flag==0){j=i; flag=1;}
		while(j<MAX-1)
		{
			if(a[j]>a[j+1])
			{
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;

				goto A;
			}
			j++;
			if(j==MAX-1){flag=0;}
			printf("swap %d and %d\n",a[j],a[j+1]);
		}
		i++;
	}
	sort_no++;
    initialize();

	A:
	i=j=0;
}

int notsorted(){
	for(int i=0;i<MAX-1;i++)
	{
		if(a[i]>a[i+1])
			return 1;
	}
	return 0;
}

void selectionsort()
{
    printf("Selection sort");
	int temp,j,min,pos;
	while(notsorted())
	{

		while(i<MAX-1)
		{
			min=a[i+1];
			pos=i+1;
			if(i!=MAX-1)
			{
				for(j=i+2;j<MAX;j++)
				{
					if(min>a[j])
					{
						min=a[j];
						pos=j;
					}
				}
			}
			if(min<a[i])
			{
				printf("\nswap %d and %d",min,a[i]);
				temp=a[pos];
				a[pos]=a[i];
				a[i]=temp;
				goto A;
			}
			i++;
		}
	}
    sort_no ++;
    initialize();
	i=j=0;
	A:  printf("");
}

void bubblesort()
{
    printf("Bubble sort");
	int temp;
	while(notsorted())
	{
		while(j<MAX-1)
		{
			if(a[j]>a[j+1])
			{
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;

				goto A;
			}
			j++;
			if(j==MAX-1) j=0;
			printf("swap %d and %d\n",a[j],a[j+1]);
		}
	}
    sort_no++;
    initialize();
    A: printf("");
}


void ripplesort()
{
    printf("Ripple sort");
	int temp;
	while(notsorted())
	{
		if(dirflag==0)
		{
			while(j<MAX-1)
			{
				if(a[j]>a[j+1])
				{
					temp=a[j];
					a[j]=a[j+1];
					a[j+1]=temp;

					goto A;
				}
				j++;
				if(j==MAX-1) {count++; j=MAX-count;	dirflag=1-dirflag;}
				printf("j=%d forward swap %d and %d\n",j,a[j],a[j+1]);
			}
		}
		else
		{
			while(j>=0)
			{
				if(a[j]>a[j+1])
				{
					temp=a[j];
					a[j]=a[j+1];
					a[j+1]=temp;

					goto A;
				}
				j--;
				if(j==0){ dirflag=1-dirflag;}
				printf("j=%d back swap %d and %d\n",j,a[j],a[j+1]);
			}
		}
	}
	sort_no++;
	initialize();
	A: printf("");
}

void heapify(int n, int k)
{
    int largest = k; // Initialize largest as root
    int l = 2*k + 1; // left = 2*i + 1
    int r = 2*k + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && a[l] > a[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && a[r] > a[largest])
        largest = r;

    // If largest is not root
    if (largest != k)
    {
        // swap a[k] a[largest]
        printf("swap %d and %d\n",a[k],a[largest]);
        int temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;
        // Recursively heapify the affected sub-tree
        heapify( n, largest);
        goto A;
    }
    A:  printf("");
}

// main function to do heap sort
void heapSort()
{
    printf("heap sort");

    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify( n, i);

    // One by one extract an element from heap
    for ( i=n-1; i>=0; i--)
    {
        // Move current root to end
        //swap(a[0], a[i]);
        int temp = a[0];
        a[0] = a[i];
        a[i] = temp;
        // call max heapify on the reduced heap
        heapify( i, 0);
        goto A;

    }
    exit(0);
	A:  printf("");

}



void makedelay(int)
{
    switch(sort_no)
    {
        case 5: insertionsort();	break;
        case 1:	selectionsort();	break;
        case 2: bubblesort();	    break;
        case 3: ripplesort();		break;
        case 0: heapSort();		    break;

    }
    glutPostRedisplay();
	glutTimerFunc(5,makedelay,1);
}


int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	//for full screen
	glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH),glutGet(GLUT_SCREEN_HEIGHT));
	glutInitWindowPosition(0,0);
	glutCreateWindow("Random number sorting");
    initialize();
	//screen display function
	glutDisplayFunc(display);
	// to show new screen after every iteration
	glutTimerFunc(5,makedelay,1);
	glutMainLoop();
}
