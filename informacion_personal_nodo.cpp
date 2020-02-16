
// Autor : Camilo Ledesma García-Ramos.
// NODO: INFORMACIÓN PERSONAL 
// Este nondo se encargará de solicitar al usuario por pantalla los siguientes datos: Nombre, edad, idiomas hablados.

//LIBRERÍAS
#include "ros/ros.h"
#include "interaccion/inf_personal_usuario.h"

using namespace std;

int main(int argc, char **argv)
{	
	cout << endl;


	ros::init(argc, argv, "informacion_personal_nodo"); //Se registra el nombre del nodo.
	ros::NodeHandle informacion_personal_nodo; //Se crea el objeto informacion_personal_nodo.
	ROS_INFO("informacion_personal_nodo creado y registrado"); //se muestra en la pantalla que ha sido creado y registrado.


	ros::Publisher publicadorMensajes = informacion_personal_nodo.advertise<interaccion::inf_personal_usuario> ("inf_pers_topic",0); //Se advierte del tipo de mensaje a enviar(inf_personal_usuario) y del nombre del topic que es inf_pers_topic

	ros::Duration seconds_sleep(1); //Se especifica el tiempo a dormir el nodo (se dormirá dentro del while).

	while (informacion_personal_nodo.ok())
	{
		//Se instancia el mensaje a enviar (mensajeInfoPersonal) y se publuca con publicadorMensajes
		interaccion::inf_personal_usuario mensajeInfoPersonal;
		int numIdiomas = 0;

		//Variables auxiliares que servirán para guardar los valores introducidos por pantalla antes de meterlos en la variable que vamos a enviar.
		string idioma_pantalla;
		int edad_aux = 0;

		cout << endl <<"#################### INFORMACIÓN PERSONAL ####################" << endl;
		//SE SOLICITA LA INFORMACION AL USUARIO POR PANTALLA Y SE RECOGE EN LAS VARIABLES CREADAS EN inf_personal_usuario.msg
		cout << "Introduzca su nombre: ";
		cin >> mensajeInfoPersonal.nombre;

		cout << "Introduzca su edad: ";
		cin >> edad_aux;
		mensajeInfoPersonal.edad = edad_aux;
		cin.ignore();		// Soluciona problemas de lectura.

		cout << "Introduzca el numero de idiomas que sabe: ";
		cin >> numIdiomas;
		cin.ignore();
		

		 for(int i = 0; i < numIdiomas; i++){
		 	cout << "Idioma " << i+1 << ": ";
		 	cin >> idioma_pantalla;
		 	mensajeInfoPersonal.idiomas.push_back(idioma_pantalla);			 
		 }
		
		//Se publica el mensaje:
		publicadorMensajes.publish(mensajeInfoPersonal);
		
		//Se duerme el nodo los segundos programados
		seconds_sleep.sleep();

	}
	return 0;
}