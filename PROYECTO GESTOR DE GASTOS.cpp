/*Programa: Gestor de Gastos
Autores; Juliana Sof�a L�pez Guerrero
		 Anggel Felipe Leal
		 Paula Isabella Mart�nez Escalante
*/

//A�ADIR LIBRERIAS

#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm> // Para std::sort
#include <iostream>
#include <windows.h>
#include <limits>
#include <iomanip>

using namespace std;

//DEFINIR LOS STRUCTS

struct Categoria {
    string codigoCat;
    string nombreCat;
    int iteracion;
};

struct Usuario {
    string nombres;
    string apellidos;
    string nickname;
    string correo;
    std::vector<Categoria> categorias;
};

struct Gasto {
    char nickname[15];
    char categoria[20];
    char descripcion[50];
    float monto;
    char fecha[11];
    int iteracion;
};

struct Ingreso {
    string descripcion;
    string fecha;
    int monto;
};

// FUNCION SPLIT PARA SEPARAR TEXTO A PARTIR DE ALGUN PARAMETRO
vector<string> split(const string &line, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(line);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Funci�n para convertir un entero a string
string intToString(int number) {
    // Creamos un objeto stringstream
    stringstream ss;
    // Insertamos el n�mero en el stringstream
    ss << number;
    // Retornamos el string resultante
    return ss.str();
}

struct Transaccion {
    string tipo; // "Gasto" o "Ingreso"
    string descripcion;
    int dia;
    int monto;
};

// Funci�n para comparar d�as
bool compararDias(const Transaccion &a, const Transaccion &b) {
    return a.dia < b.dia;
}
//DECLARAR LAS FUNCIONES QUE VAN A SER USADAS
int opcion, balance;
string currentUser; // Variable global para almacenar el usuario actual
int menuDeAcceso();
void menuInterno(string currentUser);
void registrarUsuario();
void login();
void opcMenuInt(string currentUser);
void anadirGasto(string nickname);
void anadirIngreso(string nickname);
void finPrograma();
void balanceTotal(string nickname);
void historial(string nickname);
void gastosPorCategoria(string nickname);
void ingresosMes(string nickname);
void setConsoleFont(const wchar_t* fontName, int fontSize);
bool esSoloLetras(const string& str);
bool esSoloNumeros(const string& str);
bool esAlfaNumerico(const string& str);
bool min_letras(const string& str);
bool esCorreoValido(const string& cadena);
void graficoDeBarras(string nickname);
void inicio();
bool nicknameExiste(const string& str);

//INICIAR LA FUNCI�N PRINCIPAL
int main() {
	
	//PERMITIR CARACTERES ESPECIALES
    setlocale(LC_ALL, "");
    //LLAMAR A LA FUNCI�N DE INICIO
	inicio();
	//LLAMAR A LA FUNCI�N DE MEN� DE ACCESO
    while (true) {
        menuDeAcceso();
    }
    return 0;
}
//CREAR EL INICIO, LA PRESENTACI�N DE LA APLICACI�N
void inicio(){
	cout<<""<<endl;
	cout<<"\t\t\t�������������� �������������� �������������� �������������� �������������� ����������������      ������������   ��������������\n"
		<<"\t\t\t�������������� �������������� �������������� �������������� �������������� ����������������      �������������� ��������������\n"
		<<"\t\t\t�������������� �������������� �������������� �������������� �������������� ����������������      �������������� ��������������\n"
		<<"\t\t\t������         ������         ������             ������     ������  ������ ������    ������      ������  ������ ������        \n"
		<<"\t\t\t������         �������������� ��������������     ������     ������  ������ ����������������      ������  ������ ��������������\n"
		<<"\t\t\t������  ������ �������������� ��������������     ������     ������  ������ ����������������      ������  ������ ��������������\n"
		<<"\t\t\t������  ������ ������                 ������     ������     ������  ������ ������  ������        ������  ������ ������        \n"
		<<"\t\t\t�������������� �������������� ��������������     ������     �������������� ������  ����������    �������������� ��������������\n"
		<<"\t\t\t�������������� �������������� ��������������     ������     �������������� ������  ����������    �������������� ��������������\n"
		<<"\t\t\t�������������� �������������� ��������������     ������     �������������� ������  ����������    ������������   ��������������\n\n"<<endl;
		
	cout<<"\t\t\t\t\t�������������� �������������� �������������� �������������� �������������� ��������������\n"
		<<"\t\t\t\t\t�������������� �������������� �������������� �������������� �������������� ��������������\n"
		<<"\t\t\t\t\t�������������� �������������� �������������� �������������� �������������� ��������������\n"
		<<"\t\t\t\t\t������         ������  ������ ������             ������     ������  ������ ������        \n"
		<<"\t\t\t\t\t������         ������  ������ ��������������     ������     ������  ������ ��������������\n"
		<<"\t\t\t\t\t������  ������ �������������� ��������������     ������     ������  ������ ��������������\n"
		<<"\t\t\t\t\t������  ������ ��������������         ������     ������     ������  ������         ������\n"
		<<"\t\t\t\t\t�������������� ������  ������ ��������������     ������     �������������� ��������������\n"
		<<"\t\t\t\t\t�������������� ������  ������ ��������������     ������     �������������� ��������������\n"
		<<"\t\t\t\t\t�������������� ������  ������ ��������������     ������     �������������� ��������������\n"<<endl;
	system ("color 0c");	
	cout<<"\t\t\t\t\t\t\t\t                  d888b               d8b    \n"
	    <<"\t\t\t\t\t\t\t\t                 d88888b             d888b   \n"
		<<"\t\t\t\t\t\t\t\t               d88888888b          d888888b  \n"
		<<"\t\t\t\t\t\t\t\t               d8888888b ------------  8888b \n"
		<<"\t\t\t\t\t\t\t\t       88       888P                  88888P\n"
		<<"\t\t\t\t\t\t\t\t      888    ,888                       8P,  \n"
		<<"\t\t\t\t\t\t\t\t    888    8888                         �8,  \n"
		<<"\t\t\t\t\t\t\t\t   88     8888       88888               �8, \n"
		<<"\t\t\t\t\t\t\t\t  888    d88888     8888888      88888    �8,\n"
		<<"\t\t\t\t\t\t\t\t 8888    8888888     888888     8888888   �8 \n"
		<<"\t\t\t\t\t\t\t\t 88888   8888888      888       888888   �8, \n"
		<<"\t\t\t\t\t\t\t\t 888888   88888I88               8888   �8,  \n"
		<<"\t\t\t\t\t\t\t\t 8888888   888I888888     88888        888,   \n"
		<<"\t\t\t\t\t\t\t\t  8888888   8888888888888  8888     8888888, \n"
		<<"\t\t\t\t\t\t\t\t   888888888 88888888888888 88 88888888888   \n"
		<<"\t\t\t\t\t\t\t\t   8888888888888888888888888888888Id888888   \n"
		<<"\t\t\t\t\t\t\t\t    888888888888888888888888888888888888b    \n"
		<<"\t\t\t\t\t\t\t\t     888888888 8888888888b    88888888888    \n"
		<<"\t\t\t\t\t\t\t\t      88888888  8888888888    8888888888    \n"
		<<"\t\t\t\t\t\t\t\t       8888888  8888888888     ad8888888     \n"
		<<"\t\t\t\t\t\t\t\t        888888b  888888888      8888888      \n"
		<<"\t\t\t\t\t\t\t\t                  88888888                   \n"<<endl;
	//LOS NOMBRES
	cout<<"\t\t\t\t\t\t\t\t  JULIANA L�PEZ --- ANGGEL LEAL --- PAULA MART�NEZ "<<endl;
	cout<<"\t\t\t\t\t\t\t\t\t-----PRESIONE ENTER PARA CONTINUAR-----"<<endl;
	cin.get();
	system("cls");
}
//SE CREA UNA FUNCI�N PARA MOSTRAR EL MEN� DE ACCESO
int menuDeAcceso() {
	//Declarar variables
    int opcion;
    //Cambiar el color de la letra
    system("color 0b");
    //Cambiar color de la letra
    setConsoleFont(L"Cascadia Code", 30);

        system("cls"); // Limpiar la consola
        cout << "\t\t\t      ===========================================\n";
        cout << "\t\t\t      ||               * MEN� *                ||\n";
        cout << "\t\t\t      ===========================================\n";
        cout << "\t\t\t      ||                                       ||\n";
        cout << "\t\t\t      ||              1- Registro              ||\n";
        cout << "\t\t\t      ||                                       ||\n";
        cout << "\t\t\t      ||              2- Ingresar              ||\n";
        cout << "\t\t\t      ||                                       ||\n";
        cout << "\t\t\t      ||          3- Salir del programa        ||\n";
        cout << "\t\t\t      ||                                       ||\n";
        cout << "\t\t\t      ||               Opci�n:                 ||\n";
        cout << "\t\t\t      ===========================================\n";
        cout << "\t\t\t\t\t\t  ";
	while (true) {
        
		cin >> opcion;
		//SE VALIDA QUE LA OPCI�N SEA SOLO N�MEROS
        if (cin.fail()) {
            cin.clear(); // LIMPIAR EL ERROR
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // DESCARTAR EL ERROR INGRESADO
            cout << "\t\t\t\t               ERROR              " << endl;
            cout << "\t\t\t\t    Digite un dato v�lido (1,2,3) " << endl;
            cout << "\t\t\t\t    Opci�n:";
        //VALIDAR QUE SOLO SEA UN N�MERO ENTERO ENTRE 1 Y 3
        } else if (opcion < 1 || opcion > 3) {
            cout << "\t\t\t\t               ERROR              " << endl;
            cout << "\t\t\t\t    Digite un dato v�lido (1,2,3) " << endl;
            cout << "\t\t\t\t    Opci�n:";
        //SI LOS DATOS INGRESADOS SON V�LIDOS EMPEZAR LA FUNCI�N SWITCH
        } else {
        	switch (opcion) {
            case 1:
            	//Llamar la funci�n para registrar usuario
                registrarUsuario();
                break;
            case 2:
            	//Llamar la funci�n del login
            	system("cls");
                login();
                break;
            case 3:
            	//Terminar Programa
                cout << "\n\t\t\t\t      **CERRANDO PROGRAMA\n";
                finPrograma();
                return 0;
            default:
                cout << "Opci�n no v�lida\n";
                break;
        	} 
        }
    }
}

// Funci�n para verificar si una cadena contiene solo letras v�lidas en espa�ol
bool esSoloLetras(const std::string& cadena) {
    for (size_t i = 0; i < cadena.length(); ++i) {
        if (isdigit(cadena[i])) {
            return false;
        }
    }
    return true;
}
//CREAR UNA FUNCI�N PARA VALIDAR QUE SEAN SOLO N�MEROS
bool esSoloNumeros(const string& str) {
    for (size_t i = 0; i < str.length(); ++i) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

//SE CREA UNA FUNCI�N PARA COMPROBAR QUE SEA ALFA N�MERICO
bool esAlfaNumerico(const string& str) {
    for (size_t i = 0; i < str.size(); ++i) {
    	//Comprobar que cada caracter sea un alfanumerico
        if (!isalnum(str[i])) {
            return false;
        }
    }
    return true;
}

//FUNCI�N PARA VERIFICAR QUE EL CORREO TENGA UN @ Y UN .
bool esCorreoValido(const string& cadena) {
    // Verifica si hay al menos un '@' y un '.' en la cadena
    size_t atPos = cadena.find('@');
    size_t dotPos = cadena.find('.');
    
    // @ y . deben estar presentes y @ debe estar antes de .
    return (atPos != string::npos) && (dotPos != string::npos) && (atPos < dotPos);
}

//SE CREA UNA FUNCI�N PARA COMPROBAR QUE TENGA EL M�NIMO DE LETRAS
bool min_letras(const string& str) {
    int num_let = 0;
    for (size_t i = 0; i < str.size(); ++i) {
    	//Cada que se revisa un caracter se a�ade 1 en num_let
        if (isalnum(str[i])) {
            ++num_let;
        }
    }
    return num_let >= 3;
}


//Se crea la funci�n para el Men� Interno
void menuInterno(string nickname) {
    currentUser = nickname; 
    // Almacenar el usuario actual en la variable global
    system("cls"); //Limpiar la Pantalla
    cout<<"\n"<<endl;
    cout<< "\t\t\t    ================================================="<<endl;
    cout<< "\t\t\t    ||                    MEN�                     ||"<<endl;
    cout<< "\t\t\t    ================================================="<<endl;
    printf("\t\t\t    ||               1-A�adir gastos               ||\n");
    printf("\t\t\t    ||              2-A�adir ingresos              ||\n");
    printf("\t\t\t    ||          3-Consultar balance total          ||\n");
    printf("\t\t\t    ||   4-Consultar historial de transacciones    ||\n");
    printf("\t\t\t    ||      5-Consultar gastos por categor�a       ||\n");
    printf("\t\t\t    ||        6-Consultar ingresos del mes         ||\n");
    printf("\t\t\t    || 7.Gr�fico de barras de gastos por categor�a ||\n");
    printf("\t\t\t    ||               8.Cerrar sesi�n               ||\n");
    cout<< "\t\t\t    ================================================="<<endl;
    opcMenuInt(currentUser);
}

//Se crea el men� de opciones del Men� Interno
void opcMenuInt(string nickname) {
    currentUser = nickname;
    int opcion;
    while (true) {
        cout << "\n\t\t\t\t\t    Opci�n: ";
        cin >> opcion;

        // Validar la opci�n
        if (cin.fail()) {
            cin.clear(); // Limpiar el error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar el input inv�lido
            cout << "\t\t\t\t               ERROR              " << endl;
            cout << "\t\t\t\t    Digite un dato v�lido (1-8) " << endl;
            continue; // Reiniciar el bucle
        } else if (opcion < 1 || opcion > 8) {
            cout << "\t\t\t\t               ERROR              " << endl;
            cout << "\t\t\t\t    Digite un dato v�lido (1-8) " << endl;
            continue; // Reiniciar el bucle
        } else {
            switch (opcion) {
                case 1:
                	cin.ignore();
                    anadirGasto(currentUser);
                    break;
                case 2:
                    anadirIngreso(currentUser);
                    break;
                case 3:
                    balanceTotal(currentUser);
                    break;
                case 4:
                    historial(currentUser);
                    break;
                case 5:
                    gastosPorCategoria(currentUser);
                    break;
                case 6:
                    ingresosMes(currentUser);
                    break;
                case 7:
                    graficoDeBarras(currentUser);
                    break;
                case 8:
                    menuDeAcceso();
                    return; // Salir del bucle y de la funci�n
                default:
                    cout << "\t\t\t\t               ERROR              " << endl;
                    cout << "\t\t\t\t    Digite un dato v�lido (1-8) " << endl;
                    break;
            }
        }
    }
}

//CREAR FUNCI�N PARA CAMBIAR LA FUENTE DEL TEXTO
void setConsoleFont(const wchar_t* fontName, int fontSize) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Obtener la configuraci�n actual de la consola
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(hConsole, FALSE, &cfi);

    // Configurar la nueva fuente
    wcsncpy(cfi.FaceName, fontName, LF_FACESIZE - 1);
    cfi.FaceName[LF_FACESIZE - 1] = L'\0'; // Asegurarse de que la cadena est� terminada en nulo
    cfi.dwFontSize.Y = fontSize;

    // Establecer la nueva configuraci�n de la consola
    SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
}
//FUNCI�N PARA REVISAR SI UN C�DIGO YA EXISTE
bool codigoYaExiste(const vector<string>& codigos, const string& codigo) {
    for (vector<string>::const_iterator it = codigos.begin(); it != codigos.end(); ++it) {
        const string& c = *it;
        if (c == codigo) {
            return true; // Si encuentra una coincidencia, devuelve true
        }
    }
    return false; // Si no encuentra ninguna coincidencia, devuelve false
}

//Crear la funci�n para registrar el usuario
void registrarUsuario() {
    // Cambiar la Fuente
    setConsoleFont(L"Cascadia Code", 30);
    ofstream fichero("usuarios.dat", ios::app);
    // Comprobar que haya fichero
    if (!fichero.is_open()) {
        cout << "ERROR, fichero no encontrado\n";
        cout << "Presione cualquier tecla para volver al men� anterior: ";
        getchar();
        menuDeAcceso();
        return;
    }

    // Definir las variables
    string nick, contrasena, email, nombre, apellido, categoria, codCategoria;
    Usuario usuario;
    Categoria categoriaEstruct;
    cout << "A continuaci�n se har� el proceso de registro." << endl << "\tPresione cualquier tecla para continuar:";
    getchar();
    system("cls"); // Limpiar la pantalla
    system("color 0e"); // Cambiar el color de la letra
    cout << "\t\t\t===========================================================\n";
    cout << "\t\t\t||                                                       ||\n"
            "\t\t\t||    ####   ####   ####  ###  ###  ##### ####   ####    ||\n"
            "\t\t\t||    #   #  ##    #       #  #       #   #   #  #  #    ||\n"
            "\t\t\t||    ####   ####  # ###   #   ###    #   ####   #  #    ||\n"
            "\t\t\t||    #  #   ##    #   #   #      #   #   #  #   #  #    ||\n"
            "\t\t\t||    #   #  ####   ###   ###  ###    #   #   #  ####    ||\n"
            "\t\t\t||                                                       ||\n";
    cout << "\t\t\t===========================================================\n" << endl;

    // Validar el nickname
    while (true) {
        cout << "\t\t\t-Digite su nickname: ";
        cin >> nick;
        if (nicknameExiste(nick)) {
            cout << "\t\t\tEl nombre de usuario ya existe. Por favor, elija otro." << endl;
        } else if (!esAlfaNumerico(nick)) {
            cout << "\t\t\tEl nombre de usuario no es v�lido. Debe ser alfanum�rico." << endl;
        } else if (!min_letras(nick)) {
            cout << "\t\t\tEl nombre de usuario no es v�lido. Debe contener al menos 3 letras." << endl;
        } else {
            break; // Salir del bucle si el nombre de usuario es v�lido
        }
    }
    usuario.nickname = nick;

    // Validar la contrase�a
    while (true) {
        cout << "\t\t\t-Digite su contrase�a: ";
        cin >> contrasena;
        if (!esAlfaNumerico(contrasena)) {
            cout << "\t\t\tLa contrase�a no es v�lida. Debe ser alfanum�rica." << endl;
        } else if (!min_letras(contrasena)) {
            cout << "\t\t\tLa contrase�a no es v�lida. Debe contener al menos 3 letras." << endl;
        } else {
            break; // Salir del bucle si la contrase�a es v�lida
        }
    }

    // Validar el correo
    while (true) {
        cout << "\t\t\t-Digite su email: ";
        cin >> email;
        if (!esCorreoValido(email)) {
            cout << "\t\t\tEl email no es v�lido. Debe al menos contener un '@' y un '.'" << endl;
        } else if (!min_letras(email)) {
            cout << "\t\t\tEl email no es v�lido. Debe contener al menos 3 letras." << endl;
        } else {
            break; // Salir del bucle si el email es v�lido
        }
    }
    usuario.correo = email;

    // Validar el nombre
    while (true) {
        cout << "\t\t\t-Digite su nombre: ";
        cin >> nombre;
        if (!esSoloLetras(nombre)) {
            cout << "\t\t\tEl nombre no es v�lido. Deben ser letras." << endl;
        } else if (!min_letras(nombre)) {
            cout << "\t\t\tEl nombre no es v�lido. Debe contener al menos 3 letras." << endl;
        } else {
            break; // Salir del bucle si el nombre es v�lido
        }
    }
    usuario.nombres = nombre;

    // Validar el apellido
    while (true) {
        cout << "\t\t\t-Digite su apellido: ";
        cin >> apellido;
        if (!esSoloLetras(apellido)) {
            cout << "\t\t\tEl apellido no es v�lido. Deben ser letras." << endl;
        } else if (!min_letras(apellido)) {
            cout << "\t\t\tEl apellido no es v�lido. Debe contener al menos 3 letras." << endl;
        } else {
            break; // Salir del bucle si el apellido es v�lido
        }
    }
    usuario.apellidos = apellido;

    fichero << usuario.nickname + ":" + contrasena + ":" + usuario.correo + ":" + usuario.nombres + ":" + usuario.apellidos + ":";

    system("cls");// Limpiar la Pantalla
    cout<<"\n\n\n\n\t\t\t _     _   _   _ _ _   _   _   _ _ _   _ _ _     __   _ _ _ \n"
       		   "\t\t\t|_|   | | | | |  _ _| | | | | |  _  | |  _  |   |  | |  _  | \n"
               "\t\t\t _    | | | | | |_ _  | | | | | |_| | | |_| |_  |  | | | | |\n" 
               "\t\t\t| |   | | | | |_ _  | | | | | |  _  | |  _ _  | |  | | | | |\n"   
               "\t\t\t| |   | |_| |  _ _| | | |_| | | | | | | |   | | |  | | |_| |\n"
               "\t\t\t|_|   |_ _ _| |_ _ _| |_ _ _| |_| |_| |_|   |_| |__| |_ _ _|\n"<<endl;
        cout<<"\t\t\t    _ _ _   _ _ _     _ _ _   _ _ _   _ _ _    _ _ _      _ \n" 
      		  "\t\t\t   |  _ _| |  _  |   |  _ _| |  _  | |  _  |  |  _  |    | |\n"
      		  "\t\t\t   | |     | |_| |_  | |_ _  | |_| | | | |  | | | | |    | |\n"
              "\t\t\t   | |     |  _ _  | |  _ _| |  _  | | | |  | | | | |    |_|\n"
              "\t\t\t   | |_ _  | |   | | | |_ _  | | | | | |_|  | | |_| |     _ \n"
              "\t\t\t   |_ _ _| |_|   |_| |_ _ _| |_| |_| |_ _ _|  |_ _ _|    |_|\n";
    cout << "\n\n\t\t\t\t     Presiona Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora cualquier entrada anterior
    cin.get(); // Espera a que el usuario presione Enter
    system("cls");

    cout << "\n\t\t**PARA TERMINAR SU REGISTRO, POR FAVOR DIGITE LAS CATEGORIAS DE GASTOS:\n";
    cout << "\t*Escriba 'FIN' como nombre de categor�a para salir de la funci�n y terminar el registro.\n";
    string finalizar = "";
    cout << "\t\t***************************************************************************" << endl;
        cout << "\t\t*  ,-----.          ,--.                              ,--.                *" << endl;
    	cout << "\t\t* '  .--./ ,--,--.,-'  '-. ,---.  ,---.  ,---. ,--.--.`--' ,--,--. ,---.  *" << endl;
    	cout << "\t\t* |  |    ' ,-.  |'-.  .-'| ."<<char(3)<<". :| .-. || .-. ||  .--',--.' ,-.  |(  .-'  *" << endl;
    	cout << "\t\t* '  '--'-| '-'  |  |  |  |   --.'_'-' |' '-' '|  |   |  || '-'  |.-'  `) *" << endl;
    	cout << "\t\t*  `-----' `--`--'  `--'   `----' _`-  / `---' `--'   `--' `--`--'`----'  *" << endl;
    	cout << "\t\t*                                 `---'                                   *" << endl;
    	cout << "\t\t***************************************************************************" << endl;
	
	while (true) {
		cin.ignore(); // Para ignorar el salto de l�nea previo
        cout << "\n\n\t\tPor favor escriba el nombre de la categor�a (o 'FIN' para terminar): ";
        getline(cin, categoria);
        if (categoria == "FIN") {
            break; // Salir del bucle y terminar el registro
        }
        if (!esSoloLetras(categoria)) {
            cout << "\t\tLa categor�a no es v�lida. Deben ser letras." << endl;
            continue; // Continuar al siguiente ciclo del bucle
        } else if (!min_letras(categoria)) {
            cout << "\t\tLa categor�a no es v�lida. Debe contener al menos 3 letras." << endl;
            continue; // Continuar al siguiente ciclo del bucle
        }
        categoriaEstruct.nombreCat = categoria;

        while (true) {
            cout << "\n\n\t\tPor favor escriba el c�digo de la categor�a: ";
            cin >> codCategoria;
            if (!esSoloNumeros(codCategoria)) {
                cout << "\t\tEl c�digo de la categor�a no es v�lido. Deben ser n�meros." << endl;
                continue; // Continuar al siguiente ciclo del bucle
            }
            // Comprobar que el c�digo de categor�a no est� duplicado
            bool codigoDuplicado = false;
            for (size_t i = 0; i < usuario.categorias.size(); ++i) {
                if (usuario.categorias[i].codigoCat == codCategoria) {
                    cout << "\t\tEl c�digo de categor�a ya existe. Debe ser �nico." << endl;
                    codigoDuplicado = true;
                    break; // Salir del bucle for
                }
            }
            if (codigoDuplicado) continue; // Continuar al siguiente ciclo del bucle externo si el c�digo est� duplicado

            break; // Salir del bucle si el c�digo de categor�a es v�lido y no est� duplicado
        }
        categoriaEstruct.codigoCat = codCategoria;

        usuario.categorias.push_back(categoriaEstruct);
    }

    for (size_t i = 0; i < usuario.categorias.size(); ++i) {
        fichero << usuario.categorias[i].codigoCat + ":" + usuario.categorias[i].nombreCat + ":";
    }
    fichero << endl;
    fichero.close();

    // Mensaje final de registro exitoso
    cout << "\n\t\tUsuario registrado con �xito." << endl;
    cout << "\t\tPresione cualquier tecla para volver al men� anterior: ";
    cin.get();
    menuDeAcceso();
}
	
void login() {
    ifstream fichero("usuarios.dat");
    if (!fichero.is_open()) {
        cout << "ERROR, fichero no encontrado\n";
        return; // Salir de la funci�n si el archivo no se pudo abrir
    }
    
    setConsoleFont(L"Cascadia Code", 30);
    system("color 0e");
    	cout << "\t\t\t\t*************************************\n";
    	cout << "\t\t\t\t* ,--.                 ,--.         *\n";
    	cout << "\t\t\t\t* |  |    ,---.  ,---. `--',--,--,  *\n";
    	cout << "\t\t\t\t* |  |   | .-. || .-. |,--.|      "<<char(92)<<" *\n";
    	cout << "\t\t\t\t* |  '--.' '-' ''_'-' ||  ||  ||  | *\n";
    	cout << "\t\t\t\t* `-----' `---' ._`-  /`--'`--''--' *\n";
    	cout << "\t\t\t\t*                `---'              *\n";
    	cout << "\t\t\t\t*************************************\n";

    while (true) {
        string lineaTexto;
        string nickname;
        string contrasena;
        cout << "\n\t\t\t\tDigite su nombre de usuario\n\t\t\t\t(Digite 'SALIR' para salir): ";
        cin >> nickname;
        if (nickname == "SALIR") {
                menuDeAcceso();// Salir del bucle y terminar el registro
        }
        cout << "\n\t\t\t\tDigite su contrase�a: ";
        cin >> contrasena;

        bool usuarioEncontrado = false;
        fichero.clear(); // Restablecer los indicadores de error del archivo
        fichero.seekg(0, ios::beg); // Volver al inicio del archivo

        while (getline(fichero, lineaTexto)) {
            vector<string> partes = split(lineaTexto, ':');

            if (lineaTexto.find(nickname + ":") == 0) {
                string contrasenaAux = partes[1];
                if (contrasena == contrasenaAux) {
                    cout << "\n\t\t\t\t\t  �Ingreso exitoso!\n";
                    cout << "\n\n\t\t\t\t Presiona Enter para continuar...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora cualquier entrada anterior
                    cin.get(); // Espera a que el usuario presione Enter
                    fichero.close();
                    usuarioEncontrado = true;
                    // Funci�n men� de ingreso
                    menuInterno(nickname);
                    return; // Salir de la funci�n despu�s de un ingreso exitoso
                }
            }
        }

        if (!usuarioEncontrado) {
            cout << "\n\n\t\t\t\tIngreso no v�lido, intente nuevamente\n";
        }
    }
}

void anadirGasto(string nickname) {
    currentUser = nickname;
    // Primero, lee las categor�as del usuario desde el archivo de usuarios
    ifstream ficheroUsuarios("usuarios.dat");

    if (!ficheroUsuarios.is_open()) {
        cout << "ERROR, fichero de usuarios no encontrado\n";
        return;
    }

    vector<Categoria> categoriasUsuario;
    string lineaTexto;
    bool usuarioEncontrado = false;

    while (getline(ficheroUsuarios, lineaTexto)) {
        vector<string> partes = split(lineaTexto, ':');
        if (partes[0] == nickname) {
            usuarioEncontrado = true;
            for (size_t i = 5; i + 1 < partes.size(); i += 2) {
                Categoria categoria;
                categoria.codigoCat = partes[i];
                categoria.nombreCat = partes[i + 1];
                categoriasUsuario.push_back(categoria);
            }
        }
    }
    
    ficheroUsuarios.close();

    // Verifica si el usuario tiene categor�as
    if (!usuarioEncontrado) {
        cout << "Usuario no encontrado.\n";
        return;
    }

    if (categoriasUsuario.empty()) {
        cout << "El usuario no tiene categor�as registradas.\n";
        return;
    }

    system("cls");
     cout <<" ,----.                   ,--.         \n"                                                                             
           "'  .-./    ,--,--. ,---.,-'  '-. ,---.  ,---.     .--.  \n" 
           "|  | .---.' ,-.  |(  .-''-.  .-'| .-. |(  .-'     '--'  \n" 
           "'  '--'  |' '-'  |.-'  `) |  |  ' '-' '.-'  `)    .--. \n" 
           " `------'  `--`--'`----'  `--'   `---' `----'     '--' \n";
    
    // Mostrar las categor�as disponibles
    cout << "Categor�as disponibles:\n";
    for (size_t i = 0; i < categoriasUsuario.size(); ++i) {
        cout << "\t" << categoriasUsuario[i].codigoCat << ": " << categoriasUsuario[i].nombreCat << "\n";
    }

    // Solicitar los detalles del gasto
    Gasto gasto;
    strncpy(gasto.nickname, nickname.c_str(), sizeof(gasto.nickname) - 1);
    gasto.nickname[sizeof(gasto.nickname) - 1] = '\0';

    bool categoriaValida = false;
    while (!categoriaValida) {
        cout << "Digite el c�digo de la categor�a del gasto: " << endl;
        cin.getline(gasto.categoria, sizeof(gasto.categoria));

        for (size_t i = 0; i < categoriasUsuario.size(); ++i) {
            if (categoriasUsuario[i].codigoCat == gasto.categoria) {
                categoriaValida = true;
                break;
            }
        }

        if (!categoriaValida) {
            cout << "Categor�a no v�lida. Por favor, intente de nuevo.\n";
        }
    }

    cout << "Digite la descripci�n del gasto: ";
    cin.getline(gasto.descripcion, sizeof(gasto.descripcion));

    // Validar el monto del gasto
    while (true) {
        cout << "Digite el monto del gasto: ";
        cin >> gasto.monto;

        if (cin.fail()) {
            cin.clear(); // Limpiar el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar la entrada incorrecta
            cout << "El monto no es v�lido. Debe ser un n�mero.\n";
        } else if (gasto.monto < 0) {
            cout << "El monto no puede ser negativo. Por favor, intente de nuevo.\n";
        } else {
            break;
        }
    }
    cin.ignore(); // Consumir el car�cter de nueva l�nea

    int dia;
    while (true) {
        cout << "Ingrese el d�a del monto (1-31): ";
        cin >> dia;

        // Validar la opci�n
        if (cin.fail() || dia < 1 || dia > 31) {
            cin.clear(); // Limpiar el error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar el input inv�lido
            cout << "ERROR: Digite un dato v�lido.\n";
        } else {
            sprintf(gasto.fecha, "%d", dia);
            break;
        }
    }

    // Guardar el gasto en el archivo
    ofstream ficheroGastos("gastos.dat", ios::app);
    if (!ficheroGastos.is_open()) {
        cout << "ERROR, fichero de gastos no encontrado\n";
        return;
    }
    ficheroGastos << gasto.nickname << ":" << gasto.categoria << ":" << gasto.descripcion << ":" << gasto.monto << ":" << gasto.fecha << "\n";
    ficheroGastos.close();

    cout << "Gasto a�adido exitosamente.\n";
    cout << "Digite 1 para agregar m�s gastos o 0 para salir: ";
    
    int opcion;
    cin >> opcion;
    if (opcion == 1) {
        cin.ignore();
        anadirGasto(currentUser);
    } else {
        system("cls");
        menuInterno(nickname);
    }
}

void anadirIngreso(string nickname){
    ofstream ficheroUsuarios("Ingresos.dat",ios::app);
    if (!ficheroUsuarios.is_open()) {
        cout << "ERROR, fichero de usuarios no encontrado\n";
        return;
    }
    else{   
    	system ("cls");
    	cout <<",--.                                                             \n"                                                                             
           	   "|  |,--,--,  ,---. ,--.--. ,---.  ,---.  ,---.  ,---.     .--.   \n" 
               "|  ||      || .-. ||  .--'| .-. :(  .-' | .-. |(  .-'     '--'  \n" 
               "|  ||  ||  |' '-' '|  |   |   --..-'  `)' '-' '.-'  `)    .--. \n" 
               "`--'`--''--'.`-  / `--'    `----'`----'  `---' `----'     '--'\n"
               "            `---'                                             \n";
        Ingreso datosIngreso;
        cout << "Ingrese la descripci�n de su ingreso:\n";
        cin.ignore();
        getline(cin, datosIngreso.descripcion);
        
        	//Validar el monto del gasto
		while (true) {
        	cout << "Ingrese el monto del ingreso:\n ";
        	cin >> datosIngreso.monto;

        	if (cin.fail()) {
           	cin.clear(); // Limpiar el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar la entrada incorrecta
            cout << "El monto no es v�lido. Debe ser un n�mero.\n";
        	} else if (datosIngreso.monto < 0){
				cout << "El monto no puede ser negativo. Por favor, intente de nuevo.\n";
        	} else {
           		break;
        	}
    	}
        
        int dia;
        while (true) {
    		cout << "Ingrese el d�a del ingreso (1-31)\n";
    		cin>>dia;
    		//Validar la opci�n
    		if (cin.fail()) {
        		cin.clear(); // Limpiar el error
        		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar el input inv�lido
        		cout << "ERROR, digite un dato v�lido. " << endl;
        		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Esperar a que el usuario de enter
        		continue; // Reiniciar el bucle
    		} 
    		//Validar si la opci�n es un n�mero entero entre 1 y 8
				else if (dia < 1 || dia > 31) {
        			cout << "ERROR, digite un dato v�lido" << endl;
            		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Esperar a que el usuario de enter
            		continue; // Reiniciar el bucle
        		} 
        			else{
        				datosIngreso.fecha = intToString(dia);
						break;	
					}	
	}
        // Convertir el d�a a string y almacenarlo en la estructura de datos
        datosIngreso.fecha = intToString(dia);

        ficheroUsuarios << nickname << ":" << datosIngreso.descripcion << ":" << datosIngreso.monto
        << ":" << datosIngreso.fecha << ":" << endl;  
        
        ficheroUsuarios.close();
        cout << "Ingreso a�adido exitosamente.\n";
        cout << "Digite 1 para agregar m�s ingresos o 0 para salir"<<endl;
        cin >> opcion;
        if (opcion == 1){
            anadirIngreso(nickname);
        }
        else{
            menuInterno(nickname);
        }
    
    }
}

void finPrograma(){
    exit(0);
}

void balanceTotal(string nickname) {
    currentUser = nickname;
    ifstream ficheroGastos("gastos.dat");
    ifstream ficheroIngresos("Ingresos.dat");
    if (!ficheroGastos.is_open()) {
        cout << "ERROR, fichero de gastos no encontrado\n";
        return;
    }
    if (!ficheroIngresos.is_open()) {
        cout << "ERROR, fichero de ingresos no encontrado\n";
        return;
    }
    float totalGastos = 0;
    float totalIngresos = 0;

    string lineaTexto; // Declarar lineaTexto aqu�

    // Leer y sumar los gastos
    while (getline(ficheroGastos, lineaTexto)) {
        vector<string> partes = split(lineaTexto, ':');
        if (partes[0] == currentUser) {
            int monto;
            sscanf(partes[3].c_str(), "%d", &monto); // Convertir cadena a entero
            totalGastos += monto;
        }
    }
    ficheroGastos.close();

    // Leer y sumar los ingresos
    while (getline(ficheroIngresos, lineaTexto)) {
        vector<string> partes = split(lineaTexto, ':');
        if (partes[0] == currentUser) {
            int monto;
            sscanf(partes[2].c_str(), "%d", &monto); // Convertir cadena a entero
            totalIngresos += monto;
        }
    }
    ficheroIngresos.close();
    system("cls");
cout<<" ___               _                                                _    \n" 
	      "| _ )    __ _     | |    __ _    _ _      __      ___      o O O   (_)   \n" 
		  "| _ "<<char(92)<<"   / _` |    | |   / _` |  | ' "<<char(92)<<"    / _|    / -_)    o         _    \n" 
		  "|___/   "<<char(92)<<"__,_|   _|_|_  "<<char(92)<<"__,_|  |_||_|   "<<char(92)<<"__|_   "<<char(92)<<"___|   TS__[O]  _(_)_  \n" 
		  "|=====|_|=====|_|=====|_|=====|_|=====|_|=====|_|=====| {======|_|=====| \n"
		   "`-0-0- `-0-0-' `-0-0-' `-0-0-' `-0-0-' `-0-0-' `-0-0-'./o--000' `-0-0-'  \n\n";   
	
    cout << "Balance total para el usuario " << currentUser << ":\n";
    cout << "Total de ingresos: " << totalIngresos << "\n";
    cout << "Total de gastos: " << totalGastos << "\n";
    cout << "Balance: " << totalIngresos - totalGastos << "\n"; // Corregido para mostrar el balance correcto
    cout << "\n\n\t\t\t\t Presiona Enter para continuar...";
    				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora cualquier entrada anterior
    				cin.get(); // Espera a que el usuario presione Enter
    menuInterno(nickname);
}

void historial(string nickname) {
    currentUser = nickname;
    ifstream ficheroGastos("gastos.dat");
    ifstream ficheroIngresos("Ingresos.dat");
    if (!ficheroGastos.is_open()) {
        cout << "ERROR, fichero de gastos no encontrado\n";
        return;
    }
    if (!ficheroIngresos.is_open()) {
        cout << "ERROR, fichero de ingresos no encontrado\n";
        return;
    }

    vector<Transaccion> historial;
    char lineaTexto[256];

    // Leer y almacenar los gastos
    while (ficheroGastos.getline(lineaTexto, sizeof(lineaTexto))) {
        vector<string> partes = split(lineaTexto, ':');
        if (partes[0] == currentUser) {
            Transaccion transaccion;
            transaccion.tipo = "Gasto";
            transaccion.descripcion = partes[2];
            sscanf(partes[4].c_str(), "%d", &transaccion.dia);
            sscanf(partes[3].c_str(), "%d", &transaccion.monto);
            historial.push_back(transaccion);
        }
    }
    ficheroGastos.close();

    // Leer y almacenar los ingresos
    while (ficheroIngresos.getline(lineaTexto, sizeof(lineaTexto))) {
        vector<string> partes = split(lineaTexto, ':');
        if (partes[0] == currentUser) {
            Transaccion transaccion;
            transaccion.tipo = "Ingreso";
            transaccion.descripcion = partes[1];
            sscanf(partes[3].c_str(), "%d", &transaccion.dia);
            sscanf(partes[2].c_str(), "%d", &transaccion.monto);
            historial.push_back(transaccion);
        }
    }
    ficheroIngresos.close();

    // Ordenar el historial por d�a
    sort(historial.begin(), historial.end(), compararDias);

    // Mostrar el historial ordenado
    system ("cls");
     cout <<",--.  ,--.,--.        ,--.                ,--.        ,--.         \n"                                                                             
           "|  '--'  |`--' ,---.,-'  '-. ,---. ,--.--.`--' ,--,--.|  |    .--. \n" 
           "|  .--.  |,--.(  .-''-.  .-'| .-. ||  .--',--.' ,-.  ||  |    '--' \n" 
           "|  |  |  ||  |.-'  `) |  |  ' '-' '|  |   |  |' '-'  ||  |    .--. \n" 
           "`--'  `--'`--'`----'  `--'   `---' `--'   `--' `--`--'`--'    '--' \n\n";
    cout << "Historial de transacciones para el usuario " << currentUser << ":\n";
    for (size_t i = 0; i < historial.size(); ++i) {
        cout << historial[i].tipo << " - " << historial[i].descripcion << " - " << historial[i].monto << " - D�a: " << historial[i].dia << "\n";
    }
    cout << "\n\n\t\t\t\t Presiona Enter para continuar...";
    				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora cualquier entrada anterior
    				cin.get(); // Espera a que el usuario presione Enter
    menuInterno(nickname);
}

void gastosPorCategoria(string nickname) {
    ifstream ficheroGastos("gastos.dat");
    if (!ficheroGastos.is_open()) {
        cout << "ERROR, fichero de gastos no encontrado\n";
        return;
    }

    ifstream ficheroUsuarios("usuarios.dat");
    if (!ficheroUsuarios.is_open()) {
        cout << "ERROR, fichero de usuarios no encontrado\n";
        return;
    }

    vector<Categoria> categoriasUsuario;
    string lineaTexto;
    bool usuarioEncontrado = false;

    // Leer las categor�as del usuario
    while (getline(ficheroUsuarios, lineaTexto)) {
        vector<string> partes = split(lineaTexto, ':');
        if (partes[0] == nickname) {
            usuarioEncontrado = true;
            for (size_t i = 5; i + 1 < partes.size(); i += 2) {
                Categoria categoria;
                categoria.codigoCat = partes[i];
                categoria.nombreCat = partes[i + 1];
                categoriasUsuario.push_back(categoria);
            }
        }
    }

    ficheroUsuarios.close();

    if (!usuarioEncontrado) {
        cout << "Usuario no encontrado.\n";
        return;
    }

    if (categoriasUsuario.empty()) {
        cout << "El usuario no tiene categor�as registradas.\n";
        return;
    }

    // Vector para almacenar los totales por categor�a
    vector<float> totalGastos(categoriasUsuario.size(), 0.0);

    // Leer y acumular los gastos por categor�a
    while (getline(ficheroGastos, lineaTexto)) {
        vector<string> partes = split(lineaTexto, ':');
        if (partes[0] == nickname) {
            string codigoCategoria = partes[1];
            float monto;
            if (sscanf(partes[3].c_str(), "%f", &monto) != 1) {
                cout << "Error: Datos no v�lidos en el archivo de gastos.\n";
                continue;
            }

            // Buscar la categor�a en el vector de categor�as
            for (size_t i = 0; i < categoriasUsuario.size(); ++i) {
                if (categoriasUsuario[i].codigoCat == codigoCategoria) {
                    totalGastos[i] += monto;
                    break;
                }
            }
        }
    }
    ficheroGastos.close();

    // Mostrar los gastos totales por categor�a
    system ("cls");
    cout <<" ,----.                   ,--.         \n"                                                                             
           "'  .-./    ,--,--. ,---.,-'  '-. ,---.  ,---.     .--.  \n" 
           "|  | .---.' ,-.  |(  .-''-.  .-'| .-. |(  .-'     '--'  \n" 
           "'  '--'  |' '-'  |.-'  `) |  |  ' '-' '.-'  `)    .--. \n" 
           " `------'  `--`--'`----'  `--'   `---' `----'     '--' \n";
    cout << "Gastos totales por categor�a para el usuario " << nickname << ":\n";
    for (size_t i = 0; i < categoriasUsuario.size(); ++i) {
        cout << categoriasUsuario[i].nombreCat << " (" << categoriasUsuario[i].codigoCat << "): " 
             << totalGastos[i] << "\n";
    }
	cout << "\n\n\t\t\t\t Presiona Enter para continuar...";
    				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora cualquier entrada anterior
    				cin.get(); // Espera a que el usuario presione Enter
    menuInterno(nickname);
}

void ingresosMes(string nickname) {
    ifstream ficheroIngresos("Ingresos.dat");
    if (!ficheroIngresos.is_open()) {
        cout << "ERROR, fichero de ingresos no encontrado\n";
        return;
    }

    string lineaTexto;
    vector<Ingreso> ingresosDelMes;

    while (getline(ficheroIngresos, lineaTexto)) {
        vector<string> partes = split(lineaTexto, ':');
        if (partes[0] == nickname) {
            Ingreso ingreso;
            ingreso.descripcion = partes[1];
            sscanf(partes[2].c_str(), "%d", &ingreso.monto); // Convertir string a entero
            ingreso.fecha = partes[3];
            ingresosDelMes.push_back(ingreso);
        }
    }

    ficheroIngresos.close();
    system ("cls");
cout <<",--.                                                             \n"                                                                             
           "|  |,--,--,  ,---. ,--.--. ,---.  ,---.  ,---.  ,---.     .--.   \n" 
           "|  ||      || .-. ||  .--'| .-. :(  .-' | .-. |(  .-'     '--'  \n" 
           "|  ||  ||  |' '-' '|  |   |   --..-'  `)' '-' '.-'  `)    .--. \n" 
           "`--'`--''--'.`-  / `--'    `----'`----'  `---' `----'     '--'\n"
           "            `---'                                             \n";
    cout << "Ingresos del mes para el usuario " << nickname << ":\n";
    for (size_t i = 0; i < ingresosDelMes.size(); ++i) {
        cout << "Descripci�n: " << ingresosDelMes[i].descripcion << ", Monto: " << ingresosDelMes[i].monto << ", Fecha: " << ingresosDelMes[i].fecha << "\n";
    }
	cout << "\n\n\t\t\t\t Presiona Enter para continuar...";
    				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora cualquier entrada anterior
    				cin.get(); // Espera a que el usuario presione Enter
    menuInterno(nickname);
}

void graficoDeBarras(string nickname) {
	system("cls");
	cout<<"****************************************************************************************\n";
	cout<<"*  ,---.       /  ,---.o                  |         |                                  *\n"                            
  		  "*  |  _.,---.,---.|__. .,---.,---.    ,---|,---.    |---.,---.,---.,---.,---.,---.  �  *\n"
          "*  |   ||    ,---||    ||    |   |    |   ||---'    |   |,---||    |    ,---|`---.     *\n"
          "*  `---'`    `---^`    ``---'`---'    `---'`---'    `---'`---^`    `    `---^`---'  �  *\n";
    cout<<"****************************************************************************************\n\n\n";
    cout<<"\n\n\n";
    ifstream ficheroGastos("gastos.dat");
    if (!ficheroGastos.is_open()) {
        cout << "ERROR, fichero de gastos no encontrado\n";
        return;
    }

    ifstream ficheroUsuarios("usuarios.dat");
    if (!ficheroUsuarios.is_open()) {
        cout << "ERROR, fichero de usuarios no encontrado\n";
        return;
    }

    vector<Categoria> categoriasUsuario;
    string lineaTexto;
    bool usuarioEncontrado = false;

    // Leer las categor�as del usuario
    while (getline(ficheroUsuarios, lineaTexto)) {
        vector<string> partes = split(lineaTexto, ':');
        if (partes[0] == nickname) {
            usuarioEncontrado = true;
            for (size_t i = 5; i + 1 < partes.size(); i += 2) {
                Categoria categoria;
                categoria.codigoCat = partes[i];
                categoria.nombreCat = partes[i + 1];
                categoriasUsuario.push_back(categoria);
            }
        }
    }

    ficheroUsuarios.close();

    if (!usuarioEncontrado) {
        cout << "Usuario no encontrado.\n";
        return;
    }

    if (categoriasUsuario.empty()) {
        cout << "El usuario no tiene categor�as registradas.\n";
        return;
    }

    // Vector para almacenar los totales por categor�a
    vector<float> totalGastos(categoriasUsuario.size(), 0.0);

    // Leer y acumular los gastos por categor�a
    while (getline(ficheroGastos, lineaTexto)) {
        vector<string> partes = split(lineaTexto, ':');
        if (partes[0] == nickname) {
            string codigoCategoria = partes[1];
            float monto;
            if (sscanf(partes[3].c_str(), "%f", &monto) != 1) {
                cout << "Error: Datos no v�lidos en el archivo de gastos.\n";
                continue;
            }

            // Buscar la categor�a en el vector de categor�as
            for (size_t i = 0; i < categoriasUsuario.size(); ++i) {
                if (categoriasUsuario[i].codigoCat == codigoCategoria) {
                    totalGastos[i] += monto;
                    break;
                }
            }
        }
    }
    ficheroGastos.close();

    // Encontrar el valor m�ximo de los gastos
    float maxGasto = *max_element(totalGastos.begin(), totalGastos.end());

    // Dibujar el gr�fico de barras
    for (size_t i = 0; i < categoriasUsuario.size(); ++i) {
        // Imprimir el nombre de la categor�a
        cout << setw(20) << left << categoriasUsuario[i].nombreCat << ": ";

        // Calcular la longitud de la barra proporcional al gasto
        int barLength = totalGastos[i] * 50 / maxGasto;

        // Dibujar la barra
        for (int j = 0; j < barLength; ++j) {
            cout << "*";
        }

        // Imprimir el valor num�rico asociado a la barra
        cout << " (" << totalGastos[i] << ")" << endl;
    }
    cout << "\n\n\t\t\t\t Presiona Enter para continuar...";
    				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora cualquier entrada anterior
    				cin.get(); // Espera a que el usuario presione Enter
    menuInterno(nickname);
	
}

// Funci�n para comprobar si el nickname ya existe en el archivo
bool nicknameExiste(const string& nickname) {
    ifstream fichero("usuarios.dat");
    if (!fichero.is_open()) {
        return false; // Si el archivo no existe, no hay duplicados
    }

    string linea;
    while (getline(fichero, linea)) {
        size_t pos = linea.find(':');
        if (pos != string::npos) {
            string nickRegistrado = linea.substr(0, pos);
            if (nickRegistrado == nickname) {
                return true; // Nickname encontrado en el archivo
            }
        }
    }
    return false; // Nickname no encontrado
}

