/*
* 
* Autor: Mauricio Farfan
* Registro: 20310033
* Grupo: 1P
* 
* PROYECTO GLOBAL PARA PROGRAMACIÓN ESTRUCTURADA
* 
*/

#include <stdio.h>

struct Animal
{
	int idAnimal;
	char name[23];
	char animalType[23];
	char habitat[23];
	int age;
};

int PrintMenu();
int	ConfirmExit();
int DeleteAnimal(struct Animal*, int, int);
int ModifyAnimal(struct Animal*, int, int);
int SearchAnimal(struct Animal*, int);
struct Animal NewAnimal(int);
void CheckAnimals(struct Animal*, int);
void OrderAnimalsByID(struct Animal*, int);
void PrintAnimal(struct Animal);
void InvalidInput();

int main()
{
	struct Animal animals[30], auxiliarAnimal;
	char optionMenu, confirmation = 0, name[20];
	int counter = 0, idCounter = 0, idAnimal = 0;
	// Se repite el código hasta que el usuario desee salir y haya confirmado que en realidad quiere hacerlo
	do 
	{
		// Se llama a la función que muestra el menú en pantalla y devuelve la opción que el usuario desea ejecutar.
		optionMenu = PrintMenu();
		// Se valida que haya ingresado una operación valida. De lo contrario se ofrece un mensaje de error.
		if ((optionMenu < 97 || optionMenu > 103) && (optionMenu < 65 || optionMenu > 71))
		{
			InvalidInput();
		}
		else
		{
			system("cls");
			// Se evalua la opción que el usuario haya ingresado. (Aceptando letras mayúsculas o minúsculas)
			switch (optionMenu)
			{
			case 97: case 65: //A - Agregar animal.
				// Solo es permitido agregar 30 animales máximo. De lo contrario se ofrece un mensaje de error.
				if (counter < 31)
				{
					printf("Ingrese los datos del nuevo animal:\n\n");
					// Se llama a la función que añade nuevo animal. El valor retornado se ingresa directamente al arreglo.
					// Se incrementan los contadores: ID y contador de animales.
					animals[counter] = NewAnimal(++idCounter);
					counter++;
					printf("\nRegistro introducido correctamente.\nPresiona ENTER para regresar al menu.\n");
					while (getchar() != '\n');
					system("cls");
				}
				else
				{
					printf("Ya se ha alcanzado el límite de animales permitidos.\nFavor de borrar algunos registros.\n\n");
				}
				break;


			case 98: case 66: //B - Eliminar animales
				// Validamos que existan animales.
				if (counter == 0)
				{
					printf("NO HAY REGISTROS PARA ELIMINAR");
				}
				else
				{
					// Pedimos el ID y ordenamos nuestro arreglo de acuerdo al ID correspondiente para cada animal.
					printf("Ingrese el ID del animal a eliminar:\n\n");
					scanf_s("%d", &idAnimal);
					while (getchar() != '\n');
					OrderAnimalsByID(animals, counter);
					// Llamamos a la función que elimina los animales, en caso de que nos regrese 1, sabemos que la operación ha sido correcta.
					// De lo contrario, ofrecemos un mensaje de error.
					if (DeleteAnimal(animals, idAnimal, counter) == 1)
					{
						printf("Operacion completada. El ID: %d ha sido eliminado.\n\n", idAnimal);
						counter--;
					}
					else
					{
						printf("ERROR. El ID: %d no esta registrado. No se ha eliminado nada.\n\n", idAnimal);
					}
				}
				printf("\nPresiona ENTER para regresar al menu.\n");
				while (getchar() != '\n');
				break;

			case 99: case 67: //C - Modificar animales
				//Validamos si tenemos animales registrados.
				if (counter == 0)
				{
					printf("NO HAY REGISTROS PARA MODIFICAR");
				}
				else
				{
					// Buscamos por ID al animal en un arreglo de animales ordenados por su identificador.
					printf("Ingrese el ID del animal a modificar:\n\n");
					scanf_s("%d", &idAnimal);
					while (getchar() != '\n');
					OrderAnimalsByID(animals, counter);
					// Llamamos a la función que se encarga de modificar los animales. EN caso de que se haya completado la operación
					// Ofrecemos un mensaje satisfactorio.
					if (ModifyAnimal(animals, idAnimal, counter) == 1)
						printf("Operacion completada. El ID: %d ha sido modificado.\n\n", idAnimal);
					else
						printf("ERROR. El ID: %d no esta registrado.\n\n", idAnimal);
				}
				printf("\nPresiona ENTER para regresar al menu.\n");
				while (getchar() != '\n');
				break;


			case 100: case 68: //D - Visualizar todos los registros
				// Validamos si tenemos registros almacenados.
				if (counter == 0)
				{
					printf("NO HAY REGISTROS PARA VISUALIZAR.");
				}
				else
				{
					// Ordenamos los animales por su ID y llamamos al procedimiento encargado de imprimir los registros de todos los animales.
					printf("Mostrando los registros almacenados:\n\n");
					OrderAnimalsByID(animals, counter);
					CheckAnimals(animals, counter);
				}
				printf("\nPresiona ENTER para regresar al menu.\n");
				while (getchar() != '\n');
				break;


			case 101: case 69: //E - Contador de animales
				// Imprimimos la cantidad existente de animales en el sistema.
				printf("Actualmente hay %d animales registrados.\n", counter);
				printf("\nPresiona ENTER para regresar al menu.\n");
				while (getchar() != '\n');
				break;


			case 102: case 70: //F - Buscador de animales por nombre
				// Validamos que tengamos registro de animales.
				if (counter == 0)
				{
					printf("NO HAY REGISTROS PARA BUSCAR");
				}
				else
				{
					// Llamamos a la función que busca al animal, en caso de encontrarlo lo muestra en pantalla, de lo contrario ofrece un mensaje de error.
					if (SearchAnimal(animals, counter) == 0)
						printf("\nError. No hay registro guardado con ese nombre.\n");
				}
				printf("\nPresiona ENTER para regresar al menu.\n");
				while (getchar() != '\n');
				break;


			case 103: case 71://G - Salir
				// Llamamos a la función que nos confirma si el usuario quiere salir realmente.
				confirmation = ConfirmExit();
				break;

			default: // Manejo de excepciones. 
				InvalidInput();
			}
		}
	} while (optionMenu != 103 || (confirmation != 98 && confirmation != 66));
	return 0;
}

/*
* Nombre:			PrintMenu
* Tipo de retorno:	int, caracter codificado en ascii que sirve para la evaluación del menú.
* Funcionalidad:	Mostrar el menú y permitir que el usuario ingrese la opción deseada
*/
int PrintMenu()
{
	system("cls");
	char optionMenu;
	printf("\n\nMENU DE OPCIONES\n\n");
	printf("[A]. Agregar animal.\n[B]. Eliminar animal.\n[C]. Modificar animal.\n[D]. Ver todos los animales registrados.\n");
	printf("[E]. Cantidad de animales registrados.\n[F]. Buscar animal por nombre.\n[G]. Salir.\n\n");
	scanf_s("%c", &optionMenu, 1);
	while (getchar() != '\n');
	return optionMenu;
}

/*
* Nombre:			ConfirmExit
* Tipo de retorno:	int, caracter codificado en ascii que sirve para la evaluación del menú de salida.
* Funcionalidad:	Confirmar que se desea salir del programa.
*/
int ConfirmExit()
{
	char optionMenu;
	printf("\n%cRealmente deseas salir?\nPERDERAS TODOS LOS REGISTROS GUARDADOS.\n\n", 168);
	printf("[A]. No, quiero regresar al menu.\n[B]. Si, quiero salir y perder todo.\n\n");
	scanf_s("%c", &optionMenu, 1);
	while (getchar() != '\n');
	return optionMenu;
}

/*
* Nombre:			NewAnimal
* Parámteros:		int id, id correspondiente al animal.
* Tipo de retorno:	struct Animal, devuelve los datos del animal formateados.
* Funcionalidad:	Ingresar un nuevo animal y validar que los campos se escribieron correctamente
*/
struct Animal NewAnimal(int id)
{
	int dataCorrectFormat = 0;
	struct Animal newAnimal;
	newAnimal.idAnimal = id;
	do
	{
		printf("\nNombre:");
		fgets(newAnimal.name, 22, stdin);
		if (strlen(newAnimal.name) < 21)
		{
			dataCorrectFormat = 1;
		}
		else
		{
			while (getchar() != '\n');
			printf("\nError. Demasiados caracteres. Favor de escribir nombre menor a 20 caracteres.\n");
		}
	} while (dataCorrectFormat != 1);
	dataCorrectFormat = 0;

	do
	{
		printf("Especie:");
		fgets(newAnimal.animalType, 22, stdin);
		if (strlen(newAnimal.animalType) < 21)
		{
			dataCorrectFormat = 1;
		}
		else
		{
			while (getchar() != '\n');
			printf("\nError. Demasiados caracteres. Favor de escribir especie a 20 caracteres.\n");
		}
	} while (dataCorrectFormat != 1);
	dataCorrectFormat = 0;

	do
	{
		printf("Habitat:");
		fgets(newAnimal.habitat, 22, stdin);
		if (strlen(newAnimal.habitat) < 21)
		{
			dataCorrectFormat = 1;
		}
		else
		{
			while (getchar() != '\n');
			printf("\nError. Demasiados caracteres. Favor de escribir habitat menor a 20 caracteres.\n");
		}
	} while (dataCorrectFormat != 1);	

	printf("Edad (a%cos):", 164);
	scanf_s("%d", &newAnimal.age);
	while (getchar() != '\n');

	return newAnimal;
}

/*
* Nombre:			CheckAnimals
* Parámetros:		struct Animal* animals, referencia al arreglo de animales donde se están almacenando los registros.
*					int quantity, cantidad de elementos existentes en ese punto.
* Funcionalidad:	Recorrer todo el arreglo para imprimir elemento por elemento.
*/
void CheckAnimals(struct Animal* animals, int quantity)
{
	for (int i = 0; i < quantity; i++)
		PrintAnimal(animals[i]);
}

/*
* Nombre:			DeleteAnimal
* Parámetros:		struct Animal* animals, referencia al arreglo de animales donde se están almacenando los registros.
*					int idAnimal, id del animal que se desea eliminar.
*					int quantity, cantidad de elementos existentes en ese punto.
* Tipo de retorno:	int, código identificador de la transacción 1 = éxito.
* Funcionalidad:	Eliminar un elemento del arreglo
*/
int DeleteAnimal(struct Animal* animals, int idAnimal, int quantity)
{
	struct Animal auxiliar;
	int position = 0, exists = 0;
	// Se busca la posición dentro del arreglo, se levantan banderas en caso de encontrarlos.
	for (int i = 0; i < quantity; i++)
	{
		if (animals[i].idAnimal == idAnimal)
		{
			position = i;
			exists = 1;
		}
	}
	// Si no existe retornamos con caso de error.
	if (exists == 0) return 0;
	// En caso de encontrarlo, recorremos todo el arreglo una posición antes iniciando de la posición donde se encuentra el elemento eliminado.
	for (int i = position; i <= quantity - position; i++)
	{
		// Llegando a la última posición retornamos el caso de éxito.
		if (i + 1 > quantity - 1)
			return 1;
		else
			animals[i] = animals[i+1];
	}
	return 1;
}

/*
* Nombre:			ModifyAnimal
* Parámetros:		struct Animal* animals, referencia al arreglo de animales donde se están almacenando los registros.
*					int idAnimal, id del animal que se desea eliminar.
*					int quantity, cantidad de elementos existentes en ese punto.
* Tipo de retorno:	int, código identificador de la transacción 1 = éxito.
* Funcionalidad:	Modificar un elemento del arreglo
*/
int ModifyAnimal(struct Animal* animals, int idAnimal, int quantity)
{
	int position = 0, exists = 0;
	// Buscamos el elemento en el arreglo.
	for (int i = 0; i < quantity; i++)
	{
		// En caso de encontrarlo levantamos banderas y almacenamos su posición
		if (animals[i].idAnimal == idAnimal)
		{
			position = i;
			exists = 1;
		}
	}
	// Si no existe, retornamos el código de transacción inválida.
	if (exists == 0) return 0;
	printf("\nActualiza todos los datos del animal:\n");
	// Llamamos al método para pedir todos los datos, conservamos el mismo ID que tenía el animal
	animals[position] = NewAnimal(idAnimal);
	return 1;
}

/*
* Nombre:			SearchAnimal
* Parámentros:		struct Animal* animals, referencia al arreglo de animales donde se están almacenando los registros.
*					int quantity, cantidad de elementos existentes en ese punto.
* Tipo de retorno:	int, código identificador de la transacción 1 = éxito.
* Funcionalidad:	Buscar un animal por su nombre.
*/
int SearchAnimal(struct Animal* animals, int quantity)
{
	char name[20];
	printf("Ingresa el nombre a buscar:\n\n");
	printf("\nNombre:");
	fgets(name, 20, stdin);
	if (strlen(name) > 21)
	{
		while (getchar() != '\n');
		return 0;
	}
	else
	{
		int position = 0, exists = 0;
		for (int i = 0; i < quantity; i++)
		{
			// Si lo encontramos dentro del arreglo levantamos banderas de éxito y guardamos su posición.
			if (strcmp(animals[i].name, name) == 0)
			{
				position = i;
				exists = 1;
			}
		}
		// En caso de que no exista regresamos el código de transacción inválida.
		if (exists == 0) return 0;
		printf("\nMostrando animal con nombre: %s\n", name);
		// Imprimimos los datos del animal encontrado.
		PrintAnimal(animals[position]);
		return 1;
	}
}

/*
* Nombre:			OrderAnimalsByID
* Parámetros:		struct Animal* animals, referencia al arreglo de animales donde se están almacenando los registros.
*					int quantity, cantidad de elementos existentes en ese punto.
* Funcionalidad:	Ordenar todos los elementos del arreglo de acuerdo con su ID.
*/
void OrderAnimalsByID(struct Animal* animals, int quantity)
{
	struct Animal auxiliar;
	for (int i = 0; i < quantity; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (animals[j].idAnimal > animals[i].idAnimal)
			{
				auxiliar = animals[i];
				animals[i] = animals[j];
				animals[j] = auxiliar;
			}
		}
	}
}

/*
* Nombre:			InvalidOutput
* Funcionalidad:	Ofrecer un mensaje de error cuando el usuario ha ingresado una opción incorrecta.
*/
void InvalidInput()
{
	printf("\nOPCION INVALIDA\n");
	printf("\nPresiona ENTER para regresar al menu.\n");
	while (getchar() != '\n');
}

/*
* Nombre:			PrintAnimal
* Parámetros:		struct Animal animals, referencia al arreglo del animal que se desea mostrar sus datos en pantalla.
* Funcionalidad:	Mostrar los datos del animal al usuario.
*/
void PrintAnimal(struct Animal animals)
{
	printf("IDAnimal:\t%d\n", animals.idAnimal);
	printf("Nombre:\t\t%s", animals.name);
	printf("Especie:\t%s", animals.animalType);
	printf("Habitat:\t%s", animals.habitat);
	printf("Edad:\t\t%d\n\n\n", animals.age);
}

