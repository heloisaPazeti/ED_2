#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define maxSize 100

typedef char name[maxSize];

void Merge(struct Student students[], int, int, int);
void Merge_Sort(struct Student students[], int inicio, int fim);

struct Student
{
    float media;
    int reprov;
    name name;
};

void display(struct Student students[], int len)
{
    for (int i = 0; i < len; i++) {
        printf("MEDIA : %.2f\n", students[i].media);
        printf("REPROVACOES : %d\n", students[i].reprov);
        printf("NOME : %s\n", students[i].name);
        printf("\n");
    }
}

int main()
{
    int method, numberStudents, numberScholarships = 0;

    scanf("%d", &method);
    scanf("%d %d", &numberStudents, &numberScholarships);

    struct Student students[numberStudents];

    for (int i = 0; i < numberStudents; i++)
    {
        struct Student student;
        scanf("%f %d %s", &student.media, &student.reprov, student.name);
        students[i] = student;
    }


    //display(students, numberStudents);
    Merge_Sort(students, 0, numberStudents);

    return 0;
}

void Merge_Sort(struct Student students[], int inicio, int fim)
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

void Merge(struct Student students[], int inicio, int meio, int fim)
{
	struct Students *temp;
	int i, j, k;
	int p1 = inicio, p2 = meio + 1;
	bool flag1 = false, flag2 = false;
	int size = fim - inicio + 1;

	temp = (struct Student*)malloc(size*sizeof(struct Student*));

	if(temp != NULL)
	{
		for(i = 0; i < size; i++)
		{
			if(!flag1 && !flag2)
			{
				// COMPARAR MÉDIAS
				if(students[p1].media == students[p2].media)
				{
					// COMPARAR REPROVAÇÕES
					if(students[p1].reprov == students[p2].reprov)
					{
						//AMBOS ENTRAM NA LISTA
					}
					else if (students[p1].reprov > students[p2].reprov)
					{
						//temp[i] = students[p2];
						p2++;
					}
					else
					{
						//temp[i] = students[p1];
						p1++;
					}	
				}
				else if(students[p1].media > students[p2].media)
				{
					//temp[i] = students[p2];
					p2++;
				}
				else
				{
					//temp[i] = students[p1];
					p1++;
				}


				if(p1 > meio)
					flag1 = true;
				else
					flag2 = true;
			}
			else
			{
				if(flag1)                           // Copia o restante de p1 caso p2 acabe
					//temp[i] = students[p1++];
				else                                // Copia o restante de p2 caso p1 acabe
					//temp[i]= students[p2++];
			} 
		}

		for(j = 0, k = inicio; j < size; j++, k++)     // Copia os dados do vetor auxiliar para o original
			//students[k]=temp[j];
	}

	free(temp);
}
