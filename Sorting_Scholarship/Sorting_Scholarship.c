/////////////////////////////////
// TRABALHO ED 2 - HELOÍSA PAZETI
/////////////////////////////////


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

int SetScholarshipQuant(Student *students, int numberStudents, int numberScholarships);
void CreateScholarshipList(Student *scholarships, Student *students, int numberStudents, int numberScholarships);
void Display(Student students[], int len, int scholarship);

///////////////////////////////////////////////////////////////////// MAIN

int main()
{
    int method, numberStudents, numberScholarships = 0;
	int spotsTaken = 0;
	int i = 0, j = 0, k = 0;

	Student *students;
	Student *scholarships;
	
    scanf("%d", &method);
    scanf("%d %d", &numberStudents, &numberScholarships);

    students = (Student*)malloc(numberStudents * sizeof(Student));

    for (i = 0; i < numberStudents; i++)
    {
        Student student;
		fflush(stdin);
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

	numberScholarships = SetScholarshipQuant(students, numberStudents, numberScholarships);
	scholarships = (Student*)malloc(numberScholarships * sizeof(Student));
	CreateScholarshipList(scholarships, students, numberStudents, numberScholarships);

	Display(scholarships, numberStudents, numberScholarships);
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

// Ordenação crescente:
// Menor a maior média
// Médias iguais -> maior a menor n° reprovações
// Reprovações iguais -> "maior" a "menor" letras
// É feito assim para depois vetor ser invertido
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
					if(students[p1].reprov == students[p2].reprov)				// Comparando reprovações
					{
						if(strcmp(students[p1].name, students[p2].name) < 0)	// Comparando nomes
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
				else if(students[p1].media > students[p2].media)				// COMPARANDO MEDIAS
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
				if(!flag1)                           	// Copia o restante de p1 caso p2 acabe
					temp[i] = students[p1++];
				else                                 	// Copia o restante de p2 caso p1 acabe
					temp[i] = students[p2++];
			} 
		}

		for(j = 0, k = inicio; j < size; j++, k++)     // Copia os dados do vetor auxiliar para o original
			students[k] = temp[j];
	}

	free(temp);
}

///////////////////////////////////////////////////////////////////// SELECTION SORT

// Mesmo sistema de ordenação do Merge Sort
void Selection_Sort(Student *students, int N)
{
	int i, j, menor;
	Student troca;

	for(i = 0; i < N-1; i++)
	{
		menor = i;
		for(j = i+1; j < N; j++)
		{
			if(students[j].media < students[menor].media)					// Menor é o que tem menor média
				menor = j;
			else if(students[j].media == students[menor].media)
			{
				if(students[j].reprov > students[menor].reprov)				// Menor é o que tem maior n° reprov
					menor = j;
				else if(students[j].reprov == students[menor].reprov)	
				{
					if(strcmp(students[j].name, students[menor].name) > 0)	// Menor é o que tiver "maior" letra
						menor = j;
				}
			}
		}

		if(i != menor)			// Faz a troca
		{
			troca = students[i];
			students[i] = students[menor];
			students[menor] = troca;
		}
	}
}

///////////////////////////////////////////////////////////////////// HELPERS

// Descobre quantas bolsas precisa
int SetScholarshipQuant(Student *students, int numberStudents, int numberScholarships)
{
	int spotTaken = 0;
	Student lastStudent;

	if(numberStudents < numberScholarships)		// Se não tiver alunos suficientes reduz número de bolsas
		return numberStudents;
	else
	{
		for (int k = numberStudents-1; k >= 0; k--)
		{
			if(students[k].reprov <= 10)
			{
				spotTaken++;
				if(spotTaken == numberScholarships) 		// Encontra último estudante dentro do limite de bolsas
					lastStudent = students[k];
				else if (spotTaken > numberScholarships)
				{
					if((students[k].media == lastStudent.media) && (students[k].reprov == lastStudent.reprov)) // Da mais bolsa
						numberScholarships++;
				}
			}
		}

		if(spotTaken < numberScholarships)		// Se não tiver pessoas o suficiente reduz número de bolsas
			numberScholarships = spotTaken;
	}
	
	return numberScholarships;
}

// Cria um vetor final com apenas os estudantes que conseguiram as bolsas
// Retira aqueles que foram reprovados
void CreateScholarshipList(Student *scholarships, Student *students, int numberStudents, int numberScholarships)
{
	int j = 0;
	for (int k = numberStudents-1; k >= 0; k--)
	{
		if(students[k].reprov <= 10)
		{
			scholarships[j] = students[k];
			j++;
		}

		if(j >= numberScholarships)
			break;
	}
}

void Display(Student students[], int len, int scholarship)
{
	printf("%d\n", scholarship);
    for (int i = 0; i < scholarship; i++)
		printf("%s\n", students[i].name);		
}