#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define maxSize 100

typedef char name[maxSize];

typedef struct student
{
    float media;
    int reprov;
    name name;

} Student;

///////////////////////////////////////////////////////////////////// MERGE SORT

void Merge(Student *students, int, int, int);
void Merge_Sort(Student *students, int inicio, int fim);

///////////////////////////////////////////////////////////////////// SELECTION SORT

void Selection_Sort(Student *students, int N);

///////////////////////////////////////////////////////////////////// HELPERS

void display(Student students[], int len, int scholarship);


int main()
{
    int method, numberStudents, numberScholarships = 0;
	int spotsTaken = 0;
	int i = 0, j = 0, k = 0;

	Student *scholarships;
	
    scanf("%d", &method);
    scanf("%d %d", &numberStudents, &numberScholarships);

    Student students[numberStudents];
	Student newList[numberStudents];

    for (i = 0; i < numberStudents; i++)
    {
        Student student;
        scanf("%f %d %s", &student.media, &student.reprov, student.name);
        students[i] = student;
    }

	switch (method)
	{
		case 1:
			Selection_Sort(students, numberStudents);
			break;

		case 2:
			Merge_Sort(students, 0, numberStudents-1);
			break;
		
		default:
			break;
	}

	for (int k = numberStudents-1; k >= 0; k--)
	{
		newList[j] = students[k];
		j++;
	}


	for (k = 0; k < numberStudents; k++)
	{
		spotsTaken++;
		if((newList[k].media == newList[k+1].media) && (newList[k].reprov == newList[k+1].reprov) && (spotsTaken >= numberScholarships))
			numberScholarships++;		
	}

	if(numberStudents < numberScholarships)
		numberScholarships = numberStudents;

	scholarships = (Student*)malloc(numberStudents * sizeof(Student));

	j = 0;
	for (k = 0; k < numberStudents; k++)
	{
		if(newList[k].reprov < 10)
		{
			scholarships[j] = newList[k];
			j++;
		}
			
	}

	display(scholarships, numberStudents, numberScholarships);

    return 0;
}

///////////////////////////////////////////////////////////////////// MERGE SORT

void Merge_Sort(Student *students, int inicio, int fim)
{
	int meio;
	if(inicio < fim)
	{
		meio = floor((inicio+fim)/2);       		// Determina o meio do vetor
		Merge_Sort(students, inicio, meio);        	// Chama a função para a primeira metade
		Merge_Sort(students, meio+1, fim);         	// Chama a função para a segunda metade
		Merge(students, inicio, meio, fim);        	// Combina as duas metades de forma ordenada
	}
}

void Merge(Student *students, int inicio, int meio, int fim)
{
	int i, j, k;
	int p1 = inicio, p2 = meio + 1;
	bool flag1 = false, flag2 = false;
	int size = fim - inicio + 1;

	Student* temp = (Student*)malloc(size*sizeof(Student));

	if(temp != NULL)
	{
		for(i = 0; i < size; i++)
		{
			if(!flag1 && !flag2)
			{	
				if(students[p1].media == students[p2].media)
				{
					// COMPARAR REPROVAÇÕES
					if(students[p1].reprov == students[p2].reprov)
					{
						if(strcmp(students[p1].name, students[p2].name) < 0)
						{
							temp[i] = students[p2];
							p2++;
						}
						else
						{
							temp[i] = students[p1];
							p1++;
						}
					}
					else if (students[p1].reprov < students[p2].reprov)
					{
						temp[i] = students[p2];
						p2++;
					}
					else
					{
						temp[i] = students[p1];
						p1++;
					}	
				}
				else if(students[p1].media > students[p2].media)
				{
					temp[i] = students[p2];
					p2++;
				}
				else
				{
					temp[i] = students[p1];
					p1++;
				}


				if(p1 > meio)
					flag1 = true;
				if(p2 > fim)
					flag2 = true;
			}
			else
			{
				if(!flag1)                           // Copia o restante de p1 caso p2 acabe
					temp[i] = students[p1++];
				else                                // Copia o restante de p2 caso p1 acabe
					temp[i] = students[p2++];
			} 
		}

		for(j = 0, k = inicio; j < size; j++, k++)     // Copia os dados do vetor auxiliar para o original
			students[k] = temp[j];
	}

	free(temp);
}

///////////////////////////////////////////////////////////////////// SELECTION SORT

void Selection_Sort(Student *students, int N)
{
	int i, j, menor;
	Student troca;

	for(i = 0; i < N-1; i++)
	{
		menor = i;
		for(j = i+1; j < N; j++)
		{
			if(students[j].media < students[menor].media)
				menor = j;
			else if(students[j].media == students[menor].media)
			{
				if(students[j].reprov > students[menor].reprov)
					menor = j;
				else if(students[j].reprov == students[menor].reprov)
				{
					if(strcmp(students[j].name, students[menor].name) > 0)
						menor = j;
				}
			}
		}

		if(i != menor)
		{
			troca = students[i];
			students[i] = students[menor];
			students[menor] = troca;
		}
	}
}


///////////////////////////////////////////////////////////////////// HELPERS

void display(Student students[], int len, int scholarship)
{
	printf("%d\n", scholarship);
    for (int i = 0; i < scholarship; i++)
		printf("%s\n", students[i].name);		
}